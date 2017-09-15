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

#include <vector>

#include <Crypto/ISponge.hpp>
#include <Type/Trits.hpp>
#include <constants.hpp>

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
  void reset();

  /**
   * absorb the input into the current state
   *
   * @param trists input trists to be applied (absorbed) on current state
   * @param offset offset at which the current state should be modified
   * @param length length of the given input that should be used for absorption
   */
  void absorb(const IOTA::Type::Trits& trits, unsigned int offset = 0, unsigned int length = 0);

  /**
   * squeeze the current state to the given input/output
   *
   * @param trists input trists to be updated (squeezed) based on current state
   * @param offset offset at which the input trists should be modified
   * @param length length of the current state that should be used for squeezing
   */
  void squeeze(IOTA::Type::Trits& trits, unsigned int offset = 0, unsigned int length = 0);

  /**
   * absorb the input into the current state
   *
   * @param lowTrists input trists to be applied (absorbed) on current state
   * @param highTrists input trists to be applied (absorbed) on current state
   * @param offset offset at which the current state should be modified
   * @param length length of the given input that should be used for absorption
   */
  void absorb(const std::vector<int64_t>& lowTrits, const std::vector<int64_t>& highTrits,
              int offset, unsigned int length);

  /**
   * squeeze the current state to the given input/output
   *
   * @param lowTrists input trists to be applied (absorbed) on current state
   * @param highTrists input trists to be applied (absorbed) on current state
   * @param offset offset at which the input trists should be modified
   * @param length length of the current state that should be used for squeezing
   */
  void squeeze(std::vector<int64_t>& lowTrits, std::vector<int64_t>& highTrits, int offset,
               unsigned int length);

  /**
   * @return current state of the sponge fonction
   */
  IOTA::Type::Trits getState() const;

  /**
   * @return current paired state of the sponge fonction
   */
  std::pair<std::vector<int64_t>, std::vector<int64_t>> getPairedState() const;

private:
  /**
   * Apply sponge fonction transformation algorithm during absorption/squeezing
   */
  void transform();

  /**
   * Same as transform, but for pair-curl
   */
  void pairTransform();

  /**
   * Copy input[0, length] to output[offset, offset+length]
   *
   * @param input input vector to copy
   * @param output output vector to update
   * @param offset offset after which elements should be copied in output vector
   * @ length number of bytes to copy
   */
  template <typename T>
  void arrayCopy(const std::vector<T>& input, std::vector<T>& output, int offset, int length) {
    std::transform(input.cbegin(), input.cbegin() + length, output.begin() + offset,
                   [](T c) { return c; });
  }

private:
  /**
   * Constant: state length (used to init state attr)
   */
  static const int32_t StateLength = 3 * TritHashLength;

  /**
   * Constant: number of round for transform algorithm
   */
  static const int32_t NumberOfRounds = 27;

  /**
   * Constant: truth table for conversions in transform
   */
  static constexpr int TruthTable[] = { 1, 0, -1, 2, 1, -1, 0, 2, -1, 1, 0 };

private:
  /**
   * current state
   */
  std::vector<int8_t> state_;

  /**
   * state low for pair transformation
   */
  std::vector<int64_t> stateLow_;

  /**
   * state high for pair transformation
   */
  std::vector<int64_t> stateHigh_;

  /**
   * stratch pad for transformation
   */
  std::vector<int8_t> scratchpad_;

  /**
   * stratch pad for pair transformation
   */
  std::vector<int64_t> scratchpadLow_;

  /**
   * stratch pad for pair transformation
   */
  std::vector<int64_t> scratchpadHigh_;
};

}  // namespace Crypto

}  // namespace IOTA
