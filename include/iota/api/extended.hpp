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

#include <iota/api/core.hpp>
#include <iota/models/fwd.hpp>
#include <iota/utils/stop_watch.hpp>

namespace IOTA {

namespace API {

/**
 * Extended API calls which will help do just about anything possible with IOTA. These
 * are mostly wrapper functions of Core API calls.
 * https://github.com/iotaledger/wiki/blob/master/api-proposal.md#proposed-api-calls
 */
class Extended : public Core {
public:
  /**
   * Full init ctor.
   *
   * @param host The host of the node to connect to.
   * @param port The port of the node to connect to.
   * @param localPow Whether to do local or remote proof of work.
   * @param timeout Timeout for the requests.
   */
  Extended(const std::string& host, const uint16_t& port, bool localPow = true, int timeout = 60);
  /**
   * Default dtor.
   */
  virtual ~Extended() = default;

public:
  /**
   * Gets all possible inputs of a seed and returns them with the total balance. This is either done
   * deterministically (by genearating all addresses until findTransactions is empty and doing
   * getBalances), or by providing a key range to use for searching through.
   *
   * @param seed      Seed to be used for address generation.
   * @param start     Starting key index for address generation (included).
   * @param end       Ending key index for address generation (excluded).
   * @param threshold Min balance required, 0 for unlimited.
   *
   * @return The inputs.
   */
  Responses::GetBalancesAndFormat getInputs(const Models::Seed& seed, const int32_t& start = 0,
                                            const int32_t& end       = 0,
                                            const int64_t& threshold = 0) const;

  /**
   * Gets the balances for the given addresses.
   *
   * @param addresses The addresses for which balance need to be retrieved
   * @param threshold If set to 0, fetch balance for all input addresses. Otherwise, keep fetching
   *                  until the threshold is reached. If threshold is > 0 and is not reached,
   *                  Not Enough Balance exception is raised.
   *
   * @return Addresses for which balance was retrieved, and their balance.
   **/
  Responses::GetBalancesAndFormat getBalancesAndFormat(
      const std::vector<Models::Address>& addresses, const int64_t& threshold = 0) const;

  /**
   * Generates a new address from a seed.
   * This is either done deterministically, or by providing the index of the new remainderAddress.
   *
   * @param seed      Seed to be used for address generation.
   * @param index     Key index to start search from. If the index is provided, the generation of
   * the address is not deterministic.
   * @param total     Total number of addresses to generate. If set to 0, generates from index until
   * it finds an address without any transaction.
   * @param returnAll If <code>true</code>, it returns all addresses which were deterministically
   * generated. Otherwise, returns only the last generated address.
   *
   * @return Array of generated addresses.
   */
  Responses::GetNewAddresses getNewAddresses(const Models::Seed& seed, const uint32_t& index = 0,
                                             const int32_t& total     = 0,
                                             bool           returnAll = false) const;

  /**
   * Traverse the Bundle by going down the trunkTransactions until
   * the bundle hash of the transaction is no longer the same. In case the input
   * transaction hash is not a tail, return an error.
   *
   * @param trunkTx    Hash of a trunk or a tail transaction of a bundle.
   *
   * @return Bundle corresponding to tail transaction.
   */
  Models::Bundle traverseBundle(const Types::Trytes& trunkTx) const;

  /**
   * Traverse multiple bundles. Similar to traverseBundle but with multiple trunk trxs.
   *
   * @param trunkTrxs   Hashes of trunk or a tail transactions of bundles.
   * @param throwOnFail if true, throw an exception if one of the bundle is invalid. Otherwise,
   * return an empty bundle instead and keeps processing the other bundles
   *
   * @return Bundles corresponding to tail transactions.
   */
  std::vector<Models::Bundle> traverseBundles(const std::vector<Types::Trytes>& trunkTrxs,
                                              bool throwOnFail = true) const;

  /**
   * Verify the integrity of a bundle.
   * Does validation of signatures, total sum as well as bundle ordering.
   * Throws an exception in case of invalid bundle.
   *
   * @param bundle  The bundle to verify
   */
  static void verifyBundle(const Models::Bundle& bundle);

  /**
   * Get bundles corresponding to the given addresses.
   *
   * @param addresses       List of addresses for which to find the bundle objects.
   * @param withInclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   *
   * @return Bundles.
   */
  std::vector<Models::Bundle> bundlesFromAddresses(const std::vector<Models::Address>& addresses,
                                                   bool withInclusionStates = false) const;

