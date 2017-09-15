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

#include <Crypto/Kerl.hpp>
#include <Crypto/Signing.hpp>
#include <Type/Trits.hpp>
#include <constants.hpp>

namespace IOTA {

namespace Crypto {

Signing::Signing() {
}

Signing::~Signing() {
}

Type::Trits
Signing::key(const std::string& seed, const unsigned int& index, const unsigned int& security) {
  Type::Trits trits(seed);

  for (unsigned int i = 0; i < index; ++i) {
    for (unsigned int j = 0; j < TritHashLength; ++j) {
      // TODO operator[]
      if (++trits.values()[j] > 1) {
        trits.values()[j] = -1;
      } else {
        break;
      }
    }
  }

  this->kerl_.reset();
  this->kerl_.absorb(trits);
  this->kerl_.squeeze(trits);
  this->kerl_.reset();
  this->kerl_.absorb(trits);

  std::vector<int8_t> keyTrits;
  std::vector<int8_t> bytes(TritHashLength);
  Type::Trits         bytesTrits(bytes);

  for (unsigned int i = 0; i < security; ++i) {
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      this->kerl_.squeeze(bytesTrits);
      keyTrits.insert(std::end(keyTrits), std::begin(bytesTrits.values()),
                      std::end(bytesTrits.values()));
    }
  }
  return Type::Trits(keyTrits);
}

std::vector<int>
Signing::digest(const std::vector<int>& normalizedBundleFragment,
                const std::vector<int>& signatureFragment) {
}

std::vector<int>
Signing::digests(const std::vector<int>& key) {
}

std::vector<int>
Signing::address(const std::vector<int>& digests) {
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
