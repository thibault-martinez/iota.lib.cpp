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

#include <iota/api/requests/base.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {

/*
 * GetTransactionsToApprove API call request.
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
   * @param depth Number of bundles to go back to determine the transactions for approval.
   */
  explicit GetTransactionsToApprove(const int& depth = 0);

  /**
   * Default dtor.
   */
  ~GetTransactionsToApprove() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

public:
  /**
   * @return depth.
   */
  int getDepth() const;

  /**
   * @param depth new depth for api call.
   */
  void setDepth(int depth);

private:
  /*
   * Number of bundles to go back to determine the transactions for approval.
   */
  int depth_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
