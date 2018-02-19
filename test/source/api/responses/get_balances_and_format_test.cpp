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

#include <iota/api/responses/get_balances_and_format.hpp>
#include <iota/models/input.hpp>

TEST(GetBalancesAndFormatResponse, DefaultCtorShouldInitFields) {
  const IOTA::API::Responses::GetBalancesAndFormat res{};

  EXPECT_EQ(res.getInputs().size(), 0UL);
  EXPECT_EQ(res.getTotalBalance(), 0);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesAndFormatResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetBalancesAndFormat res(
      { { "addr1", 1, 2, 3 }, { "addr2", 4, 5, 6 }, { "addr3", 7, 8, 9 } }, 42, 21);

  ASSERT_EQ(res.getInputs().size(), 3UL);

  EXPECT_EQ(res.getInputs()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getInputs()[0].getBalance(), 1);
  EXPECT_EQ(res.getInputs()[0].getKeyIndex(), 2);
  EXPECT_EQ(res.getInputs()[0].getSecurity(), 3);

  EXPECT_EQ(res.getInputs()[1].getAddress(), "addr2");
  EXPECT_EQ(res.getInputs()[1].getBalance(), 4);
  EXPECT_EQ(res.getInputs()[1].getKeyIndex(), 5);
  EXPECT_EQ(res.getInputs()[1].getSecurity(), 6);

  EXPECT_EQ(res.getInputs()[2].getAddress(), "addr3");
  EXPECT_EQ(res.getInputs()[2].getBalance(), 7);
  EXPECT_EQ(res.getInputs()[2].getKeyIndex(), 8);
  EXPECT_EQ(res.getInputs()[2].getSecurity(), 9);

  EXPECT_EQ(res.getTotalBalance(), 42);
  EXPECT_EQ(res.getDuration(), 21);
}

TEST(GetBalancesAndFormatResponse, GetInputsNonConst) {
  IOTA::API::Responses::GetBalancesAndFormat res;

  res.getInputs().push_back({ "addr1", 1, 2, 3 });

  ASSERT_EQ(res.getInputs().size(), 1UL);

  EXPECT_EQ(res.getInputs()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getInputs()[0].getBalance(), 1);
  EXPECT_EQ(res.getInputs()[0].getKeyIndex(), 2);
  EXPECT_EQ(res.getInputs()[0].getSecurity(), 3);

  EXPECT_EQ(res.getDuration(), 0);
  EXPECT_EQ(res.getTotalBalance(), 0);
}

TEST(GetBalancesAndFormatResponse, SetInputs) {
  IOTA::API::Responses::GetBalancesAndFormat res;

  res.setInputs({ { "addr1", 1, 2, 3 } });

  ASSERT_EQ(res.getInputs().size(), 1UL);

  EXPECT_EQ(res.getInputs()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getInputs()[0].getBalance(), 1);
  EXPECT_EQ(res.getInputs()[0].getKeyIndex(), 2);
  EXPECT_EQ(res.getInputs()[0].getSecurity(), 3);

  EXPECT_EQ(res.getDuration(), 0);
  EXPECT_EQ(res.getTotalBalance(), 0);
}

TEST(GetBalancesAndFormatResponse, SetTotalBalance) {
  IOTA::API::Responses::GetBalancesAndFormat res;

  res.setTotalBalance(42);

  EXPECT_EQ(res.getInputs().size(), 0UL);
  EXPECT_EQ(res.getTotalBalance(), 42);
  EXPECT_EQ(res.getDuration(), 0);
}
