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

#pragma once

#include <json.hpp>

#include <iota/api/responses/base.hpp>
#include <iota/models/input.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * Response of extended API getInputs
 * Gets all possible inputs of a seed and returns them with the total balance. This is either done
 * deterministically (by genearating all addresses until findTransactions returns null for a
 * corresponding address), or by providing a key range to use for searching through.
 *
 * You can also define the minimum threshold that is required. This means that if you provide the
 * threshold value, you can specify that the inputs should only be returned if their collective
 * balance is above the threshold value.
 */
class GetBalancesAndFormat : public Base {
public:
  GetBalancesAndFormat();
  GetBalancesAndFormat(const std::vector<Models::Input>& inputs, const int64_t& totalBalance,
                       const int64_t& duration);
  ~GetBalancesAndFormat() = default;

public:
  /*
   * The input.
   */
  const std::vector<Models::Input>& getInput() const;
  /*
   * The total balance.
   */
  const int64_t& getTotalBalance() const;

private:
  std::vector<Models::Input> inputs_;
  int64_t                    totalBalance_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
