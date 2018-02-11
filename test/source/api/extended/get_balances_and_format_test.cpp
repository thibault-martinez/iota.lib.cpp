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
#include <iota/errors/illegal_state.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Extended, GetBalancesAndFormat) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getBalancesAndFormat(
      { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH }, 0, 0, 2);

  //! address 1 has 0 iota, should not be returned as input

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_ADDRESS_2_FUND + ACCOUNT_2_ADDRESS_3_FUND);
  ASSERT_EQ(res.getInputs().size(), 2UL);

  const auto& input_1 = res.getInputs()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_2_ADDRESS_2_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 1);  //! still note the offset is shifted by one
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInputs()[1];
  EXPECT_EQ(input_2.getAddress(), ACCOUNT_2_ADDRESS_3_HASH);
  EXPECT_EQ(input_2.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input_2.getKeyIndex(), 2);  //! still note the offset is shifted by one
  EXPECT_EQ(input_2.getSecurity(), 2);
}

TEST(Extended, GetBalancesAndFormatInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBalancesAndFormat(
                   { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH },
                   0, 0, 0),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormatInvalidBalance) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBalancesAndFormat(
                   { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH },
                   717650144175136, 0, 2),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormatStart) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getBalancesAndFormat(
      { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH }, 0, 10, 2);

  //! address 1 has 0 iota, should not be returned as input

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_ADDRESS_2_FUND + ACCOUNT_2_ADDRESS_3_FUND);
  ASSERT_EQ(res.getInputs().size(), 2UL);

  const auto& input_1 = res.getInputs()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_2_ADDRESS_2_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 11);  //! still note the offset is shifted by one
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInputs()[1];
  EXPECT_EQ(input_2.getAddress(), ACCOUNT_2_ADDRESS_3_HASH);
  EXPECT_EQ(input_2.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input_2.getKeyIndex(), 12);  //! still note the offset is shifted by one
  EXPECT_EQ(input_2.getSecurity(), 2);
}
