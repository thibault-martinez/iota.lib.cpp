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

#include <iota/models/input.hpp>
#include <test/utils/constants.hpp>

TEST(Input, CtorDefault) {
  IOTA::Models::Input i;

  EXPECT_EQ(i.getAddress(), IOTA::Models::Address{ "" });
  EXPECT_EQ(i.getBalance(), 0);
  EXPECT_EQ(i.getKeyIndex(), 0);
  EXPECT_EQ(i.getSecurity(), 0);
}

TEST(Input, CtorFull) {
  IOTA::Models::Input i = { ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3 };

  EXPECT_EQ(i.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(i.getBalance(), 1);
  EXPECT_EQ(i.getKeyIndex(), 2);
  EXPECT_EQ(i.getSecurity(), 3);
}

TEST(Input, ConstGetters) {
  const IOTA::Models::Input i = { ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3 };

  EXPECT_EQ(i.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(i.getBalance(), 1);
  EXPECT_EQ(i.getKeyIndex(), 2);
  EXPECT_EQ(i.getSecurity(), 3);
}

TEST(Input, AddressGetterAndSetter) {
  IOTA::Models::Input i;
  EXPECT_EQ(i.getAddress(), IOTA::Models::Address{ "" });

  i.setAddress(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(i.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
}

TEST(Input, BalanceGetterAndSetter) {
  IOTA::Models::Input i;
  EXPECT_EQ(i.getBalance(), 0);

  i.setBalance(1);
  EXPECT_EQ(i.getBalance(), 1);
}

TEST(Input, KeyIndexGetterAndSetter) {
  IOTA::Models::Input i;
  EXPECT_EQ(i.getKeyIndex(), 0);

  i.setKeyIndex(1);
  EXPECT_EQ(i.getKeyIndex(), 1);
}

TEST(Input, SecurityGetterAndSetter) {
  IOTA::Models::Input i;
  EXPECT_EQ(i.getSecurity(), 0);

  i.setSecurity(1);
  EXPECT_EQ(i.getSecurity(), 1);
}

TEST(Input, EqOperator) {
  IOTA::Models::Input lhs(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  EXPECT_TRUE(lhs == rhs);

  IOTA::Models::Input lhs_neq_1(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_1(ACCOUNT_1_ADDRESS_2_HASH, 1, 2, 3);
  EXPECT_FALSE(lhs_neq_1 == rhs_neq_1);

  IOTA::Models::Input lhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, 4, 2, 3);
  EXPECT_FALSE(lhs_neq_2 == rhs_neq_2);

  IOTA::Models::Input lhs_neq_3(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_3(ACCOUNT_1_ADDRESS_1_HASH, 1, 4, 3);
  EXPECT_FALSE(lhs_neq_3 == rhs_neq_3);

  IOTA::Models::Input lhs_neq_4(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_4(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 4);
  EXPECT_FALSE(lhs_neq_4 == rhs_neq_4);
}

TEST(Input, NEqOperator) {
  IOTA::Models::Input lhs(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  EXPECT_FALSE(lhs != rhs);

  IOTA::Models::Input lhs_neq_1(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_1(ACCOUNT_1_ADDRESS_2_HASH, 1, 2, 3);
  EXPECT_TRUE(lhs_neq_1 != rhs_neq_1);

  IOTA::Models::Input lhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, 4, 2, 3);
  EXPECT_TRUE(lhs_neq_2 != rhs_neq_2);

  IOTA::Models::Input lhs_neq_3(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_3(ACCOUNT_1_ADDRESS_1_HASH, 1, 4, 3);
  EXPECT_TRUE(lhs_neq_3 != rhs_neq_3);

  IOTA::Models::Input lhs_neq_4(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 3);
  IOTA::Models::Input rhs_neq_4(ACCOUNT_1_ADDRESS_1_HASH, 1, 2, 4);
  EXPECT_TRUE(lhs_neq_4 != rhs_neq_4);
}
