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

#include <string>

#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

class Transfer {
public:
  /**
   * Default constructor
   */
  Transfer();

  /**
   * full constructor
   */
  Transfer(const Types::Trytes& address, int64_t value, const Types::Trytes& message,
           const Types::Trytes& tag);

  /**
   * Destructor
   */
  ~Transfer() = default;

public:
  /**
   * Get the address.
   *
   * @return The address.
   */
  const Types::Trytes& getAddress() const;

  /**
   * Set the address.
   *
   * @param address The address.
   */
  void setAddress(const Types::Trytes& address);

  /**
   * Get the value.
   *
   * @return The value.
   */
  int64_t getValue() const;

  /**
   * Set the value.
   *
   * @param value The value.
   */
  void setValue(int64_t value);

  /**
   * Get the message.
   *
   * @return The message.
   */
  const Types::Trytes& getMessage() const;

  /**
   * Set the message.
   *
   * @param message The message.
   */
  void setMessage(const Types::Trytes& message);

  /**
   * Get the tag.
   *
   * @return The tag.
   */
  const Types::Trytes& getTag() const;

  /**
   * Set the tag.
   *
   * @param tag The tag.
   */
  void setTag(const Types::Trytes& tag);

  /**
   * @return <code>true</code> if the transfer is valid; otherwise, <code>false</code>>.
   **/
  bool isValid() const;

public:
  /**
   * @param rhs An object to compare with this object.
   * @return whether the current transfer is the same as the given one
   */
  bool operator==(const Transfer& rhs) const;

  /**
   * @param rhs An object to compare with this object.
   * @return whether the current transfer is different from the given one
   */
  bool operator!=(const Transfer& rhs) const;

private:
  Types::Trytes address_;
  int64_t       value_;
  Types::Trytes message_;
  Types::Trytes tag_;
};

}  // namespace Models

}  // namespace IOTA