  /**
   * Lookup transactions for given addresses and return a list of transaction objects
   *
   * @param addresses Addresses for which transactions objects should be found.
   *
   * @return Transactions.
   */
  std::vector<Models::Transaction> findTransactionObjects(
      const std::vector<Models::Address>& addresses) const;

  /**
   * Lookup transactions for given transaction hashes and return a list of transaction objects
   * If a specific transaction does not exist, return valid transaction tryte 9-filled
   *
   * @param trx_hashes Hashes of the transactions to find
   *
   * @return Transactions.
   **/
  std::vector<Models::Transaction> getTransactionsObjects(
      const std::vector<IOTA::Types::Trytes>& trx_hashes) const;

  /**
   * Same as findTransactionObjects, but based on bundle hash
   *
   * @param input Bundle hashes
   *
   * @return Transactions.
   **/
  std::vector<Models::Transaction> findTransactionObjectsByBundle(
      const std::vector<IOTA::Types::Trytes>& input) const;

  /**
   * Get inclusion states for the given transactions.
   *
   * @param hashes Hash of the transactions for which the inclusion states will be retrieved.
   *
   * @return Inclusion states.
   */
  Responses::GetInclusionStates getLatestInclusion(const std::vector<Types::Trytes>& hashes) const;

  /**
   * Prepare the transfer by generating the correct bundle, as well as choosing and signing the
   * inputs if necessary (if it's a value transfer). The output of this function is an array of the
   * raw transaction data (trytes).
   *
   * @param seed      Seed to be used for address generation.
   * @param transfers Array of transfer objects.
   * @param remainder If this address will be used for sending the remainder value to. Leave empty
   * to automatically choose one.
   * @param inputs    The inputs. Leave empty to automatically find inputs based on the seed.
   * @param validateInputs Whether or not to validate the balances of the provided inputs.
   *
   * @return Returns bundle trytes.
   */
  std::vector<Types::Trytes> prepareTransfers(const Models::Seed&                  seed,
                                              const std::vector<Models::Transfer>& transfers,
                                              const Models::Address&               remainder = {},
                                              const std::vector<Models::Address>&  inputs    = {},
                                              bool validateInputs = true) const;

  /**
   * Gets the associated bundle of a tail transaction.
   * Does validation of signatures, total sum as well as bundle ordering.
   * Basically the same as traverseBundle, but with bundle validity check (signature, order, value
   * and hash check).
   *
   * @param transaction Hash of a tail transaction.
   *
   * @return Transactions of the bundle corresponding to the input trx
   */
  Responses::GetBundle getBundle(const Types::Trytes& transaction) const;

  /**
   * Returns the transfers which are associated with a seed. The transfers are determined by either
   * calculating deterministically which addresses were already used, or by providing a list of
   * indexes to get the transfers from.
   *
   * @param seed            Seed to be used for address generation.
   * @param start           Starting key index for address generation (included).
   * @param end             Ending key index for address generation (excluded).
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   *
   * @return Bundle of transfers.
   */
  Responses::GetTransfers getTransfers(const Models::Seed& seed, int start = 0, int end = 0,
                                       bool inclusionStates = false) const;

  /**
   * Wrapper function that basically does prepareTransfers, as well as attachToTangle and finally,
   * it broadcasts and stores the transactions.
   *
   * @param seed               Seed to be used for address generation.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   * @param transfers          Array of transfer objects.
   * @param inputs             List of inputs used for funding the transfer.
   * @param inputs             Inputs. Leave empty to automatically find inputs based on the seed.
   * @param remainder If this address will be used for sending the remainder value to. Leave empty
   * to automatically choose one.
   *
   * @return Array of Transaction objects.
   */
  Responses::SendTransfer sendTransfer(const Models::Seed& seed, int depth, int minWeightMagnitude,
                                       std::vector<Models::Transfer>&      transfers,
                                       const std::vector<Models::Address>& inputs    = {},
                                       const Models::Address&              remainder = {}) const;

  /**
   * Wrapper function that gets transactions to approve, attaches to Tangle, broadcasts and stores.
   *
   * @param trytes             The trytes of the transactions to be attached.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   *
   * @return Transactions objects.
   */
  std::vector<Models::Transaction> sendTrytes(const std::vector<Types::Trytes>& trytes,
                                              const unsigned int&               depth,
                                              const unsigned int& minWeightMagnitude) const;

