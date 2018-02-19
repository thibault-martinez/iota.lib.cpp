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
#include <iota/models/bundle.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, TraverseBundleTransactionHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.traverseBundle(BUNDLE_1_TRX_1_HASH);

  ASSERT_EQ(res.getTransactions().size(), 4UL);

  const auto& trx1 = res.getTransactions()[0];
  EXPECT_EQ(trx1.getSignatureFragments(), BUNDLE_1_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx1.getCurrentIndex(), BUNDLE_1_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx1.getLastIndex(), BUNDLE_1_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx1.getNonce(), BUNDLE_1_TRX_1_NONCE);
  EXPECT_EQ(trx1.getHash(), BUNDLE_1_TRX_1_HASH);
  EXPECT_EQ(trx1.getTag(), BUNDLE_1_TRX_1_TAG);
  EXPECT_EQ(trx1.getTimestamp(), BUNDLE_1_TRX_1_TS);
  EXPECT_EQ(trx1.getTrunkTransaction(), BUNDLE_1_TRX_1_TRUNK);
  EXPECT_EQ(trx1.getBranchTransaction(), BUNDLE_1_TRX_1_BRANCH);
  EXPECT_EQ(trx1.getAddress(), BUNDLE_1_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), BUNDLE_1_TRX_1_VALUE);
  EXPECT_EQ(trx1.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx1.getPersistence(), false);

  const auto& trx2 = res.getTransactions()[1];
  EXPECT_EQ(trx2.getSignatureFragments(), BUNDLE_1_TRX_2_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx2.getCurrentIndex(), BUNDLE_1_TRX_2_CURRENT_INDEX);
  EXPECT_EQ(trx2.getLastIndex(), BUNDLE_1_TRX_2_LAST_INDEX);
  EXPECT_EQ(trx2.getNonce(), BUNDLE_1_TRX_2_NONCE);
  EXPECT_EQ(trx2.getHash(), BUNDLE_1_TRX_2_HASH);
  EXPECT_EQ(trx2.getTag(), BUNDLE_1_TRX_2_TAG);
  EXPECT_EQ(trx2.getTimestamp(), BUNDLE_1_TRX_2_TS);
  EXPECT_EQ(trx2.getTrunkTransaction(), BUNDLE_1_TRX_2_TRUNK);
  EXPECT_EQ(trx2.getBranchTransaction(), BUNDLE_1_TRX_2_BRANCH);
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_2_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_2_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);

  const auto& trx3 = res.getTransactions()[2];
  EXPECT_EQ(trx3.getSignatureFragments(), BUNDLE_1_TRX_3_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx3.getCurrentIndex(), BUNDLE_1_TRX_3_CURRENT_INDEX);
  EXPECT_EQ(trx3.getLastIndex(), BUNDLE_1_TRX_3_LAST_INDEX);
  EXPECT_EQ(trx3.getNonce(), BUNDLE_1_TRX_3_NONCE);
  EXPECT_EQ(trx3.getHash(), BUNDLE_1_TRX_3_HASH);
  EXPECT_EQ(trx3.getTag(), BUNDLE_1_TRX_3_TAG);
  EXPECT_EQ(trx3.getTimestamp(), BUNDLE_1_TRX_3_TS);
  EXPECT_EQ(trx3.getTrunkTransaction(), BUNDLE_1_TRX_3_TRUNK);
  EXPECT_EQ(trx3.getBranchTransaction(), BUNDLE_1_TRX_3_BRANCH);
  EXPECT_EQ(trx3.getAddress(), BUNDLE_1_TRX_3_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), BUNDLE_1_TRX_3_VALUE);
  EXPECT_EQ(trx3.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx3.getPersistence(), false);

  const auto& trx4 = res.getTransactions()[3];
  EXPECT_EQ(trx4.getSignatureFragments(), BUNDLE_1_TRX_4_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx4.getCurrentIndex(), BUNDLE_1_TRX_4_CURRENT_INDEX);
  EXPECT_EQ(trx4.getLastIndex(), BUNDLE_1_TRX_4_LAST_INDEX);
  EXPECT_EQ(trx4.getNonce(), BUNDLE_1_TRX_4_NONCE);
  EXPECT_EQ(trx4.getHash(), BUNDLE_1_TRX_4_HASH);
  EXPECT_EQ(trx4.getTag(), BUNDLE_1_TRX_4_TAG);
  EXPECT_EQ(trx4.getTimestamp(), BUNDLE_1_TRX_4_TS);
  EXPECT_EQ(trx4.getTrunkTransaction(), BUNDLE_1_TRX_4_TRUNK);
  EXPECT_EQ(trx4.getBranchTransaction(), BUNDLE_1_TRX_4_BRANCH);
  EXPECT_EQ(trx4.getAddress(), BUNDLE_1_TRX_4_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), BUNDLE_1_TRX_4_VALUE);
  EXPECT_EQ(trx4.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx4.getPersistence(), false);
}

