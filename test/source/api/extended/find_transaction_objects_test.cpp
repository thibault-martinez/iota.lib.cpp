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
#include <iota/models/transaction.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Extended, FindTransactionObjects) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjects({ BUNDLE_1_TRX_1_ADDRESS });

  ASSERT_EQ(res.size(), 2UL);

  //! initial funding of account_2:address_1
  const auto& trx1 = res[0];
  EXPECT_EQ(trx1.getSignatureFragments(), BUNDLE_2_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx1.getCurrentIndex(), BUNDLE_2_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx1.getLastIndex(), BUNDLE_2_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx1.getNonce(), BUNDLE_2_TRX_1_NONCE);
  EXPECT_EQ(trx1.getHash(), BUNDLE_2_TRX_1_HASH);
  EXPECT_EQ(trx1.getTag(), BUNDLE_2_TRX_1_TAG);
  EXPECT_EQ(trx1.getTimestamp(), BUNDLE_2_TRX_1_TS);
  EXPECT_EQ(trx1.getTrunkTransaction(), BUNDLE_2_TRX_1_TRUNK);
  EXPECT_EQ(trx1.getBranchTransaction(), BUNDLE_2_TRX_1_BRANCH);
  EXPECT_EQ(trx1.getAddress(), BUNDLE_2_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), BUNDLE_2_TRX_1_VALUE);
  EXPECT_EQ(trx1.getBundle(), BUNDLE_2_HASH);
  EXPECT_EQ(trx1.getPersistence(), false);

  //! trx spending from account2 to account3
  const auto& trx2 = res[1];
  EXPECT_EQ(trx2.getSignatureFragments(), BUNDLE_1_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx2.getCurrentIndex(), BUNDLE_1_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx2.getLastIndex(), BUNDLE_1_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx2.getNonce(), BUNDLE_1_TRX_1_NONCE);
  EXPECT_EQ(trx2.getHash(), BUNDLE_1_TRX_1_HASH);
  EXPECT_EQ(trx2.getTag(), BUNDLE_1_TRX_1_TAG);
  EXPECT_EQ(trx2.getTimestamp(), BUNDLE_1_TRX_1_TS);
  EXPECT_EQ(trx2.getTrunkTransaction(), BUNDLE_1_TRX_1_TRUNK);
  EXPECT_EQ(trx2.getBranchTransaction(), BUNDLE_1_TRX_1_BRANCH);
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_1_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);
}

TEST(Extended, FindTransactionObjectsBundleHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjects({ BUNDLE_1_HASH });

  EXPECT_EQ(res.size(), 0UL);
}

TEST(Extended, FindTransactionObjectsTrxHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjects({ BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.size(), 0UL);
}

TEST(Extended, FindTransactionObjectsInvalidAddrHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  std::string hash = BUNDLE_1_TRX_1_ADDRESS;
  hash[0]          = '9';

  auto res = api.findTransactionObjects({ hash });
  EXPECT_EQ(res.size(), 0UL);
}

TEST(Extended, FindTransactionObjectsInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.findTransactionObjects({ "hello" }), IOTA::Errors::BadRequest);
}
