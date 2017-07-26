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

// TODO const methods ?

#pragma once

#include "Core.hpp"

namespace IOTA {

namespace API {

/*
 * Extended API calls which will help do just about anything possible with IOTA. These
 * are mostly wrapper functions of Core API calls.
 * https://github.com/iotaledger/wiki/blob/master/api-proposal.md#proposed-api-calls
 */
class Extended : public Core {
public:
  Extended();
  virtual ~Extended();

public:
  /*
   * Gets all possible inputs of a seed and returns them with the total balance. This is either done
   * deterministically (by genearating all addresses until findTransactions is empty and doing
   * getBalances), or by providing a key range to use for searching through.
   */
  void getInputs();
  /*
   * Main purpose of this function is to get an array of transfer objects as input, and then prepare
   * the transfer by generating the correct bundle, as well as choosing and signing the inputs if
   * necessary (if it's a value transfer). The output of this function is an array of the raw
   * transaction data (trytes).
   */
  void prepareTransfers();
  /*
   * Generates a new address from a seed and returns the address. This is either done
   * deterministically, or by providing the index of the new address (see Questions for more
   * information about this).
   */
  void getNewAddress();
  /*
   * This function returns the bundle which is associated with a transaction. Input can by any type
   * of transaction (tail and non-tail). If there are multiple bundles (because of a replay for
   * example), it will return multiple bundles. It also does important validation checking
   * (signatures, sum, order) to ensure that the correct bundle is returned.
   */
  void getBundle();
  /*
   * Returns the transfers which are associated with a seed. The transfers are determined by either
   * calculating deterministically which addresses were already used, or by providing a list of
   * indexes to get the transfers from.
   */
  void getTransfers();
  /*
   * Takes a tail transaction hash as input, gets the bundle associated with the transaction and
   * then replays the bundle by attaching it to the tangle.
   */
  void replayTransfer();
  /*
   * Wrapper function that basically does prepareTransfers, as well as attachToTangle and finally,
   * it broadcasts and stores the transactions locally.
   */
  void sendTransfer();
  /*
   * Wrapper function that does attachToTangle and finally, it broadcasts and stores the
   * transactions locally.
   */
  void sendTrytes();
  /*
   * Wrapper function that does broadcastTransactions and storeTransactions.
   */
  void broadcastAndStore();
};

}  // namespace API

}  // namespace IOTA
