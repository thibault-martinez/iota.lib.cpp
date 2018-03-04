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
#include <iota/api/responses/find_transactions.hpp>
#include <iota/api/responses/get_account_data.hpp>
#include <iota/api/responses/get_balances.hpp>
#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/api/responses/get_bundle.hpp>
#include <iota/api/responses/get_inclusion_states.hpp>
#include <iota/api/responses/get_new_addresses.hpp>
#include <iota/api/responses/get_node_info.hpp>
#include <iota/api/responses/get_transactions_to_approve.hpp>
#include <iota/api/responses/get_transfers.hpp>
#include <iota/api/responses/get_trytes.hpp>
#include <iota/api/responses/replay_bundle.hpp>
#include <iota/api/responses/send_transfer.hpp>
#include <iota/crypto/curl.hpp>
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

Extended::Extended(const std::string& host, const uint16_t& port, bool localPow, int timeout,
                   Crypto::SpongeType cryptoType)
    : Core(host, port, localPow, timeout), cryptoType_(cryptoType) {
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
  // Continue calling findTransactions to see if address was already created if null, return list
  // of addresses.
  else {
    for (int32_t i = index; true; i++) {
      const auto addr = seed.newAddress(i);
      const auto res  = findTransactionsByAddresses({ addr });

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

std::vector<Models::Bundle>
Extended::bundlesFromAddresses(const std::vector<Models::Address>& addresses,
                               bool                                withInclusionStates) const {
  //! find transactions for addresses
  const auto trxs = findTransactionObjects(addresses);
  if (trxs.empty())
    return {};

  //! filter tail/non tail transactions
  std::vector<Models::Transaction> tailTrxs;
  std::vector<Models::Transaction> nonTailTrxs;

  for (const auto& trx : trxs) {
    if (trx.isTailTransaction()) {
      tailTrxs.emplace_back(trx);
    } else {
      nonTailTrxs.emplace_back(trx);
    }
  }

  //! filter out non-tail transactions for which we already got the bundle tail transaction
  //! only keep bundle hash to pass that as argument of findTransactionObjectsByBundle
  std::vector<Types::Trytes> nonTailTrxsBundleHashes;

  for (const auto& trx : nonTailTrxs) {
    //! skip if we already filtered a non-tail transaction belonging to the same bundle
    auto nonTailDuplicateBundle =
        std::find(nonTailTrxsBundleHashes.begin(), nonTailTrxsBundleHashes.end(), trx.getBundle());

    if (nonTailDuplicateBundle != nonTailTrxsBundleHashes.end()) {
      continue;
    }

    //! skip if we already got a tail transaction fro that bundle
    auto tailDuplicateBundle = std::find_if(
        tailTrxs.begin(), tailTrxs.end(),
        [&](const Models::Transaction& lhs) { return lhs.getBundle() == trx.getBundle(); });

    if (tailDuplicateBundle != tailTrxs.end()) {
      continue;
    }

    //! otherwise keep track to fetch bundle with findTransactionObjectsByBundle
    nonTailTrxsBundleHashes.push_back(trx.getBundle());
  }

  //! find transactions for bundles of non tail transactions
  //! add these transactions to the list of tail transactions
  const auto trxFromBundle = findTransactionObjectsByBundle(nonTailTrxsBundleHashes);
  tailTrxs.insert(tailTrxs.end(), trxFromBundle.begin(), trxFromBundle.end());

  //! keep only hash
  std::vector<Types::Trytes> tailTrxsHashes;
  tailTrxsHashes.reserve(tailTrxs.size());

  for (const auto& trx : tailTrxs) {
    tailTrxsHashes.emplace_back(trx.getHash());
  }

  //! If inclusionStates, get the confirmation status
  //! of the tail transactions, and thus the bundles
  Responses::GetInclusionStates inclusionStates;
  if (withInclusionStates && !tailTrxsHashes.empty()) {
    inclusionStates = getLatestInclusion(tailTrxsHashes);

    if (inclusionStates.getStates().empty()) {
      throw Errors::IllegalState("No inclusion states");
    }
  }

  std::mutex                  allBundlesMtx;
  std::vector<Models::Bundle> allBundles;

  std::size_t nb_cores   = std::thread::hardware_concurrency();
  std::size_t nb_threads = std::min(nb_cores, tailTrxsHashes.size());

  Utils::parallel_for(nb_threads, [&](int cpu, int num_cpus) {
    int start = tailTrxsHashes.size() * cpu / num_cpus;
    int end   = tailTrxsHashes.size() * (cpu + 1) / num_cpus;

    //! for last cpu, ensure we got all remaining of the list
    if (cpu == num_cpus - 1) {
      end = tailTrxsHashes.size();
    }

    auto startIt = tailTrxsHashes.begin() + start;
    auto endIt   = tailTrxsHashes.begin() + end;
    auto bundles = traverseBundles({ startIt, endIt }, false);

    if (withInclusionStates) {
      for (std::size_t i = 0; i < bundles.size(); ++i) {
        auto& trxs      = bundles[i].getTransactions();
        bool  inclusion = inclusionStates.getStates()[start + i];

        for (auto& t : trxs) {
          t.setPersistence(inclusion);
        }
      }
    }

    std::lock_guard<std::mutex> lock(allBundlesMtx);

    //! only keep valid non-empty bundles
    for (auto& bundle : bundles) {
      if (!bundle.getTransactions().empty()) {
        try {
          verifyBundle(bundle);
          allBundles.push_back(std::move(bundle));
        } catch (std::runtime_error&) {
        }
      }
    }
  });

  std::sort(allBundles.begin(), allBundles.end());

  return allBundles;
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
    const auto curl = Crypto::create(cryptoType_);
    bundle.finalize(curl);
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
Extended::verifyBundle(const Models::Bundle& bundle) const {
  int64_t       totalSum   = 0;
  Types::Trytes bundleHash = bundle.getHash();

  //! init curl
  const auto curl = Crypto::create(Crypto::SpongeType::KERL);

  std::vector<Models::Signature> signaturesToValidate;
  for (std::size_t i = 0; i < bundle.getTransactions().size(); ++i) {
    const auto& trx = bundle.getTransactions()[i];

    if (static_cast<int64_t>(i) != trx.getCurrentIndex()) {
      throw Errors::IllegalState("Invalid Bundle");
    }

    //! sums up transaction values
    auto trxValue = trx.getValue();
    totalSum += trxValue;

    //! Absorb bundle hash + value + timestamp + lastIndex + currentIndex trytes.
    curl->absorb(Types::trytesToTrits(trx.toTrytes().substr(2187, 162)));

    //! if transaction has some value, we can processs next transactions
    if (trxValue >= 0) {
      continue;
    }

    Models::Signature sig;
    sig.setAddress(trx.getAddress());
    sig.getSignatureFragments().push_back(trx.getSignatureFragments());

    //! Find the subsequent txs with the remaining signature fragment
    for (std::size_t y = i + 1; y < bundle.getTransactions().size(); ++y) {
      const auto& newBundleTx = bundle.getTransactions()[y];

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

  std::vector<int8_t> bundleFromTrxs(TritHashLength);
  curl->squeeze(bundleFromTrxs);

  //! Check if bundle hash is the same as returned by tx object
  if (Types::tritsToTrytes(bundleFromTrxs) != bundleHash) {
    throw Errors::IllegalState("Invalid Bundle Hash");
  }

  //! Last tx in the bundle should have currentIndex == lastIndex
  const auto& lastTrx = bundle.getTransactions()[bundle.getLength() - 1];
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

Responses::GetTransfers
Extended::getTransfers(const Models::Seed& seed, int start, int end, bool inclusionStates) const {
  const Utils::StopWatch stopWatch;

  // If start value bigger than end, return error
  if (start > end) {
    throw Errors::IllegalState("Invalid inputs provided");
  }

  const auto gna     = getNewAddresses(seed, start, end - start, true);
  const auto bundles = bundlesFromAddresses(gna.getAddresses(), inclusionStates);

  return { bundles, stopWatch.getElapsedTime().count() };
}

Responses::SendTransfer
Extended::sendTransfer(const Models::Seed& seed, int depth, int minWeightMagnitude,
                       std::vector<Models::Transfer>&      transfers,
                       const std::vector<Models::Address>& inputs,
                       const Models::Address&              remainder) const {
  const Utils::StopWatch stopWatch;

  const auto trytes = prepareTransfers(seed, transfers, remainder, inputs);
  const auto trxs   = sendTrytes(trytes, depth, minWeightMagnitude);

  std::vector<bool> successful;

  for (const auto& trx : trxs) {
    auto response = findTransactionsByBundles({ trx.getBundle() });
    successful.push_back(!response.getHashes().empty());
  }

  return { successful, stopWatch.getElapsedTime().count() };
}

std::vector<Models::Transaction>
Extended::sendTrytes(const std::vector<Types::Trytes>& trytes, const unsigned int& depth,
                     const unsigned int& minWeightMagnitude) const {
  // Get branch and trunk
  const auto tta = getTransactionsToApprove(depth);

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
Extended::getAccountData(const Models::Seed& seed, int start, int end, bool inclusionStates,
                         long threshold) const {
  const Utils::StopWatch stopWatch;

  const auto addresses = getNewAddresses(seed, start, end - start, true);
  const auto transfers = bundlesFromAddresses(addresses.getAddresses(), inclusionStates);
  const auto balances  = getBalancesAndFormat(addresses.getAddresses(), threshold);

  return { addresses.getAddresses(), transfers, balances.getTotalBalance(),
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
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else if (remainder > 0) {
        // Generate a new Address by calling getNewAddress
        auto res = getNewAddresses(seed, 0, 0, false);
        // Remainder bundle entry
        bundle.addTransaction({ res.getAddresses()[0], remainder, tag, timestamp });
        // Final function for signing inputs
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else {
        // If there is no remainder, do not add transaction to bundle
        // simply sign and return
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
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

  bundle.finalize(Crypto::create(cryptoType_));
  bundle.addTrytes(signatureFragments);

  return bundle.getTransactions();
}

/*
 * Private methods.
 */

std::vector<Types::Trytes>
Extended::signInputsAndReturn(const Models::Seed& seed, const std::vector<Models::Address>& inputs,
                              Models::Bundle&                   bundle,
                              const std::vector<Types::Trytes>& signatureFragments) const {
  bundle.finalize(Crypto::create(cryptoType_));
  bundle.addTrytes(signatureFragments);

  //  SIGNING OF INPUTS
  //
  //  Here we do the actual signing of the inputs
  //  Iterate over all bundle transactions, find the inputs
  //  Get the corresponding private key and calculate the signatureFragment
  for (auto& tx : bundle.getTransactions()) {
    if (tx.getValue() < 0) {
      auto addr = tx.getAddress();

      // Get the corresponding keyIndex of the address
      int keyIndex    = 0;
      int keySecurity = 0;
      for (const auto& input : inputs) {
        if (input == addr) {
          keyIndex    = input.getKeyIndex();
          keySecurity = input.getSecurity();
        }
      }

      auto bundleHash = tx.getBundle();

      // Get corresponding private key of address
      auto key = Crypto::Signing::key(seed.toTrytes(), keyIndex, seed.getSecurity());

      //  First 6561 trits for the firstFragment
      std::vector<int8_t> firstFragment(&key[0], &key[6561]);

      //  Get the normalized bundle hash
      auto normalizedBundleHash = bundle.normalizedBundle(bundleHash);

      //  First bundle fragment uses 27 trytes
      std::vector<int8_t> firstBundleFragment(&normalizedBundleHash[0], &normalizedBundleHash[27]);

      //  Calculate the new signatureFragment with the first bundle fragment
      auto firstSignedFragment =
          Crypto::Signing::signatureFragment(firstBundleFragment, firstFragment);

      //  Convert signature to trytes and assign the new signatureFragment
      tx.setSignatureFragments(Types::tritsToTrytes(firstSignedFragment));

      // if user chooses higher than 27-tryte security
      // for each security level, add an additional signature
      for (int j = 1; j < keySecurity; j++) {
        //  Because the signature is > 2187 trytes, we need to
        //  find the second transaction to add the remainder of the signature
        for (auto& txb : bundle.getTransactions()) {
          //  Same address as well as value = 0 (as we already spent the input)
          if (txb.getAddress() == addr && txb.getValue() == 0) {
            // Use the second 6562 trits
            std::vector<int8_t> secondFragment(&key[6561], &key[6561 * 2]);

            // The second 27 to 54 trytes of the bundle hash
            std::vector<int8_t> secondBundleFragment(&normalizedBundleHash[27],
                                                     &normalizedBundleHash[27 * 2]);

            //  Calculate the new signature
            auto secondSignedFragment =
                Crypto::Signing::signatureFragment(secondBundleFragment, secondFragment);

            //  Convert signature to trytes and assign it again to this bundle entry
            txb.setSignatureFragments(Types::tritsToTrytes(secondSignedFragment));
          }
        }
      }
    }
  }

  std::vector<Types::Trytes> bundleTrytes;

  std::sort(bundle.getTransactions().begin(), bundle.getTransactions().end(),
            [](const Models::Transaction& lhs, const Models::Transaction& rhs) {
              return lhs.getCurrentIndex() < rhs.getCurrentIndex();
            });

  // Convert all bundle entries into trytes
  for (const auto& tx : bundle.getTransactions()) {
    bundleTrytes.emplace_back(tx.toTrytes());
  }

  return bundleTrytes;
}

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