TEST(Extended, TraverseBundleTransactionHashNonTail) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.traverseBundle(BUNDLE_1_TRX_2_HASH), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleBundleHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.traverseBundle(BUNDLE_1_HASH), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleInvalidTrxHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  std::string hash = BUNDLE_1_TRX_1_HASH;
  hash[0]          = '9';

  EXPECT_THROW(api.traverseBundle(hash), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.traverseBundle("salut"), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleFullTransactionHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};
  auto res    = api.traverseBundle(BUNDLE_1_TRX_1_HASH, "", bundle);

  ASSERT_EQ(res.getTransactions().size(), 4UL);

  const auto& trx1 = res.getTransactions()[0];
  EXPECT_EQ(trx1.getSignatureFragments(), BUNDLE_1_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx1.getCurrentIndex(), BUNDLE_1_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx1.getLastIndex(), BUNDLE_1_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx1.getNonce(), BUNDLE_1_TRX_1_NONCE);
  EXPECT_EQ(trx1.getHash(), BUNDLE_1_TRX_1_HASH);
  EXPECT_EQ(trx1.getTag(), BUNDLE_1_TRX_1_TAG);
  EXPECT_EQ(trx1.getTimestamp(), BUNDLE_1_TRX_1_TS);
  EXPECT_EQ(trx1.getTrunkTransaction(), BUNDLE_1_TRX_1_TRUNK);
  EXPECT_EQ(trx1.getBranchTransaction(), BUNDLE_1_TRX_1_BRANCH);
  EXPECT_EQ(trx1.getAddress(), BUNDLE_1_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), BUNDLE_1_TRX_1_VALUE);
  EXPECT_EQ(trx1.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx1.getPersistence(), false);

  const auto& trx2 = res.getTransactions()[1];
  EXPECT_EQ(trx2.getSignatureFragments(), BUNDLE_1_TRX_2_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx2.getCurrentIndex(), BUNDLE_1_TRX_2_CURRENT_INDEX);
  EXPECT_EQ(trx2.getLastIndex(), BUNDLE_1_TRX_2_LAST_INDEX);
  EXPECT_EQ(trx2.getNonce(), BUNDLE_1_TRX_2_NONCE);
  EXPECT_EQ(trx2.getHash(), BUNDLE_1_TRX_2_HASH);
  EXPECT_EQ(trx2.getTag(), BUNDLE_1_TRX_2_TAG);
  EXPECT_EQ(trx2.getTimestamp(), BUNDLE_1_TRX_2_TS);
  EXPECT_EQ(trx2.getTrunkTransaction(), BUNDLE_1_TRX_2_TRUNK);
  EXPECT_EQ(trx2.getBranchTransaction(), BUNDLE_1_TRX_2_BRANCH);
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_2_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_2_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);

  const auto& trx3 = res.getTransactions()[2];
  EXPECT_EQ(trx3.getSignatureFragments(), BUNDLE_1_TRX_3_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx3.getCurrentIndex(), BUNDLE_1_TRX_3_CURRENT_INDEX);
  EXPECT_EQ(trx3.getLastIndex(), BUNDLE_1_TRX_3_LAST_INDEX);
  EXPECT_EQ(trx3.getNonce(), BUNDLE_1_TRX_3_NONCE);
  EXPECT_EQ(trx3.getHash(), BUNDLE_1_TRX_3_HASH);
  EXPECT_EQ(trx3.getTag(), BUNDLE_1_TRX_3_TAG);
  EXPECT_EQ(trx3.getTimestamp(), BUNDLE_1_TRX_3_TS);
  EXPECT_EQ(trx3.getTrunkTransaction(), BUNDLE_1_TRX_3_TRUNK);
  EXPECT_EQ(trx3.getBranchTransaction(), BUNDLE_1_TRX_3_BRANCH);
  EXPECT_EQ(trx3.getAddress(), BUNDLE_1_TRX_3_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), BUNDLE_1_TRX_3_VALUE);
  EXPECT_EQ(trx3.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx3.getPersistence(), false);

  const auto& trx4 = res.getTransactions()[3];
  EXPECT_EQ(trx4.getSignatureFragments(), BUNDLE_1_TRX_4_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx4.getCurrentIndex(), BUNDLE_1_TRX_4_CURRENT_INDEX);
  EXPECT_EQ(trx4.getLastIndex(), BUNDLE_1_TRX_4_LAST_INDEX);
  EXPECT_EQ(trx4.getNonce(), BUNDLE_1_TRX_4_NONCE);
  EXPECT_EQ(trx4.getHash(), BUNDLE_1_TRX_4_HASH);
  EXPECT_EQ(trx4.getTag(), BUNDLE_1_TRX_4_TAG);
  EXPECT_EQ(trx4.getTimestamp(), BUNDLE_1_TRX_4_TS);
  EXPECT_EQ(trx4.getTrunkTransaction(), BUNDLE_1_TRX_4_TRUNK);
  EXPECT_EQ(trx4.getBranchTransaction(), BUNDLE_1_TRX_4_BRANCH);
  EXPECT_EQ(trx4.getAddress(), BUNDLE_1_TRX_4_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), BUNDLE_1_TRX_4_VALUE);
  EXPECT_EQ(trx4.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx4.getPersistence(), false);
}

