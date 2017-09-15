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

// TODO const methods ?

#pragma once

#include <API/Responses/getBalancesAndFormatResponse.hpp>
#include <API/Responses/getBalancesResponse.hpp>
#include <API/Responses/getNewAddressResponse.hpp>
#include <Core.hpp>
#include <Utils/StopWatch.hpp>

#include <list>

namespace IOTA {

namespace API {

/*
 * Extended API calls which will help do just about anything possible with IOTA. These
 * are mostly wrapper functions of Core API calls.
 * https://github.com/iotaledger/wiki/blob/master/api-proposal.md#proposed-api-calls
 */
class Extended : public Core {
public:
  Extended(const std::string& host, const unsigned int& port);
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
                                         const int64_t& threshold);

  /**
   * Gets the balances and formats the output.
   *
   * @param addresses The addresses.
   * @param threshold Min balance required.
   * @param start     Starting key index.
   * @param end       Ending key index.
   * @param stopWatch the stopwatch.
   * @param security  The security level of private key / seed.
   * @return Inputs object.
   **/
  getBalancesAndFormatResponse getBalanceAndFormat(const std::vector<std::string>& addresses,
                                                   const int64_t& threshold, const int32_t& start,
                                                   const int32_t& end, Utils::StopWatch stopWatch,
                                                   const int32_t& security);

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
  getNewAddressResponse getNewAddress(const std::string& seed, const int32_t& security,
                                      const int32_t& index, bool checksum, const int32_t& total,
                                      bool returnAll);

  /*
   * Main purpose of this function is to get an array of transfer objects as input, and then prepare
   * the transfer by generating the correct bundle, as well as choosing and signing the inputs if
   * necessary (if it's a value transfer). The output of this function is an array of the raw
   * transaction data (trytes).
   */
  void prepareTransfers();
  /*
   * Generates a new address from a seed and returns the address. This is either done
   * deterministically, or by providing the index of the new address (see Questions for more
   * information about this).
   */
  void getNewAddress();
  /*
   * This function returns the bundle which is associated with a transaction. Input can by any type
   * of transaction (tail and non-tail). If there are multiple bundles (because of a replay for
   * example), it will return multiple bundles. It also does important validation checking
   * (signatures, sum, order) to ensure that the correct bundle is returned.
   */
  void getBundle();
  /*
   * Returns the transfers which are associated with a seed. The transfers are determined by either
   * calculating deterministically which addresses were already used, or by providing a list of
   * indexes to get the transfers from.
   */
  void getTransfers();
  /*
   * Takes a tail transaction hash as input, gets the bundle associated with the transaction and
   * then replays the bundle by attaching it to the tangle.
   */
  void replayTransfer();
  /*
   * Wrapper function that basically does prepareTransfers, as well as attachToTangle and finally,
   * it broadcasts and stores the transactions locally.
   */
  void sendTransfer();
  /*
   * Wrapper function that does attachToTangle and finally, it broadcasts and stores the
   * transactions locally.
   */
  void sendTrytes();
  /*
   * Wrapper function that does broadcastTransactions and storeTransactions.
   */
  void broadcastAndStore();
};

}  // namespace API

}  // namespace IOTA
