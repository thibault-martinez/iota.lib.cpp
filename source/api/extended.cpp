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

#include <iostream>

#include <iota/api/extended.hpp>
#include <iota/api/responses/attach_to_tangle.hpp>
#include <iota/api/responses/check_consistency.hpp>
#include <iota/api/responses/find_transactions.hpp>
#include <iota/api/responses/get_account_data.hpp>
#include <iota/api/responses/get_balances.hpp>
#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/api/responses/get_bundle.hpp>
#include <iota/api/responses/get_inclusion_states.hpp>
#include <iota/api/responses/get_new_addresses.hpp>
#include <iota/api/responses/get_node_info.hpp>
#include <iota/api/responses/get_transactions_to_approve.hpp>
#include <iota/api/responses/get_trytes.hpp>
#include <iota/api/responses/replay_bundle.hpp>
#include <iota/api/responses/send_transfer.hpp>
#include <iota/api/responses/were_addresses_spent_from.hpp>
#include <iota/crypto/curl.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/crypto/signing.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/bundle.hpp>
#include <iota/models/seed.hpp>
#include <iota/models/signature.hpp>
#include <iota/models/transaction.hpp>
#include <iota/models/transfer.hpp>
#include <iota/types/trinary.hpp>
#include <iota/types/utils.hpp>
#include <iota/utils/parallel_for.hpp>

