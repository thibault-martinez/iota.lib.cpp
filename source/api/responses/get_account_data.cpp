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

#include <iota/api/responses/get_account_data.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetAccountData::GetAccountData() : balance_(0) {
}

GetAccountData::GetAccountData(const std::vector<IOTA::Types::Trytes>& addresses,
                               const std::vector<Models::Bundle>& transferBundle, long balance,
                               long duration)
    : Base(duration), addresses_(addresses), transferBundle_(transferBundle), balance_(balance) {
}

const std::vector<IOTA::Types::Trytes>&
GetAccountData::getAddresses() const {
  return addresses_;
}

std::vector<IOTA::Types::Trytes>&
GetAccountData::getAddresses() {
  return addresses_;
}

void
GetAccountData::setAddresses(const std::vector<IOTA::Types::Trytes>& addresses) {
  addresses_ = addresses;
}

const std::vector<Models::Bundle>&
GetAccountData::getTransfers() const {
  return transferBundle_;
}

std::vector<Models::Bundle>&
GetAccountData::getTransfers() {
  return transferBundle_;
}

void
GetAccountData::setTransfers(const std::vector<Models::Bundle>& transfers) {
  transferBundle_ = transfers;
}

long
GetAccountData::getBalance() const {
  return balance_;
}

void
GetAccountData::setBalance(long balance) {
  balance_ = balance;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
