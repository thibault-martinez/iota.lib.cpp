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
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Core, GetNodeInfo) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getNodeInfo();

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_FALSE(res.getAppName().empty());
  EXPECT_FALSE(res.getAppVersion().empty());
  EXPECT_GE(res.getJreAvailableProcessors(), 0);
  EXPECT_GE(res.getJreFreeMemory(), 0);
  EXPECT_GE(res.getJreMaxMemory(), 0);
  EXPECT_GE(res.getJreTotalMemory(), 0);
  EXPECT_FALSE(res.getLatestMilestone().empty());
  EXPECT_GE(res.getLatestMilestoneIndex(), 0);
  EXPECT_FALSE(res.getLatestSolidSubtangleMilestone().empty());
  EXPECT_GE(res.getLatestSolidSubtangleMilestoneIndex(), 0);
  EXPECT_GE(res.getNeighbors(), 0);
  EXPECT_GE(res.getPacketsQueueSize(), 0);
  EXPECT_GE(res.getTime(), 0);
  EXPECT_GE(res.getTips(), 0);
  EXPECT_GE(res.getTransactionsToRequest(), 0);
}

TEST(Core, GetNeighbors) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getNeighbors();

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(res.getNeighbors().size() >= 0);
}

TEST(Core, GetTips) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTips();

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(res.getHashes().size() >= 0);
}

TEST(Core, GetTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTrytes({ BUNDLE_1_TRX_1_HASH });

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_EQ(res.getTrytes()[0], BUNDLE_1_TRX_1_TRYTES);
}

TEST(Core, GetTrytesInvalidHash) {
  IOTA::API::Core                 api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::GetTrytes res;

  EXPECT_EXCEPTION(res = api.getTrytes({ "9999" });
                   , IOTA::Errors::BadRequest, "Invalid hashes input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetBalances) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getBalances({ ACCOUNT_1_ADDRESS_1_HASH }, 100);

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_FALSE(res.getBalances().empty());
  EXPECT_GE(res.getMilestoneIndex(), 0);
}

TEST(Core, GetBalancesInvalidAddress) {
  IOTA::API::Core                   api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::GetBalances res;

  EXPECT_EXCEPTION(res = api.getBalances({ "9999" }, 100);
                   , IOTA::Errors::BadRequest, "Invalid addresses input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetBalancesInvalidThreshold) {
  IOTA::API::Core                   api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::GetBalances res;

  EXPECT_EXCEPTION(res = api.getBalances({ BUNDLE_1_TRX_1_TRYTES }, 0);
                   , IOTA::Errors::BadRequest, "Illegal 'threshold'")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetTransactionsToApprove) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTransactionsToApprove(27);

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getTrunkTransaction()));
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getBranchTransaction()));
}

TEST(Core, BroadcastTransactions) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.broadcastTransactions({ BUNDLE_1_TRX_1_TRYTES });

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsInvalidTrytes) {
  IOTA::API::Core            api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::Base res;

  EXPECT_EXCEPTION(res = api.broadcastTransactions({ "9999" });
                   , IOTA::Errors::BadRequest, "Invalid trytes input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, FindTransactionsWithAddress) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.findTransactions({ BUNDLE_1_TRX_1_ADDRESS }, {}, {}, {});

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Core, FindTransactionsWithInvalidAddress) {
  IOTA::API::Core                        api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactions({ "9999" }, {}, {}, {});
                   , IOTA::Errors::BadRequest, "Invalid addresses input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, FindTransactionsWithTag) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.findTransactions({}, { BUNDLE_1_TRX_1_TAG }, {}, {});

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Core, FindTransactionsWithApprovee) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.findTransactions({}, {}, { BUNDLE_1_TRX_2_HASH }, {});

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Core, FindTransactionsWithInvalidApprovee) {
  IOTA::API::Core                        api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactions({}, {}, { "9999" }, {});
                   , IOTA::Errors::BadRequest, "Invalid approvees input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, FindTransactionsWithBundle) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.findTransactions({}, {}, {}, { BUNDLE_1_HASH });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Core, FindTransactionsWithInvalidBundle) {
  IOTA::API::Core                        api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactions({}, {}, {}, { "9999" });
                   , IOTA::Errors::BadRequest, "Invalid bundles input")

  EXPECT_GE(res.getDuration(), 0);
}
