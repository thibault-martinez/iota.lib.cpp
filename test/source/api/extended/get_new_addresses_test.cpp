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

#include <iota/api/extended.hpp>
#include <iota/api/responses/get_new_addresses.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/seed.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, GetNewAddressesTotalReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 7, true);

  EXPECT_EQ(res.getAddresses().size(), 7UL);
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH);
}

TEST(Extended, GetNewAddressesTotalReturnOne) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 7, false);

  EXPECT_EQ(res.getAddresses().size(), 1UL);
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, GetNewAddressesNoTotalReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 0, true);

  EXPECT_EQ(res.getAddresses().size(), 7UL);
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH);
}

TEST(Extended, GetNewAddressesNoTotalReturnOne) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 0, false);

  EXPECT_EQ(res.getAddresses().size(), 1UL);
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}
