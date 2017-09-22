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

#include <list>

#include <API/Core.hpp>
#include <API/Responses/getBalancesAndFormatResponse.hpp>
#include <API/Responses/getBalancesResponse.hpp>
#include <API/Responses/getBundleResponse.hpp>
#include <API/Responses/getNewAddressesResponse.hpp>
#include <API/Responses/storeTransactionsResponse.hpp>
#include <Crypto/SpongeFactory.hpp>
#include <Model/Bundle.hpp>
#include <Utils/StopWatch.hpp>

namespace IOTA {

namespace API {

/*
 * Extended API calls which will help do just about anything possible with IOTA. These
 * are mostly wrapper functions of Core API calls.
 * https://github.com/iotaledger/wiki/blob/master/api-proposal.md#proposed-api-calls
 */
class Extended : public Core {
public:
  Extended(const std::string& host, const unsigned int& port,
           Crypto::SpongeType cryptoType = Crypto::SpongeType::KERL);
  virtual ~Extended();

public:
  /*
   * Gets all possible inputs of a seed and returns them with the total balance. This is either done
   * deterministically (by genearating all addresses until findTransactions is empty and doing
   * getBalances), or by providing a key range to use for searching through.
   *
   * @param seed      Tryte-encoded seed. It should be noted that this seed is not transferred.
   * @param security  The Security level of private key / seed.
   * @param start     Starting key index.
   * @param end       Ending key index.
   * @param threshold Min balance required.
   */
  getBalancesAndFormatResponse getInputs(const std::string& seed, const int32_t& security,
                                         const int32_t& start, const int32_t& end,
                                         const int64_t& threshold) const;

  /**
   * Gets the balances and formats the output.
   *
   * @param addresses The addresses.
   * @param threshold Min balance required.
   * @param start     Starting key index.
   * @param stopWatch the stopwatch.
   * @param security  The security level of private key / seed.
   * @return Inputs object.
   **/
  getBalancesAndFormatResponse getBalancesAndFormat(const std::vector<std::string>& addresses,
                                                    const int64_t& threshold, const int32_t& start,
                                                    Utils::StopWatch stopWatch,
                                                    const int32_t&   security) const;

  /**
   * Generates a new address from a seed and returns the remainderAddress.
   * This is either done deterministically, or by providing the index of the new remainderAddress.
   *
   * @param seed      Tryte-encoded seed. It should be noted that this seed is not transferred.
   * @param security  Security level to be used for the private key / address. Can be 1, 2 or 3.
   * @param index     Key index to start search from. If the index is provided, the generation of
   * the address is not deterministic.
   * @param checksum  Adds 9-tryte address checksum.
   * @param total     Total number of addresses to generate.
   * @param returnAll If <code>true</code>, it returns all addresses which were deterministically
   * generated (until findTransactions returns null).
   * @return An array of strings with the specifed number of addresses.
   */
  getNewAddressesResponse getNewAddresses(const std::string& seed, const uint32_t& index = 0,
                                          const int32_t& security = 2, bool checksum = false,
                                          const int32_t& total = 0, bool returnAll = false) const;

  /**
   * Basically traverse the Bundle by going down the trunkTransactions until
   * the bundle hash of the transaction is no longer the same. In case the input
   * transaction hash is not a tail, we return an error.
   *
   * @param trunkTx    Hash of a trunk or a tail transaction of a bundle.
   * @return Filled bundle corresponding to tail transaction.
   */
  Bundle traverseBundle(const std::string& trunkTx) const;

  /**
   * Basically traverse the Bundle by going down the trunkTransactions until
   * the bundle hash of the transaction is no longer the same. In case the input
   * transaction hash is not a tail, we return an error.
   *
   * @param trunkTx    Hash of a trunk or a tail transaction of a bundle.
   * @param bundleHash The bundle hashe.
   * @param bundle     Bundle to be populated.
   * @return Filled bundle corresponding to tail transaction.
   */
  Bundle traverseBundle(const std::string& trunkTx, std::string bundleHash, Bundle& bundle) const;

  /**
   * function to get the formatted bundles of a list of addresses.
   *
   * @param addresses       List of addresses.
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   * @return List of bundles
   */
  std::vector<Bundle> bundlesFromAddresses(const std::vector<IOTA::Type::Trytes>& addresses,
                                           bool inclusionStates) const;

