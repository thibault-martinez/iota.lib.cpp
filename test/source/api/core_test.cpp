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

#include <chrono>
#include <thread>

#include <iota/api/core.hpp>
#include <iota/errors/illegal_state.hpp>
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

TEST(Core, AddRemoveAndGetNeighbors) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto resGetEmpty = api.getNeighbors();
  EXPECT_GE(resGetEmpty.getDuration(), 0);
  EXPECT_EQ(resGetEmpty.getNeighbors().size(), 0UL);

  auto resAdd = api.addNeighbors({ "udp://8.8.8.8:14265", "udp://8.8.8.5:14265" });
  EXPECT_GE(resAdd.getDuration(), 0);
  EXPECT_EQ(resAdd.getAddedNeighbors(), 2);

  auto resGetAfterAdd = api.getNeighbors();
  EXPECT_GE(resGetAfterAdd.getDuration(), 0);
  ASSERT_EQ(resGetAfterAdd.getNeighbors().size(), 2UL);
  EXPECT_EQ(resGetAfterAdd.getNeighbors()[0].getAddress(), "8.8.8.8:14265");
  EXPECT_EQ(resGetAfterAdd.getNeighbors()[1].getAddress(), "8.8.8.5:14265");

  auto resRemove = api.removeNeighbors({ "udp://8.8.8.8:14265", "udp://8.8.8.5:14265" });
  EXPECT_GE(resRemove.getDuration(), 0);
  EXPECT_EQ(resRemove.getRemovedNeighbors(), 2);

  auto resGetAfterRemove = api.getNeighbors();
  EXPECT_GE(resGetAfterRemove.getDuration(), 0);
  EXPECT_EQ(resGetAfterRemove.getNeighbors().size(), 0UL);
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

  EXPECT_EXCEPTION(res = api.getTrytes({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid hashes input")

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

  EXPECT_EXCEPTION(res = api.getBalances({ "9999" }, 100), IOTA::Errors::BadRequest,
                   "Invalid addresses input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetBalancesInvalidThreshold) {
  IOTA::API::Core                   api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::GetBalances res;

  EXPECT_EXCEPTION(res = api.getBalances({ BUNDLE_1_TRX_1_TRYTES }, 0), IOTA::Errors::BadRequest,
                   "Illegal 'threshold'")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetTransactionsToApprove) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTransactionsToApprove(27);

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getTrunkTransaction()));
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getBranchTransaction()));
}

TEST(Core, FindTransactionsWithAddress) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.findTransactions({ BUNDLE_1_TRX_1_ADDRESS }, {}, {}, {});

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Core, FindTransactionsWithInvalidAddress) {
  IOTA::API::Core                        api(get_proxy_host(), get_proxy_port());
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactions({ "9999" }, {}, {}, {}), IOTA::Errors::BadRequest,
                   "Invalid addresses input")

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

  EXPECT_EXCEPTION(res = api.findTransactions({}, {}, { "9999" }, {}), IOTA::Errors::BadRequest,
                   "Invalid approvees input")

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

  EXPECT_EXCEPTION(res = api.findTransactions({}, {}, {}, { "9999" }), IOTA::Errors::BadRequest,
                   "Invalid bundles input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, GetInclusionStates) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true }));
}

TEST(Core, GetInclusionStatesNoTrx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({}, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({}));
}

TEST(Core, GetInclusionStatesOlderMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({ BUNDLE_1_TRX_1_HASH }, { BUNDLE_2_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false }));
}

TEST(Core, GetInclusionStatesNoMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, {});
                   , IOTA::Errors::IllegalState, "Empty list of tips")
}

TEST(Core, GetInclusionStatesInvalidMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, { "hello" }),
                   IOTA::Errors::BadRequest, "Invalid tips input")
}

TEST(Core, GetInclusionStatesInvalidHash) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto hash = BUNDLE_2_TRX_1_HASH;
  hash[0]   = '9';

  auto res = api.getInclusionStates({ hash }, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false }));
}

TEST(Core, InterruptAttachingToTangle) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::AttachToTangle attachToTangleRes;

  //! run attach in background
  std::thread t([&] {
    attachToTangleRes = api.attachToTangle(BUNDLE_2_TRX_1_TRUNK, BUNDLE_2_TRX_1_BRANCH, 18,
                                           { BUNDLE_2_TRX_1_TRYTES });
  });

  //! wait 2 sec to make sure thread started and request was sent
  std::this_thread::sleep_for(std::chrono::seconds(2));

  //! interrup
  api.interruptAttachingToTangle();

  //! wait for attach completion
  t.join();

  //! check that attach indeed failed
  EXPECT_EQ(attachToTangleRes.getTrytes().size(), 0UL);
}

TEST(Core, BroadcastTransactionsEmpty) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsInvalidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "INVALIDTRYTES" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsAlmostInvalidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto tx   = BUNDLE_1_TRX_1_TRYTES;
  tx.back() = '9';
  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "INVALIDTRYTES" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsValidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.storeTransactions({ BUNDLE_1_TRX_1_TRYTES }));
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsValidMultiTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.storeTransactions({ BUNDLE_1_TRX_1_TRYTES, BUNDLE_1_TRX_2_TRYTES,
                                                BUNDLE_1_TRX_3_TRYTES, BUNDLE_1_TRX_4_TRYTES }));
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, StoreTransactionsEmpty) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, StoreTransactionsInvalidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "INVALIDTRYTES" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, StoreTransactionsAlmostInvalidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto tx   = BUNDLE_1_TRX_1_TRYTES;
  tx.back() = '9';
  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.storeTransactions({ "INVALIDTRYTES" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, StoreTransactionsValidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.storeTransactions({ BUNDLE_1_TRX_1_TRYTES }));
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, StoreTransactionsValidMultiTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.storeTransactions({ BUNDLE_1_TRX_1_TRYTES, BUNDLE_1_TRX_2_TRYTES,
                                                BUNDLE_1_TRX_3_TRYTES, BUNDLE_1_TRX_4_TRYTES }));
  EXPECT_GE(res.getDuration(), 0);
}
