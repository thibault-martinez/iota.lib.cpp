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
#include <json.hpp>

#include <iota/api/responses/get_transactions_to_approve.hpp>

TEST(GetTransactionsToApproveResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetTransactionsToApprove res{ "TESTA", "TESTB" };

  EXPECT_EQ(res.getTrunkTransaction(), "TESTA");
  EXPECT_EQ(res.getBranchTransaction(), "TESTB");
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetTransactionsToApproveResponse, Setters) {
  IOTA::API::Responses::GetTransactionsToApprove res;

  res.setTrunkTransaction("TEST1");
  res.setBranchTransaction("TEST2");

  EXPECT_EQ(res.getTrunkTransaction(), "TEST1");
  EXPECT_EQ(res.getBranchTransaction(), "TEST2");
}

TEST(GetTransactionsToApproveResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::GetTransactionsToApprove res;
  json                                           data;

  data["trunkTransaction"]  = "TEST1";
  data["branchTransaction"] = "TEST2";
  res.deserialize(data);

  EXPECT_EQ(res.getTrunkTransaction(), "TEST1");
  EXPECT_EQ(res.getBranchTransaction(), "TEST2");
}
