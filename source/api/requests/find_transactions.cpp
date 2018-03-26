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

#include <iota/api/requests/find_transactions.hpp>

namespace IOTA {

namespace API {

namespace Requests {

FindTransactions::FindTransactions(const std::vector<Models::Address>& addresses,
                                   const std::vector<Models::Tag>&     tags,
                                   const std::vector<Types::Trytes>&   approvees,
                                   const std::vector<Types::Trytes>&   bundles)
    : Base("findTransactions"),
      addresses_(addresses),
      tags_(tags),
      approvees_(approvees),
      bundles_(bundles) {
}

void
FindTransactions::serialize(json& data) const {
  Base::serialize(data);
  //
  // if (!addresses_.empty()) {
  //   for (auto& address : addresses_) {
  //     data["addresses"].emplace_back(address.toTrytes());
  //   }
  // }
  //
  // if (!tags_.empty()) {
  //   for (const auto& tag : tags_) {
  //     data["tags"].emplace_back(tag.toTrytesWithPadding());
  //   }
  // }
  //
  // if (!approvees_.empty()) {
  //   data["approvees"] = approvees_;
  // }
  //
  // if (!bundles_.empty()) {
  //   data["bundles"] = bundles_;
  // }
}

const std::vector<Models::Address>&
FindTransactions::getAddresses() const {
  return addresses_;
}

std::vector<Models::Address>&
FindTransactions::getAddresses() {
  return addresses_;
}

void
FindTransactions::setAddresses(const std::vector<Models::Address>& addrs) {
  addresses_ = addrs;
}

const std::vector<Models::Tag>&
FindTransactions::getTags() const {
  return tags_;
}

std::vector<Models::Tag>&
FindTransactions::getTags() {
  return tags_;
}

void
FindTransactions::setTags(const std::vector<Models::Tag>& tags) {
  tags_ = tags;
}

const std::vector<Types::Trytes>&
FindTransactions::getApprovees() const {
  return approvees_;
}

std::vector<Types::Trytes>&
FindTransactions::getApprovees() {
  return approvees_;
}

void
FindTransactions::setApprovees(const std::vector<Types::Trytes>& approvees) {
  approvees_ = approvees;
}

const std::vector<Types::Trytes>&
FindTransactions::getBundles() const {
  return bundles_;
}

std::vector<Types::Trytes>&
FindTransactions::getBundles() {
  return bundles_;
}

void
FindTransactions::setBundles(const std::vector<Types::Trytes>& bundles) {
  bundles_ = bundles;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
