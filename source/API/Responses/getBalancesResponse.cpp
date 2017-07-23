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

#include "getBalancesResponse.hpp"

getBalancesResponse::getBalancesResponse() {
}

getBalancesResponse::~getBalancesResponse() {
}

void
getBalancesResponse::deserialize(const json& res) {
  this->balances_       = res.at("balances").get<std::vector<std::string>>();
  this->milestone_      = res.at("milestone").get<std::string>();
  this->milestoneIndex_ = res.at("milestoneIndex").get<int64_t>();
}

const std::vector<std::string>&
getBalancesResponse::getBalances() const {
  return this->balances_;
}

const std::string&
getBalancesResponse::getMilestone() const {
  return this->milestone_;
}

const int64_t&
getBalancesResponse::getMilestoneIndex() const {
  return this->milestoneIndex_;
}
