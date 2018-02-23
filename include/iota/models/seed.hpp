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

namespace Models {

/**
 * Used to store seeds.
 * Provides validity checks at construction / value set.
 * Any seeds stored represented with this class are ensured to be valid.
 */
class Seed {
public:
  /**
   * Ctor.
   *
   * @param seed the seed value. It must be a valid seed.
   * @param security Security level of the seed. Must be between 1 (low, fast) and 3 (high slow).
   */
  Seed(const Types::Trytes& seed = "", int security = 2);

  /**
   * Ctor, char* based to make implicitly convertion to Seed more flexible.
   *
   * @param seed the seed value. It must be a valid seed.
   * @param security Security level of the seed. Must be between 1 (low, fast) and 3 (high slow).
   */
  Seed(const char* seed, int security = 2);

  /**
   * Default dtor.
   */
  ~Seed() = default;

public:
  /**
   * @return seed as a trytes string, without the checksum
   */
  const Types::Trytes& toTrytes() const;

  /**
   * Set the seed value
   *
   * @param seed the seed value. It must be a valid seed.
   */
  void setSeed(const Types::Trytes& seed);

  /**
   * Set the seed security.
   * Must be between 1 (low, fast) and 3 (high slow).
   *
   * @param security the new security level of the seed.
   */
  void setSecurity(int security);

  /**
   * @return the security level of the seed
   */
  int getSecurity() const;

public:
  /**
   * Generate seed randomly
   * @return generated seed
   */
  static Seed generateRandomSeed();

public:
  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Seed& rhs) const;

  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Seed& rhs) const;

public:
  /**
   * Comparison operator, trytes-based for convenient use
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Types::Trytes& rhs) const;

  /**
   * Comparison operator, trytes-based for convenient use
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Types::Trytes& rhs) const;

private:
  /**
   * seed value
   */
  Types::Trytes seed_;
  /**
   * security level of the seem
   */
  int security_;
};

}  // namespace Models

}  // namespace IOTA
