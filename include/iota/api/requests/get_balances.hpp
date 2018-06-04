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

#include <iota/api/requests/base.hpp>
#include <iota/models/address.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Requests {

/**
 * GetBalances API call request.
 *
 * Similar to getInclusionStates. It returns the confirmed balance which a list of addresses have
 * at the latest confirmed milestone. In addition to the balances, it also returns the milestone
 * as well as the index with which the confirmed balance was determined. The balances is returned
 * as a list in the same order as the addresses were provided as input.
 *
 * https://iota.readme.io/reference#getbalances
 */
class GetBalances : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param addresses List of addresses you want to get the confirmed balance from.
   * @param threshold Confirmation threshold, should be set to 100.
   */
  explicit GetBalances(const std::vector<Models::Address>& addresses = {}, const int& threshold = 0,
                       const std::vector<Types::Trytes>& tips = {});

  /**
   * Default dtor.
   */
  ~GetBalances() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

private:
  /**
   * List of addresses you want to get the confirmed balance from.
   */
  std::vector<Models::Address> addresses_;
  /**
   * Confirmation threshold, should be set to 100.
   */
  int threshold_;

  /**
   * List of hashes, if present calculate the balance of addresses from the PoV of these
   * transactions, can be used to chain bundles.
   */
  std::vector<Types::Trytes> tips_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
