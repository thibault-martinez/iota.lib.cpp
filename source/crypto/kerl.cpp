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

#include <iota/constants.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/errors/crypto.hpp>
#include <iota/types/big_int.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

void
Kerl::reset() {
  keccak_.reset();
}

void
Kerl::absorb(const std::vector<uint8_t>& bytes, std::size_t offset, std::size_t length) {
  if (length == 0)
    length = bytes.size();
  if (length % ByteHashLength != 0)
    throw Errors::Crypto("Kerl::absorb failed : illegal length");
  while (length > 0) {
    keccak_.absorb(bytes.data() + offset, ByteHashLength);
    offset += ByteHashLength;
    length -= ByteHashLength;
  }
}

void
Kerl::squeeze(std::vector<uint8_t>& bytes, std::size_t offset) {
  uint8_t state[ByteHashLength];
  keccak_.squeeze(bytes.data() + offset);
  std::memcpy(state, bytes.data() + offset, ByteHashLength);
  Types::Bigint b;  // TODO(bigint class or namespace ?)
  b.fromBytes(bytes, offset);
  b.setLastTritZero();
  b.toBytes(bytes, offset);
  std::transform(std::begin(state), std::end(state), std::begin(state),
                 [](const int8_t& byte) { return byte ^ 0xFF; });
  keccak_.reset();
  keccak_.absorb(state);
}

void
Kerl::finalSqueeze(std::vector<uint8_t>& bytes, std::size_t offset) {
  keccak_.squeeze(bytes.data() + offset);
  Types::Bigint b;  // TODO(bigint class or namespace ?)
  b.fromBytes(bytes, offset);
  b.setLastTritZero();
  b.toBytes(bytes, offset);
}

}  // namespace Crypto

}  // namespace IOTA
