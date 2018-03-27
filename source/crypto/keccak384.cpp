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

#include <string>

#include <iota/crypto/keccak384.hpp>
#include <iota/errors/crypto.hpp>

namespace IOTA {

namespace Crypto {

Keccak384::Keccak384() {
  initialize();
}

void
Keccak384::reset() {
  initialize();
}

void
Keccak384::absorb(const uint8_t* bytes, size_t size) {
  if (!hashUpdate(bytes, size)) {
    throw Errors::Crypto("Keccak384::update failed");
  }
}

bool
Keccak384::hashUpdate(const uint8_t* bytes, size_t size) {
  return Keccak_HashUpdate(&khi_, reinterpret_cast<const BitSequence*>(bytes), size * 8) != FAIL;
}

void
Keccak384::squeeze(uint8_t* bytes) {
  if (!hashSqueeze(bytes)) {
    throw Errors::Crypto("Keccak384::squeeze failed");
  }
}

bool
Keccak384::hashSqueeze(uint8_t* bytes) {
  return Keccak_HashSqueeze(&khi_, reinterpret_cast<BitSequence*>(bytes), khi_.fixedOutputLength) !=
         FAIL;
}

void
Keccak384::initialize() {
  if (!hashInitialize()) {
    throw Errors::Crypto("Keccak384::initialize failed");
  }
}

bool
Keccak384::hashInitialize(void) {
  return Keccak_HashInitialize(&khi_, Keccak384::rate, Keccak384::capacity,
                               Keccak384::hashBitLength, Keccak384::delimitedSuffix) != FAIL;
}

}  // namespace Crypto

}  // namespace IOTA
