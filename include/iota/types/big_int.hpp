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
  /**
   * Default ctor.
   */
  Bigint();
  /**
   * Default dtor.
   */
  virtual ~Bigint();

public:
  /**
   * Initialize bigint from trits.
   *
   * @trits The trits.
   */
  void fromTrits(const Trits &trits, std::size_t offset = 0);
  /**
   * Initialize bigint from bytes.
   *
   * @bytes The bytes.
   */
  void fromBytes(const std::vector<uint8_t> &bytes, std::size_t offset = 0);

public:
  /**
   * Convert bigint to trits.
   *
   * @return The trits.
   */
  Trits toTrits();
  /**
   * Convert bigint to bytes.
   *
   * @return The bytes.
   */
  void toBytes(std::vector<uint8_t> &bytes, std::size_t offset = 0) const;

public:  // TODO(Bigint class or namespace ?)
  bool         setLastTritZero();
  unsigned int addU32(uint32_t summand);

private:
  inline bool     isNegative() const;
  inline uint32_t mul(uint8_t factor, unsigned int ms_index);
  inline uint32_t div(uint8_t divisor);
  inline bool     add(const uint32_t *a, const uint32_t *b);
  inline bool     sub(const uint32_t *a, const uint32_t *b);
  inline bool     addcarryU32(uint32_t *r, uint32_t a, uint32_t b, bool c_in);
  inline int      cmp(const uint32_t *b) const;

private:
  uint32_t data[WordHashLength];
};

}  // namespace Types

}  // namespace IOTA
