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

#include "Trytes.hpp"
#include <algorithm>
#include "Trits.hpp"
#include "constants.hpp"

// static const int8_t tryteToTritsMappings[27][3] = {
//   { 0, 0, 0 },  { 1, 0, 0 },  { -1, 1, 0 },   { 0, 1, 0 },   { 1, 1, 0 },   { -1, -1, 1 },
//   { 0, -1, 1 }, { 1, -1, 1 }, { -1, 0, 1 },   { 0, 0, 1 },   { 1, 0, 1 },   { -1, 1, 1 },
//   { 0, 1, 1 },  { 1, 1, 1 },  { -1, -1, -1 }, { 0, -1, -1 }, { 1, -1, -1 }, { -1, 0, -1 },
//   { 0, 0, -1 }, { 1, 0, -1 }, { -1, 1, -1 },  { 0, 1, -1 },  { 1, 1, -1 },  { -1, -1, 0 },
//   { 0, -1, 0 }, { 1, -1, 0 }, { -1, 0, 0 },
// };

namespace IOTA {

namespace Type {

Trytes::Trytes(const std::string& values) : values_(values) {
}

Trytes::~Trytes() {
}

bool
Trytes::isValidTryte(const char& tryte) {
  return TryteAlphabet.find(tryte) != std::string::npos;
}

bool
Trytes::isValid() const {
  return std::find_if_not(std::begin(this->values_), std::end(this->values_),
                          Trytes::isValidTryte) == std::end(this->values_);
}

const std::string&
Trytes::string() const {
  return this->values_;
}

std::ostream&
operator<<(std::ostream& os, const Trytes& trytes) {
  os << trytes.string();
  return os;
}

}  // namespace Type

}  // namespace IOTA
