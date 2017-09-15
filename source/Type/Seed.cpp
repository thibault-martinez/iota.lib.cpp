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

#include <Type/Seed.hpp>
#include <Type/Trytes.hpp>

namespace IOTA {

namespace Type {

Seed::Seed(const std::string& seed) : seed_(seed) {
}

Seed::~Seed() {
}

const std::string&
Seed::getRawSeed() const {
  return seed_;
}

bool
Seed::isValidSeed(const std::string& seed) {
  for (const auto& c : seed) {
    if (!Trytes::isValidTryte(c)) {
      return false;
    }
  }

  return true;
}

bool
Seed::isValid() const {
  return Seed::isValidSeed(seed_);
}

}  // namespace Type

}  // namespace IOTA
