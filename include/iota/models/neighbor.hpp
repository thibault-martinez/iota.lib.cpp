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

#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

class Neighbor {
public:
  /**
   * default ctor
   */
  Neighbor();

  /**
   * full init ctor
   */
  Neighbor(const IOTA::Types::Trytes& address, const int64_t& numberOfAllTransactions,
           const int64_t& numberOfInvalidTransactions, const int64_t& numberOfNewTransactions);

  /**
   * default dtor
   */
  ~Neighbor() = default;

public:
  /**
   * @return Address of your peer.
   */
  const IOTA::Types::Trytes& getAddress() const;

  /**
   * @param addr set address of your peer
   */
  void setAddress(const IOTA::Types::Trytes& addr);

public:
  /**
   * @return Number of all transactions sent (invalid, valid, already-seen).
   */
  const int64_t& getNumberOfAllTransactions() const;

  /**
   * @param nbTrx set number of all transactions sent (invalid, valid, already seen)
   */
  void setNumberOfAllTransactions(const int64_t& nbTrx);

public:
  /**
   * @return Invalid transactions your peer has sent you. These are transactions with invalid
   * signatures or overall schema.
   */
  const int64_t& getNumberOfInvalidTransactions() const;

  /**
   * @param nbTrx set number of invalid transactions sent your peer
   */
  void setNumberOfInvalidTransactions(const int64_t& nbTrx);

public:
  /**
   * @return New transactions which were transmitted.
   */
  const int64_t& getNumberOfNewTransactions() const;

  /**
   * @param nbTrx set number of newly transmitted transactions
   */
  void setNumberOfNewTransactions(const int64_t& nbTrx);

private:
  IOTA::Types::Trytes address_;
  int64_t             numberOfAllTransactions_;
  int64_t             numberOfInvalidTransactions_;
  int64_t             numberOfNewTransactions_;
};

}  // namespace Models

}  // namespace IOTA
