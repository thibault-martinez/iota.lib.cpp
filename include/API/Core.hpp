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

#pragma once

#include <API/Responses/addNeighborsResponse.hpp>
#include <API/Responses/attachToTangleResponse.hpp>
#include <API/Responses/broadcastTransactionsResponse.hpp>
#include <API/Responses/findTransactionsResponse.hpp>
#include <API/Responses/getBalancesResponse.hpp>
#include <API/Responses/getInclusionStatesResponse.hpp>
#include <API/Responses/getNeighborsResponse.hpp>
#include <API/Responses/getNodeInfoResponse.hpp>
#include <API/Responses/getTipsResponse.hpp>
#include <API/Responses/getTransactionsToApproveResponse.hpp>
#include <API/Responses/getTrytesResponse.hpp>
#include <API/Responses/interruptAttachingToTangleResponse.hpp>
#include <API/Responses/removeNeighborsResponse.hpp>
#include <API/Responses/storeTransactionsResponse.hpp>
#include <API/Service.hpp>

namespace IOTA {

namespace API {

/*
 * Strict implementation of IOTA core API commands.
 * https://iota.readme.io/docs/getting-started
 */
class Core {
public:
  Core(const std::string& host, const unsigned int& port);
  virtual ~Core();

  // public:
  //   template <typename Request, typename Response, typename... Args>
  //   Response test(Args&&... args);

public:
  /*
   * Returns information about your node.
   * https://iota.readme.io/docs/getnodeinfo
   */
  getNodeInfoResponse getNodeInfo();
  /*
   * Returns the set of neighbors you are connected with, as well as their activity count. The
   * activity counter is reset after restarting IRI.
   * https://iota.readme.io/docs/getneighborsactivity
   */
  getNeighborsResponse getNeighbors();
  /*
   * Add a list of neighbors to your node. It should be noted that this is only temporary, and the
   * added neighbors will be removed from your set of neighbors after you relaunch IRI.
   * https://iota.readme.io/docs/addneighors
   */
  addNeighborsResponse addNeighbors(const std::vector<std::string>& uris);
  /*
   * Removes a list of neighbors to your node. This is only temporary, and if you have your
   * neighbors added via the command line, they will be retained after you restart your node.
   * https://iota.readme.io/docs/removeneighors
   */
  removeNeighborsResponse removeNeighbors(const std::vector<std::string>& uris);
  /*
   * Returns the list of tips.
   * https://iota.readme.io/docs/gettips
   */
  getTipsResponse getTips();
  /*
   * Find the transactions which match the specified input and return. All input values are lists,
   * for which a list of return values (transaction hashes), in the same order, is returned for
   * all individual elements. The input fields can either be bundles, addresses, tags or
   * approvees. Using multiple of these input fields returns the intersection of the values.
   * https://iota.readme.io/docs/findtransactions
   */
  findTransactionsResponse findTransactions();
  /*
   * Returns the raw transaction data (trytes) of a specific transaction. These trytes can then be
   * easily converted into the actual transaction object. See utility functions for more details.
   * https://iota.readme.io/docs/gettrytes
   */
  getTrytesResponse getTrytes(const std::vector<std::string>& hashes);
  /*
   * Get the inclusion states of a set of transactions. This is for determining if a transaction
   * was accepted and confirmed by the network or not. You can search for multiple tips (and thus,
   * milestones) to get past inclusion states of transactions.
   * This API call simply returns a list of boolean values in the same order as the transaction
   * list you submitted, thus you get a true/false whether a transaction is confirmed or not.
   * https://iota.readme.io/docs/getinclusionstates
   */
  getInclusionStatesResponse getInclusionStates(const std::vector<std::string>& transactions,
                                                const std::vector<std::string>& tips);
  /*
   * Similar to getInclusionStates. It returns the confirmed balance which a list of addresses
   * have at the latest confirmed milestone. In addition to the balances, it also returns the
   * milestone as well as the index with which the confirmed balance was determined. The balances
   * is returned as a list in the same order as the addresses were provided as input.
   * https://iota.readme.io/docs/getbalances
   */
  getBalancesResponse getBalances(const std::vector<std::string>& addresses, const int& threshold);
  /*
   * Tip selection which returns trunkTransaction and branchTransaction. The input value is depth,
   * which basically determines how many bundles to go back to for finding the transactions to
   * approve. The higher your depth value, the more "babysitting" you do for the network (as you
   * have to confirm more transactions).
   * https://iota.readme.io/docs/gettransactionstoapprove
   */
  getTransactionsToApproveResponse getTransactionsToApprove(const int& depth);
  /*
   * Attaches the specified transactions (trytes) to the Tangle by doing Proof of Work. You need
   * to supply branchTransaction as well as trunkTransaction (basically the tips which you're
   * going to validate and reference with this transaction) - both of which you'll get through the
   * getTransactionsToApprove API call.
   * The returned value is a different set of tryte values which you can input into
   * broadcastTransactions and storeTransactions. The returned tryte value, the last 243 trytes
   * basically consist of the: trunkTransaction + branchTransaction + nonce. These are valid
   * trytes which are then accepted by the network. https://iota.readme.io/docs/attachtotangle
   */
  attachToTangleResponse attachToTangle(const std::string&              trunkTransaction,
                                        const std::string&              branchTransaction,
                                        const int&                      minWeightMagnitude,
                                        const std::vector<std::string>& trytes);
  /*
   * Interrupts and completely aborts the attachToTangle process.
   * https://iota.readme.io/docs/interruptattachingtotangle
   */
  interruptAttachingToTangleResponse interruptAttachingToTangle();
  /*
   * Broadcast a list of transactions to all neighbors. The input trytes for this call are
   * provided by attachToTangle. https://iota.readme.io/docs/broadcasttransactions
   */
  broadcastTransactionsResponse broadcastTransactions(const std::vector<std::string>& trytes);
  /*
   * Store transactions into the local storage. The trytes to be used for this call are returned
   * by attachToTangle. https://iota.readme.io/docs/storetransactions
   */
  storeTransactionsResponse storeTransactions(const std::vector<std::string>& trytes);

private:
  Service service_;
};

}  // namespace API

}  // namespace IOTA
