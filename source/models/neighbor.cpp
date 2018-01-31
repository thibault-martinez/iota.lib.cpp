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

#include <iota/models/neighbor.hpp>

namespace IOTA {

namespace Models {

Neighbor::Neighbor(const Types::Trytes& address, const int64_t& numberOfAllTransactions,
                   const int64_t& numberOfInvalidTransactions,
                   const int64_t& numberOfNewTransactions)
    : address_(address),
      numberOfAllTransactions_(numberOfAllTransactions),
      numberOfInvalidTransactions_(numberOfInvalidTransactions),
      numberOfNewTransactions_(numberOfNewTransactions) {
}

const Types::Trytes&
Neighbor::getAddress() const {
  return address_;
}

void
Neighbor::setAddress(const Types::Trytes& addr) {
  address_ = addr;
}

const int64_t&
Neighbor::getNumberOfAllTransactions() const {
  return numberOfAllTransactions_;
}

void
Neighbor::setNumberOfAllTransactions(const int64_t& nbTrx) {
  numberOfAllTransactions_ = nbTrx;
}

const int64_t&
Neighbor::getNumberOfInvalidTransactions() const {
  return numberOfInvalidTransactions_;
}

void
Neighbor::setNumberOfInvalidTransactions(const int64_t& nbTrx) {
  numberOfInvalidTransactions_ = nbTrx;
}

const int64_t&
Neighbor::getNumberOfNewTransactions() const {
  return numberOfNewTransactions_;
}

void
Neighbor::setNumberOfNewTransactions(const int64_t& nbTrx) {
  numberOfNewTransactions_ = nbTrx;
}

bool
Neighbor::operator==(const Neighbor& rhs) const {
  return address_ == rhs.address_;
}

bool
Neighbor::operator!=(const Neighbor& rhs) const {
  return !operator==(rhs);
}

}  // namespace Models

}  // namespace IOTA
