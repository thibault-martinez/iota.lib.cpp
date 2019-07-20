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

#pragma once

#include <iota/api/responses/fwd.hpp>
#include <iota/api/service.hpp>
#include <iota/models/address.hpp>
#include <iota/models/tag.hpp>

namespace IOTA {

namespace API {

/**
 * Strict implementation of IOTA core API commands.
 *
 * https://iota.readme.io/reference
 *
 */
class Core {
public:
  /**
   * Full init ctor.
   *
   * @param host The host of the node to connect to.
   * @param port The port of the node to connect to.
   * @param localPow Whether to do local or remote proof of work.
   * @param timeout Timeout for the requests.
   */
  explicit Core(const std::string& host, const uint16_t& port, bool localPow = true,
                int timeout = 60, const std::string& user = "", const std::string& pass = "");
  /**
   * Default dtor.
   */
  virtual ~Core() = default;

public:
  /**
   * Returns information about your node.
   *
   * https://iota.readme.io/reference#getnodeinfo
   *
   * @return The response.
   */
  Responses::GetNodeInfo getNodeInfo() const;

  /**
   * Returns the set of neighbors you are connected with, as well as their activity count. The
   * activity counter is reset after restarting IRI.
   *
   * https://iota.readme.io/reference#getneighborsactivity
   *
   * @return The response.
   */
  Responses::GetNeighbors getNeighbors() const;

  /**
   * Add a list of neighbors to your node. It should be noted that this is only temporary, and the
   * added neighbors will be removed from your set of neighbors after you relaunch IRI.
   *
   * https://iota.readme.io/reference#addneighors
   *
   * @param uris List of URI elements.
   *
   * @return The response.
   */
  Responses::AddNeighbors addNeighbors(const std::vector<std::string>& uris) const;

  /**
   * Removes a list of neighbors to your node. This is only temporary, and if you have your
   * neighbors added via the command line, they will be retained after you restart your node.
   *
   * https://iota.readme.io/reference#removeneighors
   *
   * @param uris List of URI elements.
   *
   * @return The response.
   */
  Responses::RemoveNeighbors removeNeighbors(const std::vector<std::string>& uris) const;

  /**
   * Returns the list of tips.
   *
   * https://iota.readme.io/reference#gettips
   *
   * @return The response.
   */
  Responses::GetTips getTips() const;

  /**
   * Find the transactions which match the specified input and return. All input values are lists,
   * for which a list of return values (transaction hashes), in the same order, is returned for all
   * individual elements. The input fields can either be bundles, addresses, tags or approvees.
   * Using multiple of these input fields returns the intersection of the values.
   *
   * https://iota.readme.io/reference#findtransactions
   *
   * @param addresses List of addresses.
   * @param tags List of transaction tags.
   * @param approvees List of approvees of a transaction.
   * @param bundles List of bundle hashes. The hashes need to be extended to 81chars by padding the
   * hash with 9's.
   *
   * @return The response.
   */
  Responses::FindTransactions findTransactions(const std::vector<Models::Address>& addresses,
                                               const std::vector<Models::Tag>&     tags,
                                               const std::vector<Types::Trytes>&   approvees,
                                               const std::vector<Types::Trytes>&   bundles) const;

  /**
   * Returns the raw transaction data (trytes) of a specific transaction. These trytes can then be
   * easily converted into the actual transaction object. See utility functions for more details.
   *
   * https://iota.readme.io/reference#gettrytes
   *
   * @param hashes List of transaction hashes of which you want to get trytes from.
   *
   * @return The response.
   */
  Responses::GetTrytes getTrytes(const std::vector<Types::Trytes>& hashes) const;

  /**
   * Get the inclusion states of a set of transactions. This is for determining if a transaction was
   * accepted and confirmed by the network or not. You can search for multiple tips (and thus,
   * milestones) to get past inclusion states of transactions. This API call simply returns a list
   * of boolean values in the same order as the transaction list you submitted, thus you get a
   * true/false whether a transaction is confirmed or not.
   *
   * https://iota.readme.io/reference#getinclusionstates
   *
   * @param transactions List of transactions you want to get the inclusion state for.
   * @param tips List of tips (including milestones) you want to search for the inclusion state.
   *
   * @return The response.
   */
  Responses::GetInclusionStates getInclusionStates(const std::vector<Types::Trytes>& transactions,
                                                   const std::vector<Types::Trytes>& tips) const;

