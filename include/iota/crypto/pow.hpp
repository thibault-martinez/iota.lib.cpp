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

#include <mutex>

#include <iota/constants.hpp>
#include <iota/crypto/i_pow.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

class Pow : public IPow {
private:
  static constexpr uint64_t hBits = 0xFFFFFFFFFFFFFFFF;
  static constexpr uint64_t lBits = 0x0000000000000000;

  static constexpr uint64_t low0  = 0xDB6DB6DB6DB6DB6D;
  static constexpr uint64_t high0 = 0xB6DB6DB6DB6DB6DB;
  static constexpr uint64_t low1  = 0xF1F8FC7E3F1F8FC7;
  static constexpr uint64_t high1 = 0x8FC7E3F1F8FC7E3F;
  static constexpr uint64_t low2  = 0x7FFFE00FFFFC01FF;
  static constexpr uint64_t high2 = 0xFFC01FFFF803FFFF;
  static constexpr uint64_t low3  = 0xFFC0000007FFFFFF;
  static constexpr uint64_t high3 = 0x003FFFFFFFFFFFFF;

  static constexpr uint64_t nonceOffset         = TritHashLength - NonceLength;
  static constexpr uint64_t nonceInitStart      = nonceOffset + 4;
  static constexpr uint64_t nonceIncrementStart = nonceInitStart + NonceLength / 3;

  static constexpr int stateSize      = 729;  // TODO constants
  static constexpr int numberOfRounds = 81;   // TODO constants

public:
  Pow();
  virtual ~Pow();

public:
  Types::Trytes operator()(const Types::Trytes& trytes, int minWeightMagnitude);

private:
  void         transform64(uint64_t* lmid, uint64_t* hmid) const;
  bool         incr(uint64_t* lmid, uint64_t* hmid) const;
  Types::Trits seri(const uint64_t* l, const uint64_t* h, uint64_t n) const;
  int64_t      check(const uint64_t* l, const uint64_t* h, int m) const;
  Types::Trits loop(uint64_t* lmid, uint64_t* hmid, int m) const;
  void         para(uint64_t* l, uint64_t* h, const Types::Trits& in) const;

private:
  bool       stop_;
  std::mutex mtx_;
};

}  // namespace Crypto

}  // namespace IOTA
