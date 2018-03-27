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

#include <iota/crypto/keccak384.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Hashing algorithm, based on keccak.
 * Trits are absorbed by the sponge function and later squeezed to provide message digest, derive
 * keys etc.
 */
class Kerl {
public:
  Kerl()          = default;
  virtual ~Kerl() = default;

public:
  /**
   * Reset current state of the sponge.
   */
  void reset();

  /**
   * Absorb the input bytes into the current state of the sponge.
   *
   * @param bytes Input bytes to be absorbed on current state of the sponge.
   * @param offset Offset at which the current state of the sponge should be modified.
   * @param length Length of the given input that should be used for absorption.
   */
  void absorb(const std::vector<uint8_t>& bytes, std::size_t offset = 0, std::size_t length = 0);

  /**
   * Squeeze the current state of the sponge to the given trits.
   *
   * @param bytes Bytes to be squeezed based on current state of the sponge.
   * @param offset Offset at which the bytes should be modified.
   */
  void squeeze(std::vector<uint8_t>& bytes, std::size_t offset = 0);

  /**
   * Squeeze the final current state of the sponge to the given trits.
   * Kerl should not be used after this function is called, unless it is reseted.
   *
   * @param bytes Bytes to be squeezed based on current state of the sponge.
   * @param offset Offset at which the bytes should be modified.
   */
  void finalSqueeze(std::vector<uint8_t>& bytes, std::size_t offset = 0);

private:
  /**
   * Internal keccak algorithm.
   */
  Keccak384 keccak_;
};

}  // namespace Crypto

}  // namespace IOTA
