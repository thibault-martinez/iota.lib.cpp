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

#include <algorithm>
#include <vector>

#include <iota/constants.hpp>
#include <iota/crypto/i_sponge.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

class Curl : public ISponge {
public:
  Curl();
  ~Curl() = default;

public:
  /**
   * Reset current state of the crypto algorithm
   */
  void reset() override;

  /**
   * absorb the input into the current state
   *
   * @param trists input trists to be applied (absorbed) on current state
   * @param offset offset at which the current state should be modified
   * @param length length of the given input that should be used for absorption
   */
  void absorb(const Types::Trits& trits, unsigned int offset = 0, unsigned int length = 0) override;

  /**
   * squeeze the current state to the given input/output
   *
   * @param trists input trists to be updated (squeezed) based on current state
   * @param offset offset at which the input trists should be modified
   * @param length length of the current state that should be used for squeezing
   */
  void squeeze(Types::Trits& trits, unsigned int offset = 0, unsigned int length = 0) override;

public:
  const std::vector<int8_t>& getState() const;

private:
  /**
   * Apply sponge fonction transformation algorithm during absorption/squeezing
   */
  void transform();

  /**
   * Copy input[0, length] to output[offset, offset+length]
   *
   * @param input input vector to copy
   * @param output output vector to update
   * @param offset offset after which elements should be copied in output vector
   * @ length number of bytes to copy
   */
  template <typename T>
  void arrayCopy(const typename std::vector<T>::const_iterator& input,
                 const typename std::vector<T>::iterator& output, int length) {
    std::transform(input, input + length, output, [](T c) { return c; });
  }

private:
  /**
   * Constant: state length (used to init state attr)
   */
  static const int32_t StateLength = 3 * TritHashLength;

  /**
   * Constant: number of round for transform algorithm
   */
  static const int32_t NumberOfRounds = 81;

  /**
   * Constant: truth table for conversions in transform
   */
  static int TruthTable[];

private:
  /**
   * current state
   */
  std::vector<int8_t> state_;

  /**
   * stratch pad for transformation
   */
  std::vector<int8_t> scratchpad_;
};

}  // namespace Crypto

}  // namespace IOTA
