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

#include "BigInt.hpp"

namespace IOTA {

namespace Crypto {

BigInt::BigInt(const int& value) : cpp_int(value) {
}

BigInt::BigInt(const cpp_int& value) : cpp_int(value) {
}

BigInt::BigInt(const std::vector<int8_t>& bytes) : cpp_int(0) {
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

BigInt::BigInt(const IOTA::Type::Trits& trits) : cpp_int(0) {
  // TODO operator []
  // for (int i = trits.size() - 1; i >= 0; --i) {
  for (unsigned int i = 0; i < trits.size(); ++i) {
    // std::cout << i << '\n';
    *this += trits.values()[i] * boost::multiprecision::pow(cpp_int(3), i);
    // *this *= 3;
    // *this += trits.values()[i];
  }
}  // namespace Crypto

// SEEMS OK
std::vector<int8_t>
BigInt::toBytes() const {
  std::vector<int8_t> exported_bytes;
  export_bits(*this, std::back_inserter(exported_bytes), 8, true);
  std::vector<int8_t> bytes(48 - exported_bytes.size(), 0);
  bytes.insert(bytes.end(), std::make_move_iterator(exported_bytes.begin()),
               std::make_move_iterator(exported_bytes.end()));
  // wat ????? Might be useless (keep it a while)
  // std::transform(bytes.begin(), bytes.end(), bytes.begin(),
  //                [](const int8_t& byte) { return (byte <= 0x7F ? byte : byte - 0x100); });

  if (*this < 0) {
    std::transform(bytes.begin(), bytes.end(), bytes.begin(),
                   [](const int8_t& byte) { return ~byte; });
    // TODO 47 ???
    for (int i = 47; i >= 0; --i) {
      int add  = (bytes[i] & 0xFF) + 1;
      bytes[i] = (add <= 0x7F ? add : add - 0x100);
      if (bytes[i] != 0)
        break;
    }
  }
  return bytes;
}

Type::Trits
BigInt::toTrits() const {
  std::vector<int8_t> trits;
  bool                is_negative = *this < 0;
  cpp_int             quotient    = boost::multiprecision::abs(*this);

  for (unsigned int i = 0; i < 243; ++i) {
    cpp_int remainder;
    boost::multiprecision::divide_qr(quotient, cpp_int(3), quotient, remainder);
    if (remainder > 1) {
      quotient += 1;
      remainder -= 3;
    }
    trits.push_back(static_cast<int8_t>(is_negative ? (-1) * remainder : remainder));
  }
  return Type::Trits(trits);
}

}  // namespace Crypto

}  // namespace IOTA
