//
// MIT License
//
// Copyright (c) 2017 Thibault Martinez
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <iota/constants.hpp>
#include <iota/crypto/signing.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

Signing::Signing() {
}

Signing::~Signing() {
}

Types::Trits
Signing::key(const Types::Trytes& seed, const unsigned int& index, const unsigned int& security) {
  Types::Trits seedTrits = IOTA::Types::trytesToTrits(seed);

  for (unsigned int i = 0; i < index; ++i) {
    for (unsigned int j = 0; j < TritHashLength; ++j) {
      if (++seedTrits[j] > 1) {
        seedTrits[j] = -1;
      } else {
        break;
      }
    }
  }

  this->kerl_.reset();
  this->kerl_.absorb(seedTrits);
  this->kerl_.squeeze(seedTrits);
  this->kerl_.reset();
  this->kerl_.absorb(seedTrits);

  Types::Trits keyTrits;
  Types::Trits trits;

  for (unsigned int i = 0; i < security; ++i) {
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      this->kerl_.squeeze(trits);
      keyTrits.insert(std::end(keyTrits), std::begin(trits), std::end(trits));
    }
  }
  return keyTrits;
}

Types::Trits
Signing::digest(const std::vector<int8_t>& normalizedBundleFragment,
                const Types::Trits&        signatureFragment) {
  this->kerl_.reset();
  Crypto::Kerl kerl;

  for (unsigned int i = 0; i < FragmentLength; i++) {
    Types::Trits buffer(&signatureFragment[i * TritHashLength],
                        &signatureFragment[(i + 1) * TritHashLength]);
    // TODO 13 ? Constant
    for (unsigned int j = normalizedBundleFragment[i] + 13; j-- > 0;) {
      kerl.reset();
      kerl.absorb(buffer);
      kerl.squeeze(buffer);
    }
    this->kerl_.absorb(buffer);
  }
  Types::Trits buffer(TritHashLength);
  this->kerl_.squeeze(buffer);
  return buffer;
}

Types::Trits
Signing::digests(const Types::Trits& key) {
  auto         numKeys = key.size() / (TritHashLength * FragmentLength);
  Types::Trits digests;

  for (unsigned int i = 0; i < numKeys; ++i) {
    Types::Trits keyFragment(&key[i * TritHashLength * FragmentLength],
                             &key[(i + 1) * TritHashLength * FragmentLength]);
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      Types::Trits buffer(&keyFragment[j * TritHashLength], &keyFragment[(j + 1) * TritHashLength]);
      for (unsigned int k = 0; k < FragmentLength - 1; ++k) {
        this->kerl_.reset();
        this->kerl_.absorb(buffer);
        this->kerl_.squeeze(buffer);
      }
      // TODO optimize
      for (unsigned int k = 0; k < 243; ++k) {
        keyFragment[j * 243 + k] = buffer[k];
      }
    }
    this->kerl_.reset();
    this->kerl_.absorb(keyFragment);
    Types::Trits buffer(TritHashLength);
    this->kerl_.squeeze(buffer);
    digests.insert(std::end(digests), std::begin(buffer), std::end(buffer));
  }
  return digests;
}

Types::Trits
Signing::address(const Types::Trits& digests) {
  Types::Trits addressTrits(TritHashLength);
  this->kerl_.reset();
  this->kerl_.absorb(digests);
  this->kerl_.squeeze(addressTrits);
  return addressTrits;
}

Types::Trits
Signing::signatureFragment(const std::vector<int8_t>& normalizedBundleFragment,
                           const Types::Trits&        keyFragment) {
  Types::Trits signatureFragment;

  for (unsigned int i = 0; i < FragmentLength; ++i) {
    Types::Trits buffer(&keyFragment[i * TritHashLength], &keyFragment[(i + 1) * TritHashLength]);
    // TODO 13 ? Constant
    for (int j = 0; j < 13 - normalizedBundleFragment[i]; ++j) {
      this->kerl_.reset();
      this->kerl_.absorb(buffer);
      this->kerl_.squeeze(buffer);
    }
    signatureFragment.insert(std::end(signatureFragment), std::begin(buffer), std::end(buffer));
  }

  return signatureFragment;
}

bool
Signing::validateSignatures(const Types::Trytes&              expectedAddress,
                            const std::vector<Types::Trytes>& signatureFragments,
                            const Types::Trytes&              bundleHash) {
  Models::Bundle                   bundle;
  auto                             normalizedBundleHash = bundle.normalizedBundle(bundleHash);
  std::vector<std::vector<int8_t>> normalizedBundleFragments;
  Types::Trits                     digests;

  for (unsigned int i = 0; i < 3; i++) {
    normalizedBundleFragments.emplace_back(&normalizedBundleHash[i * FragmentLength],
                                           &normalizedBundleHash[(i + 1) * FragmentLength]);
  }

  for (unsigned int i = 0; i < signatureFragments.size(); ++i) {
    auto digestBuffer = this->digest(normalizedBundleFragments[i % 3],
                                     IOTA::Types::trytesToTrits(signatureFragments[i]));

    digests.insert(std::end(digests), std::begin(digestBuffer), std::end(digestBuffer));
  }

  auto address = IOTA::Types::tritsToTrytes(this->address(digests));

  return address == expectedAddress;
}

}  // namespace Crypto

}  // namespace IOTA
