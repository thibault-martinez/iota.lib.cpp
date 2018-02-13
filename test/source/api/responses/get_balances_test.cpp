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

#include <iota/api/responses/get_balances.hpp>

TEST(GetBalancesReponse, DefaultCtorShouldInitFields) {
  const IOTA::API::Responses::GetBalances res;

  EXPECT_EQ(res.getBalances(), std::vector<std::string>());
  EXPECT_EQ(res.getMilestone(), "");
  EXPECT_EQ(res.getMilestoneIndex(), 0);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetBalances res{ { "bal1", "bal2", "bal3" }, "milestone", 1 };

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3" }));
  EXPECT_EQ(res.getMilestone(), "milestone");
  EXPECT_EQ(res.getMilestoneIndex(), 1);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, AssignementOperator) {
  const IOTA::API::Responses::GetBalances res1{ { "bal1", "bal2", "bal3" }, "milestone", 1 };
  IOTA::API::Responses::GetBalances       res2;

  res2 = res1;
  EXPECT_EQ(res1.getBalances(), res2.getBalances());
  EXPECT_EQ(res1.getMilestone(), res2.getMilestone());
  EXPECT_EQ(res1.getMilestoneIndex(), res2.getMilestoneIndex());
  EXPECT_EQ(res1.getDuration(), res2.getDuration());
}

TEST(GetBalancesReponse, GetBalancesNonConst) {
  IOTA::API::Responses::GetBalances res{ { "bal1", "bal2", "bal3" }, "milestone", 1 };

  res.getBalances().push_back("bal4");

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3", "bal4" }));
  EXPECT_EQ(res.getMilestone(), "milestone");
  EXPECT_EQ(res.getMilestoneIndex(), 1);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, SetBalances) {
  IOTA::API::Responses::GetBalances res{ { "bal1", "bal2", "bal3" }, "milestone", 1 };

  res.setBalances({ "bal1", "bal2", "bal3", "bal4" });

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3", "bal4" }));
  EXPECT_EQ(res.getMilestone(), "milestone");
  EXPECT_EQ(res.getMilestoneIndex(), 1);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, SetMilestone) {
  IOTA::API::Responses::GetBalances res{ { "bal1", "bal2", "bal3" }, "milestone", 1 };

  res.setMilestone("newmilestone");

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3" }));
  EXPECT_EQ(res.getMilestone(), "newmilestone");
  EXPECT_EQ(res.getMilestoneIndex(), 1);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, SetMilestoneIndex) {
  IOTA::API::Responses::GetBalances res{ { "bal1", "bal2", "bal3" }, "milestone", 1 };

  res.setMilestoneIndex(42);

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3" }));
  EXPECT_EQ(res.getMilestone(), "milestone");
  EXPECT_EQ(res.getMilestoneIndex(), 42);
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBalancesReponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::GetBalances res;
  json                              data;

  data["balances"]       = std::vector<std::string>({ "bal1", "bal2", "bal3" });
  data["milestone"]      = "milestone";
  data["milestoneIndex"] = 1;

  res.deserialize(data);

  EXPECT_EQ(res.getBalances(), std::vector<std::string>({ "bal1", "bal2", "bal3" }));
  EXPECT_EQ(res.getMilestone(), "milestone");
  EXPECT_EQ(res.getMilestoneIndex(), 1);
  EXPECT_EQ(res.getDuration(), 0);
}
