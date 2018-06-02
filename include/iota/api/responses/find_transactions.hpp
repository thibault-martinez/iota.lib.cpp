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
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * FindTransactions API call response.
 *
 * Find the transactions which match the specified input and return. All input values are lists,
 * for which a list of return values (transaction hashes), in the same order, is returned for all
 * individual elements. The input fields can either be bundles, addresses, tags or approvees.
 * Using multiple of these input fields returns the intersection of the values.
 *
 * https://iota.readme.io/reference#findtransactions
 */
class FindTransactions : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param hashes The transaction hashes.
   */
  explicit FindTransactions(const std::vector<Types::Trytes>& hashes = {});

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit FindTransactions(const json& res);

  /**
   * Default dtor.
   */
  ~FindTransactions() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return hashes.
   */
  const std::vector<Types::Trytes>& getHashes() const;

private:
  /**
   * The transaction hashes which are returned depend on your input. For each specified input value,
   * the command will return the following:
   * bundles: list of transactions which contain the specified bundle hash.
   * addresses: list of transactions which have the specified address as an input/output field.
   * tags: list of transactions which contain the specified tag value.
   * approvees: list of transaction which reference (i.e. confirm) the specified transaction.
   */
  std::vector<Types::Trytes> hashes_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