namespace IOTA {

namespace API {

Extended::Extended(const std::string& host, const uint16_t& port, bool localPow, int timeout, const std::string& user, const std::string& pass)
    : Core(host, port, localPow, timeout, user, pass) {
}

/*
 * Public methods.
 */

Responses::GetBalancesAndFormat
Extended::getInputs(const Models::Seed& seed, const int32_t& start, const int32_t& end,
                    const int64_t& threshold) const {
  const Utils::StopWatch stopWatch;

  // If start value bigger than end, return error
  if (start > end) {
    throw Errors::IllegalState("Invalid inputs provided");
  }

  int32_t nbAddresses = end != 0 ? end - start : 0;
  auto    addresses   = getNewAddresses(seed, start, nbAddresses, true).getAddresses();
  auto    res         = getBalancesAndFormat(addresses, threshold);

  //! update duration
  res.setDuration(stopWatch.getElapsedTime().count());

  return res;
}

Responses::GetBalancesAndFormat
Extended::getBalancesAndFormat(const std::vector<Models::Address>& addresses,
                               const int64_t&                      threshold) const {
  const Utils::StopWatch stopWatch;

  //! retrieve balances for all given addresses
  std::vector<std::string> balances =
      getBalances(addresses, GetBalancesRecommandedConfirmationThreshold).getBalances();

  // If threshold defined, keep track of whether reached or not
  // else set default to true
  bool thresholdReached = threshold == 0;
  int  i                = -1;

  std::vector<Models::Address> inputs;
  int64_t                      totalBalance = 0;

  for (const auto& address : addresses) {
    //! retrieve balance for given address
    int64_t balance = std::stoll(balances[++i]);

    //! skip if no balance
    if (balance <= 0) {
      continue;
    }

    Models::Address input = address;
    input.setBalance(balance);

    //! Add input to result and increase totalBalance of all aggregated inputs
    inputs.push_back(std::move(input));
    totalBalance += balance;

    if (!thresholdReached && totalBalance >= threshold) {
      thresholdReached = true;
      break;
    }
  }

  if (!thresholdReached) {
    throw Errors::IllegalState("Not enough balance");
  }

  return { inputs, totalBalance, stopWatch.getElapsedTime().count() };
}

Responses::GetNewAddresses
Extended::getNewAddresses(const Models::Seed& seed, const uint32_t& index, const int32_t& total,
                          bool returnAll) const {
  const Utils::StopWatch stopWatch;

  std::vector<Models::Address> allAddresses;

  // Case 1 : total number of addresses to generate is supplied.
  // Simply generate and return the list of all addresses.
  if (total) {
    for (uint32_t i = index; i < index + total; ++i) {
      allAddresses.emplace_back(seed.newAddress(i));
    }
  }
  // Case 2 : no total provided.
  // Continue calling wereAddressesSpentFrom & findTransactions to see if address was already
  // created if null, return list of addresses.
  else {
    for (int32_t i = index; true; i++) {
      const auto addr = seed.newAddress(i);

      const auto spent = wereAddressesSpentFrom({ addr });
      if (spent.getStates()[0]) {
        allAddresses.emplace_back(std::move(addr));
        continue;
      }

      const auto res = findTransactionsByAddresses({ addr });
      allAddresses.emplace_back(std::move(addr));
      if (res.getHashes().empty()) {
        break;
      }
    }
  }

  // Return only the last address that was generated.
  if (!returnAll) {
    allAddresses.erase(std::begin(allAddresses), std::end(allAddresses) - 1);
  }

  return { allAddresses, stopWatch.getElapsedTime().count() };
}

Models::Bundle
Extended::traverseBundle(const Types::Trytes& trunkTx) const {
  return traverseBundles({ trunkTx }).front();
}

std::vector<Models::Bundle>
Extended::traverseBundles(const std::vector<Types::Trytes>& trunkTrxs, bool throwOnFail) const {
  //! Check for invalid hash
  for (const auto& trx : trunkTrxs) {
    if (!Types::isValidHash(trx)) {
      throw Errors::IllegalState("Invalid transaction supplied.");
    }
  }

  //! init bundles to return
  std::vector<Models::Bundle> bundles(trunkTrxs.size(), Models::Bundle{});

  //! convert to vector<ref_wrapper<bundle>>
  std::vector<std::reference_wrapper<Models::Bundle>> bundlesRefs;
  for (auto& bundle : bundles) {
    bundlesRefs.push_back(std::ref(bundle));
  }

  traverseBundles(trunkTrxs, bundlesRefs, throwOnFail);

  return bundles;
}

void
Extended::traverseBundles(const std::vector<Types::Trytes>&                          trxs,
                          const std::vector<std::reference_wrapper<Models::Bundle>>& bundles,
                          bool throwOnFail) const {
  //! nothing to fetch
  if (trxs.empty()) {
    return;
  }

  //! get trytes for non-empty transactions
  const auto gtr = getTrytes(trxs);

  //! If fail to get trytes, return error
  if (gtr.getTrytes().empty()) {
    throw Errors::IllegalState("Invalid transaction supplied.");
  }

  //! keep track of which bundles need to be filled recursively
  std::vector<Types::Trytes>                          trunkTrxs;
  std::vector<std::reference_wrapper<Models::Bundle>> partialBundles;

  //! process each tryte
  for (std::size_t i = 0; i < gtr.getTrytes().size(); ++i) {
    //! get transaction itself
    const auto trx = Models::Transaction{ gtr.getTrytes()[i] };

    //! get bundle
    auto& bundle = bundles[i].get();

    //! If first transaction to search is not a tail, return error
    if (bundle.getHash().empty() && !trx.isTailTransaction()) {
      if (throwOnFail) {
        throw Errors::IllegalState("Invalid tail transaction supplied.");
      }
      //! if we are in silent mode, we clear the bundle and continue
      bundle = {};
      continue;
    }

    //! Detect infinite recursion
    if (trx.getTrunkTransaction() == trx.getHash()) {
      if (throwOnFail) {
        throw Errors::IllegalState("Invalid transaction supplied.");
      }
      //! if we are in silent mode, we clear the bundle and continue
      bundle = {};
      continue;
    }

    //! If no bundle hash, define it
    if (bundle.getHash().empty()) {
      bundle.setHash(trx.getBundle());
    }

    if (bundle.getHash() == trx.getBundle()) {
      //! Add transaction object to bundle
      bundle.addTransaction(trx);

      //! keep track of which bundles need to be filled recursively
      trunkTrxs.push_back(trx.getTrunkTransaction());
      partialBundles.push_back(bundle);
      continue;
    }
  }

  //! Continue traversing with new trunkTx
  traverseBundles(trunkTrxs, partialBundles, throwOnFail);
}

std::vector<Models::Transaction>
Extended::findTransactionObjects(const std::vector<Models::Address>& addresses) const {
  //! get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions(addresses, {}, {}, {}).getHashes());
}

std::vector<Models::Transaction>
Extended::findTransactionObjectsByBundle(const std::vector<Types::Trytes>& input) const {
  // check hashes format
  for (const auto& hash : input) {
    if (!Types::isValidHash(hash)) {
      throw Errors::IllegalState(
          "findTransactionObjectsByBundle parameter is not a valid array of hashes");
    }
  }

  // get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions({}, {}, {}, input).getHashes());
}

std::vector<Models::Transaction>
Extended::getTransactionsObjects(const std::vector<Types::Trytes>& hashes) const {
  if (!Types::isArrayOfHashes(hashes)) {
    throw Errors::IllegalState("getTransactionsObjects parameter is not a valid array of hashes");
  }

  //! get trytes forhashes
  const auto trytesResponse = getTrytes(hashes);

  //! build response
  std::vector<Models::Transaction> trxs;

  for (const auto& tryte : trytesResponse.getTrytes()) {
    trxs.emplace_back(tryte);
  }

  return trxs;
}

Responses::GetInclusionStates
Extended::getLatestInclusion(const std::vector<Types::Trytes>& hashes) const {
  return getInclusionStates(hashes, { getNodeInfo().getLatestSolidSubtangleMilestone() });
}

std::vector<Types::Trytes>
Extended::prepareTransfers(const Models::Seed& seed, const std::vector<Models::Transfer>& transfers,
                           const Models::Address&              remainder,
                           const std::vector<Models::Address>& inputs, bool validateInputs) const {
  // Validate transfers object
  if (!isTransfersCollectionValid(transfers)) {
    throw Errors::IllegalState("Invalid Transfer");
  }

  Models::Bundle             bundle;
  std::vector<Types::Trytes> signatureFragments;
  int64_t                    totalValue = 0;

  //  Iterate over all transfers, get totalValue
  //  and prepare the signatureFragments, message and tag
  for (const auto& transfer : transfers) {
    int signatureMessageLength = 1;

    // If message longer than 2187 trytes, increase signatureMessageLength (add 2nd transaction)
    if (transfer.getMessage().size() > MaxTrxMsgLength) {
      // Get total length, message / maxLength (2187 trytes)
      signatureMessageLength += (int)std::floor(transfer.getMessage().length() / MaxTrxMsgLength);

      Types::Trytes msgCopy = transfer.getMessage();

      // While there is still a message, copy it
      while (!msgCopy.empty()) {
        Types::Trytes fragment = msgCopy.substr(0, MaxTrxMsgLength);

        if (msgCopy.length() > MaxTrxMsgLength) {
          msgCopy = msgCopy.substr(MaxTrxMsgLength, msgCopy.length());
        } else {
          msgCopy = "";
        }

        signatureFragments.push_back(Types::Utils::rightPad(fragment, MaxTrxMsgLength, '9'));
      }
    } else {
      // Else, get single fragment with 2187 of 9's trytes
      auto fragment = transfer.getMessage().substr(0, MaxTrxMsgLength);

      fragment = Types::Utils::rightPad(fragment, MaxTrxMsgLength, '9');

      signatureFragments.push_back(fragment);
    }

    // get current timestamp in seconds
    int64_t timestamp = Utils::StopWatch::now().count();

    // Add first entry to the bundle
    bundle.addTransaction(
        { transfer.getAddress(), transfer.getValue(), transfer.getTag(), timestamp },
        signatureMessageLength);
    // Sum up total value
    totalValue += transfer.getValue();
  }

  // Get inputs if we are sending tokens
  if (totalValue != 0) {
    //  Case 1: user provided inputs
    //  Validate the inputs by calling getBalances
    if (!validateInputs)
      return addRemainder(seed, inputs, bundle, transfers.back().getTag(), totalValue, remainder,
                          signatureFragments);
    if (!inputs.empty()) {
      const auto balancesResponse =
          getBalances(inputs, GetBalancesRecommandedConfirmationThreshold);
      const auto balances = balancesResponse.getBalances();

      std::vector<Models::Address> confirmedInputs;
      int64_t                      totalBalance = 0;
      int                          i            = 0;
      for (const auto& balance : balances) {
        int64_t thisBalance = std::stoll(balance);

        // If input has balance, add it to confirmedInputs
        if (thisBalance > 0) {
          totalBalance += thisBalance;
          auto inputEl = inputs[i++];
          inputEl.setBalance(thisBalance);
          confirmedInputs.push_back(inputEl);

          // if we've already reached the intended input value, break out of loop
          if (totalBalance >= totalValue) {
            break;
          }
        }
      }

      // Return not enough balance error
      if (totalValue > totalBalance) {
        throw Errors::IllegalState("Not enough balance");
      }

      return addRemainder(seed, confirmedInputs, bundle, transfers.back().getTag(), totalValue,
                          remainder, signatureFragments);
    }

    //  Case 2: Get inputs deterministically
    //
    //  If no inputs provided, derive the addresses from the seed and
    //  confirm that the inputs exceed the threshold
    else {
      const auto newinputs = getInputs(seed, 0, 0, totalValue);
      // If inputs with enough balance
      return addRemainder(seed, newinputs.getInputs(), bundle, transfers.back().getTag(),
                          totalValue, remainder, signatureFragments);
    }
  } else {
    // If no input required, don't sign and simply finalize the bundle
    bundle.finalize();
    bundle.addTrytes(signatureFragments);

    const auto                 trxb = bundle.getTransactions();
    std::vector<Types::Trytes> bundleTrytes;

    for (const auto& trx : trxb) {
      bundleTrytes.emplace_back(trx.toTrytes());
    }
    std::reverse(bundleTrytes.begin(), bundleTrytes.end());
    return bundleTrytes;
  }
}

Responses::GetBundle
Extended::getBundle(const Types::Trytes& transaction) const {
  const Utils::StopWatch stopWatch;

  //! get bundle hash for transaction
  const auto bundle = traverseBundle(transaction);

  //! verify bundle integrity
  verifyBundle(bundle);

  return { bundle.getTransactions(), stopWatch.getElapsedTime().count() };
}

void
Extended::verifyBundle(const Models::Bundle& bundle) {
  int64_t       totalSum   = 0;
  Types::Trytes bundleHash = bundle.getHash();

  //! init curl
  Crypto::Kerl k;

  std::vector<Models::Signature> signaturesToValidate;
  for (std::size_t i = 0; i < bundle.getTransactions().size(); ++i) {
    const auto& trx = bundle[i];

    if (static_cast<int64_t>(i) != trx.getCurrentIndex()) {
      throw Errors::IllegalState("Invalid Bundle");
    }

    //! sums up transaction values
    auto trxValue = trx.getValue();
    totalSum += trxValue;

    //! Absorb bundle hash + value + timestamp + lastIndex + currentIndex trytes.
    k.absorb(Types::trytesToBytes(trx.toTrytes().substr(2187, 162)));

    //! if transaction has some value, we can processs next transactions
    if (trxValue >= 0) {
      continue;
    }

    Models::Signature sig;
    sig.setAddress(trx.getAddress());
    sig.getSignatureFragments().push_back(trx.getSignatureFragments());

    //! Find the subsequent txs with the remaining signature fragment
    for (std::size_t y = i + 1; y < bundle.getTransactions().size(); ++y) {
      const auto& newBundleTx = bundle[y];

      // Check if new tx is part of the signature fragment
      if (newBundleTx.getAddress() == trx.getAddress() && newBundleTx.getValue() == 0) {
        if (std::find(sig.getSignatureFragments().begin(), sig.getSignatureFragments().end(),
                      newBundleTx.getSignatureFragments()) == sig.getSignatureFragments().end()) {
          sig.getSignatureFragments().push_back(newBundleTx.getSignatureFragments());
        }
      }
    }

    signaturesToValidate.push_back(sig);
  }

  //! Check for total sum, if not equal 0 return error
  if (totalSum != 0) {
    throw Errors::IllegalState("Invalid Bundle Sum");
  }

  std::vector<uint8_t> bundleFromTrxs(ByteHashLength);
  k.finalSqueeze(bundleFromTrxs);

  //! Check if bundle hash is the same as returned by tx object
  if (Types::bytesToTrytes(bundleFromTrxs) != bundleHash) {
    throw Errors::IllegalState("Invalid Bundle Hash");
  }

  //! Last tx in the bundle should have currentIndex == lastIndex
  const auto& lastTrx = bundle[bundle.getLength() - 1];
  if (lastTrx.getCurrentIndex() != lastTrx.getLastIndex())
    throw Errors::IllegalState("Invalid Bundle");

  //! Validate the signatures
  for (const auto& signature : signaturesToValidate) {
    const auto& addr  = signature.getAddress();
    const auto& frags = signature.getSignatureFragments();

    if (!Crypto::Signing::validateSignatures(addr, frags, bundleHash)) {
      throw Errors::IllegalState("Invalid Signature");
    }
  }
}

Responses::SendTransfer
Extended::sendTransfer(const Models::Seed& seed, int depth, int minWeightMagnitude,
                       std::vector<Models::Transfer>&      transfers,
                       const std::vector<Models::Address>& inputs, const Models::Address& remainder,
                       const Types::Trytes& reference) const {
  const Utils::StopWatch stopWatch;

  const auto trytes = prepareTransfers(seed, transfers, remainder, inputs);
  const auto trxs   = sendTrytes(trytes, depth, minWeightMagnitude, reference);

  std::vector<bool> successful;

  for (const auto& trx : trxs) {
    auto response = findTransactionsByBundles({ trx.getBundle() });
    successful.push_back(!response.getHashes().empty());
  }

  return { successful, stopWatch.getElapsedTime().count() };
}

std::vector<Models::Transaction>
Extended::sendTrytes(const std::vector<Types::Trytes>& trytes, const unsigned int& depth,
                     const unsigned int& minWeightMagnitude, const Types::Trytes& reference) const {
  // Get branch and trunk
  const auto tta = getTransactionsToApprove(depth, reference);

  // Attach to tangle, do pow
  const auto res = attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(),
                                  minWeightMagnitude, trytes);

