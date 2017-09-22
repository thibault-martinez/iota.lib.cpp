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

#include <string>

#include <Type/Trinary.hpp>

class Transfer {
public:
  Transfer(const std::string& timestamp, const IOTA::Type::Trytes& address,
           const IOTA::Type::Trytes& hash, bool persistence, int64_t value,
           const std::string& message, const std::string& tag);
  Transfer(const IOTA::Type::Trytes& address, int64_t value, const std::string& message,
           const std::string& tag);
  virtual ~Transfer();

public:
  /**
   * Get the address.
   *
   * @return The address.
   */
  const IOTA::Type::Trytes& getAddress();

  /**
   * Set the address.
   *
   * @param address The address.
   */
  void setAddress(const IOTA::Type::Trytes& address);

  /**
   * Get the hash.
   *
   * @return The hash.
   */
  const IOTA::Type::Trytes& getHash();

  /**
   * Set the hash.
   *
   * @param hash The hash.
   */
  void setHash(const IOTA::Type::Trytes& hash);

  /**
   * Get the persistence.
   *
   * @return The persistence.
   */
  bool getPersistence();

  /**
   * Set the persistence.
   *
   * @param persistence The persistence.
   */
  void setPersistence(bool persistence);

  /**
   * Get the timestamp.
   *
   * @return The timestamp.
   */
  const std::string& getTimestamp();

  /**
   * Set the timestamp.
   *
   * @param timestamp The timestamp.
   */
  void setTimestamp(const std::string& timestamp);

  /**
   * Get the value.
   *
   * @return The value.
   */
  int64_t getValue();

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
  const std::string& getMessage();

  /**
   * Set the message.
   *
   * @param message The message.
   */
  void setMessage(const std::string& message);

  /**
   * Get the tag.
   *
   * @return The tag.
   */
  const std::string& getTag();

  /**
   * Set the tag.
   *
   * @param tag The tag.
   */
  void setTag(const std::string& tag);

private:
  std::string        timestamp_;
  IOTA::Type::Trytes address_;
  IOTA::Type::Trytes hash_;
  bool               persistence_;
  int64_t            value_;
  std::string        message_;
  std::string        tag_;
};
