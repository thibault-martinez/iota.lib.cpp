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
#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/address.hpp>
#include <iota/models/seed.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, GetInputs) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getInputs(ACCOUNT_2_SEED, 0, 0, 0);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_FUND);
  ASSERT_EQ(res.getInputs().size(), 4UL);

  //! Note that the first address is skipped because it has no fund

  auto input1 = res.getInputs()[0];
  EXPECT_EQ(input1.toTrytes(), ACCOUNT_2_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input1.getKeyIndex(), 1);
  EXPECT_EQ(input1.getSecurity(), 2);

  auto input2 = res.getInputs()[1];
  EXPECT_EQ(input2.toTrytes(), ACCOUNT_2_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input2.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input2.getKeyIndex(), 2);
  EXPECT_EQ(input2.getSecurity(), 2);

  auto input3 = res.getInputs()[2];
  EXPECT_EQ(input3.toTrytes(), ACCOUNT_2_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input3.getBalance(), ACCOUNT_2_ADDRESS_4_FUND);
  EXPECT_EQ(input3.getKeyIndex(), 3);
  EXPECT_EQ(input3.getSecurity(), 2);

  auto input4 = res.getInputs()[3];
  EXPECT_EQ(input4.toTrytes(), ACCOUNT_2_ADDRESS_5_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input4.getBalance(), ACCOUNT_2_ADDRESS_5_FUND);
  EXPECT_EQ(input4.getKeyIndex(), 4);
  EXPECT_EQ(input4.getSecurity(), 2);
}

TEST(Extended, GetInputsStartEnd) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getInputs(ACCOUNT_2_SEED, 2, 4, 0);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_ADDRESS_3_FUND + ACCOUNT_2_ADDRESS_4_FUND);
  ASSERT_EQ(res.getInputs().size(), 2UL);

  //! Note that the first address is skipped because it has no fund

  auto input1 = res.getInputs()[0];
  EXPECT_EQ(input1.toTrytes(), ACCOUNT_2_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input1.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input1.getKeyIndex(), 2);
  EXPECT_EQ(input1.getSecurity(), 2);

  auto input2 = res.getInputs()[1];
  EXPECT_EQ(input2.toTrytes(), ACCOUNT_2_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input2.getBalance(), ACCOUNT_2_ADDRESS_4_FUND);
  EXPECT_EQ(input2.getKeyIndex(), 3);
  EXPECT_EQ(input2.getSecurity(), 2);
}

TEST(Extended, GetInputsInvalidStart) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  EXPECT_EXCEPTION(auto res = api.getInputs(ACCOUNT_2_SEED, 5, 4, 0), IOTA::Errors::IllegalState,
                   "Invalid inputs provided");
}

TEST(Extended, GetInputMin) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getInputs(ACCOUNT_2_SEED, 0, 0, 1000000), IOTA::Errors::IllegalState);
}
