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

#include <iota/api/requests/base.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {
/*
 * AttachToTangle API call request.
 * Attaches the specified transactions (trytes) to the Tangle by doing Proof of Work. You need to
 * supply branchTransaction as well as trunkTransaction (basically the tips which you're going to
 * validate and reference with this transaction) - both of which you'll get through the
 * getTransactionsToApprove API call.
 * The returned value is a different set of tryte values which you can input into
 * broadcastTransactions and storeTransactions. The returned tryte value, the last 243 trytes
 * basically consist of the: trunkTransaction + branchTransaction + nonce. These are valid trytes
 * which are then accepted by the network.
 * https://iota.readme.io/docs/attachtotangle
 */
class AttachToTangle : public Base {
public:
  AttachToTangle(const std::string& trunkTransaction, const std::string& branchTransaction,
                 const int& minWeightMagnitude, const std::vector<std::string>& trytes);
  ~AttachToTangle() = default;

public:
  void serialize(json& res);

private:
  /*
   * Trunk transaction to approve.
   */
  std::string trunkTransaction_;
  /*
   * Branch transaction to approve.
   */
  std::string branchTransaction_;
  /*
   * Proof of Work intensity. Minimum value is 18.
   */
  int minWeightMagnitude_;
  /*
   * List of trytes (raw transaction data) to attach to the tangle.
   */
  std::vector<std::string> trytes_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
