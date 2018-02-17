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
 * Neighbor model.
 */
class Neighbor {
public:
  /**
   * Default ctor.
   */
  Neighbor() = default;

  /**
   * Full init ctor.
   *
   * @param address Address of your peer.
   * @param numberOfAllTransactions Number of all transactions sent (invalid, valid, already-seen).
   * @param numberOfInvalidTransactions Number of invalid transactions your peer has sent you.
   * @param numberOfNewTransactions Number of newly transmitted transactions.
   */
  Neighbor(const Types::Trytes& address, const int64_t& numberOfAllTransactions,
           const int64_t& numberOfInvalidTransactions, const int64_t& numberOfNewTransactions);

  /**
   * Default dtor.
   */
  ~Neighbor() = default;

public:
  /**
   * @return Address of your peer.
   */
  const Types::Trytes& getAddress() const;

  /**
   * @param addr Set address of your peer.
   */
  void setAddress(const Types::Trytes& addr);

public:
  /**
   * @return Number of all transactions sent (invalid, valid, already-seen).
   */
  const int64_t& getNumberOfAllTransactions() const;

  /**
   * @param nbTrx Set number of all transactions sent (invalid, valid, already seen).
   */
  void setNumberOfAllTransactions(const int64_t& nbTrx);

public:
  /**
   * @return Invalid transactions your peer has sent you. These are transactions with invalid
   * signatures or overall schema.
   */
  const int64_t& getNumberOfInvalidTransactions() const;

  /**
   * @param nbTrx Set number of invalid transactions sent your peer.
   */
  void setNumberOfInvalidTransactions(const int64_t& nbTrx);

public:
  /**
   * @return New transactions which were transmitted.
   */
  const int64_t& getNumberOfNewTransactions() const;

  /**
   * @param nbTrx Set number of newly transmitted transactions.
   */
  void setNumberOfNewTransactions(const int64_t& nbTrx);

public:
  /**
   * @param rhs An object to compare with this object.
   * @return Whether the current neighbor is the same as the given one.
   */
  bool operator==(const Neighbor& rhs) const;

  /**
   * @param rhs An object to compare with this object.
   * @return Whether the current neighbor is different from the given one.
   */
  bool operator!=(const Neighbor& rhs) const;

private:
  /**
   * Address of your peer.
   */
  Types::Trytes address_;
  /**
   * Number of all transactions sent (invalid, valid, already-seen).
   */
  int64_t numberOfAllTransactions_ = 0;
  /**
   * Invalid transactions your peer has sent you. These are transactions with invalid signatures or
   * overall schema.
   */
  int64_t numberOfInvalidTransactions_ = 0;
  /**
   * Number of newly transmitted transactions.
   */
  int64_t numberOfNewTransactions_ = 0;
};

}  // namespace Models

}  // namespace IOTA
