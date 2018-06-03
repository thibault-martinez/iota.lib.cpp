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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
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

#include <iota/api/core.hpp>
#include <iota/api/requests/add_neighbors.hpp>
#include <iota/api/requests/attach_to_tangle.hpp>
#include <iota/api/requests/broadcast_transactions.hpp>
#include <iota/api/requests/check_consistency.hpp>
#include <iota/api/requests/find_transactions.hpp>
#include <iota/api/requests/get_balances.hpp>
#include <iota/api/requests/get_inclusion_states.hpp>
#include <iota/api/requests/get_neighbors.hpp>
#include <iota/api/requests/get_node_info.hpp>
#include <iota/api/requests/get_tips.hpp>
#include <iota/api/requests/get_transactions_to_approve.hpp>
#include <iota/api/requests/get_trytes.hpp>
#include <iota/api/requests/interrupt_attaching_to_tangle.hpp>
#include <iota/api/requests/remove_neighbors.hpp>
#include <iota/api/requests/store_transactions.hpp>
#include <iota/api/requests/were_addresses_spent_from.hpp>
#include <iota/api/responses/add_neighbors.hpp>
#include <iota/api/responses/attach_to_tangle.hpp>
#include <iota/api/responses/check_consistency.hpp>
#include <iota/api/responses/find_transactions.hpp>
#include <iota/api/responses/get_balances.hpp>
#include <iota/api/responses/get_inclusion_states.hpp>
#include <iota/api/responses/get_neighbors.hpp>
#include <iota/api/responses/get_node_info.hpp>
#include <iota/api/responses/get_tips.hpp>
#include <iota/api/responses/get_transactions_to_approve.hpp>
#include <iota/api/responses/get_trytes.hpp>
#include <iota/api/responses/remove_neighbors.hpp>
#include <iota/api/responses/were_addresses_spent_from.hpp>
#include <iota/crypto/pow.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/neighbor.hpp>
#include <iota/models/transaction.hpp>
#include <iota/utils/stop_watch.hpp>

namespace IOTA {

namespace API {

Core::Core(const std::string& host, const uint16_t& port, bool localPow, int timeout)
    : service_(host, port, timeout), localPow_(localPow) {
}

Responses::GetNodeInfo
Core::getNodeInfo() const {
  return service_.request<Requests::GetNodeInfo, Responses::GetNodeInfo>();
}

Responses::GetNeighbors
Core::getNeighbors() const {
  return service_.request<Requests::GetNeighbors, Responses::GetNeighbors>();
}

Responses::AddNeighbors
Core::addNeighbors(const std::vector<std::string>& uris) const {
  return service_.request<Requests::AddNeighbors, Responses::AddNeighbors>(uris);
}

Responses::RemoveNeighbors
Core::removeNeighbors(const std::vector<std::string>& uris) const {
  return service_.request<Requests::RemoveNeighbors, Responses::RemoveNeighbors>(uris);
}

Responses::GetTips
Core::getTips() const {
  return service_.request<Requests::GetTips, Responses::GetTips>();
}

Responses::FindTransactions
Core::findTransactions(const std::vector<Models::Address>& addresses,
                       const std::vector<Models::Tag>&     tags,
                       const std::vector<Types::Trytes>&   approvees,
                       const std::vector<Types::Trytes>&   bundles) const {
  //! skip request if no input, simply return empty
  if (addresses.empty() && tags.empty() && approvees.empty() && bundles.empty()) {
    return Responses::FindTransactions();
  }

  return service_.request<Requests::FindTransactions, Responses::FindTransactions>(
      addresses, tags, approvees, bundles);
}

Responses::GetTrytes
Core::getTrytes(const std::vector<Types::Trytes>& hashes) const {
  return service_.request<Requests::GetTrytes, Responses::GetTrytes>(hashes);
}

Responses::GetInclusionStates
Core::getInclusionStates(const std::vector<Types::Trytes>& transactions,
                         const std::vector<Types::Trytes>& tips) const {
  if (transactions.empty()) {
    return Responses::GetInclusionStates{};
  }

  if (tips.empty()) {
    throw Errors::IllegalState("Empty list of tips");
  }

  return service_.request<Requests::GetInclusionStates, Responses::GetInclusionStates>(transactions,
                                                                                       tips);
}

Responses::GetBalances
Core::getBalances(const std::vector<Models::Address>& addresses, const int& threshold,
                  const std::vector<Types::Trytes>& tips) const {
  return service_.request<Requests::GetBalances, Responses::GetBalances>(addresses, threshold,
                                                                         tips);
}

Responses::GetTransactionsToApprove
Core::getTransactionsToApprove(const int& depth, const Types::Trytes& reference) const {
  return service_.request<Requests::GetTransactionsToApprove, Responses::GetTransactionsToApprove>(
      depth, reference);
}

Responses::AttachToTangle
Core::attachToTangle(const Types::Trytes& trunkTransaction, const Types::Trytes& branchTransaction,
                     const int&                        minWeightMagnitude,
                     const std::vector<Types::Trytes>& trytes) const {
  if (localPow_) {
    Crypto::Pow                pow;
    std::vector<Types::Trytes> resultTrytes;
    Types::Trytes              prevTx;
    for (auto& txTrytes : trytes) {
      auto tx = IOTA::Models::Transaction(txTrytes);

      tx.setTrunkTransaction(prevTx.empty() ? trunkTransaction : prevTx);
      tx.setBranchTransaction(prevTx.empty() ? branchTransaction : trunkTransaction);
      tx.setAttachmentTimestamp(Utils::StopWatch::now().count());
      tx.setAttachmentTimestampLowerBound(0);
      tx.setAttachmentTimestampUpperBound(3812798742493L);
      tx.setNonce(pow(tx.toTrytes(), minWeightMagnitude));

      if (tx.getTag().empty()) {
        tx.setTag(tx.getObsoleteTag());
      }

      resultTrytes.emplace_back(tx.toTrytes());
      prevTx = tx.getHash();
    }
    return Responses::AttachToTangle(resultTrytes);
  }
  return service_.request<Requests::AttachToTangle, Responses::AttachToTangle>(
      trunkTransaction, branchTransaction, minWeightMagnitude, trytes);
}

Responses::Base
Core::interruptAttachingToTangle() const {
  return service_.request<Requests::InterruptAttachingToTangle, Responses::Base>();
}

Responses::Base
Core::broadcastTransactions(const std::vector<Types::Trytes>& trytes) const {
  return service_.request<Requests::BroadcastTransactions, Responses::Base>(trytes);
}

Responses::Base
Core::storeTransactions(const std::vector<Types::Trytes>& trytes) const {
  return service_.request<Requests::StoreTransactions, Responses::Base>(trytes);
}

Responses::WereAddressesSpentFrom
Core::wereAddressesSpentFrom(const std::vector<Models::Address>& addresses) const {
  return service_.request<Requests::WereAddressesSpentFrom, Responses::WereAddressesSpentFrom>(
      addresses);
}

Responses::CheckConsistency
Core::checkConsistency(const std::vector<Types::Trytes>& tails) const {
  return service_.request<Requests::CheckConsistency, Responses::CheckConsistency>(tails);
}

}  // namespace API

}  // namespace IOTA
