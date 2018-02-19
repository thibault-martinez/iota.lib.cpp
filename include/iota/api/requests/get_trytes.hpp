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
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Requests {

/**
 * GetTrytes API call request.
 *
 * Returns the raw transaction data (trytes) of a specific transaction. These trytes can then be
 * easily converted into the actual transaction object. See utility functions for more details.
 *
 * https://iota.readme.io/reference#gettrytes
 */
class GetTrytes : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param hashes List of transaction hashes of which you want to get trytes from.
   */
  explicit GetTrytes(const std::vector<Types::Trytes>& hashes = {});

  /**
   * Default dtor.
   */
  ~GetTrytes() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

public:
  /**
   * @return hashes.
   */
  const std::vector<Types::Trytes>& getHashes() const;

  /**
   * @return hashes (non const version).
   */
  std::vector<Types::Trytes>& getHashes();

  /**
   * @param hashes new hashes for api call.
   */
  void setHashes(const std::vector<Types::Trytes>& hashes);

private:
  /**
   * List of transaction hashes of which you want to get trytes from.
   */
  std::vector<Types::Trytes> hashes_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