  /**
   * Wrapper function for findTransactions, getTrytes and transactionObjects.
   * Returns the transactionObject of a transaction hash. The input can be a valid findTransactions
   * input.
   *
   * @param input The inputs.
   * @return Transactions.
   */
  std::vector<Transaction> findTransactionObjects(
      const std::vector<IOTA::Type::Trytes>& input) const;

  /**
   * Wrapper function for getTrytes and transactionObjects.
   * Gets the trytes and transaction object from a list of transaction hashes.
   *
   * @param hashes The hashes
   * @return Transaction objects.
   **/
  std::vector<Transaction> getTransactionsObjects(
      const std::vector<IOTA::Type::Trytes>& hashes) const;

  /**
   * Same as findTransactionObjects, but based on bundle hash
   *
   * @param input Bundle hashes
   * @return Transactions.
   **/
  std::vector<Transaction> findTransactionObjectsByBundle(
      const std::vector<IOTA::Type::Trytes>& input) const;

  /**
   * Wrapper function for getNodeInfo and getInclusionStates
   *
   * @param hashes The hashes.
   * @return Inclusion state.
   */
  getInclusionStatesResponse getLatestInclusion(const std::vector<Type::Trytes>& hashes) const;

  /*
   * Main purpose of this function is to get an array of transfer objects as input, and then prepare
   * the transfer by generating the correct bundle, as well as choosing and signing the inputs if
   * necessary (if it's a value transfer). The output of this function is an array of the raw
   * transaction data (trytes).
   */
  void prepareTransfers() const;

  /*
   * Generates a new address from a seed and returns the address. This is either done
   * deterministically, or by providing the index of the new address (see Questions for more
   * information about this).
   */
  void getNewAddress() const;

  /*
   * This function returns the bundle which is associated with a transaction. Input can by any type
   * of transaction (tail and non-tail). If there are multiple bundles (because of a replay for
   * example), it will return multiple bundles. It also does important validation checking
   * (signatures, sum, order) to ensure that the correct bundle is returned.
   *
   * @param transaction The transaction encoded in trytes.
   * @return an array of bundle, if there are multiple arrays it means that there are conflicting
   * bundles.
   */
  getBundleResponse getBundle(const Type::Trytes& transaction) const;

  /*
   * Returns the transfers which are associated with a seed. The transfers are determined by either
   * calculating deterministically which addresses were already used, or by providing a list of
   * indexes to get the transfers from.
   */
  void getTransfers() const;

  /*
   * Takes a tail transaction hash as input, gets the bundle associated with the transaction and
   * then replays the bundle by attaching it to the tangle.
   */
  void replayTransfer() const;

  /*
   * Wrapper function that basically does prepareTransfers, as well as attachToTangle and finally,
   * it broadcasts and stores the transactions locally.
   */
  void sendTransfer() const;

  /*
   * Wrapper function that gets transactions to approve, attaches to Tangle, broadcasts and stores.
   *
   * @param trytes             The trytes.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   * @return Transactions objects.
   */
  std::vector<Transaction> sendTrytes(const std::vector<Type::Trytes>& trytes,
                                      const unsigned int&              depth,
                                      const unsigned int&              minWeightMagnitude) const;

  /*
   * Wrapper function that does broadcastTransactions and storeTransactions.
   */
  storeTransactionsResponse broadcastAndStore(const std::vector<Type::Trytes>& trytes) const;

  findTransactionsResponse findTransactionsByAddresses(
      const std::vector<Type::Trytes>& addresses) const;

  findTransactionsResponse findTransactionsByDigests(
      const std::vector<Type::Trytes>& digests) const;

  findTransactionsResponse findTransactionsByApprovees(
      const std::vector<Type::Trytes>& approvees) const;

  findTransactionsResponse findTransactionsByBundles(
      const std::vector<Type::Trytes>& bundles) const;

private:
  /**
   * Generates a new address.
   * It should be noted that the seed is not transferred.
   *
   * @param seed      The tryte-encoded seed.
   * @param index     The index to start search from.
   * @param security  The security level of private key.
   * @param checksum  Adds a 9-tryte address checksum.
   *
   * @return A new address.
   */
  Type::Trytes newAddress(const Type::Trytes& seed, const int32_t& index, const int32_t& security,
                          bool checksum) const;

private:
  /**
   * crypto algorithm to be used internally
   */
  Crypto::SpongeType cryptoType_;
};

}  // namespace API

}  // namespace IOTA
