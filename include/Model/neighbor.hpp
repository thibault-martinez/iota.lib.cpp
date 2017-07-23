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

#include <iostream>

class Neighbor {
public:
  Neighbor(const std::string& address, const int64_t& numberOfAllTransactions,
           const int64_t& numberOfInvalidTransactions, const int64_t& numberOfNewTransactions);
  virtual ~Neighbor();

public:
  /*
   * Address of your peer.
   */
  const std::string& getAddress() const;
  /*
   * Number of all transactions sent (invalid, valid, already-seen).
   */
  const int64_t& getNumberOfAllTransactions() const;
  /*
   * Invalid transactions your peer has sent you. These are transactions with invalid signatures or
   * overall schema.
   */
  const int64_t& getNumberOfInvalidTransactions() const;
  /*
   * New transactions which were transmitted.
   */
  const int64_t& getNumberOfNewTransactions() const;

private:
  std::string address_;
  int64_t     numberOfAllTransactions_;
  int64_t     numberOfInvalidTransactions_;
  int64_t     numberOfNewTransactions_;
};