  /**
   * Wrapper function that does broadcastTransactions and storeTransactions.
   *
   * @param trytes Trytes to be broadcasted and stored.
   *
   * @return The response.
   */
  Responses::Base broadcastAndStore(const std::vector<Types::Trytes>& trytes) const;

  /**
   * Find the transactions which match the specified addresses.
   *
   * @param addresses The list of addresses.
   *
   * @return the list of transactions which have the specified address as an input/output field.
   */
  Responses::FindTransactions findTransactionsByAddresses(
      const std::vector<Models::Address>& addresses) const;

  /**
   * Find the transactions which match the specified tags.
   *
   * @param tags The list of transaction tags.
   *
   * @return the list of transactions which contain the specified tag value.
   */
  Responses::FindTransactions findTransactionsByTags(const std::vector<Models::Tag>& tags) const;

  /**
   * Find the transactions which match the specified approvees.
   *
   * @param approvees The list of approvees of a transaction.
   *
   * @return the list of transaction which reference (i.e. confirm) the specified transactions.
   */
  Responses::FindTransactions findTransactionsByApprovees(
      const std::vector<Types::Trytes>& approvees) const;

  /**
   * Find the transactions which match the specified bundles.
   *
   * @param bundles The list of bundle hashes.
   *
   * @return the list of transactions which contain the specified bundle hash.
   */
  Responses::FindTransactions findTransactionsByBundles(
      const std::vector<Types::Trytes>& bundles) const;

  /**
   * Get inputs, transfers and balance of a given account.
   *
   * @param seed            Seed to be used for address generation.
   * @param start           Starting key index for address generation (included).
   * @param end             Ending key index for address generation (excluded).
   * deterministically generated. Otherwise, returns only the last generated address.
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   * @param threshold       Min balance required. 0 to skip.
   *
   * @return Account data.
   */
  Responses::GetAccountData getAccountData(const Models::Seed& seed, int start = 0, int end = 0,
                                           bool inclusionStates = true, long threshold = 0) const;

  /**
   * Add remainder transaction to the given bundle
   *
   * @param seed               Seed to be used for address generation.
   * @param inputs             Inputs used for funding the transfer.
   * @param bundle             To be populated.
   * @param tag                Tag of the transaction
   * @param totalValue         The total value to be transfered.
   * @param remainderAddress   If this address will be used for sending the remainder value to.
   * @param signatureFragments The signature fragments.
   *
   * @return Vector of trytes.
   */
  std::vector<Types::Trytes> addRemainder(
      const Models::Seed& seed, const std::vector<Models::Address>& inputs, Models::Bundle& bundle,
      const Models::Tag& tag, int64_t totalValue, const Models::Address& remainderAddress,
      const std::vector<Types::Trytes>& signatureFragments = {}) const;

  /**
   * Replays a transfer by doing Proof of Work again.
   *
   * @param transaction        The transaction.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   *
   * @return Analyzed Transaction objects.
   */
  Responses::ReplayBundle replayBundle(const Types::Trytes& transaction, int depth,
                                       int minWeightMagnitude) const;

  /**
   * Prepares transfer by generating the bundle with the corresponding cosigner transactions.
   * Does not contain signatures.
   *
   * @param inputAddress     Array of input addresses.
   * @param remainderAddress Has to be generated by the cosigners before initiating the transfer,
   * can be empty if fully spent.
   * @param transfers The transfers.
   *
   * @return Array of transaction objects.
   */
  std::vector<Models::Transaction> initiateTransfer(
      const Models::Address& inputAddress, const Models::Address& remainderAddress,
      const std::vector<Models::Transfer>& transfers) const;

  /**
   * Checks if tail transaction is promotable by calling checkConsistency API call.
   *
   * @param tail Tail transaction hash.
   *
   * @return whether the given tail is promotable or not.
   */
  bool isPromotable(const Types::Trytes& tail) const;

private:
  void traverseBundles(const std::vector<Types::Trytes>&                          trxs,
                       const std::vector<std::reference_wrapper<Models::Bundle>>& bundles,
                       bool throwOnFail) const;

  /**
   * @return true if all transfers are valid, false otherwise
   */
  static bool isTransfersCollectionValid(const std::vector<Models::Transfer>& transfers);
};

}  // namespace API

}  // namespace IOTA
