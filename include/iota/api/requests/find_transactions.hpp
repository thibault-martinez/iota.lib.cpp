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

// TODO Don't really like that design, refactor it later.

#pragma once

#include <json.hpp>

#include <iota/api/requests/base.hpp>
#include <iota/types/trinary.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {

/*
 * FindTransactions API call request.
 * Find the transactions which match the specified input and return. All input values are lists, for
 * which a list of return values (transaction hashes), in the same order, is returned for all
 * individual elements. The input fields can either be bundles, addresses, tags or approvees. Using
 * multiple of these input fields returns the intersection of the values.
 * https://iota.readme.io/docs/findtransactions
 */
class FindTransactions : public Base {
public:
  FindTransactions(const std::vector<Types::Trytes>& addresses,
                   const std::vector<Types::Trytes>& digests,
                   const std::vector<Types::Trytes>& approvees,
                   const std::vector<Types::Trytes>& bundles);
  ~FindTransactions() = default;

public:
  const std::vector<Types::Trytes>& getAddresses() const;
  const std::vector<Types::Trytes>& getDigests() const;
  const std::vector<Types::Trytes>& getApprovees() const;
  const std::vector<Types::Trytes>& getBundles() const;

private:
  std::vector<Types::Trytes> addresses_;
  std::vector<Types::Trytes> digests_;
  std::vector<Types::Trytes> approvees_;
  std::vector<Types::Trytes> bundles_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
