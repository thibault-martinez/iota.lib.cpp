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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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

#include <vector>

#include <API/Responses/genericResponse.hpp>
#include <Model/Bundle.hpp>
#include <Type/Trinary.hpp>

/*
 * getAccountData API call response.
 */
class getAccountDataResponse : public genericResponse {
public:
  /**
   * default ctor
   */
  getAccountDataResponse();

  /**
   * full init ctor
   */
  getAccountDataResponse(const std::vector<IOTA::Type::Trytes>& addresses,
                         const std::vector<Bundle>& transferBundle, long balance, long duration);

  /**
   * default dtor
   */
  ~getAccountDataResponse() = default;

public:
  /**
   * @return The addresses.
   */
  const std::vector<IOTA::Type::Trytes>& getAddresses() const;

  /**
   * @return The addresses (non-const version).
   */
  std::vector<IOTA::Type::Trytes>& getAddresses();

  /**
   * @param addresses new vector of addresses for getAccountData response
   */
  void setAddresses(const std::vector<IOTA::Type::Trytes>& addresses);

public:
  /**
   * @return The transfers.
   */
  const std::vector<Bundle>& getTransfers() const;

  /**
   * @return The transfers (non-const version).
   */
  std::vector<Bundle>& getTransfers();

  /**
   * @param transfers new vector of bundles for getAccountData response
   */
  void setTransfers(const std::vector<Bundle>& transfers);

public:
  /**
   * @return The balance.
   */
  long getBalance() const;

  /**
   * @param balance new balance for getAccountData response
   */
  void setBalance(long balance);

private:
  std::vector<IOTA::Type::Trytes> addresses_;
  std::vector<Bundle>             transferBundle_;
  long                            balance_;
};
