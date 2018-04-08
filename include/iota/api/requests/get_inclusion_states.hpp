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

#include <iota/api/requests/base.hpp>
#include <iota/types/trytes.hpp>

#include <vector>

namespace IOTA {

namespace API {

namespace Requests {

/**
 * GetInclusionStates API call request.
 *
 * Get the inclusion states of a set of transactions. This is for determining if a transaction was
 * accepted and confirmed by the network or not. You can search for multiple tips (and thus,
 * milestones) to get past inclusion states of transactions.
 * This API call simply returns a list of boolean values in the same order as the transaction list
 * you submitted, thus you get a true/false whether a transaction is confirmed or not.
 *
 * https://iota.readme.io/reference#getinclusionstates
 *
 */
class GetInclusionStates : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param transactions List of transactions you want to get the inclusion state for.
   * @param tips List of tips (including milestones) you want to search for the inclusion state.
   */
  explicit GetInclusionStates(const std::vector<Types::Trytes>& transactions = {},
                              const std::vector<Types::Trytes>& tips         = {});

  /**
   * Default dtor.
   */
  ~GetInclusionStates() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(Utils::json& data) const override;

public:
  /**
   * @return transactions.
   */
  const std::vector<Types::Trytes>& getTransactions() const;

  /**
   * @return transactions (non const version).
   */
  std::vector<Types::Trytes>& getTransactions();

  /**
   * @param trxs new transactions for api call.
   */
  void setTransactions(const std::vector<Types::Trytes>& trxs);

public:
  /**
   * @return tips.
   */
  const std::vector<Types::Trytes>& getTips() const;

  /**
   * @return tips (non const version).
   */
  std::vector<Types::Trytes>& getTips();

  /**
   * @param tips new tips for api call.
   */
  void setTips(const std::vector<Types::Trytes>& tips);

private:
  /**
   * List of transactions you want to get the inclusion state for.
   */
  std::vector<Types::Trytes> transactions_;
  /**
   * List of tips (including milestones) you want to search for the inclusion state.
   */
  std::vector<Types::Trytes> tips_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
