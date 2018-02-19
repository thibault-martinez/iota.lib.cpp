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

#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/models/input.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetBalancesAndFormat::GetBalancesAndFormat(const std::vector<Models::Input>& inputs,
                                           const int64_t& totalBalance, const int64_t& duration)
    : Base(duration), inputs_(inputs), totalBalance_(totalBalance) {
}

const std::vector<Models::Input>&
GetBalancesAndFormat::getInputs() const {
  return inputs_;
}

std::vector<Models::Input>&
GetBalancesAndFormat::getInputs() {
  return inputs_;
}

void
GetBalancesAndFormat::setInputs(const std::vector<Models::Input>& inputs) {
  inputs_ = inputs;
}

const int64_t&
GetBalancesAndFormat::getTotalBalance() const {
  return totalBalance_;
}

void
GetBalancesAndFormat::setTotalBalance(const int64_t& totalBalance) {
  totalBalance_ = totalBalance;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
