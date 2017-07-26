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

// TODO are the method const ?
// TODO forward declarations here ? file ?

#pragma once

#include "getNodeInfoResponse.hpp"

namespace IOTA {

namespace API {

class getNeighborsResponse;
class addNeighborsResponse;
class removeNeighborsResponse;
class getTipsResponse;
class findTransactionsResponse;
class getTrytesResponse;
class getInclusionStatesResponse;
class getBalancesResponse;
class getTransactionsToApproveResponse;
class attachToTangleResponse;
class interruptAttachingToTangleResponse;
class broadcastTransactionsResponse;
class storeTransactionsResponse;

class Core {
public:
  Core();
  virtual ~Core();

public:
  getNodeInfoResponse                getNodeInfo();
  getNeighborsResponse               getNeighbors();
  addNeighborsResponse               addNeighbors();
  removeNeighborsResponse            removeNeighbors();
  getTipsResponse                    getTips();
  findTransactionsResponse           findTransactions();
  getTrytesResponse                  getTrytes();
  getInclusionStatesResponse         getInclusionStates();
  getBalancesResponse                getBalances();
  getTransactionsToApproveResponse   getTransactionsToApprove();
  attachToTangleResponse             attachToTangle();
  interruptAttachingToTangleResponse interruptAttachingToTangle();
  broadcastTransactionsResponse      broadcastTransactions();
  storeTransactionsResponse          storeTransactions();

private:
};

}  // namespace API

}  // namespace IOTA
