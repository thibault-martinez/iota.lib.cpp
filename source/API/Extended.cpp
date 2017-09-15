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

    return getBalancesAndFormat(allAddresses, threshold, start, end, stopWatch, security);
  }
  //  Case 2: iterate till threshold || end
  //
  //  Either start from index: 0 or start (if defined) until threshold is reached.
  //  Calls getNewAddress and deterministically generates and returns all addresses
  //  We then do getBalance, format the output and return it
  else {
    getNewAddressResponse res = getNewAddress(seed, security, start, false, 0, true);
    return getBalancesAndFormat(res.getAddresses(), threshold, start, end, stopWatch, security);
  }
}

getBalancesAndFormatResponse
Extended::getBalancesAndFormat(const std::vector<std::string>&, const int64_t&, const int32_t&,
                               const int32_t&, Utils::StopWatch, const int32_t&) {
  //! TODO
  return { {}, 0, 0 };
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
