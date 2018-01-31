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

  static constexpr uint64_t nonceOffset         = TritHashLength - TritNonceLength;
  static constexpr uint64_t nonceInitStart      = nonceOffset + 4;
  static constexpr uint64_t nonceIncrementStart = nonceInitStart + TritNonceLength / 3;

  static constexpr int stateSize      = PowStateSize;
  static constexpr int numberOfRounds = PowNumberOfRounds;

public:
  Pow()          = default;
  virtual ~Pow() = default;

public:
  Types::Trytes operator()(const Types::Trytes& trytes, int minWeightMagnitude,
                           int threads = 0) override;

private:
  inline void         initialize(uint64_t* stateLow, uint64_t* stateHigh,
                                 const IOTA::Types::Trits& trits) const;
  inline void         transform(uint64_t* curlStateLow, uint64_t* curlStateHigh,
                                uint64_t* curlScratchpadLow, uint64_t* curlScratchpadHigh) const;
  inline void         increment(uint64_t* midCurlStateCopyLow, uint64_t* midCurlStateCopyHigh,
                                int fromIndex, int toIndex) const;
  inline Types::Trits loop(uint64_t* lmid, uint64_t* hmid, int minWeightMagnitude);

private:
  bool       stop_ = true;
  std::mutex mtx_;
};

}  // namespace Crypto

}  // namespace IOTA
