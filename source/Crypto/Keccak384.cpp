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

// TODO check SUCCESS and FAIL returns and throws

#include "Keccak384.hpp"
#include <cstring>

namespace IOTA {

namespace Crypto {

Keccak384::Keccak384() {
  this->initialize();
}

Keccak384::~Keccak384() {
}

void
Keccak384::reset() {
  this->initialize();
}

void
Keccak384::update(const std::vector<uint8_t>& values) {
  Keccak_HashUpdate(&this->khi_, values.data(), values.size() * 8);
}

void
Keccak384::finalize(std::vector<uint8_t>& values) {
  Keccak_HashFinal(&this->khi_, values.data());
}

void
Keccak384::squeeze(std::vector<uint8_t>& values) {
  Keccak_HashSqueeze(&this->khi_, values.data(), this->khi_.fixedOutputLength);
}

void
Keccak384::initialize() {
  // TODO Constants ?
  Keccak_HashInitialize(&this->khi_, 832, 768, 384, 0x01);
}

}  // namespace Crypto

}  // namespace IOTA
