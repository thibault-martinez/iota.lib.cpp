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

#include <vector>

#include <iota/api/responses/base.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/*
 * GetAccountData API call response.
 */
class GetAccountData : public Base {
public:
  /**
   * default ctor
   */
  GetAccountData() = default;

  /**
   * full init ctor
   */
  GetAccountData(const std::vector<Types::Trytes>&  addresses,
                 const std::vector<Models::Bundle>& transferBundle, const int64_t& balance,
                 const int64_t& duration);

  /**
   * default dtor
   */
  ~GetAccountData() = default;

public:
  /**
   * @return The addresses.
   */
  const std::vector<Types::Trytes>& getAddresses() const;

  /**
   * @return The addresses (non-const version).
   */
  std::vector<Types::Trytes>& getAddresses();

  /**
   * @param addresses new vector of addresses for GetAccountData response
   */
  void setAddresses(const std::vector<Types::Trytes>& addresses);

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
  std::vector<Types::Trytes>  addresses_;
  std::vector<Models::Bundle> transferBundle_;
  int64_t                     balance_ = 0;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
