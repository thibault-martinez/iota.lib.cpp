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

#include <iostream>
#include <vector>
#include "KeccakHash.hpp"

namespace IOTA {

namespace Crypto {

class Keccak384 {
public:
  static const unsigned int rate            = 832;
  static const unsigned int capacity        = 768;
  static const unsigned int hashBitLength   = 384;
  static const unsigned int delimitedSuffix = 0x01;

public:
  Keccak384();
  virtual ~Keccak384();

public:
  void                reset();
  void                update(const std::vector<int8_t>& values);
  std::vector<int8_t> finalize();
  std::vector<int8_t> squeeze();
  std::string         digest();

private:
  void initialize();

private:
  Keccak_HashInstance khi_;
};

}  // namespace Crypto

}  // namespace IOTA
