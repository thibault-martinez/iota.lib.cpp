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

#include <API/Extended.hpp>
#include <Crypto/Checksum.hpp>
#include <Crypto/Curl.hpp>
#include <Crypto/Signing.hpp>
#include <Errors/IllegalState.hpp>
#include <Model/Bundle.hpp>
#include <Model/Signature.hpp>
#include <Model/Transaction.hpp>
#include <Type/Seed.hpp>

namespace IOTA {

namespace API {

Extended::Extended(const std::string& host, const unsigned int& port, Crypto::SpongeType t)
    : Core(host, port), cryptoType_(t) {
}

Extended::~Extended() {
}

/*
 * Public methods.
 */

getBalancesAndFormatResponse
Extended::getInputs(const std::string& seed, const int32_t& security, const int32_t& start,
                    const int32_t& end, const int64_t& threshold) const {
  Utils::StopWatch stopWatch;

  // validate the seed
  if ((!Type::Seed::isValidSeed(seed))) {
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

  // TODO Case 1 and 2 : can't we just delegate that to getNewAddresses
  // TODO Seems to do the same thing.

  //  Case 1: start and end
  //
  //  If start and end is defined by the user, simply iterate through the keys
  //  and call getBalances
  if (end != 0) {
    std::vector<std::string> allAddresses;

    for (int i = start; i < end; ++i) {
      allAddresses.push_back(this->newAddress(seed, i, security, false));
    }

    return getBalancesAndFormat(allAddresses, threshold, start, stopWatch, security);
  }
  //  Case 2: iterate till threshold || end
  //
  //  Either start from index: 0 or start (if defined) until threshold is reached.
  //  Calls getNewAddress and deterministically generates and returns all addresses
  //  We then do getBalance, format the output and return it
  else {
    auto res = getNewAddresses(seed, start, security, false, 0, true);
    return getBalancesAndFormat(res.getAddresses(), threshold, start, stopWatch, security);
  }
}

getBalancesAndFormatResponse
Extended::getBalancesAndFormat(const std::vector<std::string>& addresses, const int64_t& threshold,
                               const int32_t& start, Utils::StopWatch stopWatch,
                               const int32_t& security) const {
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  //! retrieve balances for all given addresses
  std::vector<std::string> balances = getBalances(addresses, 100).getBalances();

  // If threshold defined, keep track of whether reached or not
  // else set default to true
  bool thresholdReached = threshold == 0;
  int  i                = -1;

  std::vector<input> inputs;
  int64_t            totalBalance = 0;

  for (const auto& address : addresses) {
    //! retrieve balance for given address
    long balance = std::stol(balances[++i]);

    //! skip if no balance
    if (balance <= 0) {
      continue;
    }

    //! Add input to result and increase totalBalance of all aggregated inputs
    inputs.push_back({ address, balance, start + i, security });
    totalBalance += balance;

    if (!thresholdReached && totalBalance >= threshold) {
      thresholdReached = true;
      //! TODO: is this break necessary? (that's the logic of the reference java client)
      //! threshold is defined as minimum balance expected, but here we stop the process whenever
      //! threshold is reached (if different from 0)
      //! so is it an expected behavior? If so, why so? Maybe we will get more clues further during
      //! the development of other API
      break;
    }
  }

  if (!thresholdReached) {
    throw Errors::IllegalState("Not enough balance");
  }

  return { inputs, totalBalance, stopWatch.getElapsedTimeMiliSeconds().count() };
}

getNewAddressesResponse
Extended::getNewAddresses(const Type::Trytes& seed, const uint32_t& index, const int32_t& security,
                          bool checksum, const int32_t& total, bool returnAll) const {
  Utils::StopWatch stopWatch;

  // Validate the seed
  if ((!Type::Seed::isValidSeed(seed))) {
    throw Errors::IllegalState("Invalid Seed");
  }

  // Validate the security level
  if (security < 1 || security > 3) {
    throw Errors::IllegalState("Invalid Security Level");
  }

  std::vector<Type::Trytes> allAddresses;

  // Case 1 : total number of addresses to generate is supplied.
  // Simply generate and return the list of all addresses.
  if (total) {
    for (uint32_t i = index; i < index + total; ++i) {
      allAddresses.push_back(this->newAddress(seed, i, security, checksum));
    }
  }
  // Case 2 : no total provided.
  // Continue calling findTransactions to see if address was already created if null, return list
  // of addresses.
  else {
    for (int32_t i = index; true; i++) {
      auto newAddress = this->newAddress(seed, i, security, checksum);
      auto res        = this->findTransactionsByAddresses({ newAddress });

      allAddresses.push_back(newAddress);
      if (res.getHashes().empty()) {
        break;
      }
    }
  }

  // Return only the last address that was generated.
  if (not returnAll) {
    allAddresses.erase(std::begin(allAddresses), std::end(allAddresses) - 1);
  }

  return { allAddresses, stopWatch.getElapsedTimeMiliSeconds().count() };
}

Bundle
Extended::traverseBundle(const std::string& trunkTx) const {
  Bundle bundle;
  return traverseBundle(trunkTx, "", bundle);
}

Bundle
Extended::traverseBundle(const std::string& trunkTx, std::string bundleHash, Bundle& bundle) const {
  //! get trytes for transaction
  getTrytesResponse gtr = getTrytes({ trunkTx });
  // If fail to get trytes, return error
  if (gtr.getTrytes().empty()) {
    throw Errors::IllegalState("Bundle transactions not visible");
  }

  //! get transaction itself
  auto trx = Transaction{ gtr.getTrytes()[0] };
  // If first transaction to search is not a tail, return error
  if (bundleHash.empty() && !trx.isTailTransaction()) {
    throw Errors::IllegalState("Invalid tail transaction supplied.");
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

std::vector<Transaction>
Extended::findTransactionObjects(const std::vector<IOTA::Type::Trytes>& input) const {
  //! get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions(input, {}, {}, {}).getHashes());
}

std::vector<Transaction>
Extended::findTransactionObjectsByBundle(const std::vector<IOTA::Type::Trytes>& input) const {
  // get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions({}, {}, {}, input).getHashes());
}

std::vector<Transaction>
Extended::getTransactionsObjects(const std::vector<IOTA::Type::Trytes>& hashes) const {
  if (!Type::isArrayOfHashes(hashes)) {
    throw Errors::IllegalState("getTransactionsObjects parameter is not a valid array of hashes");
  }

  //! get trytes forhashes
  getTrytesResponse trytesResponse = getTrytes(hashes);

  //! build response
  std::vector<Transaction> trxs;

  for (const auto& tryte : trytesResponse.getTrytes()) {
    trxs.push_back(Transaction{ tryte });
  }

  return trxs;
}

std::vector<Bundle>
Extended::bundlesFromAddresses(const std::vector<IOTA::Type::Trytes>& addresses,
                               bool                                   withInclusionStates) const {
  //! find transactions for addresses
  std::vector<Transaction> trxs = findTransactionObjects(addresses);

  //! filter tail/non tail transactions
  std::vector<IOTA::Type::Trytes> tailTransactions;
  std::vector<IOTA::Type::Trytes> nonTailBundleHashes;

  // Sort tail and nonTails
  for (const auto& trx : trxs) {
    if (trx.isTailTransaction()) {
      tailTransactions.push_back(trx.getHash());
    } else if (std::find(nonTailBundleHashes.begin(), nonTailBundleHashes.end(), trx.getBundle()) ==
               nonTailBundleHashes.end()) {
      nonTailBundleHashes.push_back(trx.getBundle());
    }
  }

  //! find transactions for bundles of non tail transactions
  //! TODO: this will maybe re-query some tail transactions we already got (and we do filter that
  //! out in the next for loop) we maybe can filter the bundle list passed to
  //! findTransactionObjectsByBundle by restructuring the previous loop
  std::vector<Transaction> bundleObjects = findTransactionObjectsByBundle(nonTailBundleHashes);

  //! add tail transactions found with findTransactionObjectsByBundle
  for (const auto& trx : bundleObjects) {
    if (trx.isTailTransaction() && std::find(tailTransactions.begin(), tailTransactions.end(),
                                             trx.getHash()) == tailTransactions.end()) {
      tailTransactions.push_back(trx.getHash());
    }
  }

  // If inclusionStates, get the confirmation status
  // of the tail transactions, and thus the bundles
  getInclusionStatesResponse inclusionStates;
  if (withInclusionStates && !tailTransactions.empty()) {
    inclusionStates = getLatestInclusion(tailTransactions);

    if (inclusionStates.getStates().empty()) {
      throw Errors::IllegalState("No inclusion states");
    }
  }

  std::vector<Bundle> bundles;
  //! TODO: was done in parallel in java lib, do we need to or performance are fine in cpp?
  for (std::size_t i = 0; i < tailTransactions.size(); ++i) {
    try {
      const auto& transaction    = tailTransactions[i];
      auto        bundleResponse = getBundle(transaction);
      auto        gbr            = Bundle{ bundleResponse.getTransactions() };

      if (gbr.getTransactions().empty()) {
        continue;
      }

      if (withInclusionStates) {
        bool inclusion = inclusionStates.getStates()[i];

        for (auto& t : gbr.getTransactions()) {
          t.setPersistence(inclusion);
        }
      }

      bundles.push_back(std::move(gbr));
    } catch (const std::runtime_error&) {
      // If error returned from getBundle, ignore it because the bundle was most likely incorrect
    }
  }

  std::sort(bundles.begin(), bundles.end());

  return bundles;
}

getInclusionStatesResponse
Extended::getLatestInclusion(const std::vector<Type::Trytes>& hashes) const {
  return getInclusionStates(hashes, { getNodeInfo().getLatestSolidSubtangleMilestone() });
}

void
Extended::prepareTransfers() const {
}

getBundleResponse
Extended::getBundle(const Type::Trytes& transaction) const {
  Utils::StopWatch stopWatch;

  //! get bundle hash for transaction
  auto         bundle     = traverseBundle(transaction);
  long         totalSum   = 0;
  Type::Trytes bundleHash = bundle.getTransactions()[0].getBundle();

  //! init curl
  auto curl = Crypto::create(Crypto::SpongeType::KERL);
  curl->reset();

  std::vector<Signature> signaturesToValidate;

  for (std::size_t i = 0; i < bundle.getTransactions().size(); ++i) {
    const auto& trx = bundle.getTransactions()[i];

    if (static_cast<int64_t>(i) != trx.getCurrentIndex()) {
      throw Errors::IllegalState("Invalid Bundle");
    }

    //! sums up transaction values
    auto trxValue = trx.getValue();
    totalSum += trxValue;

    //! Absorb bundle hash + value + timestamp + lastIndex + currentIndex trytes.
    curl->absorb(Type::trytesToTrits(trx.toTrytes().substr(2187, 2187 + 162)));

    //! if transaction has some value, we can processs next transactions
    if (trxValue >= 0) {
      continue;
    }

    Signature sig;
    sig.setAddress(trx.getAddress());
    sig.getSignatureFragments().push_back(trx.getSignatureFragments());

    //! Find the subsequent txs with the remaining signature fragment
    for (std::size_t y = i + 1; y < bundle.getTransactions().size(); ++y) {
      const auto& newBundleTx = bundle.getTransactions()[i];

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
  if (Type::tritsToTrytes(bundleFromTrxs) != bundleHash) {
    throw Errors::IllegalState("Invalid Bundle Hash");
  }

  //! Last tx in the bundle should have currentIndex == lastIndex
  const auto& lastTrx = bundle.getTransactions()[bundle.getLength() - 1];
  if (lastTrx.getCurrentIndex() != (lastTrx.getLastIndex()))
    throw Errors::IllegalState("Invalid Bundle");

  //! Validate the signatures
  for (const auto& signature : signaturesToValidate) {
    Crypto::Signing s;
    const auto&     addr  = signature.getAddress();
    const auto&     frags = signature.getSignatureFragments();

    if (!s.validateSignatures(addr, frags, bundleHash)) {
      throw Errors::IllegalState("Invalid Signature");
    }
  }

  return { bundle.getTransactions(), stopWatch.getElapsedTimeMiliSeconds().count() };
}

getTransfersResponse
Extended::getTransfers(const Type::Trytes& seed, int security, int start, int end,
                       bool inclusionStates) const {
  Utils::StopWatch stopWatch;

  // Validate the seed
  if ((!Type::Seed::isValidSeed(seed))) {
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

  auto gnr     = getNewAddresses(seed, start, security, false, end, true);
  auto bundles = bundlesFromAddresses(gnr.getAddresses(), inclusionStates);

  return { bundles, stopWatch.getElapsedTimeMiliSeconds().count() };
}

void
Extended::replayTransfer() const {
}

void
Extended::sendTransfer() const {
}

std::vector<Transaction>
Extended::sendTrytes(const std::vector<Type::Trytes>& trytes, const unsigned int& depth,
                     const unsigned int& minWeightMagnitude) const {
  // Get branch and trunk
  auto tta = this->getTransactionsToApprove(depth);

  // Attach to tangle, do pow
  auto res = this->attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(),
                                  minWeightMagnitude, trytes);

  this->broadcastAndStore(res.getTrytes());

  std::vector<Transaction> trx;

  for (const auto& trxTrytes : res.getTrytes()) {
    trx.emplace_back(trxTrytes);
  }

  return trx;
}

storeTransactionsResponse
Extended::broadcastAndStore(const std::vector<Type::Trytes>& trytes) const {
  this->broadcastTransactions(trytes);
  return this->storeTransactions(trytes);
}

findTransactionsResponse
Extended::findTransactionsByAddresses(const std::vector<Type::Trytes>& addresses) const {
  return this->findTransactions(addresses, {}, {}, {});
}

findTransactionsResponse
Extended::findTransactionsByDigests(const std::vector<Type::Trytes>& digests) const {
  return this->findTransactions({}, digests, {}, {});
}

findTransactionsResponse
Extended::findTransactionsByApprovees(const std::vector<Type::Trytes>& approvees) const {
  return this->findTransactions({}, {}, approvees, {});
}

findTransactionsResponse
Extended::findTransactionsByBundles(const std::vector<Type::Trytes>& bundles) const {
  return this->findTransactions({}, {}, {}, bundles);
}

getAccountDataResponse
Extended::getAccountData(const Type::Trytes& seed, int security, int index, bool checksum,
                         int total, bool returnAll, int start, int end, bool inclusionStates,
                         long threshold) const {
  Utils::StopWatch stopWatch;

  auto gna = getNewAddresses(seed, index, security, checksum, total, returnAll);
  auto gtr = getTransfers(seed, security, start, end, inclusionStates);
  auto gbr = getInputs(seed, security, start, end, threshold);

  return { gna.getAddresses(), gtr.getTransfers(), gbr.getTotalBalance(),
           stopWatch.getElapsedTimeMiliSeconds().count() };
}

const Type::Trytes&
Extended::findTailTransactionHash(const Type::Trytes& hash) const {
  auto gtr = getTrytes({ hash });

  if (gtr.getTrytes().empty()) {
    throw Errors::IllegalState("Bundle transactions not visible");
  }

  auto trx = Transaction{ gtr.getTrytes()[0] };

  if (trx.getBundle().empty()) {
    throw Errors::IllegalState("Invalid trytes, could not create object");
  }

  if (trx.getCurrentIndex() == 0) {
    return trx.getHash();
  }

  return findTailTransactionHash(trx.getBundle());
}

std::vector<std::string>
Extended::addRemainder(const Type::Trytes& seed, const unsigned int& security,
                       const std::vector<input>& inputs, Bundle& bundle, const std::string& tag,
                       const long& totalValue, const Type::Trytes& remainderAddress,
                       const std::vector<std::string>& signatureFragments) const {
  auto totalTransferValue = totalValue;
  for (const auto& input : inputs) {
    auto thisBalance = input.getBalance();
    auto toSubtract  = -thisBalance;
    // TODO std::chrono ?
    auto timestamp = std::time(0);
    // Add input as bundle entry
    bundle.addTransaction(input.getSecurity(), input.getAddress(), toSubtract, tag, timestamp);
    // If there is a remainder value
    // Add extra output to send remaining funds to
    if (thisBalance >= totalTransferValue) {
      auto remainder = thisBalance - totalTransferValue;
      // If user has provided remainder address
      // Use it to send remaining funds to
      if (remainder > 0 && not remainderAddress.empty()) {
        // Remainder bundle entry
        bundle.addTransaction(1, remainderAddress, remainder, tag, timestamp);
        // Final function for signing inputs
        return this->signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else if (remainder > 0) {
        // Generate a new Address by calling getNewAddress
        auto res = this->getNewAddresses(seed, 0, security, false, 0, false);
        // Remainder bundle entry
        bundle.addTransaction(1, res.getAddresses()[0], remainder, tag, timestamp);
        // Final function for signing inputs
        return this->signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      } else {
        // If there is no remainder, do not add transaction to bundle
        // simply sign and return
        return this->signInputsAndReturn(seed, inputs, bundle, signatureFragments);
      }
      // If multiple inputs provided, subtract the totalTransferValue by
      // the inputs balance
    } else {
      totalTransferValue -= thisBalance;
    }
  }
  throw Errors::IllegalState("Not enough balance");
}

/*
 * Private methods.
 */

Type::Trytes
Extended::newAddress(const Type::Trytes& seed, const int32_t& index, const int32_t& security,
                     bool checksum) const {
  // TODO custom sponge
  // Crypto::create(cryptoType_)
  Crypto::Signing s;

  auto key          = s.key(seed, index, security);
  auto digests      = s.digests(key);
  auto addressTrits = s.address(digests);
  auto address      = Type::tritsToTrytes(addressTrits);

  if (checksum) {
    Crypto::Checksum c;
    address = c.add(address);
  }
  return address;
}

std::vector<std::string>
Extended::signInputsAndReturn(const std::string& seed, const std::vector<input>& inputs,
                              Bundle&                         bundle,
                              const std::vector<std::string>& signatureFragments) const {
  // TODO param ?
  auto curl = Crypto::create(this->cryptoType_);
  bundle.finalize(curl);
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

      Crypto::Signing s;
      // Get corresponding private key of address
      // TODO Do we have to use the previous curl ?
      // int[] key = new Signing(curl).key(Converter.trits(seed), keyIndex, keySecurity);
      auto key = s.key(seed, keyIndex, keySecurity);

      //  First 6561 trits for the firstFragment
      std::vector<int8_t> firstFragment(&key[0], &key[6561]);

      //  Get the normalized bundle hash
      auto normalizedBundleHash = bundle.normalizedBundle(bundleHash);

      //  First bundle fragment uses 27 trytes
      std::vector<int8_t> firstBundleFragment(&normalizedBundleHash[0], &normalizedBundleHash[27]);

      //  Calculate the new signatureFragment with the first bundle fragment
      auto firstSignedFragment = s.signatureFragment(firstBundleFragment, firstFragment);

      //  Convert signature to trytes and assign the new signatureFragment
      tx.setSignatureFragments(Type::tritsToTrytes(firstSignedFragment));

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
            auto secondSignedFragment = s.signatureFragment(secondBundleFragment, secondFragment);

            //  Convert signature to trytes and assign it again to this bundle entry
            txb.setSignatureFragments(Type::tritsToTrytes(secondSignedFragment));
          }
        }
      }
    }
  }

  std::vector<Type::Trytes> bundleTrytes;

  // Convert all bundle entries into trytes
  for (const auto& tx : bundle.getTransactions()) {
    bundleTrytes.push_back(tx.toTrytes());
  }
  std::reverse(bundleTrytes.begin(), bundleTrytes.end());
  return bundleTrytes;
}

}  // namespace API

}  // namespace IOTA
