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

namespace IOTA {

namespace API {

Core::Core(const std::string& host, const unsigned int& port) : service_(host, port) {
}

Core::~Core() {
}

Responses::GetNodeInfo
Core::getNodeInfo() const {
  return this->service_.request<Requests::GetNodeInfo, Responses::GetNodeInfo>();
}

Responses::GetNeighbors
Core::getNeighbors() const {
  return this->service_.request<Requests::GetNeighbors, Responses::GetNeighbors>();
}

Responses::AddNeighbors
Core::addNeighbors(const std::vector<std::string>& uris) const {
  return this->service_.request<Requests::AddNeighbors, Responses::AddNeighbors>(uris);
}

Responses::RemoveNeighbors
Core::removeNeighbors(const std::vector<std::string>& uris) const {
  return this->service_.request<Requests::RemoveNeighbors, Responses::RemoveNeighbors>(uris);
}

Responses::GetTips
Core::getTips() const {
  return this->service_.request<Requests::GetTips, Responses::GetTips>();
}

Responses::FindTransactions
Core::findTransactions(const std::vector<Types::Trytes>& addresses,
                       const std::vector<Types::Trytes>& digests,
                       const std::vector<Types::Trytes>& approvees,
                       const std::vector<Types::Trytes>& bundles) const {
  return this->service_.request<Requests::FindTransactions, Responses::FindTransactions>(
      addresses, digests, approvees, bundles);
}

Responses::GetTrytes
Core::getTrytes(const std::vector<std::string>& hashes) const {
  return this->service_.request<Requests::GetTrytes, Responses::GetTrytes>(hashes);
}

Responses::GetInclusionStates
Core::getInclusionStates(const std::vector<std::string>& transactions,
                         const std::vector<std::string>& tips) const {
  return this->service_.request<Requests::GetInclusionStates, Responses::GetInclusionStates>(
      transactions, tips);
}

Responses::GetBalances
Core::getBalances(const std::vector<std::string>& addresses, const int& threshold) const {
  return this->service_.request<Requests::GetBalances, Responses::GetBalances>(addresses,
                                                                               threshold);
}

Responses::GetTransactionsToApprove
Core::getTransactionsToApprove(const int& depth) const {
  return this->service_
      .request<Requests::GetTransactionsToApprove, Responses::GetTransactionsToApprove>(depth);
}

Responses::AttachToTangle
Core::attachToTangle(const std::string& trunkTransaction, const std::string& branchTransaction,
                     const int& minWeightMagnitude, const std::vector<std::string>& trytes) const {
  return this->service_.request<Requests::AttachToTangle, Responses::AttachToTangle>(
      trunkTransaction, branchTransaction, minWeightMagnitude, trytes);
}

Responses::InterruptAttachingToTangle
Core::interruptAttachingToTangle() const {
  return this->service_
      .request<Requests::InterruptAttachingToTangle, Responses::InterruptAttachingToTangle>();
}

Responses::BroadcastTransactions
Core::broadcastTransactions(const std::vector<Types::Trytes>& trytes) const {
  return this->service_.request<Requests::BroadcastTransactions, Responses::BroadcastTransactions>(
      trytes);
}

Responses::StoreTransactions
Core::storeTransactions(const std::vector<Types::Trytes>& trytes) const {
  return this->service_.request<Requests::StoreTransactions, Responses::StoreTransactions>(trytes);
}

}  // namespace API

}  // namespace IOTA
