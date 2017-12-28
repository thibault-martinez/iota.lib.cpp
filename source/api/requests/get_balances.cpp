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

#include <iota/api/requests/get_balances.hpp>

namespace IOTA {

namespace API {

namespace Requests {

GetBalances::GetBalances(const std::vector<std::string>& addresses, const int& threshold)
    : Base("getBalances"), addresses_(addresses), threshold_(threshold) {
}

void
GetBalances::serialize(json& data) {
  Base::serialize(data);
  data["addresses"] = addresses_;
  data["threshold"] = threshold_;
}

const std::vector<Types::Trytes>&
GetBalances::getAddresses() const {
  return addresses_;
}

std::vector<Types::Trytes>&
GetBalances::getAddresses() {
  return addresses_;
}

void
GetBalances::setAddresses(const std::vector<Types::Trytes>& addrs) {
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

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
