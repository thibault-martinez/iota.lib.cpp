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

class Tag {
public:
  /**
   * Ctor.
   *
   * @param tag the tag value. Tag can be any valid tryte string not exceeding TagLength
   */
  Tag(const Types::Trytes& tag = "");

  /**
   * Default dtor.
   */
  ~Tag() = default;

public:
  /**
   * @return tag as a trytes string, without any 9's padded. For example, tag 'ABC9999...' will
   * return 'ABC'
   */
  const Types::Trytes& toTrytes() const;

  /**
   * @return tag as a trytes string, 9's right-padded to match the valid tag length. For example,
   * tag 'ABC' will return 'ABC9999...'
   */
  const Types::Trytes& toTrytesWithPadding() const;

  /**
   * Set the tag value
   *
   * @param tag new value of the tag
   */
  void setTag(const Types::Trytes& tag);

  /**
   * @return whether the tag is empty or not. Please note that if your tag consists only of 9's, it
   * will be considered empty as 9 is the padding character
   */
  bool empty() const;

public:
  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Tag& rhs) const;

  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Tag& rhs) const;

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
   * tag value without padding
   */
  Types::Trytes tag_;

  /**
   * tag value with 9's right-padding
   */
  Types::Trytes paddedTag_;
};

}  // namespace Models

}  // namespace IOTA
