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

#include <iota/api/requests/were_addresses_spent_from.hpp>

namespace IOTA {

namespace API {

namespace Requests {

WereAddressesSpentFrom::WereAddressesSpentFrom(const std::vector<Models::Address>& addresses)
    : Base("wereAddressesSpentFrom"), addresses_(addresses) {
}

void
WereAddressesSpentFrom::serialize(json& data) const {
  Base::serialize(data);

  for (auto& address : addresses_) {
    data["addresses"].emplace_back(address.toTrytes());
  }
}

const std::vector<Models::Address>&
WereAddressesSpentFrom::getAddresses() const {
  return addresses_;
}

std::vector<Models::Address>&
WereAddressesSpentFrom::getAddresses() {
  return addresses_;
}

void
WereAddressesSpentFrom::setAddresses(const std::vector<Models::Address>& addrs) {
  addresses_ = addrs;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
