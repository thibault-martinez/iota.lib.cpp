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

#include <Crypto/Signing.hpp>
#include <Type/Trinary.hpp>
#include <constants.hpp>

namespace IOTA {

namespace Crypto {

Signing::Signing() {
}

Signing::~Signing() {
}

Type::Trits
Signing::key(const std::string& seed, const unsigned int& index, const unsigned int& security) {
  Type::Trits seedTrits = IOTA::Type::trytesToTrits(seed);

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

  Type::Trits keyTrits;
  Type::Trits trits;

  for (unsigned int i = 0; i < security; ++i) {
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      this->kerl_.squeeze(trits);
      keyTrits.insert(std::end(keyTrits), std::begin(trits), std::end(trits));
    }
  }
  return keyTrits;
}

// Type::Trits
// Signing::digest(const std::vector<int>& normalizedBundleFragment,
//                 const std::vector<int>& signatureFragment) {
//   this->kerl_.reset();
//   auto kerl = Kerl();
//
//   for (unsigned int i = 0; i < FragmentLength; ++i) {
//     std::vector<int8_t> buffer(&signatureFragment[i * TritHashLength],
//                                &signatureFragment[(i + 1) * TritHashLength]);
//     for (unsigned int j = normalizedBundleFragment[i] + 13; j > 0; --j) {
//       kerl.reset();
//       kerl.absorb(buffer);
//       kerl.squeeze(buffer);
//     }
//     this->kerl_.absorb(buffer);
//   }
//   Type::Trits trits;
//   this->kerl_.squeeze(buffer);
//   return buffer;
// }

Type::Trits
Signing::digests(const Type::Trits& key) {
  auto        numKeys = key.size() / (TritHashLength * FragmentLength);
  Type::Trits digests;

  for (unsigned int i = 0; i < numKeys; ++i) {
    Type::Trits keyFragment(&key[i * TritHashLength * FragmentLength],
                            &key[(i + 1) * TritHashLength * FragmentLength]);
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      Type::Trits buffer(&keyFragment[j * TritHashLength], &keyFragment[(j + 1) * TritHashLength]);
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
    Type::Trits buffer(TritHashLength);
    this->kerl_.squeeze(buffer);
    digests.insert(std::end(digests), std::begin(buffer), std::end(buffer));
  }
  return digests;
}

Type::Trits
Signing::address(const Type::Trits& digests) {
  Type::Trits addressTrits(TritHashLength);
  this->kerl_.reset();
  this->kerl_.absorb(digests);
  this->kerl_.squeeze(addressTrits);
  return addressTrits;
}

std::vector<int>
Signing::signatureFragment(const std::vector<int>& normalizedBundleFragment,
                           const std::vector<int>& keyFragment) {
}

void
Signing::validateSignatures(const std::string&              expectedAddress,
                            const std::vector<std::string>& signatureFragments,
                            const std::string&              bundleHash) {
}

}  // namespace Crypto

}  // namespace IOTA
