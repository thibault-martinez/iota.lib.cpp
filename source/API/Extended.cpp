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
#include <Crypto/Curl.hpp>
#include <Errors/IllegalState.hpp>
#include <Type/Seed.hpp>
#include <Utils/RandomAddressGenerator.hpp>

namespace IOTA {

namespace API {

Extended::Extended(const std::string& host, const unsigned int& port) : Core(host, port) {
}

Extended::~Extended() {
}

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

  //  Case 1: start and end
  //
  //  If start and end is defined by the user, simply iterate through the keys
  //  and call getBalances
  if (end != 0) {
    std::vector<std::string>      allAddresses;
    Utils::RandomAddressGenerator addressGenerator;

    for (int i = start; i < end; ++i) {
      allAddresses.push_back(addressGenerator(seed, security, i, false, {}));
    }

    return getBalancesAndFormat(allAddresses, threshold, start, stopWatch, security);
  }
  //  Case 2: iterate till threshold || end
  //
  //  Either start from index: 0 or start (if defined) until threshold is reached.
  //  Calls getNewAddress and deterministically generates and returns all addresses
  //  We then do getBalance, format the output and return it
  else {
    getNewAddressResponse res = getNewAddress(seed, security, start, false, 0, true);
    return getBalancesAndFormat(res.getAddresses(), threshold, start, stopWatch, security);
  }
}

getBalancesAndFormatResponse
Extended::getBalancesAndFormat(const std::vector<std::string>& addresses, const int64_t& threshold,
                               const int32_t& start, Utils::StopWatch stopWatch,
                               const int32_t& security) {
  if (security < 1 || security > 3) {
    throw std::runtime_error("Invalid Security Level");
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
    throw std::runtime_error("Not enough balance");
  }

  return { inputs, totalBalance, stopWatch.getElapsedTimeMiliSeconds().count() };
}

getNewAddressResponse
Extended::getNewAddress(const std::string&, const int32_t&, const int32_t&, bool, const int32_t&,
                        bool) {
  //! TODO
  return { {}, 0 };
}

void
Extended::prepareTransfers() {
}

void
Extended::getNewAddress() {
}

void
Extended::getBundle() {
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

}  // namespace API

}  // namespace IOTA
