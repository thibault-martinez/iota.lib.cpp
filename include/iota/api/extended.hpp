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

#include <iota/api/core.hpp>
#include <iota/api/responses/get_account_data.hpp>
#include <iota/api/responses/get_balances.hpp>
#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/api/responses/get_bundle.hpp>
#include <iota/api/responses/get_new_addresses.hpp>
#include <iota/api/responses/get_transfers.hpp>
#include <iota/api/responses/replay_bundle.hpp>
#include <iota/api/responses/send_transfer.hpp>
#include <iota/crypto/sponge_factory.hpp>
#include <iota/models/bundle.hpp>
#include <iota/models/transfer.hpp>
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
  Extended(const std::string& host, const uint16_t& port,
           Crypto::SpongeType cryptoType = Crypto::SpongeType::KERL);
  virtual ~Extended();

public:
  /**
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
  Responses::GetBalancesAndFormat getInputs(const std::string& seed, const int32_t& start,
                                            const int32_t& end, const int32_t& security,
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
  Responses::GetBalancesAndFormat getBalancesAndFormat(
      const std::vector<std::string>& addresses, const int64_t& threshold, const int32_t& start,
      const int32_t& security, const Utils::StopWatch& stopWatch = {}) const;

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
  Responses::GetNewAddresses getNewAddresses(const std::string& seed, const uint32_t& index = 0,
                                             const int32_t& security = 2, bool checksum = false,
                                             const int32_t& total     = 0,
                                             bool           returnAll = false) const;

  /**
   * Basically traverse the Bundle by going down the trunkTransactions until
   * the bundle hash of the transaction is no longer the same. In case the input
   * transaction hash is not a tail, we return an error.
   *
   * @param trunkTx    Hash of a trunk or a tail transaction of a bundle.
   * @return Filled bundle corresponding to tail transaction.
   */
  Models::Bundle traverseBundle(const std::string& trunkTx) const;

  /**
   * Basically traverse the Bundle by going down the trunkTransactions until
   * the bundle hash of the transaction is no longer the same. In case the input
   * transaction hash is not a tail, we return an error.
   *
   * @param trunkTx    Hash of a trunk or a tail transaction of a bundle.
   * @param bundleHash The bundle hash.
   * @param bundle     Bundle to be populated.
   * @return Filled bundle corresponding to tail transaction.
   */
  Models::Bundle traverseBundle(const std::string& trunkTx, std::string bundleHash,
                                Models::Bundle& bundle) const;

  /**
   * function to get the formatted bundles of a list of addresses.
   *
   * @param addresses       List of addresses.
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   * @return List of bundles
   */
  std::vector<Models::Bundle> bundlesFromAddresses(
      const std::vector<IOTA::Types::Trytes>& addresses, bool inclusionStates) const;

  /**
   * Wrapper function for findTransactions, getTrytes and transactionObjects.
   * Returns the transactionObject of a transaction hash. The input can be a valid findTransactions
   * input.
   *
   * @param input The inputs.
   * @return Transactions.
   */
  std::vector<Models::Transaction> findTransactionObjects(
      const std::vector<IOTA::Types::Trytes>& input) const;

  /**
   * Wrapper function for getTrytes and transactionObjects.
   * Gets the trytes and transaction object from a list of transaction hashes.
   *
   * @param hashes The hashes
   * @return Transaction objects.
   **/
  std::vector<Models::Transaction> getTransactionsObjects(
      const std::vector<IOTA::Types::Trytes>& hashes) const;

  /**
   * Same as findTransactionObjects, but based on bundle hash
   *
   * @param input Bundle hashes
   * @return Transactions.
   **/
  std::vector<Models::Transaction> findTransactionObjectsByBundle(
      const std::vector<IOTA::Types::Trytes>& input) const;

  /**
   * Wrapper function for getNodeInfo and getInclusionStates
   *
   * @param hashes The hashes.
   * @return Inclusion state.
   */
  Responses::GetInclusionStates getLatestInclusion(const std::vector<Types::Trytes>& hashes) const;

  /*
   * Main purpose of this function is to get an array of transfer objects as input, and then prepare
   * the transfer by generating the correct bundle, as well as choosing and signing the inputs if
   * necessary (if it's a value transfer). The output of this function is an array of the raw
   * transaction data (trytes).
   *
   * @param seed      81-tryte encoded address of recipient.
   * @param security  The security level of private key / seed.
   * @param transfers Array of transfer objects.
   * @param remainder If defined, this address will be used for sending the remainder value (of the
   * inputs) to.
   * @param inputs    The inputs.
   * @return Returns bundle trytes.
   */
  std::vector<Types::Trytes> prepareTransfers(const Types::Trytes& seed, int security,
                                              std::vector<Models::Transfer>&    transfers,
                                              const std::string&                remainder,
                                              const std::vector<Models::Input>& inputs,
                                              bool validateInputs = true) const;

  /**
   * Gets the associated bundle transactions of a single transaction
   * Does validation of signatures, total sum as well as bundle order
   *
   * @param transaction Hash of a tail transaction
   * @return array of transactions belonging to bundle corresponding to the input trx
   */
  Responses::GetBundle getBundle(const Types::Trytes& transaction) const;

  /**
   * Returns the transfers which are associated with a seed. The transfers are determined by either
   * calculating deterministically which addresses were already used, or by providing a list of
   * indexes to get the transfers from.
   *
   * @param seed            Tryte-encoded seed. It should be noted that this seed is not
   * transferred.
   * @param security        The security level of private key / seed.
   * @param start           Starting key index.
   * @param end             Ending key index.
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   * @return Bundle of transfers.
   */
  Responses::GetTransfers getTransfers(const Types::Trytes& seed, int start, int end, int security,
                                       bool inclusionStates) const;

  /**
   * Takes a tail transaction hash as input, gets the bundle associated with the transaction and
   * then replays the bundle by attaching it to the tangle.
   */
  void replayTransfer() const;

  /**
   * Wrapper function that basically does prepareTransfers, as well as attachToTangle and finally,
   * it broadcasts and stores the transactions locally.
   *
   * @param seed               Tryte-encoded seed
   * @param security           The security level of private key / seed.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   * @param transfers          Array of transfer objects.
   * @param inputs             List of inputs used for funding the transfer.
   * @param address            If defined, this address will be used for sending the remainder value
   * (of the inputs) to.
   * @return Array of Transaction objects.
   */
  Responses::SendTransfer sendTransfer(const Types::Trytes& seed, int security, int depth,
                                       int                               minWeightMagnitude,
                                       std::vector<Models::Transfer>&    transfers,
                                       const std::vector<Models::Input>& inputs,
                                       const Types::Trytes&              address) const;

  /**
   * Wrapper function that gets transactions to approve, attaches to Tangle, broadcasts and stores.
   *
   * @param trytes             The trytes.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   * @return Transactions objects.
   */
  std::vector<Models::Transaction> sendTrytes(const std::vector<Types::Trytes>& trytes,
                                              const unsigned int&               depth,
                                              const unsigned int& minWeightMagnitude) const;

  /**
   * Wrapper function that does broadcastTransactions and storeTransactions.
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
      const std::vector<Types::Trytes>& addresses) const;

  /**
   * Find the transactions which match the specified tags.
   *
   * @param tags The list of transaction tags.
   *
   * @return the list of transactions which contain the specified tag value.
   */
  Responses::FindTransactions findTransactionsByTags(const std::vector<Types::Trytes>& tags) const;

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
   * @param bundles The list of bundle hashes that need to be extended to 81 chars by padding the
   * hash with 9's.
   *
   * @return the list of transactions which contain the specified bundle hash.
   */
  Responses::FindTransactions findTransactionsByBundles(
      const std::vector<Types::Trytes>& bundles) const;

  /**
   * Similar to getTransfers, just that it returns additional account data
   *
   * @param seed            Tryte-encoded seed. It should be noted that this seed is not
   * transferred.
   * @param security        The Security level of private key / seed.
   * @param index           Key index to start search from. If the index is provided, the generation
   * of the address is not deterministic. Default is 0.
   * @param checksum        Adds 9-tryte address checksum.
   * @param total           Total number of addresses to generate. 0 for unlimited
   * @param returnAll       If <code>true</code>, it returns all addresses which were
   * deterministically generated (until findTransactions returns null).
   * @param start           Starting key index. 0 to skip.
   * @param end             Ending key index. 0 to skip.
   * @param inclusionStates If <code>true</code>, it gets the inclusion states of the transfers.
   * @param threshold       Min balance required. 0 to skip.
   */
  Responses::GetAccountData getAccountData(const Types::Trytes& seed, int index, int security,
                                           bool checksum, int total, bool returnAll, int start,
                                           int end, bool inclusionStates, long threshold) const;

  /**
   * @param hash The hash of a transaction
   * @return hash of the tail transaction of the bundle to which the input trx belongs or EmptyHash
   */
  Types::Trytes findTailTransactionHash(const Types::Trytes& hash) const;

  /**
   * @param seed               Tryte-encoded seed.
   * @param security           The security level of private key / seed.
   * @param inputs             List of inputs used for funding the transfer.
   * @param bundle             To be populated.
   * @param tag                The tag.
   * @param totalValue         The total value.
   * @param remainderAddress   If defined, this address will be used for sending the remainder value
   * (of the inputs) to.
   * @param signatureFragments The signature fragments.
   */
  std::vector<std::string> addRemainder(const Types::Trytes& seed, const unsigned int& security,
                                        const std::vector<Models::Input>& inputs,
                                        Models::Bundle& bundle, const std::string& tag,
                                        const int64_t&                  totalValue,
                                        const Types::Trytes&            remainderAddress,
                                        const std::vector<std::string>& signatureFragments) const;

  /**
   * Replays a transfer by doing Proof of Work again.
   *
   * @param transaction        The transaction.
   * @param depth              The depth.
   * @param minWeightMagnitude The minimum weight magnitude.
   * @return Analyzed Transaction objects.
   */
  Responses::ReplayBundle replayBundle(const Types::Trytes& transaction, int depth,
                                       int minWeightMagnitude);

  /**
   * Prepares transfer by generating the bundle with the corresponding cosigner transactions.
   * Does not contain signatures.
   *
   * @param securitySum      The sum of security levels used by all co-signers.
   * @param inputAddress     Array of input addresses as well as the securitySum.
   * @param remainderAddress Has to be generated by the cosigners before initiating the transfer,
   * can be null if fully spent.
   * @return Bundle of transaction objects.
   */
  std::vector<Models::Transaction> initiateTransfer(int                            securitySum,
                                                    const Types::Trytes&           inputAddress,
                                                    const Types::Trytes&           remainderAddress,
                                                    std::vector<Models::Transfer>& transfers) const;

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
  Types::Trytes newAddress(const Types::Trytes& seed, const int32_t& index, const int32_t& security,
                           bool checksum) const;

  std::vector<std::string> signInputsAndReturn(
      const std::string& seed, const std::vector<Models::Input>& inputs, Models::Bundle& bundle,
      const std::vector<std::string>& signatureFragments) const;

  /**
   * @return true if all transfers are valid, false otherwise
   */
  bool isTransfersCollectionValid(const std::vector<Models::Transfer>& transfers) const;

private:
  /**
   * crypto algorithm to be used internally
   */
  Crypto::SpongeType cryptoType_;
};

}  // namespace API

}  // namespace IOTA
