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

#include <API/Requests/findTransactionsRequest.hpp>

namespace IOTA {

namespace API {

findTransactionsRequest::findTransactionsRequest(const std::vector<Type::Trytes>& addresses,
                                                 const std::vector<Type::Trytes>& digests,
                                                 const std::vector<Type::Trytes>& approvees,
                                                 const std::vector<Type::Trytes>& bundles)
    : genericRequest("findTransactions"),
      addresses_(addresses),
      digests_(digests),
      approvees_(approvees),
      bundles_(bundles) {
}

findTransactionsRequest::~findTransactionsRequest() {
}

const std::vector<Type::Trytes>&
findTransactionsRequest::getAddresses() const {
  return this->addresses_;
}

const std::vector<Type::Trytes>&
findTransactionsRequest::getDigests() const {
  return this->digests_;
}

const std::vector<Type::Trytes>&
findTransactionsRequest::getApprovees() const {
  return this->approvees_;
}

const std::vector<Type::Trytes>&
findTransactionsRequest::getBundles() const {
  return this->bundles_;
}

}  // namespace API

}  // namespace IOTA
