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

/*
 * GetTransactionsToApprove API call response.
 *
 * Tip selection which returns trunkTransaction and branchTransaction. The input value is depth,
 * which basically determines how many bundles to go back to for finding the transactions to
 * approve. The higher your depth value, the more "babysitting" you do for the network (as you
 * have to confirm more transactions).
 *
 * https://iota.readme.io/reference#getbalances
 */
class GetTransactionsToApprove : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param trunkTransaction The trunk transaction.
   * @param branchTransaction The branch transaction.
   */
  explicit GetTransactionsToApprove(const Types::Trytes& trunkTransaction  = "",
                                    const Types::Trytes& branchTransaction = "");

  /**
   * Default dtor.
   */
  ~GetTransactionsToApprove() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return trunk transaction.
   */
  const Types::Trytes& getTrunkTransaction() const;

  /**
   * @param trx new trunk transaction for api call.
   */
  void setTrunkTransaction(const Types::Trytes& trx);

public:
  /**
   * @return branch transaction.
   */
  const Types::Trytes& getBranchTransaction() const;

  /**
   * @param trx new branch transaction for api call.
   */
  void setBranchTransaction(const Types::Trytes& trx);

private:
  /**
   * Trunk transaction.
   */
  Types::Trytes trunkTransaction_;
  /**
   * Branch transaction.
   */
  Types::Trytes branchTransaction_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
