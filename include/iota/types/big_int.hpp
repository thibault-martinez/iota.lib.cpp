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

#pragma once

#include <iota/constants.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Types {

class Bigint {
public:
  Bigint();
  virtual ~Bigint();

public:
  void fromTrits(const Trits &trits);
  void fromBytes(const std::vector<int8_t> &bytes);

public:
  Trits               toTrits();
  std::vector<int8_t> toBytes() const;

private:
  bool         is_negative() const;
  uint32_t     mul(uint8_t factor, unsigned int ms_index);
  uint32_t     div(uint8_t divisor);
  bool         add(const uint32_t *a, const uint32_t *b);
  bool         sub(const uint32_t *a, const uint32_t *b);
  unsigned int add_u32(uint32_t summand);
  int          cmp(const uint32_t *b) const;
  bool         set_last_trit_zero();

private:
  uint32_t data[WordHashLength];
};

}  // namespace Types

}  // namespace IOTA
