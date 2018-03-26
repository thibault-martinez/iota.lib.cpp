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

#include <iota/api/responses/get_balances.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetBalances::GetBalances(const std::vector<std::string>& balances, const Types::Trytes& milestone,
                         const int64_t& milestoneIndex)
    : balances_(balances), milestone_(milestone), milestoneIndex_(milestoneIndex) {
}

GetBalances::GetBalances(const json& res) {
  deserialize(res);
}

void
GetBalances::deserialize(const json& res) {
  Base::deserialize(res);

  if (res.HasMember("balances")) {
    auto arr = res["balances"].GetArray();

    balances_.clear();
    for (auto it = arr.Begin(); it != arr.End(); ++it) {
      balances_.push_back(it->GetString());
    }
  }

  if (res.HasMember("milestone")) {
    milestone_ = res["milestone"].GetString();
  }

  if (res.HasMember("milestoneIndex")) {
    milestoneIndex_ = res["milestoneIndex"].GetInt64();
  }
}

const std::vector<std::string>&
GetBalances::getBalances() const {
  return balances_;
}

std::vector<std::string>&
GetBalances::getBalances() {
  return balances_;
}

void
GetBalances::setBalances(const std::vector<std::string>& balances) {
  balances_ = balances;
}

const Types::Trytes&
GetBalances::getMilestone() const {
  return milestone_;
}

void
GetBalances::setMilestone(const Types::Trytes& milestone) {
  milestone_ = milestone;
}

const int64_t&
GetBalances::getMilestoneIndex() const {
  return milestoneIndex_;
}

void
GetBalances::setMilestoneIndex(const int64_t& milestoneIndex) {
  milestoneIndex_ = milestoneIndex;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