  /**
   * Similar to getInclusionStates. It returns the confirmed balance which a list of addresses have
   * at the latest confirmed milestone. In addition to the balances, it also returns the milestone
   * as well as the index with which the confirmed balance was determined. The balances is returned
   * as a list in the same order as the addresses were provided as input.
   *
   * https://iota.readme.io/reference#getbalances
   *
   * @param addresses List of addresses you want to get the confirmed balance from.
   * @param threshold Confirmation threshold, should be set to 100.
   * @param tips List of hashes, if present calculate the balance of addresses from the PoV of these
   * transactions, can be used to chain bundles.
   *
   * @return The response.
   */
  Responses::GetBalances getBalances(const std::vector<Models::Address>& addresses,
                                     const int&                          threshold = 100,
                                     const std::vector<Types::Trytes>&   tips      = {}) const;

  /**
   * Tip selection which returns trunkTransaction and branchTransaction. The input value is depth,
   * which basically determines how many bundles to go back to for finding the transactions to
   * approve. The higher your depth value, the more "babysitting" you do for the network (as you
   * have to confirm more transactions).
   *
   * https://iota.readme.io/reference#getbalances
   *
   * @param depth Number of bundles to go back to determine the transactions for approval.
   * @param reference Hash of transaction to start random-walk from, used to make sure the tips
   * returned reference a given transaction in their past.
   *
   * @return The response.
   */
  Responses::GetTransactionsToApprove getTransactionsToApprove(
      const int& depth, const Types::Trytes& reference = "") const;

  /**
   * Attaches the specified transactions (trytes) to the Tangle by doing Proof of Work. You need to
   * supply branchTransaction as well as trunkTransaction (basically the tips which you're going to
   * validate and reference with this transaction) - both of which you'll get through the
   * getTransactionsToApprove API call.
   * The returned value is a different set of tryte values which you can input into
   * broadcastTransactions and storeTransactions. The returned tryte value, the last 243 trytes
   * basically consist of the: trunkTransaction + branchTransaction + nonce. These are valid trytes
   * which are then accepted by the network.
   *
   * https://iota.readme.io/reference#attachtotangle
   *
   * @param trunkTransaction Trunk transaction to approve.
   * @param branchTransaction Branch transaction to approve.
   * @param minWeightMagnitude Proof of Work intensity. Minimum value is 18.
   * @param trytes List of trytes (raw transaction data) to attach to the tangle.
   *
   * @return The response.
   */
  Responses::AttachToTangle attachToTangle(const Types::Trytes&              trunkTransaction,
                                           const Types::Trytes&              branchTransaction,
                                           const int&                        minWeightMagnitude,
                                           const std::vector<Types::Trytes>& trytes) const;

  /**
   * Interrupts and completely aborts the attachToTangle process.
   *
   * https://iota.readme.io/reference#interruptattachingtotangle
   *
   * @return The response.
   */
  Responses::Base interruptAttachingToTangle() const;

  /**
   * Broadcast a list of transactions to all neighbors. The input trytes for this call are provided
   * by attachToTangle.
   *
   * https://iota.readme.io/reference#broadcasttransactions
   *
   * @param trytes List of raw data of transactions to be rebroadcast.
   *
   * @return The response.
   */
  Responses::Base broadcastTransactions(const std::vector<Types::Trytes>& trytes) const;

  /**
   * Store transactions into the local storage. The trytes to be used for this call are returned by
   * attachToTangle.
   *
   * https://iota.readme.io/reference#storetransactions
   *
   * @param trytes List of raw data of transactions to be rebroadcast.
   *
   * @return The response.
   */
  Responses::Base storeTransactions(const std::vector<Types::Trytes>& trytes) const;

  /*
   * Used to ensure tail resolves to a consistent ledger which is necessary to validate before
   * attempting promotion. Checks transaction hashes for promotability.
   *
   * This is called with a pending transaction (or more of them) and it will tell you if it is still
   * possible for this transaction (or all the transactions simultaneously if you give more than
   * one) to be confirmed, or not (because it conflicts with another already confirmed transaction).
   *
   * https://iota.readme.io/reference#checkconsistency
   *
   * @param tails Tails to check consistency.
   *
   * @return The response.
   */
  Responses::CheckConsistency checkConsistency(const std::vector<Types::Trytes>& tails) const;

protected:
    /**
     * Check if a list of addresses was ever spent from, in the current epoch, or in previous epochs.
     *
     * https://iota.readme.io/reference#wereaddressesspentfrom
     *
     * From iota.lib.js:
     * `wereAddressesSpentFrom` command is a temporary measure to prevent loss of funds,
     * when security assumptions are ignored by developers or wallet users.
     * It's being used internally by `getNewAddress()`.
     * Avoid developing programs that rely on this method.
     *
     * @param addresses List of addresses you want to check if they were spent from.
     *
     * @return The response.
     */
    Responses::WereAddressesSpentFrom wereAddressesSpentFrom(
        const std::vector<Models::Address>& addresses) const;

private:
  /**
   * Internal service for api calls.
   */
  Service service_;
  /**
   * Defines whether PoW is done locally or remotely.
   */
  bool localPow_;
};

}  // namespace API

}  // namespace IOTA
