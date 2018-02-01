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

#include <iota/constants.hpp>
#include <iota/types/big_int.hpp>

namespace IOTA {

namespace Types {

BigInt::BigInt() : cpp_int(0) {
}

BigInt::BigInt(const int& value) : cpp_int(value) {
}

void
BigInt::fromTrits(const Types::Trits& trits) {
  assign(0);
  for (unsigned int i = 0; i < trits.size(); ++i) {
    *this += trits[i] * boost::multiprecision::pow(cpp_int(3), i);
  }
}

Types::Trits
BigInt::toTrits() const {
  Types::Trits trits;
  bool         is_negative = *this < 0;
  cpp_int      quotient    = boost::multiprecision::abs(*this);

  // TODO why TritHashLength ?
  for (unsigned int i = 0; i < TritHashLength; ++i) {
    cpp_int remainder;
    boost::multiprecision::divide_qr(quotient, cpp_int(3), quotient, remainder);
    if (remainder > 1) {
      quotient += 1;
      remainder -= 3;
    }
    trits.push_back(static_cast<int8_t>(is_negative ? (-1) * remainder : remainder));
  }
  return trits;
}

void
BigInt::fromBytes(const std::vector<int8_t>& bytes) {
  auto  bytesCopy = bytes;
  short sign      = (bytesCopy[0] >= 0 ? 1 : -1);

  if (sign == -1) {
    for (int i = bytes.size() - 1; i >= 0; --i) {
      int sub      = (bytesCopy[i] & 0xFF) - 1;
      bytesCopy[i] = (sub <= 0x7F ? sub : sub - 0x100);
      if (bytesCopy[i] != -1)
        break;
    }
    std::transform(bytesCopy.begin(), bytesCopy.end(), bytesCopy.begin(),
                   [](const int8_t& byte) { return ~byte; });
  }
  import_bits(*this, bytesCopy.begin(), bytesCopy.end(), 8, true);
  *this *= sign;
}

std::vector<int8_t>
BigInt::toBytes() const {
  std::vector<int8_t> exported_bytes;
  export_bits(*this, std::back_inserter(exported_bytes), 8, true);
  std::vector<int8_t> bytes(48 - exported_bytes.size(), 0);
  bytes.insert(bytes.end(), std::make_move_iterator(exported_bytes.begin()),
               std::make_move_iterator(exported_bytes.end()));
  if (*this < 0) {
    std::transform(bytes.begin(), bytes.end(), bytes.begin(),
                   [](const int8_t& byte) { return ~byte; });
    for (int i = ByteHashLength - 1; i >= 0; --i) {
      int add  = (bytes[i] & 0xFF) + 1;
      bytes[i] = (add <= 0x7F ? add : add - 0x100);
      if (bytes[i] != 0)
        break;
    }
  }
  return bytes;
}

}  // namespace Types

}  // namespace IOTA
