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

#include "Core.hpp"
#include "addNeighborsRequest.hpp"
#include "attachToTangleRequest.hpp"
#include "broadcastTransactionsRequest.hpp"
#include "findTransactionsRequest.hpp"
#include "getBalancesRequest.hpp"
#include "getInclusionStatesRequest.hpp"
#include "getNeighborsRequest.hpp"
#include "getNodeInfoRequest.hpp"
#include "getTipsRequest.hpp"
#include "getTransactionsToApproveRequest.hpp"
#include "getTrytesRequest.hpp"
#include "interruptAttachingToTangleRequest.hpp"
#include "removeNeighborsRequest.hpp"
#include "storeTransactionsRequest.hpp"

namespace IOTA {

namespace API {

Core::Core(const std::string& host, const unsigned int& port) : service_(host, port) {
}

Core::~Core() {
}

getNodeInfoResponse
Core::getNodeInfo() {
  return this->service_.request<getNodeInfoRequest, getNodeInfoResponse>();
}

getNeighborsResponse
Core::getNeighbors() {
  return this->service_.request<getNeighborsRequest, getNeighborsResponse>();
}

addNeighborsResponse
Core::addNeighbors(const std::vector<std::string>& uris) {
  return this->service_.request<addNeighborsRequest, addNeighborsResponse>(uris);
}

removeNeighborsResponse
Core::removeNeighbors(const std::vector<std::string>& uris) {
  return this->service_.request<removeNeighborsRequest, removeNeighborsResponse>(uris);
}

getTipsResponse
Core::getTips() {
  return this->service_.request<getTipsRequest, getTipsResponse>();
}

findTransactionsResponse
Core::findTransactions() {
  return this->service_.request<findTransactionsRequest, findTransactionsResponse>();
}

getTrytesResponse
Core::getTrytes(const std::vector<std::string>& hashes) {
  return this->service_.request<getTrytesRequest, getTrytesResponse>(hashes);
}

getInclusionStatesResponse
Core::getInclusionStates(const std::vector<std::string>& transactions,
                         const std::vector<std::string>& tips) {
  return this->service_.request<getInclusionStatesRequest, getInclusionStatesResponse>(transactions,
                                                                                       tips);
}

getBalancesResponse
Core::getBalances(const std::vector<std::string>& addresses, const int& threshold) {
  return this->service_.request<getBalancesRequest, getBalancesResponse>(addresses, threshold);
}

getTransactionsToApproveResponse
Core::getTransactionsToApprove(const int& depth) {
  return this->service_.request<getTransactionsToApproveRequest, getTransactionsToApproveResponse>(
      depth);
}

attachToTangleResponse
Core::attachToTangle(const std::string& trunkTransaction, const std::string& branchTransaction,
                     const int& minWeightMagnitude, const std::vector<std::string>& trytes) {
  return this->service_.request<attachToTangleRequest, attachToTangleResponse>(
      trunkTransaction, branchTransaction, minWeightMagnitude, trytes);
}

interruptAttachingToTangleResponse
Core::interruptAttachingToTangle() {
  return this->service_
      .request<interruptAttachingToTangleRequest, interruptAttachingToTangleResponse>();
}

broadcastTransactionsResponse
Core::broadcastTransactions(const std::vector<std::string>& trytes) {
  return this->service_.request<broadcastTransactionsRequest, broadcastTransactionsResponse>(
      trytes);
}

storeTransactionsResponse
Core::storeTransactions(const std::vector<std::string>& trytes) {
  return this->service_.request<storeTransactionsRequest, storeTransactionsResponse>(trytes);
}

}  // namespace API

}  // namespace IOTA
