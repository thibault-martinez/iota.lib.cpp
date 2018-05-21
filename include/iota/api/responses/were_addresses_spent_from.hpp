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

#pragma once

#include <iota/api/responses/base.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * WereAddressesSpentFrom API call response.
 *
 * Check if a list of addresses was ever spent from, in the current epoch, or in previous epochs.
 *
 * https://iota.readme.io/reference#wereaddressesspentfrom
 */
class WereAddressesSpentFrom : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param states The inclusion states.
   */
  explicit WereAddressesSpentFrom(const std::vector<bool>& states = {});

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit WereAddressesSpentFrom(const json& res);

  /**
   * Default dtor.
   */
  ~WereAddressesSpentFrom() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return Inclusion states of the set of transactions.
   */
  const std::vector<bool>& getStates() const;

  /**
   * @param states new states for api response.
   */
  void setStates(const std::vector<bool>& states);

private:
  /**
   * List of state if addresses were spent from.
   */
  std::vector<bool> states_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
