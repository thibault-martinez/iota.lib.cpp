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

#include <iota/api/responses/base.hpp>
#include <iota/models/fwd.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * GetAccountData API call response.
 *
 * Similar to getTransfers, just a bit more comprehensive in the sense that it also returns the
 * balance and addresses that are associated with your account (seed). This function is useful in
 * getting all the relevant information of your account.
 */
class GetAccountData : public Base {
public:
  /**
   * Default ctor.
   */
  GetAccountData() = default;

  /**
   * Full init ctor.
   *
   * @param addresses The addresses.
   * @param transfers The transfers.
   * @param balance The balance.
   * @param duration The request duration.
   */
  GetAccountData(const std::vector<Models::Address>& addresses,
                 const std::vector<Models::Bundle>& transfers, const int64_t& balance,
                 const int64_t& duration);

  /**
   * Default dtor.
   */
  ~GetAccountData() = default;

public:
  /**
   * @return The addresses.
   */
  const std::vector<Models::Address>& getAddresses() const;

  /**
   * @return The addresses (non-const version).
   */
  std::vector<Models::Address>& getAddresses();

  /**
   * @param addresses new vector of addresses for GetAccountData response
   */
  void setAddresses(const std::vector<Models::Address>& addresses);

public:
  /**
   * @return The transfers.
   */
  const std::vector<Models::Bundle>& getTransfers() const;

  /**
   * @return The transfers (non-const version).
   */
  std::vector<Models::Bundle>& getTransfers();

  /**
   * @param transfers new vector of bundles for GetAccountData response
   */
  void setTransfers(const std::vector<Models::Bundle>& transfers);

public:
  /**
   * @return The balance.
   */
  const int64_t& getBalance() const;

  /**
   * @param balance new balance for GetAccountData response
   */
  void setBalance(const int64_t& balance);

private:
  /**
   * The account addresses.
   */
  std::vector<Models::Address> addresses_;
  /**
   * The account transfers.
   */
  std::vector<Models::Bundle> transfers_;
  /**
   * The account balance.
   */
  int64_t balance_ = 0;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
