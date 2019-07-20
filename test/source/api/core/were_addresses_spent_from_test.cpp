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

#include <gtest/gtest.h>

#include <iota/api/core.hpp>
#include <iota/api/responses/were_addresses_spent_from.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

class TestWereAddressesSpentFrom : public IOTA::API::Core {
public:
  TestWereAddressesSpentFrom(const std::string& host, int port)
      : IOTA::API::Core(host, port) {}

  IOTA::API::Responses::WereAddressesSpentFrom wereAddressesSpentFrom(
      const std::vector<IOTA::Models::Address>& addresses) const {
        return IOTA::API::Core::wereAddressesSpentFrom(addresses);
      }
};

TEST(Core, WereAddressesSpentFromOneTrue) {
  TestWereAddressesSpentFrom api(get_proxy_host(), get_proxy_port());

  auto res = api.wereAddressesSpentFrom({ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true }));
}

TEST(Core, WereAddressesSpentFromOneFalse) {
  TestWereAddressesSpentFrom api(get_proxy_host(), get_proxy_port());

  auto res = api.wereAddressesSpentFrom({ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false }));
}

TEST(Core, WereAddressesSpentFromMany) {
  TestWereAddressesSpentFrom api(get_proxy_host(), get_proxy_port());

  auto res = api.wereAddressesSpentFrom(
      { ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
        ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false, true, false, true }));
}

TEST(Core, WereAddressesSpentFromEmpty) {
  TestWereAddressesSpentFrom api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(auto res = api.wereAddressesSpentFrom({});
                   , IOTA::Errors::BadRequest, "Invalid parameters")
}
