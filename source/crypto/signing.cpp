//
// MIT License
//
// Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
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
#include <iota/crypto/kerl.hpp>
#include <iota/crypto/signing.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

namespace Signing {

Types::Trits
key(const Types::Trytes& seed, const unsigned int& index, const unsigned int& security) {
  Kerl         k;
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

  k.absorb(seedTrits);
  k.squeeze(seedTrits);
  k.reset();
  k.absorb(seedTrits);

  Types::Trits keyTrits;
  Types::Trits trits;

  for (unsigned int i = 0; i < security; ++i) {
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      k.squeeze(trits);
      keyTrits.insert(std::end(keyTrits), std::begin(trits), std::end(trits));
    }
  }
  return keyTrits;
}

Types::Trits
digest(const std::vector<int8_t>& normalizedBundleFragment, const Types::Trits& signatureFragment) {
  Kerl k1;
  Kerl k2;

  for (unsigned int i = 0; i < FragmentLength; i++) {
    Types::Trits buffer(&signatureFragment[i * TritHashLength],
                        &signatureFragment[(i + 1) * TritHashLength]);
    // TODO 13 ? Constant
    for (unsigned int j = normalizedBundleFragment[i] + 13; j-- > 0;) {
      k2.reset();
      k2.absorb(buffer);
      k2.squeeze(buffer);
    }
    k1.absorb(buffer);
  }
  Types::Trits buffer(TritHashLength);
  k1.squeeze(buffer);
  return buffer;
}

Types::Trits
digests(const Types::Trits& key) {
  Kerl         k;
  auto         numKeys = key.size() / (TritHashLength * FragmentLength);
  Types::Trits digests;

  for (unsigned int i = 0; i < numKeys; ++i) {
    Types::Trits keyFragment(key.begin() + (i * TritHashLength * FragmentLength),
                             key.begin() + ((i + 1) * TritHashLength * FragmentLength));
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      Types::Trits buffer(keyFragment.begin() + (j * TritHashLength),
                          keyFragment.begin() + ((j + 1) * TritHashLength));
      for (unsigned int l = 0; l < FragmentLength - 1; ++l) {
        k.reset();
        k.absorb(buffer);
        k.squeeze(buffer);
      }
      // TODO optimize
      for (unsigned int l = 0; l < 243; ++l) {
        keyFragment[j * 243 + l] = buffer[l];
      }
    }

    k.reset();
    k.absorb(keyFragment);
    Types::Trits buffer(TritHashLength);
    k.squeeze(buffer);
    digests.insert(std::end(digests), std::begin(buffer), std::end(buffer));
  }
  return digests;
}

Types::Trits
address(const Types::Trits& digests) {
  Kerl         k;
  Types::Trits addressTrits(TritHashLength);
  k.absorb(digests);
  k.squeeze(addressTrits);
  return addressTrits;
}

Types::Trits
signatureFragment(const std::vector<int8_t>& normalizedBundleFragment,
                  const Types::Trits&        keyFragment) {
  Kerl         k;
  Types::Trits signatureFragment;

  for (unsigned int i = 0; i < FragmentLength; ++i) {
    Types::Trits buffer(keyFragment.begin() + i * TritHashLength,
                        keyFragment.begin() + (i + 1) * TritHashLength);
    // TODO 13 ? Constant
    for (int j = 0; j < 13 - normalizedBundleFragment[i]; ++j) {
      k.reset();
      k.absorb(buffer);
      k.squeeze(buffer);
    }
    signatureFragment.insert(std::end(signatureFragment), std::begin(buffer), std::end(buffer));
  }

  return signatureFragment;
}

bool
validateSignatures(const Types::Trytes&              expectedAddr,
                   const std::vector<Types::Trytes>& signatureFragments,
                   const Types::Trytes&              bundleHash) {
  Models::Bundle                   bundle;
  auto                             normalizedBundleHash = bundle.normalizedBundle(bundleHash);
  std::vector<std::vector<int8_t>> normalizedBundleFragments;
  Types::Trits                     digests;

  for (unsigned int i = 0; i < 3; i++) {
    normalizedBundleFragments.emplace_back(normalizedBundleHash.begin() + i * FragmentLength,
                                           normalizedBundleHash.begin() + (i + 1) * FragmentLength);
  }

  for (unsigned int i = 0; i < signatureFragments.size(); ++i) {
    auto digestBuffer =
        digest(normalizedBundleFragments[i % 3], IOTA::Types::trytesToTrits(signatureFragments[i]));

    digests.insert(std::end(digests), std::begin(digestBuffer), std::end(digestBuffer));
  }

  auto addr = IOTA::Types::tritsToTrytes(address(digests));

  return addr == expectedAddr;
}

}  // namespace Signing

}  // namespace Crypto

}  // namespace IOTA
