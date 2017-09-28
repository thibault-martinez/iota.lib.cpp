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

#include <json.hpp>

#include <iota/api/responses/base.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * BroadcastTransactions API call response.
 * Broadcast a list of transactions to all neighbors. The input trytes for this call are provided by
 * attachToTangle.
 * https://iota.readme.io/docs/broadcasttransactions
 */
class BroadcastTransactions : public Base {
public:
  /**
   * default ctor
   */
  BroadcastTransactions() = default;

  /**
   * default dtor
   */
  ~BroadcastTransactions() = default;

public:
  /**
   * init class based on json data
   *
   * @param res json data to be used for deserialization
   */
  void deserialize(const json& res);
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
