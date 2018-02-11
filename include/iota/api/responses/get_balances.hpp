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

#pragma once

#include <json.hpp>

#include <iota/api/responses/base.hpp>
#include <iota/types/trinary.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/**
 * GetBalances API call response.
 *
 * Similar to getInclusionStates. It returns the confirmed balance which a list of addresses have
 * at the latest confirmed milestone. In addition to the balances, it also returns the milestone
 * as well as the index with which the confirmed balance was determined. The balances is returned
 * as a list in the same order as the addresses were provided as input.
 *
 * https://iota.readme.io/reference#getbalances
 */
class GetBalances : public Base {
public:
  /**
   * Full init ctor.
   * @param balances The confirmed balances.
   * @param milestone The latest confirmed milestone.
   * @param milestoneIndex The latest confirmed milestone index.
   */
  explicit GetBalances(const std::vector<std::string>& balances = {},
                       const Types::Trytes& milestone = "", const int64_t& milestoneIndex = 0);

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit GetBalances(const json& res);

  /**
   * Default dtor.
   */
  ~GetBalances() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return balances.
   */
  const std::vector<std::string>& getBalances() const;

  /**
   * @return balances. (non const version).
   */
  std::vector<std::string>& getBalances();

  /**
   * @param balances new balances for api response.
   */
  void setBalances(const std::vector<std::string>& balances);

public:
  /**
   * @return milestone.
   */
  const Types::Trytes& getMilestone() const;

  /**
   * @param milestone new milestone for api response.
   */
  void setMilestone(const Types::Trytes& milestone);

public:
  /**
   * @return milestone index.
   */
  const int64_t& getMilestoneIndex() const;

  /**
   * @param milestoneIndex new milestone index for api response.
   */
  void setMilestoneIndex(const int64_t& milestoneIndex);

private:
  /**
   * Confirmed balance in the same order as the addresses were provided as input.
   */
  std::vector<std::string> balances_;
  /**
   * Latest confirmed milestone.
   */
  Types::Trytes milestone_;
  /**
   * Latest confirmed milestone index.
   */
  int64_t milestoneIndex_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
