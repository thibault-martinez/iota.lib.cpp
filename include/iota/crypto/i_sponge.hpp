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

#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Sponge construction interface for hashing algorithms.
 * Trits are absorbed by the sponge function and later squeezed to provide message digest, derive
 * keys etc.
 */
class ISponge {
public:
  /**
   * Default ctor.
   */
  ISponge() = default;
  /**
   * Default dtor.
   */
  virtual ~ISponge() = default;

public:
  /**
   * Reset current state of the crypto algorithm.
   */
  virtual void reset() = 0;
  /**
   * Absorb the input into the current state.
   *
   * @param trits input trits to be applied (absorbed) on current state.
   * @param offset offset at which the current state should be modified.
   * @param length length of the given input that should be used for absorption.
   */
  virtual void absorb(const Types::Trits& trits, std::size_t offset = 0,
                      std::size_t length = 0) = 0;
  /**
   * Squeeze the current state to the given input/output.
   *
   * @param trits input trits to be updated (squeezed) based on current state.
   * @param offset offset at which the input trists should be modified.
   * @param length length of the current state that should be used for squeezing.
   */
  virtual void squeeze(Types::Trits& trits, std::size_t offset = 0, std::size_t length = 0) = 0;
};

}  // namespace Crypto

}  // namespace IOTA
