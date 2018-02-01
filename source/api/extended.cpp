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

#include <iota/api/extended.hpp>
#include <iota/crypto/checksum.hpp>
#include <iota/crypto/curl.hpp>
#include <iota/crypto/signing.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/bundle.hpp>
#include <iota/models/signature.hpp>
#include <iota/models/transaction.hpp>
#include <iota/types/utils.hpp>
#include <iota/utils/parallel_for.hpp>

namespace IOTA {

namespace API {

Extended::Extended(const std::string& host, const uint16_t& port, bool localPow, int timeout,
                   Crypto::SpongeType t)
    : Core(host, port, localPow, timeout), cryptoType_(t) {
}

Extended::~Extended() {
}

/*
 * Public methods.
 */

Responses::GetBalancesAndFormat
Extended::getInputs(const Types::Trytes& seed, const int32_t& start, const int32_t& end,
                    const int32_t& security, const int64_t& threshold) const {
  const Utils::StopWatch stopWatch;

  // validate the seed
  if ((!Types::isValidTrytes(seed))) {
    throw Errors::IllegalState("Invalid Seed");
  }

  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  // If start value bigger than end, return error
  // or if difference between end and start is bigger than 500 keys
  if (start > end || end > (start + 500)) {
    throw Errors::IllegalState("Invalid inputs provided");
  }

  //  Case 1: start and end
  //
  //  If start and end is defined by the user, simply iterate through the keys
  //  and call getBalances
  if (end != 0) {
    std::vector<Types::Trytes> allAddresses;

    for (int i = start; i < end; ++i) {
      allAddresses.emplace_back(newAddress(seed, i, security, false));
    }

    return getBalancesAndFormat(allAddresses, threshold, start, security, stopWatch);
  }
  //  Case 2: iterate till threshold || end
  //
  //  Either start from index: 0 or start (if defined) until threshold is reached.
  //  Calls getNewAddress and deterministically generates and returns all addresses
  //  We then do getBalance, format the output and return it
  else {
    const auto res = getNewAddresses(seed, start, security, false, 0, true);
    return getBalancesAndFormat(res.getAddresses(), threshold, start, security, stopWatch);
  }
}

Responses::GetBalancesAndFormat
Extended::getBalancesAndFormat(const std::vector<Types::Trytes>& addresses,
                               const int64_t& threshold, const int32_t& start,
                               const int32_t& security, const Utils::StopWatch& stopWatch) const {
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  //! retrieve balances for all given addresses
  std::vector<std::string> balances =
      getBalances(addresses, GetBalancesRecommandedConfirmationThreshold).getBalances();

  // If threshold defined, keep track of whether reached or not
  // else set default to true
  bool thresholdReached = threshold == 0;
  int  i                = -1;

  std::vector<Models::Input> inputs;
  int64_t                    totalBalance = 0;

  for (const auto& address : addresses) {
    //! retrieve balance for given address
    long balance = std::stol(balances[++i]);

    //! skip if no balance
    if (balance <= 0) {
      continue;
    }

    //! Add input to result and increase totalBalance of all aggregated inputs
    inputs.emplace_back(address, balance, start + i, security);
    totalBalance += balance;

    if (!thresholdReached && totalBalance >= threshold) {
      thresholdReached = true;
      break;
    }
  }

  if (!thresholdReached) {
    throw Errors::IllegalState("Not enough balance");
  }

  return { inputs, totalBalance, stopWatch.getElapsedTimeMilliSeconds().count() };
}

Responses::GetNewAddresses
Extended::getNewAddresses(const Types::Trytes& seed, const uint32_t& index, const int32_t& security,
                          bool checksum, const int32_t& total, bool returnAll) const {
  const Utils::StopWatch stopWatch;

  // Validate the seed
  if ((!Types::isValidTrytes(seed))) {
    throw Errors::IllegalState("Invalid Seed");
  }

  // Validate the security level
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  std::vector<Types::Trytes> allAddresses;

  // Case 1 : total number of addresses to generate is supplied.
  // Simply generate and return the list of all addresses.
  if (total) {
    for (uint32_t i = index; i < index + total; ++i) {
      allAddresses.emplace_back(newAddress(seed, i, security, checksum));
    }
  }
  // Case 2 : no total provided.
  // Continue calling findTransactions to see if address was already created if null, return list
  // of addresses.
  else {
    for (int32_t i = index; true; i++) {
      const auto addr = newAddress(seed, i, security, checksum);
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

  return { allAddresses, stopWatch.getElapsedTimeMilliSeconds().count() };
}

Models::Bundle
Extended::traverseBundle(const Types::Trytes& trunkTx) const {
  Models::Bundle bundle;

  //! Check for invalid hash
  if (!Types::isValidHash(trunkTx)) {
    throw Errors::IllegalState("Invalid transaction supplied.");
  }

  return traverseBundle(trunkTx, "", bundle);
}

Models::Bundle
Extended::traverseBundle(const Types::Trytes& trunkTx, Types::Trytes bundleHash,
                         Models::Bundle& bundle) const {
  //! get trytes for transaction
  const auto gtr = getTrytes({ trunkTx });
  // If fail to get trytes, return error
  if (gtr.getTrytes().empty()) {
    throw Errors::IllegalState("Bundle transactions not visible");
  }

  //! get transaction itself
  const auto trx = Models::Transaction{ gtr.getTrytes()[0] };
  // If first transaction to search is not a tail, return error
  if (bundleHash.empty() && !trx.isTailTransaction()) {
    throw Errors::IllegalState("Invalid tail transaction supplied.");
  }
  // Detect infinite recursion
  if (trx.getTrunkTransaction() == trx.getHash()) {
    throw Errors::IllegalState("Invalid transaction supplied.");
  }

  // If no bundle hash, define it
  if (bundleHash.empty()) {
    bundleHash = trx.getBundle();
  }

  // If different bundle hash, return with bundle
  if (bundleHash != trx.getBundle()) {
    return bundle;
  }

  // Add transaction object to bundle
  bundle.addTransaction(trx);

  // Continue traversing with new trunkTx
  return traverseBundle(trx.getTrunkTransaction(), bundleHash, bundle);
}

std::vector<Models::Transaction>
Extended::findTransactionObjects(const std::vector<Types::Trytes>& input) const {
  //! get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions(input, {}, {}, {}).getHashes());
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
Extended::bundlesFromAddresses(const std::vector<Types::Trytes>& addresses,
                               bool                              withInclusionStates) const {
  //! find transactions for addresses
  const auto trxs = findTransactionObjects(addresses);
  if (trxs.empty())
    return {};

  //! filter tail/non tail transactions
  std::vector<Types::Trytes> tailTransactions;
  std::vector<Types::Trytes> nonTailBundleHashes;

  // Sort tail and nonTails
  for (const auto& trx : trxs) {
    if (trx.isTailTransaction()) {
      tailTransactions.emplace_back(trx.getHash());
    } else if (std::find(nonTailBundleHashes.begin(), nonTailBundleHashes.end(), trx.getBundle()) ==
               nonTailBundleHashes.end()) {
      nonTailBundleHashes.emplace_back(trx.getBundle());
    }
  }

  //! find transactions for bundles of non tail transactions
  //! TODO:v1.2.0(optimization): this will maybe re-query some tail transactions we already got (and
  //! we do filter that out in the next for loop) we maybe can filter the bundle list passed to
  //! findTransactionObjectsByBundle by restructuring the previous loop
  const auto bundleObjects = findTransactionObjectsByBundle(nonTailBundleHashes);

  //! add tail transactions found with findTransactionObjectsByBundle
  for (const auto& trx : bundleObjects) {
    if (trx.isTailTransaction() && std::find(tailTransactions.begin(), tailTransactions.end(),
                                             trx.getHash()) == tailTransactions.end()) {
      tailTransactions.emplace_back(trx.getHash());
    }
  }

  // If inclusionStates, get the confirmation status
  // of the tail transactions, and thus the bundles
  Responses::GetInclusionStates inclusionStates;
  if (withInclusionStates && !tailTransactions.empty()) {
    inclusionStates = getLatestInclusion(tailTransactions);

    if (inclusionStates.getStates().empty()) {
      throw Errors::IllegalState("No inclusion states");
    }
  }

  std::vector<Models::Bundle> bundles;
  std::mutex                  bundlesMtx;

  Utils::parallel_for(0, tailTransactions.size(), [&](int i) {
    try {
      const auto& transaction    = tailTransactions[i];
      const auto  bundleResponse = getBundle(transaction);
      auto        gbr            = Models::Bundle{ bundleResponse.getTransactions() };

      if (!gbr.getTransactions().empty()) {
        if (withInclusionStates) {
          bool inclusion = inclusionStates.getStates()[i];

          for (auto& t : gbr.getTransactions()) {
            t.setPersistence(inclusion);
          }
        }

        std::lock_guard<std::mutex> lock(bundlesMtx);
        bundles.push_back(std::move(gbr));
      }
    } catch (const std::runtime_error&) {
      // If error returned from getBundle, ignore it because the bundle was most likely incorrect
    }
  });

  std::sort(bundles.begin(), bundles.end());

  return bundles;
}

Responses::GetInclusionStates
Extended::getLatestInclusion(const std::vector<Types::Trytes>& hashes) const {
  return getInclusionStates(hashes, { getNodeInfo().getLatestSolidSubtangleMilestone() });
}

std::vector<Types::Trytes>
Extended::prepareTransfers(const Types::Trytes& seed, int security,
                           std::vector<Models::Transfer>& transfers, const std::string& remainder,
                           const std::vector<Models::Input>& inputs, bool validateInputs) const {
  // Validate transfers object
  if (!isTransfersCollectionValid(transfers)) {
    throw Errors::IllegalState("Invalid Transfer");
  }

  // Validate the seed
  if (!Types::isValidTrytes(seed)) {
    throw Errors::IllegalState("Invalid Seed");
  }

  if (!remainder.empty() && !Types::isValidAddress(remainder)) {
    throw Errors::IllegalState("Invalid Remainder");
  }

  // Validate the security level
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  Models::Bundle             bundle;
  std::vector<Types::Trytes> signatureFragments;
  int64_t                    totalValue = 0;
  Types::Trytes              tag;

  //  Iterate over all transfers, get totalValue
  //  and prepare the signatureFragments, message and tag
  for (auto& transfer : transfers) {
    // If address with checksum then remove checksum
    if (Crypto::Checksum::isValid(transfer.getAddress()))
      transfer.setAddress(Crypto::Checksum::remove(transfer.getAddress()));

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

    // If no tag defined, get 27 tryte tag.
    tag = transfer.getTag().empty() ? "999999999999999999999999999" : transfer.getTag();

    // Pad for required 27 tryte length
    tag = Types::Utils::rightPad(tag, TryteAlphabetLength, '9');

    // Add first entry to the bundle
    bundle.addTransaction(signatureMessageLength, transfer.getAddress(), transfer.getValue(), tag,
                          timestamp);
    // Sum up total value
    totalValue += transfer.getValue();
  }

  // Get inputs if we are sending tokens
  if (totalValue != 0) {
    //  Case 1: user provided inputs
    //  Validate the inputs by calling getBalances
    if (!validateInputs)
      return addRemainder(seed, security, inputs, bundle, tag, totalValue, remainder,
                          signatureFragments);
    if (!inputs.empty()) {
      // Get list if addresses of the provided inputs
      std::vector<Types::Trytes> inputsAddresses;
      for (const auto& input : inputs) {
        inputsAddresses.emplace_back(input.getAddress());
      }

      const auto balancesResponse =
          getBalances(inputsAddresses, GetBalancesRecommandedConfirmationThreshold);
      const auto balances = balancesResponse.getBalances();

      std::vector<Models::Input> confirmedInputs;
      int                        totalBalance = 0;
      int                        i            = 0;
      for (const auto& balance : balances) {
        long thisBalance = std::stol(balance);

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

      return addRemainder(seed, security, confirmedInputs, bundle, tag, totalValue, remainder,
                          signatureFragments);
    }

    //  Case 2: Get inputs deterministically
    //
    //  If no inputs provided, derive the addresses from the seed and
    //  confirm that the inputs exceed the threshold
    else {
      const auto newinputs = getInputs(seed, 0, 0, security, totalValue);
      // If inputs with enough balance
      return addRemainder(seed, security, newinputs.getInput(), bundle, tag, totalValue, remainder,
                          signatureFragments);
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
  const auto    bundle     = traverseBundle(transaction);
  int64_t       totalSum   = 0;
  Types::Trytes bundleHash = bundle.getTransactions()[0].getBundle();

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

  return { bundle.getTransactions(), stopWatch.getElapsedTimeMilliSeconds().count() };
}

Responses::GetTransfers
Extended::getTransfers(const Types::Trytes& seed, int start, int end, int security,
                       bool inclusionStates) const {
  const Utils::StopWatch stopWatch;

  // Validate the seed
  if ((!Types::isValidTrytes(seed))) {
    throw Errors::IllegalState("Invalid Seed");
  }

  // Validate the security level
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  // If start value bigger than end, return error
  // or if difference between end and start is bigger than 500 keys
  if (start > end || end > (start + 500)) {
    throw Errors::IllegalState("Invalid inputs provided");
  }

  const auto gna     = getNewAddresses(seed, start, security, false, end, true);
  const auto bundles = bundlesFromAddresses(gna.getAddresses(), inclusionStates);

  return { bundles, stopWatch.getElapsedTimeMilliSeconds().count() };
}

Responses::SendTransfer
Extended::sendTransfer(const Types::Trytes& seed, int security, int depth, int minWeightMagnitude,
                       std::vector<Models::Transfer>&    transfers,
                       const std::vector<Models::Input>& inputs,
                       const Types::Trytes&              address) const {
  // Validate the security level
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  const Utils::StopWatch stopWatch;

  const auto trytes = prepareTransfers(seed, security, transfers, address, inputs);
  const auto trxs   = sendTrytes(trytes, depth, minWeightMagnitude);

  std::vector<bool> successful;

  for (const auto& trx : trxs) {
    auto response = findTransactionsByBundles({ trx.getBundle() });
    successful.push_back(!response.getHashes().empty());
  }

  return { successful, stopWatch.getElapsedTimeMilliSeconds().count() };
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
Extended::findTransactionsByAddresses(const std::vector<Types::Trytes>& addresses) const {
  return findTransactions(addresses, {}, {}, {});
}

Responses::FindTransactions
Extended::findTransactionsByTags(const std::vector<Types::Trytes>& tags) const {
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
Extended::getAccountData(const Types::Trytes& seed, int index, int security, bool checksum,
                         int total, bool returnAll, int start, int end, bool inclusionStates,
                         long threshold) const {
  const Utils::StopWatch stopWatch;

  const auto gna = getNewAddresses(seed, index, security, checksum, total, returnAll);
  const auto gtr = getTransfers(seed, start, end, security, inclusionStates);
  const auto gip = getInputs(seed, start, end, security, threshold);

  return { gna.getAddresses(), gtr.getTransfers(), gip.getTotalBalance(),
           stopWatch.getElapsedTimeMilliSeconds().count() };
}

Types::Trytes
Extended::findTailTransactionHash(const Types::Trytes& hash) const {
  const auto gtr = getTrytes({ hash });

  if (gtr.getTrytes().empty()) {
    throw Errors::IllegalState("Bundle transactions not visible");
  }

  auto trx = Models::Transaction{ gtr.getTrytes()[0] };

  if (trx.getBundle().empty()) {
    throw Errors::IllegalState("Invalid trytes, could not create object");
  }

  //! check if current trx is tail
  if (trx.isTailTransaction()) {
    return trx.getHash();
  }

  //! if not, fetch based on bundle hash
  for (const auto& t : findTransactionObjectsByBundle({ trx.getBundle() })) {
    if (t.isTailTransaction()) {
      return t.getHash();
    }
  }

  return EmptyHash;
}

std::vector<Types::Trytes>
Extended::addRemainder(const Types::Trytes& seed, const unsigned int& security,
                       const std::vector<Models::Input>& inputs, Models::Bundle& bundle,
                       const Types::Trytes& unpadTag, const int64_t& totalValue,
                       const Types::Trytes&              remainderAddress,
                       const std::vector<Types::Trytes>& signatureFragments) const {
  //! Validate the seed
  if (!Types::isValidTrytes(seed)) {
    throw Errors::IllegalState("Invalid Seed");
  }

  //! Validate the tag
  auto tag = Types::Utils::rightPad(unpadTag, TagLength, '9');
  if (!Types::isValidTrytes(tag)) {
    throw Errors::IllegalState("Invalid Tag");
  }

  auto totalTransferValue = totalValue;

  for (const auto& input : inputs) {
    auto    thisBalance = input.getBalance();
    auto    toSubtract  = -thisBalance;
    int64_t timestamp   = Utils::StopWatch::now().count();
    // Add input as bundle entry
    bundle.addTransaction(input.getSecurity(), input.getAddress(), toSubtract, tag, timestamp);
    // If there is a remainder value
    // Add extra output to send remaining funds to
    if (thisBalance >= totalTransferValue) {
      auto remainder = thisBalance - totalTransferValue;
      // If user has provided remainder address
      // Use it to send remaining funds to
      if (remainder > 0 && !remainderAddress.empty()) {
        // Remainder bundle entry
        bundle.addTransaction(1, remainderAddress, remainder, tag, timestamp);
        // Final function for signing inputs
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else if (remainder > 0) {
        // Generate a new Address by calling getNewAddress
        auto res = getNewAddresses(seed, 0, security, false, 0, false);
        // Remainder bundle entry
        bundle.addTransaction(1, res.getAddresses()[0], remainder, tag, timestamp);
        // Final function for signing inputs
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else {
        // If there is no remainder, do not add transaction to bundle
        // simply sign and return
        return signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      }
      // If multiple inputs provided, subtract the totalTransferValue by
      // the inputs balance
    } else {
      totalTransferValue -= thisBalance;
    }
  }
  throw Errors::IllegalState("Not enough balance");
}

Responses::ReplayBundle
Extended::replayBundle(const Types::Trytes& transaction, int depth, int minWeightMagnitude) {
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

  return { successful, stopWatch.getElapsedTimeMilliSeconds().count() };
}

std::vector<Models::Transaction>
Extended::initiateTransfer(int securitySum, const Types::Trytes& inputAddress,
                           const Types::Trytes&           remainderAddress,
                           std::vector<Models::Transfer>& transfers) const {
  //! If message or tag is not supplied, provide it
  //! Also remove the checksum of the address if it's there

  for (auto& transfer : transfers) {
    if (transfer.getMessage().empty()) {
      transfer.setMessage(Types::Utils::rightPad(transfer.getMessage(), 2187, '9'));
    }

    if (transfer.getTag().empty()) {
      transfer.setTag(Types::Utils::rightPad(transfer.getTag(), 27, '9'));
    }

    if (!Types::isValidAddress(transfer.getAddress())) {
      throw Errors::IllegalState("Invalid transfer");
    }

    if (Crypto::Checksum::isValid(transfer.getAddress())) {
      transfer.setAddress(Crypto::Checksum::remove(transfer.getAddress()));
    }
  }

  // Input validation of transfers object
  if (!isTransfersCollectionValid(transfers)) {
    throw Errors::IllegalState("Invalid transfer");
  }

  //! validate input address
  if (!Types::isValidAddress(inputAddress)) {
    throw Errors::IllegalState("Invalid input address");
  }

  // validate remainder address
  if (!remainderAddress.empty() && !Types::isValidAddress(remainderAddress)) {
    throw Errors::IllegalState("Invalid remainder address");
  }

  //! Create a new bundle
  Models::Bundle             bundle;
  int64_t                    totalValue = 0;
  std::vector<Types::Trytes> signatureFragments;
  Types::Trytes              tag;

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

    //! Pad for required TagLength tryte length
    tag = Types::Utils::rightPad(transfer.getTag(), TagLength, '9');

    //! Add first entry to the bundle
    bundle.addTransaction(signatureMessageLength, transfer.getAddress(), transfer.getValue(), tag,
                          timestamp);

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
    bundle.addTransaction(securitySum, inputAddress, toSubtract, tag, timestamp);
  }

  //! Return not enough balance error
  if (totalValue > totalBalance) {
    throw Errors::IllegalState("Not enough balance");
  }

  //! If there is a remainder value
  //! Add extra output to send remaining funds to
  if (totalBalance > totalValue) {
    int64_t remainder = totalBalance - totalValue;

    // Remainder bundle entry if necessary
    if (remainderAddress.empty()) {
      throw Errors::IllegalState("No remainder address defined");
    }

    bundle.addTransaction(1, remainderAddress, remainder, tag, timestamp);
  }

  bundle.finalize(Crypto::create(cryptoType_));
  bundle.addTrytes(signatureFragments);

  return bundle.getTransactions();
}

/*
 * Private methods.
 */

Types::Trytes
Extended::newAddress(const Types::Trytes& seed, const int32_t& index, const int32_t& security,
                     bool checksum) const {
  auto key          = Crypto::Signing::key(seed, index, security);
  auto digests      = Crypto::Signing::digests(key);
  auto addressTrits = Crypto::Signing::address(digests);
  auto address      = Types::tritsToTrytes(addressTrits);

  if (checksum) {
    address = Crypto::Checksum::add(address);
  }
  return address;
}

std::vector<Types::Trytes>
Extended::signInputsAndReturn(const Types::Trytes& seed, const std::vector<Models::Input>& inputs,
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
        if (input.getAddress() == addr) {
          keyIndex    = input.getKeyIndex();
          keySecurity = input.getSecurity();
        }
      }

      auto bundleHash = tx.getBundle();

      // Get corresponding private key of address
      auto key = Crypto::Signing::key(seed, keyIndex, keySecurity);

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
Extended::isTransfersCollectionValid(const std::vector<Models::Transfer>& transfers) const {
  for (const auto& transfer : transfers) {
    if (!transfer.isValid()) {
      return false;
    }
  }

  return true;
}

}  // namespace API

}  // namespace IOTA
