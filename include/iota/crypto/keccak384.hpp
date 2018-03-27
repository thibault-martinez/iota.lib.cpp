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

#include <vector>

extern "C" {
#include <KeccakHash.h>
}

namespace IOTA {

namespace Crypto {

/**
 * Keccak sponge construction with a 384 bits output.
 */
class Keccak384 {
public:
  /**
   * The value of the rate r (size of the part of the state that is written and read).
   */
  static constexpr unsigned int rate = 832;

  /**
   * The value of the capacity c (size of the part that is untouched by input/output).
   */
  static constexpr unsigned int capacity = 768;

  /**
   * The desired number of output bits.
   */
  static constexpr unsigned int hashBitLength = 384;

  /**
   * Bits that will be automatically appended to the end of the input message, as in domain
   * separation.
   */
  static constexpr unsigned int delimitedSuffix = 0x01;

public:
  Keccak384();
  virtual ~Keccak384() = default;

public:
  /**
   * Reset internal state of the sponge.
   */
  void reset();

  /**
   * Absorb the given bytes into the internal state of the sponge.
   *
   * @param bytes The bytes.
   * @param size The number of bytes.
   */
  void absorb(const uint8_t* bytes, size_t size = hashBitLength / 8);

  /**
   * Squeeze out bytes from the internal state of the sponge into the given bytes.
   *
   * @param bytes The bytes.
   */
  void squeeze(uint8_t* bytes);

protected:
  /**
  ** Keccak_HashUpdate wrapper to allow mock testing.
  *
  * @param bytes Bytes to be absorbed into the internal state of the sponge.
  *
  * @return The update status.
  */
  virtual bool hashUpdate(const uint8_t* bytes, size_t size);

  /**
  ** Keccak_HashSqueeze wrapper to allow mock testing.
  *
  * @param bytes Bytes where to squeeze out the internal state of the sponge.
  *
  * @return The squeeze status.
  */
  virtual bool hashSqueeze(uint8_t* bytes);

  /**
  ** Keccak_HashInitialize wrapper to allow mock testing.
  *
  * @return The initialization status.
  */
  virtual bool hashInitialize(void);

private:
  /**
   * Initialization routine.
   */
  void initialize();

private:
  /**
   * Internal keccak state instance.
   */
  Keccak_HashInstance khi_;
};

}  // namespace Crypto

}  // namespace IOTA
