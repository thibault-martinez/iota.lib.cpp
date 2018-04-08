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

#include <iota/api/responses/get_transactions_to_approve.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetTransactionsToApprove::GetTransactionsToApprove(const Types::Trytes& trunkTransaction,
                                                   const Types::Trytes& branchTransaction)
    : trunkTransaction_(trunkTransaction), branchTransaction_(branchTransaction) {
}

GetTransactionsToApprove::GetTransactionsToApprove(const Utils::json& res) {
  deserialize(res);
}

void
GetTransactionsToApprove::deserialize(const Utils::json& res) {
  Base::deserialize(res);

  if (res.has("trunkTransaction")) {
    trunkTransaction_ = res.getString("trunkTransaction");
  }

  if (res.has("branchTransaction")) {
    branchTransaction_ = res.getString("branchTransaction");
  }
}

const Types::Trytes&
GetTransactionsToApprove::getTrunkTransaction() const {
  return trunkTransaction_;
}

void
GetTransactionsToApprove::setTrunkTransaction(const Types::Trytes& trx) {
  trunkTransaction_ = trx;
}

const Types::Trytes&
GetTransactionsToApprove::getBranchTransaction() const {
  return branchTransaction_;
}

void
GetTransactionsToApprove::setBranchTransaction(const Types::Trytes& trx) {
  branchTransaction_ = trx;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
