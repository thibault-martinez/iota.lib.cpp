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

#include <iota/api/responses/get_balances.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetBalances::GetBalances(const std::vector<std::string>& balances, const Types::Trytes& milestone,
                         const int64_t& milestoneIndex)
    : balances_(balances), milestone_(milestone), milestoneIndex_(milestoneIndex) {
}

GetBalances::GetBalances(const std::vector<std::string>&   balances,
                         const std::vector<Types::Trytes>& references,
                         const int64_t&                    milestoneIndex)
    : balances_(balances), references_(references), milestoneIndex_(milestoneIndex) {
}

GetBalances::GetBalances(const json& res) {
  deserialize(res);
}

void
GetBalances::deserialize(const json& res) {
  Base::deserialize(res);

  if (res.count("balances")) {
    balances_ = res.at("balances").get<std::vector<std::string>>();
  }

  if (res.count("references")) {
    references_ = res.at("references").get<std::vector<Types::Trytes>>();
  }

  if (res.count("milestone")) {
    milestone_ = res.at("milestone").get<Types::Trytes>();
  }

  if (res.count("milestoneIndex")) {
    milestoneIndex_ = res.at("milestoneIndex").get<int64_t>();
  }
}

const std::vector<std::string>&
GetBalances::getBalances() const {
  return balances_;
}

const std::vector<Types::Trytes>&
GetBalances::getReferences() const {
  return references_;
}

const Types::Trytes&
GetBalances::getMilestone() const {
  return milestone_;
}

const int64_t&
GetBalances::getMilestoneIndex() const {
  return milestoneIndex_;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
