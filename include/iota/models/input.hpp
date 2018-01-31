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

class Input {
public:
  /**
   * default ctor
   */
  Input();

  /**
   * full init ctor
   */
  Input(const Types::Trytes& address, const int64_t& balance, const int32_t& keyIndex,
        const int32_t& security);

  /**
   * default dtor
   */
  ~Input() = default;

public:
  /**
   * @return Address of your peer.
   */
  const Types::Trytes& getAddress() const;

  /**
   * @param addr set address of your peer
   */
  void setAddress(const Types::Trytes& addr);

public:
  /**
   * @return Balance
   */
  const int64_t& getBalance() const;

  /**
   * @param balance set new balance for input
   */
  void setBalance(const int64_t& balance);

public:
  /**
   * @return Key Index
   */
  const int32_t& getKeyIndex() const;

  /**
   * @param keyIndex set new keyIndex for input in transaction
   */
  void setKeyIndex(const int32_t& keyIndex);

public:
  /**
   * @return Security
   */
  const int32_t& getSecurity() const;

  /**
   * @param security set new security level for input
   */
  void setSecurity(const int32_t& security);

public:
  /**
   * @param rhs An object to compare with this object.
   * @return whether the current input is the same as the given one
   */
  bool operator==(const Input& rhs) const;

  /**
   * @param rhs An object to compare with this object.
   * @return whether the current input is different from the given one
   */
  bool operator!=(const Input& rhs) const;

private:
  Types::Trytes address_;
  int64_t       balance_;
  int32_t       keyIndex_;
  int32_t       security_;
};

}  // namespace Models

}  // namespace IOTA
