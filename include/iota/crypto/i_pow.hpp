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

#include <iota/types/trytes.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Interface for proof of work algorithms.
 */
class IPow {
public:
  /**
   * Default ctor.
   */
  IPow() = default;
  /**
   * Default dtor.
   */
  virtual ~IPow() = default;

public:
  /**
   * Compute nonce from the given trytes.
   *
   * @param trytes The trytes to compute nonce from.
   * @param minWeightMagnitude The minimum number of zeroes the hash has to end with.
   * @param threads The number of thread to run the algorithm to.
   *
   * @return The nonce.
   */
  virtual Types::Trytes operator()(const Types::Trytes& trytes, int minWeightMagnitude,
                                   int threads = 0) = 0;
};

}  // namespace Crypto

}  // namespace IOTA
