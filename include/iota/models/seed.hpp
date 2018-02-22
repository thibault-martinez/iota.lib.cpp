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
   */
  Seed(const Types::Trytes& seed = "");

  /**
   * Ctor, char* based to make implicitly convertion to Seed more flexible.
   *
   * @param seed the seed value. It must be a valid seed.
   */
  Seed(const char* seed);

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
   * @return whether the seed is empty or not.
   */
  bool empty() const;

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
   * seed value without checksum
   */
  Types::Trytes seed_;
};

}  // namespace Models

}  // namespace IOTA
