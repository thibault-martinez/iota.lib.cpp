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
 * CheckConsistency API call request.
 *
 * Used to ensure tail resolves to a consistent ledger which is necessary to validate before
 * attempting promotionChecks transaction hashes for promotability.
 *
 * This is called with a pending transaction (or more of them) and it will tell you if it is still
 * possible for this transaction (or all the transactions simultaneously if you give more than one)
 * to be confirmed, or not (because it conflicts with another already confirmed transaction).
 *
 * https://iota.readme.io/reference#checkconsistency
 */
class CheckConsistency : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param tails List of tail transactions you want consistency from.
   */
  explicit CheckConsistency(const std::vector<Types::Trytes>& tails = {});

  /**
   * Default dtor.
   */
  ~CheckConsistency() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

private:
  /**
   * List of tail transactions you want consistency from.
   */
  std::vector<Types::Trytes> tails_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
