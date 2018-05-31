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

#include <json.hpp>

#include <iota/api/requests/get_balances.hpp>

namespace IOTA {

namespace API {

namespace Requests {

GetBalances::GetBalances(const std::vector<Models::Address>& addresses, const int& threshold,
                         const std::vector<Types::Trytes>& tips)
    : Base("getBalances"), addresses_(addresses), threshold_(threshold), tips_(tips) {
}

void
GetBalances::serialize(json& data) const {
  Base::serialize(data);

  for (auto& address : addresses_) {
    data["addresses"].emplace_back(address.toTrytes());
  }
  data["threshold"] = threshold_;
  for (auto& tip : tips_) {
    data["tips"].emplace_back(tip);
  }
}

const std::vector<Models::Address>&
GetBalances::getAddresses() const {
  return addresses_;
}

std::vector<Models::Address>&
GetBalances::getAddresses() {
  return addresses_;
}

void
GetBalances::setAddresses(const std::vector<Models::Address>& addrs) {
  addresses_ = addrs;
}

int
GetBalances::getThreshold() const {
  return threshold_;
}

void
GetBalances::setThreshold(int threshold) {
  threshold_ = threshold;
}

const std::vector<Types::Trytes>&
GetBalances::getTips() const {
  return tips_;
}

std::vector<Types::Trytes>&
GetBalances::getTips() {
  return tips_;
}

void
GetBalances::setTips(const std::vector<Types::Trytes>& tips) {
  tips_ = tips;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
