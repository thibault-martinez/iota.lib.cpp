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
#include <iota/models/tag.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Requests {

/**
 * FindTransactions API call request.
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
   * @param addresses List of addresses.
   * @param tags List of transaction tags.
   * @param approvees List of approvees of a transaction.
   * @param bundles List of bundle hashes. The hashes need to be extended to 81chars by padding
   * the hash with 9's.
   */
  explicit FindTransactions(const std::vector<Types::Trytes>& addresses = {},
                            const std::vector<Models::Tag>&   tags      = {},
                            const std::vector<Types::Trytes>& approvees = {},
                            const std::vector<Types::Trytes>& bundles   = {});

  /**
   * Default dtor.
   */
  ~FindTransactions() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

public:
  /**
   * @return addresses.
   */
  const std::vector<Types::Trytes>& getAddresses() const;

  /**
   * @return addresses (non const version).
   */
  std::vector<Types::Trytes>& getAddresses();

  /**
   * @param addrs new addresses for api call.
   */
  void setAddresses(const std::vector<Types::Trytes>& addrs);

public:
  /**
   * @return tags.
   */
  const std::vector<Models::Tag>& getTags() const;

  /**
   * @return tags (non const version).
   */
  std::vector<Models::Tag>& getTags();

  /**
   * @param tags new tags for api call.
   */
  void setTags(const std::vector<Models::Tag>& tags);

public:
  /**
   * @return approvees.
   */
  const std::vector<Types::Trytes>& getApprovees() const;

  /**
   * @return approvees (non const version).
   */
  std::vector<Types::Trytes>& getApprovees();

  /**
   * @param approvees new approvees for api call.
   */
  void setApprovees(const std::vector<Types::Trytes>& approvees);

public:
  /**
   * @return bundles.
   */
  const std::vector<Types::Trytes>& getBundles() const;

  /**
   * @return bundles (non const version).
   */
  std::vector<Types::Trytes>& getBundles();

  /**
   * @param bundles new bundles for api call.
   */
  void setBundles(const std::vector<Types::Trytes>& bundles);

private:
  /**
   * List of addresses.
   */
  std::vector<Types::Trytes> addresses_;
  /**
   * List of transaction tags.
   */
  std::vector<Models::Tag> tags_;
  /**
   * List of approvees of a transaction.
   */
  std::vector<Types::Trytes> approvees_;
  /**
   * List of bundle hashes. The hashes need to be extended to 81chars by padding the hash with
   * 9's.
   */
  std::vector<Types::Trytes> bundles_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
