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

#include <API/Responses/getAccountDataResponse.hpp>

getAccountDataResponse::getAccountDataResponse() : balance_(0) {
}

getAccountDataResponse::getAccountDataResponse(const std::vector<IOTA::Type::Trytes>& addresses,
                                               const std::vector<Bundle>& transferBundle,
                                               long balance, long duration)
    : genericResponse(duration),
      addresses_(addresses),
      transferBundle_(transferBundle),
      balance_(balance) {
}

const std::vector<IOTA::Type::Trytes>&
getAccountDataResponse::getAddresses() const {
  return addresses_;
}

std::vector<IOTA::Type::Trytes>&
getAccountDataResponse::getAddresses() {
  return addresses_;
}

void
getAccountDataResponse::setAddresses(const std::vector<IOTA::Type::Trytes>& addresses) {
  addresses_ = addresses;
}

const std::vector<Bundle>&
getAccountDataResponse::getTransfers() const {
  return transferBundle_;
}

std::vector<Bundle>&
getAccountDataResponse::getTransfers() {
  return transferBundle_;
}

void
getAccountDataResponse::setTransfers(const std::vector<Bundle>& transfers) {
  transferBundle_ = transfers;
}

long
getAccountDataResponse::getBalance() const {
  return balance_;
}

void
getAccountDataResponse::setBalance(long balance) {
  balance_ = balance;
}
