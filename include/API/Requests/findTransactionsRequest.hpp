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

#include <API/Requests/genericRequest.hpp>
#include <Type/Trinary.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

/*
 * findTransactions API call request.
 * Find the transactions which match the specified input and return. All input values are lists, for
 * which a list of return values (transaction hashes), in the same order, is returned for all
 * individual elements. The input fields can either be bundles, addresses, tags or approvees. Using
 * multiple of these input fields returns the intersection of the values.
 * https://iota.readme.io/docs/findtransactions
 */
class findTransactionsRequest : public genericRequest {
public:
  findTransactionsRequest(const std::vector<Type::Trytes>& addresses,
                          const std::vector<Type::Trytes>& digests,
                          const std::vector<Type::Trytes>& approvees,
                          const std::vector<Type::Trytes>& bundles);
  virtual ~findTransactionsRequest();

public:
  const std::vector<Type::Trytes>& getAddresses() const;
  const std::vector<Type::Trytes>& getDigests() const;
  const std::vector<Type::Trytes>& getApprovees() const;
  const std::vector<Type::Trytes>& getBundles() const;

private:
  std::vector<Type::Trytes> addresses_;
  std::vector<Type::Trytes> digests_;
  std::vector<Type::Trytes> approvees_;
  std::vector<Type::Trytes> bundles_;
};

}  // namespace API

}  // namespace IOTA
