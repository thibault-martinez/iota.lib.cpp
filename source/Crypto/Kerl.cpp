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

#include "Kerl.hpp"
#include "BigInt.hpp"

// TODO offset and lenght

namespace IOTA {

namespace Crypto {

Kerl::Kerl() {
}

Kerl::~Kerl() {
}

void
Kerl::reset() {
  this->keccak_.reset();
}

void
Kerl::absorb(const Type::Trits& trits, unsigned int offset, unsigned int length) {
  // TODO Throw
  if (length == 0)
    length = trits.size();
  auto& values = trits.values();
  while (offset < length) {
    auto                end = std::min(offset + 243, length);
    std::vector<int8_t> chunk(&values[offset], &values[end - 1]);

    if (end - offset == 243)
      chunk[end - 1] = 0;
    Type::Trits cpy(chunk);
    BigInt      tmp(cpy);
    auto        bytes = tmp.toBytes();
    this->keccak_.update(bytes);
    offset += 243;
  }
}

void
Kerl::squeeze(Type::Trits& trits, unsigned int offset, unsigned int length) {
  // TODO Throw
  std::vector<int8_t> bytes(48);
  this->keccak_.squeeze(bytes);
  BigInt tmp(bytes);
  trits                   = tmp.toTrits();
  trits.values()[243 - 1] = 0;
  std::transform(bytes.begin(), bytes.end(), bytes.begin(),
                 [](const int8_t& byte) { return byte ^ 0xFF; });
  this->keccak_.reset();
  this->keccak_.update(bytes);
}

}  // namespace Crypto

}  // namespace IOTA
