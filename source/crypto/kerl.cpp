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
#include <cstring>

#include <iota/constants.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/errors/crypto.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

void
Kerl::reset() {
  keccak_.reset();
}

void
Kerl::absorb(const Types::Trits& trits, std::size_t offset, std::size_t length) {
  if (length == 0)
    length = trits.size();
  if (length % TritHashLength != 0)
    throw Errors::Crypto("Kerl::absorb failed : illegal length");
  absorb(trits.data(), offset, length);
}

void
Kerl::squeeze(Types::Trits& trits, std::size_t offset, std::size_t length) {
  if (length == 0)
    length = TritHashLength;
  if (length % TritHashLength != 0)
    throw Errors::Crypto("Kerl::squeeze failed : illegal length");
  trits.resize(TritHashLength);
  squeeze(trits.data(), offset, length);
}

/**
 * Private methods
 */

void
Kerl::absorb(const int8_t* trits, std::size_t offset, std::size_t length) {
  int8_t              bytesChunk[ByteHashLength];
  std::vector<int8_t> cpy;
  cpy.assign(trits, trits + length);
  while (offset < length) {
    auto end = std::min(offset + TritHashLength, length);

    cpy[end - 1] = 0;
    Types::tritsToBytes(cpy.data() + offset, end - offset, bytesChunk);

    keccak_.absorb(bytesChunk, ByteHashLength);
    offset += TritHashLength;
  }
}

void
Kerl::squeeze(int8_t* trits, std::size_t offset, std::size_t length) {
  int8_t bytesChunk[ByteHashLength];
  while (offset < length) {
    keccak_.squeeze(bytesChunk);
    Types::bytesToTrits(bytesChunk, ByteHashLength, trits);

    trits[TritHashLength - 1] = 0;
    std::transform(bytesChunk, bytesChunk + ByteHashLength, bytesChunk,
                   [](const int8_t& byte) { return byte ^ 0xFF; });
    keccak_.reset();
    keccak_.absorb(bytesChunk, ByteHashLength);
    offset += TritHashLength;
  }
}

}  // namespace Crypto

}  // namespace IOTA
