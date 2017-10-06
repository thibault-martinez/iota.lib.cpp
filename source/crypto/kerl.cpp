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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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

#include <algorithm>

#include <iota/constants.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/errors/crypto.hpp>

namespace IOTA {

namespace Crypto {

Kerl::Kerl() {
}

Kerl::~Kerl() {
}

void
Kerl::reset() {
  keccak_.reset();
}

void
Kerl::absorb(const Types::Trits& trits, unsigned int offset, unsigned int length) {
  if (length == 0)
    length = trits.size();
  if (length % TritHashLength != 0)
    throw Errors::Crypto("Kerl::absorb failed : illegal length");
  while (offset < length) {
    auto                end = std::min(offset + TritHashLength, length);
    std::vector<int8_t> tritsChunk(&trits[offset], &trits[end]);

    tritsChunk.back() = 0;
    auto bytesChunk   = Types::tritsToBytes(tritsChunk);

    keccak_.update(bytesChunk);
    offset += TritHashLength;
  }
}

void
Kerl::squeeze(Types::Trits& trits, unsigned int offset, unsigned int length) {
  if (length == 0)
    length = TritHashLength;
  if (length % TritHashLength != 0)
    throw Errors::Crypto("Kerl::squeeze failed : illegal length");
  while (offset < length) {
    auto bytes = keccak_.squeeze();
    trits      = Types::bytesToTrits(bytes);

    trits[TritHashLength - 1] = 0;
    std::transform(bytes.begin(), bytes.end(), bytes.begin(),
                   [](const int8_t& byte) { return byte ^ 0xFF; });
    keccak_.reset();
    keccak_.update(bytes);
    offset += TritHashLength;
  }
}

}  // namespace Crypto

}  // namespace IOTA