TEST(Extended, TraverseBundleFullTransactionHashNonTail) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_THROW(api.traverseBundle(BUNDLE_1_TRX_2_HASH, "", bundle), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleFullBundleHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_THROW(api.traverseBundle(BUNDLE_1_HASH, "", bundle), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleFullInvalidTrxHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};

  std::string hash = BUNDLE_1_TRX_1_HASH;
  hash[0]          = '9';

  EXPECT_THROW(api.traverseBundle(hash, "", bundle), IOTA::Errors::IllegalState);
}

TEST(Extended, TraverseBundleFullInvalidHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_EXCEPTION(api.traverseBundle("salut", "hello", bundle), IOTA::Errors::BadRequest,
                   "Invalid hashes input");
}

TEST(Extended, TraverseBundleFullInvalidBundleHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};
  auto res    = api.traverseBundle(BUNDLE_1_TRX_1_HASH, "yolo", bundle);

  EXPECT_EQ(res.getTransactions().size(), 0UL);
}

TEST(Extended, TraverseBundleFullIntermediateTrxWithAppending) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{ { IOTA::Models::Transaction{ "address", 42, "TAG", 21 } } };
  auto res    = api.traverseBundle(BUNDLE_1_TRX_4_HASH, BUNDLE_1_HASH, bundle);

  EXPECT_EQ(res.getTransactions().size(), 2UL);

  const auto& trx1 = res.getTransactions()[0];
  EXPECT_EQ(trx1.getAddress(), "address");
  EXPECT_EQ(trx1.getValue(), 42);
  EXPECT_EQ(trx1.getTag(), "TAG");
  EXPECT_EQ(trx1.getTimestamp(), 21);

  const auto& trx2 = res.getTransactions()[1];
  EXPECT_EQ(trx2.getSignatureFragments(), BUNDLE_1_TRX_4_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx2.getCurrentIndex(), BUNDLE_1_TRX_4_CURRENT_INDEX);
  EXPECT_EQ(trx2.getLastIndex(), BUNDLE_1_TRX_4_LAST_INDEX);
  EXPECT_EQ(trx2.getNonce(), BUNDLE_1_TRX_4_NONCE);
  EXPECT_EQ(trx2.getHash(), BUNDLE_1_TRX_4_HASH);
  EXPECT_EQ(trx2.getTag(), BUNDLE_1_TRX_4_TAG);
  EXPECT_EQ(trx2.getTimestamp(), BUNDLE_1_TRX_4_TS);
  EXPECT_EQ(trx2.getTrunkTransaction(), BUNDLE_1_TRX_4_TRUNK);
  EXPECT_EQ(trx2.getBranchTransaction(), BUNDLE_1_TRX_4_BRANCH);
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_4_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_4_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);
}
