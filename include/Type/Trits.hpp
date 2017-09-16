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

#include <cstdint>
#include <iostream>
#include <vector>
// #include "bigint.h"

// using namespace Dodecahedron;

namespace IOTA {
namespace Type {

// class Trytes;

class Trits {
public:
  explicit Trits(const std::vector<int8_t>& values);
  explicit Trits(const int& value);
  explicit Trits(const std::string& trytes);
  virtual ~Trits();

public:
  std::size_t                size() const;
  std::vector<int8_t>&       values();
  const std::vector<int8_t>& values() const;
  std::vector<int8_t>        values(unsigned int length) const;
  std::vector<Trits>         chunks(unsigned int length) const;

public:
  bool isValid() const;
  bool canTrytes() const;

public:
  template <typename T>
  T toInt() const {
    T res = 0;

    for (std::size_t i = this->values_.size() - 1; i-- > 0;) {
      res = res * 3 + this->values_[i];
    }

    return res;
  }

  // Bigint              toBigInt() const;
  std::string         toTryteString() const;
  std::string         toTryteString(unsigned int length) const;
  std::vector<int8_t> toBytes() const;

  // public:
  //   const int8_t& operator[](const int& i) const;
  //   int8_t&       operator[](const int& i);

private:
  std::vector<int8_t> values_;
};

bool operator==(const Trits& lhs, const Trits& rhs);
bool operator!=(const Trits& lhs, const Trits& rhs);
// Trytes tritsToTrytes(const Trits& trits);

}  // namespace Type

}  // namespace IOTA
