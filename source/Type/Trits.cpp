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
#include "constants.hpp"
#include "utils.hpp"

namespace IOTA {

namespace Type {

// TODO Keep that ?
static std::vector<std::vector<int8_t>> trytesTrits = {
  { 0, 0, 0 },  { 1, 0, 0 },  { -1, 1, 0 },   { 0, 1, 0 },   { 1, 1, 0 },   { -1, -1, 1 },
  { 0, -1, 1 }, { 1, -1, 1 }, { -1, 0, 1 },   { 0, 0, 1 },   { 1, 0, 1 },   { -1, 1, 1 },
  { 0, 1, 1 },  { 1, 1, 1 },  { -1, -1, -1 }, { 0, -1, -1 }, { 1, -1, -1 }, { -1, 0, -1 },
  { 0, 0, -1 }, { 1, 0, -1 }, { -1, 1, -1 },  { 0, 1, -1 },  { 1, 1, -1 },  { -1, -1, 0 },
  { 0, -1, 0 }, { 1, -1, 0 }, { -1, 0, 0 }
};

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

Trits::Trits(const std::string& trytes) {
  for (unsigned i = 0; i < trytes.size(); i++) {
    unsigned int index = TryteAlphabet.find(trytes[i]);
    // TODO append vec to vec ?
    this->values_.push_back(trytesTrits[index][0]);
    this->values_.push_back(trytesTrits[index][1]);
    this->values_.push_back(trytesTrits[index][2]);
  }
}

Trits::~Trits() {
}

std::size_t
Trits::size() const {
  return this->values_.size();
}

std::vector<int8_t>&
Trits::values() {
  return this->values_;
}

const std::vector<int8_t>&
Trits::values() const {
  return this->values_;
}

std::vector<int8_t>
Trits::values(unsigned int length) const {
  return { this->values_.begin(),
           length < this->values_.size() ? this->values_.begin() + length : this->values_.end() };
}

std::vector<Trits>
Trits::chunks(unsigned int) const {
  std::vector<Trits> chunks;

  // size_t len = this->size() / length;
  // size_t rem = this->size() % length;
  //
  // size_t begin = 0;
  // size_t end   = 0;
  //
  // for (size_t i = 0; i < std::min(length, this->size()); ++i) {
  //   end += (rem > 0) ? (len + !!(rem--)) : len;
  //
  //   chunks.emplace_back(
  //       std::vector<int8_t>(std::begin(this->values_) + begin, std::begin(this->values_) + end));
  //
  //   begin = end;
  // }

  return chunks;
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

// Bigint
// Trits::toBigInt() const {
//   Bigint res = 0;
//   int    i   = this->values_.size() - 1;
//
//   while (i >= 0)
//     res = res * 3 + this->values_[i--];
//
//   return res;
// }

std::string
Trits::toTryteString(unsigned int length) const {
  std::string trytes;

  for (unsigned int i = 0; i < length; i += 3) {
    for (unsigned int j = 0; j < TryteAlphabet.size(); j++) {
      if (trytesTrits[j][0] == this->values_[i] && trytesTrits[j][1] == this->values_[i + 1] &&
          trytesTrits[j][2] == this->values_[i + 2]) {
        trytes += TryteAlphabet[j];
        break;
      }
    }
  }

  return trytes;
}

std::string
Trits::toTryteString() const {
  return toTryteString(this->size());
}

std::vector<int8_t>
Trits::toBytes() const {
  // TODO Constants !!!
  std::vector<int8_t> bytes((this->size() + 5 - 1) / 5);
  // byte[] bytes = new byte[(size + NumberOfTritsInAByte - 1) / NumberOfTritsInAByte];
  for (unsigned int i = 0; i < bytes.size(); ++i) {
    int value = 0;
    for (int j = (this->size() - i * 5) < 5 ? (this->size() - i * 5) : 5; j-- > 0;) {
      value = value * 3 + this->values_[i * 5 + j];
    }
    bytes[i] = (int8_t)value;
  }

  return bytes;
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