  broadcastAndStore(res.getTrytes());

  std::vector<Models::Transaction> trx;

  for (const auto& trxTrytes : res.getTrytes()) {
    trx.emplace_back(trxTrytes);
  }

  return trx;
}

Responses::Base
Extended::broadcastAndStore(const std::vector<Types::Trytes>& trytes) const {
  broadcastTransactions(trytes);
  return storeTransactions(trytes);
}

Responses::FindTransactions
Extended::findTransactionsByAddresses(const std::vector<Models::Address>& addresses) const {
  return findTransactions(addresses, {}, {}, {});
}

Responses::FindTransactions
Extended::findTransactionsByTags(const std::vector<Models::Tag>& tags) const {
  return findTransactions({}, tags, {}, {});
}

Responses::FindTransactions
Extended::findTransactionsByApprovees(const std::vector<Types::Trytes>& approvees) const {
  return findTransactions({}, {}, approvees, {});
}

Responses::FindTransactions
Extended::findTransactionsByBundles(const std::vector<Types::Trytes>& bundles) const {
  return findTransactions({}, {}, {}, bundles);
}

Responses::GetAccountData
Extended::getAccountData(const Models::Seed& seed, int start, int end, long threshold) const {
  const Utils::StopWatch stopWatch;

  auto addresses              = getNewAddresses(seed, start, end - start, true).getAddresses();
  const auto balances         = getBalancesAndFormat(addresses, threshold);
  const auto updatedAddresses = balances.getInputs();

  //! addresses returned by getNewAddresses do not contain the balance information
  //! getBalancesAndFormat get the balances but:
  //!  * it only returns addresses with positive balance
  //!  * it does not update the input addresses
  //!
  //! this loop goes through the getBalancesAndFormat result to update the balance
  //! of addresses returned by getNewAddresses before returning them.
  for (size_t i = 0, j = 0; i < updatedAddresses.size(); ++i) {
    while (j < addresses.size() && updatedAddresses[i] != addresses[j]) {
      ++j;
    }

    if (j < addresses.size()) {
      addresses[j].setBalance(updatedAddresses[i].getBalance());
    }
  }

  return { addresses, balances.getTotalBalance(),
           stopWatch.getElapsedTime().count() };
}

std::vector<Types::Trytes>
Extended::addRemainder(const Models::Seed& seed, const std::vector<Models::Address>& inputs,
                       Models::Bundle& bundle, const Models::Tag& tag, int64_t totalValue,
                       const Models::Address&            remainderAddress,
                       const std::vector<Types::Trytes>& signatureFragments) const {
  for (const auto& input : inputs) {
    auto    thisBalance = input.getBalance();
    auto    toSubtract  = -thisBalance;
    int64_t timestamp   = Utils::StopWatch::now().count();
    // Add input as bundle entry
    bundle.addTransaction({ input, toSubtract, tag, timestamp }, input.getSecurity());
    // If there is a remainder value
    // Add extra output to send remaining funds to
    if (thisBalance >= totalValue) {
      auto remainder = thisBalance - totalValue;
      // If user has provided remainder address
      // Use it to send remaining funds to
      if (remainder > 0 && !remainderAddress.empty()) {
        // Remainder bundle entry
        bundle.addTransaction({ remainderAddress, remainder, tag, timestamp });
        // Final function for signing inputs
        return Crypto::Signing::signInputs(seed, inputs, bundle, signatureFragments);
      } else if (remainder > 0) {
        // Generate a new Address by calling getNewAddress
        auto res = getNewAddresses(seed, 0, 0, false);
        // Remainder bundle entry
        bundle.addTransaction({ res.getAddresses()[0], remainder, tag, timestamp });
        // Final function for signing inputs
        return Crypto::Signing::signInputs(seed, inputs, bundle, signatureFragments);
      } else {
        // If there is no remainder, do not add transaction to bundle
        // simply sign and return
        return Crypto::Signing::signInputs(seed, inputs, bundle, signatureFragments);
      }
      // If multiple inputs provided, subtract the totalValue by
      // the inputs balance
    } else {
      totalValue -= thisBalance;
    }
  }
  throw Errors::IllegalState("Not enough balance");
}

Responses::ReplayBundle
Extended::replayBundle(const Types::Trytes& transaction, int depth, int minWeightMagnitude) const {
  const Utils::StopWatch stopWatch;

  auto bundleResponse = getBundle(transaction);

  std::vector<Types::Trytes> bundleTrytes;
  for (const auto& trx : bundleResponse.getTransactions()) {
    bundleTrytes.emplace_back(trx.toTrytes());
  }

  const auto trxs = sendTrytes(bundleTrytes, depth, minWeightMagnitude);

  std::vector<bool> successful;
  for (const auto& trx : trxs) {
    auto response = findTransactionsByBundles({ trx.getBundle() });
    successful.push_back(!response.getHashes().empty());
  }

  return { successful, stopWatch.getElapsedTime().count() };
}

std::vector<Models::Transaction>
Extended::initiateTransfer(const Models::Address&               inputAddress,
                           const Models::Address&               remainderAddress,
                           const std::vector<Models::Transfer>& transfers) const {
  //! validate input address
  if (inputAddress.empty()) {
    throw Errors::IllegalState("Invalid input address");
  }

  // Address validation of transfers object
  if (!isTransfersCollectionValid(transfers)) {
    throw Errors::IllegalState("Invalid transfer");
  }

  //! Create a new bundle
  Models::Bundle             bundle;
  int64_t                    totalValue = 0;
  std::vector<Types::Trytes> signatureFragments;

  //! Iterate over all transfers, get totalValue
  //! and prepare the signatureFragments, message and tag
  for (const auto& transfer : transfers) {
    int signatureMessageLength = 1;

    //! If message longer than 2187 trytes, increase signatureMessageLength (add 2nd transaction)
    if (transfer.getMessage().length() > MaxTrxMsgLength) {
      //! Get total length, message / maxLength (MaxTrxMsgLength trytes)
      signatureMessageLength += (int)std::floor(transfer.getMessage().length() / MaxTrxMsgLength);

      //! copy msg
      Types::Trytes msgCopy = transfer.getMessage();

      //! While there is still a message, copy it
      while (!msgCopy.empty()) {
        Types::Trytes fragment = msgCopy.substr(0, MaxTrxMsgLength);

        if (msgCopy.length() > MaxTrxMsgLength) {
          msgCopy = msgCopy.substr(MaxTrxMsgLength, msgCopy.length());
        } else {
          msgCopy = "";
        }

        // Pad remainder of fragment
        signatureFragments.push_back(Types::Utils::rightPad(fragment, MaxTrxMsgLength, '9'));
      }
    } else {
      //! Else, get single fragment with MaxTrxMsgLength of 9's trytes
      signatureFragments.push_back(
          Types::Utils::rightPad(transfer.getMessage(), MaxTrxMsgLength, '9'));
    }

    //! get current timestamp in seconds
    int64_t timestamp = Utils::StopWatch::now().count();

    //! Add first entry to the bundle
    bundle.addTransaction(
        { transfer.getAddress(), transfer.getValue(), transfer.getTag(), timestamp },
        signatureMessageLength);

    //! Sum up total value
    totalValue += transfer.getValue();
  }

  //! Get inputs if we are sending tokens
  if (totalValue == 0) {
    throw Errors::IllegalState("Invalid value transfer");
  }

  long totalBalance = 0;
  auto balances =
      getBalances({ inputAddress }, GetBalancesRecommandedConfirmationThreshold).getBalances();

  for (const auto& balance : balances) {
    totalBalance += std::atol(balance.c_str());
  }

  // get current timestamp in seconds
  int64_t timestamp = Utils::StopWatch::now().count();

  if (totalBalance > 0) {
    long toSubtract = -totalBalance;

    //! Add input as bundle entry
    //! Only a single entry, signatures will be added later
    bundle.addTransaction({ inputAddress, toSubtract, transfers.back().getTag(), timestamp },
                          inputAddress.getSecurity());
  }

  //! Return not enough balance error
  if (totalValue > totalBalance) {
    throw Errors::IllegalState("Not enough balance");
  }

  //! If there is a remainder value
  //! Add extra output to send remaining funds to
  if (totalBalance > totalValue) {
    int64_t remainder = totalBalance - totalValue;

    //! Remainder bundle entry if necessary
    if (remainderAddress.empty()) {
      throw Errors::IllegalState("No remainder address defined");
    }

    bundle.addTransaction({ remainderAddress, remainder, transfers.back().getTag(), timestamp });
  }

  bundle.finalize();
  bundle.addTrytes(signatureFragments);

  return bundle.getTransactions();
}

bool
Extended::isPromotable(const Types::Trytes& tail) const {
  if (!Types::isValidHash(tail)) {
    return false;
  }

  try {
    return checkConsistency({ tail }).getState();
  } catch (IOTA::Errors::BadRequest) {
    return false;
  }
  return false;
}

Responses::SendTransfer
Extended::promoteTransaction(const Types::Trytes& tail, int depth, int minWeightMagnitude,
                             std::vector<Models::Transfer>& transfers, int delay,
                             const std::function<bool()>& interrupt) const {
  if (!Types::isValidHash(tail)) {
    throw Errors::IllegalState("Invalid tail transaction");
  }

  if (!isPromotable(tail)) {
    throw Errors::IllegalState("Inconsistent subtangle");
  }

  if (interrupt()) {
    return {};
  }

  auto res = sendTransfer(transfers[0].getAddress().toTrytes(), depth, minWeightMagnitude,
                          transfers, {}, {}, tail);
  if (delay > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    return promoteTransaction(tail, depth, minWeightMagnitude, transfers, delay, interrupt);
  }
  return res;
}

std::vector<bool>
Extended::isReattachable(const std::vector<Models::Address>& addresses) {
  std::map<Types::Trytes, std::vector<Types::Trytes>> addressTxsMap;
  std::vector<Types::Trytes>                          valueTransactions;

  auto trxs = findTransactionObjects(addresses);
  for (const auto& trx : trxs) {
    if (trx.getValue() < 0) {
      addressTxsMap[trx.getAddress().toTrytes()].push_back(trx.getHash());
      valueTransactions.push_back(trx.getHash());
    }
  }

  if (!valueTransactions.empty()) {
    //! get the includion states of all the transactions
    auto inclusionStates = getLatestInclusion(valueTransactions);
    auto results         = std::vector<bool>{};

    for (const auto& address : addresses) {
      const auto& trxs = addressTxsMap[address.toTrytes()];

      if (trxs.empty()) {
        results.push_back(true);
        continue;
      }

      bool shouldReattach = true;
      for (const auto& trx : trxs) {
        auto txIndex =
            std::distance(valueTransactions.begin(),
                          std::find(valueTransactions.begin(), valueTransactions.end(), trx));
        auto isConfirmed = inclusionStates.getStates()[txIndex];

        //! if tx confirmed, break
        if (isConfirmed) {
          shouldReattach = false;
          break;
        }
      }

      results.push_back(shouldReattach);
    }

    return results;
  } else {
    return std::vector<bool>(addresses.size(), true);
  }
}

/*
 * Private methods.
 */

bool
Extended::isTransfersCollectionValid(const std::vector<Models::Transfer>& transfers) {
  for (const auto& transfer : transfers) {
    if (!transfer.isValid()) {
      return false;
    }
  }

  return true;
}

}  // namespace API

}  // namespace IOTA
