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

#include <iota/api/requests/get_inclusion_states.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Requests {

GetInclusionStates::GetInclusionStates(const std::vector<Types::Trytes>& transactions,
                                       const std::vector<Types::Trytes>& tips)
    : Base("getInclusionStates"), transactions_(transactions), tips_(tips) {
}

void
GetInclusionStates::serialize(Utils::json& data) const {
  Base::serialize(data);

  data.set("transactions", transactions_);
  data.set("tips", tips_);
}

const std::vector<Types::Trytes>&
GetInclusionStates::getTransactions() const {
  return transactions_;
}

std::vector<Types::Trytes>&
GetInclusionStates::getTransactions() {
  return transactions_;
}

void
GetInclusionStates::setTransactions(const std::vector<Types::Trytes>& trxs) {
  transactions_ = trxs;
}

const std::vector<Types::Trytes>&
GetInclusionStates::getTips() const {
  return tips_;
}

std::vector<Types::Trytes>&
GetInclusionStates::getTips() {
  return tips_;
}

void
GetInclusionStates::setTips(const std::vector<Types::Trytes>& tips) {
  tips_ = tips;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
