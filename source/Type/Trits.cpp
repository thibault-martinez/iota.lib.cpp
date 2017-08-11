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

#include "Trits.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
// #include "Trytes.hpp"
// #include "constants.hpp"
#include "utils.hpp"

namespace IOTA {

namespace Type {

Trits::Trits(const std::vector<int8_t>& values) : values_(values) {
  if (this->isValid() == false)
    throw std::exception();
}

Trits::Trits(const int& value) {
  unsigned int absoluteValue = std::abs(value);

  while (absoluteValue > 0) {
    int8_t remainder = absoluteValue % 3;
    absoluteValue    = absoluteValue / 3;

    if (remainder > 1) {
      remainder = -1;
      absoluteValue++;
    }

    values_.push_back(remainder);
  }
  if (value < 0) {
    std::transform(std::begin(this->values_), std::end(this->values_), std::begin(this->values_),
                   std::negate<int>());
  }
}

Trits::~Trits() {
}

std::size_t
Trits::size() const {
  return this->values_.size();
}

const std::vector<int8_t>&
Trits::values() const {
  return this->values_;
}

bool
Trits::isValid() const {
  return std::find_if_not(std::begin(this->values_), std::end(this->values_), Utils::isValidTrit) ==
         std::end(this->values_);
}

bool
Trits::canTrytes() const {
  return this->values_.size() % 3 == 0;
}

int
Trits::toInt() const {
  int res = 0;
  int i   = this->values_.size() - 1;

  while (i >= 0)
    res = res * 3 + this->values_[i++];

  return res;
}

//
// const int8_t& Trits::operator[](const int& i) const {
//   return this->values_.at(i);
// }
//
// int8_t& Trits::operator[](const int& i) {
//   return this->values_.at(i);
// }
//

bool
operator==(const Trits& lhs, const Trits& rhs) {
  return lhs.values() == rhs.values();
}

bool
operator!=(const Trits& lhs, const Trits& rhs) {
  return lhs.values() != rhs.values();
}

// Trytes
// tritsToTrytes(const Trits& trits) {
//   // if !t.CanTrytes() {
//   // panic("length of trits must be x3.")
//   // }
//   // o = make([] byte, len(t) / 3);
//   std::string o;
//   for (size_t i = 0; i < trits.size() / 3; ++i) {
//     int8_t j = trits[i * 3] + trits[i * 3 + 1] * 3 + trits[i * 3 + 2] * 9;
//     if (j < 0) {
//       j += static_cast<int8_t>(TryteAlphabet.size());
//     }
//     std::cout << (int)j << '\n';
//     o += TryteAlphabet[j];
//   }
//   std::cout << o << '\n';
//   return Trytes(o);
// }

}  // namespace Type

}  // namespace IOTA
