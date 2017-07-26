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

#include "json.hpp"

#include <iostream>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

using json = nlohmann::json;

namespace IOTA {

namespace API {

Core::Core() {
}

Core::~Core() {
}

template <typename Request, typename Response>
Response
test() {
  RestClient::init();

  RestClient::Connection* conn = new RestClient::Connection("http://iota.bitfinex.com");

  conn->AppendHeader("Content-Type", "text/json");
  RestClient::Response r = conn->post("/post", "{\"command\":\"getNodeInfo\"}");

  auto body = json::parse(r.body);

  RestClient::disable();
  Response res;
  res.deserialize(body);

  std::cout << res.getLatestSolidSubtangleMilestone() << '\n';
  return res;
}

getNodeInfoResponse
Core::getNodeInfo() {
  return getNodeInfoResponse();
}

getNeighborsResponse
Core::getNeighbors() {
  return getNeighborsResponse();
}

addNeighborsResponse
Core::addNeighbors() {
  return addNeighborsResponse();
}

removeNeighborsResponse
Core::removeNeighbors() {
  return removeNeighborsResponse();
}

getTipsResponse
Core::getTips() {
  return getTipsResponse();
}

findTransactionsResponse
Core::findTransactions() {
  return findTransactionsResponse();
}

getTrytesResponse
Core::getTrytes() {
  return getTrytesResponse();
}

getInclusionStatesResponse
Core::getInclusionStates() {
  return getInclusionStatesResponse();
}

getBalancesResponse
Core::getBalances() {
  return getBalancesResponse();
}

getTransactionsToApproveResponse
Core::getTransactionsToApprove() {
  return getTransactionsToApproveResponse();
}

attachToTangleResponse
Core::attachToTangle() {
  return attachToTangleResponse();
}

interruptAttachingToTangleResponse
Core::interruptAttachingToTangle() {
  return interruptAttachingToTangleResponse();
}

broadcastTransactionsResponse
Core::broadcastTransactions() {
  return broadcastTransactionsResponse();
}

storeTransactionsResponse
Core::storeTransactions() {
  return storeTransactionsResponse();
}

}  // namespace API

}  // namespace IOTA
