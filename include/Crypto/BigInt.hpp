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

#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include "Trits.hpp"

using boost::multiprecision::cpp_int;

namespace IOTA {

namespace Crypto {

class BigInt : public cpp_int {
public:
  BigInt(const int& value);
  BigInt(const cpp_int& value);
  BigInt(const std::vector<int8_t>& bytes);
  BigInt(const IOTA::Type::Trits& trits);

public:
  std::vector<int8_t> toBytes() const;
  Type::Trits         toTrits() const;
};

// TODO not sure to keep them, only test purpose.
inline bool
operator!=(const BigInt& lhs, const BigInt& rhs) {
  return static_cast<const cpp_int&>(lhs) != static_cast<const cpp_int&>(rhs);
}

inline bool
operator==(const BigInt& lhs, const BigInt& rhs) {
  return static_cast<const cpp_int&>(lhs) == static_cast<const cpp_int&>(rhs);
}

}  // namespace Crypto

}  // namespace IOTA
