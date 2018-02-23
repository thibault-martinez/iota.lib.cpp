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

#include <iota/api/responses/base.hpp>
#include <iota/models/fwd.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * GetBalancesAndFormat API call response.
 *
 * Gets all possible inputs of a seed and returns them with the total balance. This is either done
 * deterministically (by genearating all addresses until findTransactions returns null for a
 * corresponding address), or by providing a key range to use for searching through.
 * You can also define the minimum threshold that is required. This means that if you provide the
 * threshold value, you can specify that the inputs should only be returned if their collective
 * balance is above the threshold value.
 */
class GetBalancesAndFormat : public Base {
public:
  /**
   * Default ctor.
   */
  GetBalancesAndFormat() = default;

  /**
   * Full init ctor.
   *
   * @param inputs All input associated.
   * @param totalBalance The total balance.
   * @param duration Request duration.
   */
  GetBalancesAndFormat(const std::vector<Models::Address>& inputs, const int64_t& totalBalance,
                       const int64_t& duration);

  /**
   * Default dtor.
   */
  ~GetBalancesAndFormat() = default;

public:
  /**
   * @return Inputs.
   */
  const std::vector<Models::Address>& getInputs() const;

  /**
   * @return Inputs. (non const version)
   */
  std::vector<Models::Address>& getInputs();

  /**
   * @param inputs New inputs for api response
   */
  void setInputs(const std::vector<Models::Address>& inputs);

public:
  /**
   * @return Total balance.
   */
  const int64_t& getTotalBalance() const;

  /**
   * @param totalBalance New total balance for api response.
   */
  void setTotalBalance(const int64_t& totalBalance);

private:
  std::vector<Models::Address> inputs_;
  int64_t                      totalBalance_ = 0;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
