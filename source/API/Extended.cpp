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
                    const int32_t& end, const int64_t& threshold) {
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
                               const int32_t& security) {
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
                          bool checksum, const int32_t& total, bool returnAll) {
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
Extended::traverseBundle(const std::string& trunkTx) {
  Bundle bundle;
  return traverseBundle(trunkTx, "", bundle);
}

Bundle
Extended::traverseBundle(const std::string& trunkTx, std::string bundleHash, Bundle& bundle) {
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
Extended::findTransactionObjects(const std::vector<IOTA::Type::Trytes>& input) {
  //! get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions(input, {}, {}, {}).getHashes());
}

std::vector<Transaction>
Extended::findTransactionObjectsByBundle(const std::vector<IOTA::Type::Trytes>& input) {
  // get the transaction objects of the transactions
  return getTransactionsObjects(findTransactions({}, {}, {}, input).getHashes());
}

std::vector<Transaction>
Extended::getTransactionsObjects(const std::vector<IOTA::Type::Trytes>& hashes) {
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
                               bool                                   withInclusionStates) {
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
Extended::getLatestInclusion(const std::vector<Type::Trytes>& hashes) {
  return getInclusionStates(hashes, { getNodeInfo().getLatestSolidSubtangleMilestone() });
}

void
Extended::prepareTransfers() {
}

void
Extended::getNewAddress() {
}

getBundleResponse
Extended::getBundle(const Type::Trytes&) {
  return { {}, 0 };
}

void
Extended::getTransfers() {
}

void
Extended::replayTransfer() {
}

void
Extended::sendTransfer() {
}

void
Extended::sendTrytes() {
}

void
Extended::broadcastAndStore() {
}

findTransactionsResponse
Extended::findTransactionsByAddresses(const std::vector<Type::Trytes>& addresses) {
  return this->findTransactions(addresses, {}, {}, {});
}

findTransactionsResponse
Extended::findTransactionsByDigests(const std::vector<Type::Trytes>& digests) {
  return this->findTransactions({}, digests, {}, {});
}

findTransactionsResponse
Extended::findTransactionsByApprovees(const std::vector<Type::Trytes>& approvees) {
  return this->findTransactions({}, {}, approvees, {});
}

findTransactionsResponse
Extended::findTransactionsByBundles(const std::vector<Type::Trytes>& bundles) {
  return this->findTransactions({}, {}, {}, bundles);
}

/*
 * Private methods.
 */

Type::Trytes
Extended::newAddress(const Type::Trytes& seed, const int32_t& index, const int32_t& security,
                     bool checksum) {
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

}  // namespace API

}  // namespace IOTA
