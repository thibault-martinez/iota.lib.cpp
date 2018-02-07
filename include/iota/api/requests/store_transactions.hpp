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

#include <json.hpp>

#include <iota/api/requests/base.hpp>
#include <iota/types/trinary.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {

/*
 * StoreTransactions API call request.
 *
 * Store transactions into the local storage. The trytes to be used for this call are returned by
 * attachToTangle.
 *
 * https://iota.readme.io/reference#storetransactions
 */
class StoreTransactions : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param trytes List of raw data of transactions to be rebroadcast.
   */
  explicit StoreTransactions(const std::vector<Types::Trytes>& trytes = {});

  /**
   * Default dtor.
   */
  ~StoreTransactions() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

public:
  /**
   * @return trytes.
   */
  const std::vector<Types::Trytes>& getTrytes() const;

  /**
   * @return trytes (non const version).
   */
  std::vector<Types::Trytes>& getTrytes();

  /**
   * @param trytes new trytes for api call.
   */
  void setTrytes(const std::vector<Types::Trytes>& trytes);

private:
  /*
   * List of raw data of transactions to be rebroadcast.
   */
  std::vector<Types::Trytes> trytes_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
