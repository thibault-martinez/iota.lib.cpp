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
#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, GetBundleTransactionHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getBundle(BUNDLE_1_TRX_1_HASH);

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

TEST(Extended, GetBundleTransactionHashNonTail) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBundle(BUNDLE_1_TRX_2_HASH), IOTA::Errors::IllegalState);
}

TEST(Extended, GetBundleBundleHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBundle(BUNDLE_1_HASH), IOTA::Errors::IllegalState);
}

TEST(Extended, GetBundleInvalidTrxHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  std::string hash = BUNDLE_1_TRX_1_HASH;
  hash[0]          = '9';

  EXPECT_THROW(api.getBundle(hash), IOTA::Errors::IllegalState);
}

TEST(Extended, GetBundleInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBundle("salut"), IOTA::Errors::IllegalState);
}

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
  auto bundle = IOTA::Models::Bundle{ { IOTA::Models::Transaction{ "address", 42, "tag", 21 } } };
  auto res    = api.traverseBundle(BUNDLE_1_TRX_4_HASH, BUNDLE_1_HASH, bundle);

  EXPECT_EQ(res.getTransactions().size(), 2UL);

  const auto& trx1 = res.getTransactions()[0];
  EXPECT_EQ(trx1.getAddress(), "address");
  EXPECT_EQ(trx1.getValue(), 42);
  EXPECT_EQ(trx1.getTag(), "tag");
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

TEST(Extended, FindTransactionObjectsByBundle) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjectsByBundle({ BUNDLE_1_HASH });

  ASSERT_EQ(res.size(), 4UL);

  //! note that transactions are NOT ordered

  const auto& trx1 = res[0];
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

  const auto& trx2 = res[1];
  EXPECT_EQ(trx2.getSignatureFragments(), BUNDLE_1_TRX_3_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx2.getCurrentIndex(), BUNDLE_1_TRX_3_CURRENT_INDEX);
  EXPECT_EQ(trx2.getLastIndex(), BUNDLE_1_TRX_3_LAST_INDEX);
  EXPECT_EQ(trx2.getNonce(), BUNDLE_1_TRX_3_NONCE);
  EXPECT_EQ(trx2.getHash(), BUNDLE_1_TRX_3_HASH);
  EXPECT_EQ(trx2.getTag(), BUNDLE_1_TRX_3_TAG);
  EXPECT_EQ(trx2.getTimestamp(), BUNDLE_1_TRX_3_TS);
  EXPECT_EQ(trx2.getTrunkTransaction(), BUNDLE_1_TRX_3_TRUNK);
  EXPECT_EQ(trx2.getBranchTransaction(), BUNDLE_1_TRX_3_BRANCH);
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_3_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_3_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);

  const auto& trx3 = res[2];
  EXPECT_EQ(trx3.getSignatureFragments(), BUNDLE_1_TRX_4_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx3.getCurrentIndex(), BUNDLE_1_TRX_4_CURRENT_INDEX);
  EXPECT_EQ(trx3.getLastIndex(), BUNDLE_1_TRX_4_LAST_INDEX);
  EXPECT_EQ(trx3.getNonce(), BUNDLE_1_TRX_4_NONCE);
  EXPECT_EQ(trx3.getHash(), BUNDLE_1_TRX_4_HASH);
  EXPECT_EQ(trx3.getTag(), BUNDLE_1_TRX_4_TAG);
  EXPECT_EQ(trx3.getTimestamp(), BUNDLE_1_TRX_4_TS);
  EXPECT_EQ(trx3.getTrunkTransaction(), BUNDLE_1_TRX_4_TRUNK);
  EXPECT_EQ(trx3.getBranchTransaction(), BUNDLE_1_TRX_4_BRANCH);
  EXPECT_EQ(trx3.getAddress(), BUNDLE_1_TRX_4_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), BUNDLE_1_TRX_4_VALUE);
  EXPECT_EQ(trx3.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx3.getPersistence(), false);

  const auto& trx4 = res[3];
  EXPECT_EQ(trx4.getSignatureFragments(), BUNDLE_1_TRX_2_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx4.getCurrentIndex(), BUNDLE_1_TRX_2_CURRENT_INDEX);
  EXPECT_EQ(trx4.getLastIndex(), BUNDLE_1_TRX_2_LAST_INDEX);
  EXPECT_EQ(trx4.getNonce(), BUNDLE_1_TRX_2_NONCE);
  EXPECT_EQ(trx4.getHash(), BUNDLE_1_TRX_2_HASH);
  EXPECT_EQ(trx4.getTag(), BUNDLE_1_TRX_2_TAG);
  EXPECT_EQ(trx4.getTimestamp(), BUNDLE_1_TRX_2_TS);
  EXPECT_EQ(trx4.getTrunkTransaction(), BUNDLE_1_TRX_2_TRUNK);
  EXPECT_EQ(trx4.getBranchTransaction(), BUNDLE_1_TRX_2_BRANCH);
  EXPECT_EQ(trx4.getAddress(), BUNDLE_1_TRX_2_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), BUNDLE_1_TRX_2_VALUE);
  EXPECT_EQ(trx4.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx4.getPersistence(), false);
}

TEST(Extended, FindTransactionObjectsByBundleInvalidTrxHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjectsByBundle({ BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.size(), 0UL);
}

TEST(Extended, FindTransactionObjectsByBundleInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.findTransactionObjectsByBundle({ "salut" }), IOTA::Errors::IllegalState);
}

TEST(Extended, FindTailTransactionHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTailTransactionHash({ BUNDLE_1_TRX_2_HASH });

  EXPECT_EQ(res, BUNDLE_1_TRX_1_HASH);
}

TEST(Extended, FindTailTransactionHashWithTailTrx) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTailTransactionHash({ BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res, BUNDLE_1_TRX_1_HASH);
}

TEST(Extended, FindTailTransactionHashWithBundle) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTailTransactionHash(BUNDLE_1_HASH);

  EXPECT_EQ(res, IOTA::EmptyHash);
}

TEST(Extended, FindTailTransactionHashWithInvalid) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_EXCEPTION(api.findTailTransactionHash("salut"), IOTA::Errors::BadRequest,
                   "Invalid hashes input");
}

TEST(Extended, FindTransactionsByAddresses) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByAddresses({ BUNDLE_1_TRX_1_ADDRESS });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByAddressesInvalidAddress) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByAddresses({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid addresses input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, FindTransactionsByTags) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByTags({ BUNDLE_1_TRX_1_TAG });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByApprovees) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByApprovees({ BUNDLE_1_TRX_2_HASH });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByApproveesInvalidApprovee) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByApprovees({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid approvees input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, FindTransactionsByBundles) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByBundles({ BUNDLE_1_HASH });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByBundlesInvalidBundle) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByBundles({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid bundles input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, GetAccountData) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_2_SEED, 0, 2, true, 0, true, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>(
                { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH,
                  ACCOUNT_2_ADDRESS_4_HASH, ACCOUNT_2_ADDRESS_5_HASH, ACCOUNT_2_ADDRESS_6_HASH }));

  std::vector<IOTA::Models::Bundle> expectedBundleRes;

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_1_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_2_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_3_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_4_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_1_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_2_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_3_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_4_TRYTES) }));

  ASSERT_EQ(res.getTransfers().size(), expectedBundleRes.size());

  for (size_t i = 0; i < expectedBundleRes.size(); ++i) {
    EXPECT_EQ(res.getTransfers()[i], expectedBundleRes[i]);
  }

  EXPECT_EQ(res.getBalance(), ACCOUNT_2_FUND);
}

TEST(Extended, GetAccountDataInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData("hello", 0, 2, true, 0, true, 0, 0, true, 0),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetAccountDataInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData(ACCOUNT_2_SEED, 0, 42, true, 0, true, 0, 0, true, 0),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetAccountDataWithoutChechsum) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_2_SEED, 0, 2, false, 0, true, 0, 0, true, 0);

  EXPECT_EQ(
      res.getAddresses(),
      std::vector<IOTA::Types::Trytes>(
          { ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_2_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_2_ADDRESS_3_HASH_WITHOUT_CHECKSUM, ACCOUNT_2_ADDRESS_4_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_2_ADDRESS_5_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_2_ADDRESS_6_HASH_WITHOUT_CHECKSUM }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_2_FUND);
}

TEST(Extended, GetAccountDataTotal) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_2_SEED, 0, 2, true, 3, true, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>(
                { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_2_FUND);
}

TEST(Extended, GetAccountDataReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_2_SEED, 0, 2, true, 0, false, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(), std::vector<IOTA::Types::Trytes>({ ACCOUNT_2_ADDRESS_6_HASH }));
  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_2_FUND);
}

TEST(Extended, GetAccountDataStartEnd) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_2_SEED, 0, 2, true, 0, true, 1, 3, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>(
                { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH,
                  ACCOUNT_2_ADDRESS_4_HASH, ACCOUNT_2_ADDRESS_5_HASH, ACCOUNT_2_ADDRESS_6_HASH }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_2_ADDRESS_2_FUND + ACCOUNT_2_ADDRESS_3_FUND);
}

TEST(Extended, GetAccountDataMin) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData(ACCOUNT_2_SEED, 0, 2, true, 0, true, 0, 0, true, 1000000),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetInputs) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getInputs(ACCOUNT_2_SEED, 0, 0, 2, 0);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_FUND);
  ASSERT_EQ(res.getInput().size(), 4UL);

  //! Note that the first address is skipped because it has no fund

  auto input1 = res.getInput()[0];
  EXPECT_EQ(input1.getAddress(), ACCOUNT_2_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input1.getKeyIndex(), 1);
  EXPECT_EQ(input1.getSecurity(), 2);

  auto input2 = res.getInput()[1];
  EXPECT_EQ(input2.getAddress(), ACCOUNT_2_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input2.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input2.getKeyIndex(), 2);
  EXPECT_EQ(input2.getSecurity(), 2);

  auto input3 = res.getInput()[2];
  EXPECT_EQ(input3.getAddress(), ACCOUNT_2_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input3.getBalance(), ACCOUNT_2_ADDRESS_4_FUND);
  EXPECT_EQ(input3.getKeyIndex(), 3);
  EXPECT_EQ(input3.getSecurity(), 2);

  auto input4 = res.getInput()[3];
  EXPECT_EQ(input4.getAddress(), ACCOUNT_2_ADDRESS_5_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input4.getBalance(), ACCOUNT_2_ADDRESS_5_FUND);
  EXPECT_EQ(input4.getKeyIndex(), 4);
  EXPECT_EQ(input4.getSecurity(), 2);
}

TEST(Extended, GetInputsInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getInputs("hello", 0, 0, 2, 0), IOTA::Errors::IllegalState);
}

TEST(Extended, GetInputsInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getInputs(ACCOUNT_2_SEED, 0, 0, 42, 0), IOTA::Errors::IllegalState);
}

TEST(Extended, GetInputsStartEnd) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getInputs(ACCOUNT_2_SEED, 2, 4, 2, 0);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_ADDRESS_3_FUND + ACCOUNT_2_ADDRESS_4_FUND);
  ASSERT_EQ(res.getInput().size(), 2UL);

  //! Note that the first address is skipped because it has no fund

  auto input1 = res.getInput()[0];
  EXPECT_EQ(input1.getAddress(), ACCOUNT_2_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input1.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input1.getKeyIndex(), 2);
  EXPECT_EQ(input1.getSecurity(), 2);

  auto input2 = res.getInput()[1];
  EXPECT_EQ(input2.getAddress(), ACCOUNT_2_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(input2.getBalance(), ACCOUNT_2_ADDRESS_4_FUND);
  EXPECT_EQ(input2.getKeyIndex(), 3);
  EXPECT_EQ(input2.getSecurity(), 2);
}

TEST(Extended, GetInputMin) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getInputs(ACCOUNT_2_SEED, 0, 0, 2, 1000000), IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormat) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getBalancesAndFormat(
      { ACCOUNT_2_ADDRESS_1_HASH, ACCOUNT_2_ADDRESS_2_HASH, ACCOUNT_2_ADDRESS_3_HASH }, 0, 0, 2);

  //! address 1 has 0 iota, should not be returned as input

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_2_ADDRESS_2_FUND + ACCOUNT_2_ADDRESS_3_FUND);
  ASSERT_EQ(res.getInput().size(), 2UL);

  const auto& input_1 = res.getInput()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_2_ADDRESS_2_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 1);  //! still note the offset is shifted by one
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInput()[1];
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
  ASSERT_EQ(res.getInput().size(), 2UL);

  const auto& input_1 = res.getInput()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_2_ADDRESS_2_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_2_ADDRESS_2_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 11);  //! still note the offset is shifted by one
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInput()[1];
  EXPECT_EQ(input_2.getAddress(), ACCOUNT_2_ADDRESS_3_HASH);
  EXPECT_EQ(input_2.getBalance(), ACCOUNT_2_ADDRESS_3_FUND);
  EXPECT_EQ(input_2.getKeyIndex(), 12);  //! still note the offset is shifted by one
  EXPECT_EQ(input_2.getSecurity(), 2);
}

TEST(Extended, BundlesFromAddresses) {
  auto api     = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundles = api.bundlesFromAddresses({ BUNDLE_1_TRX_1_ADDRESS }, true);

  ASSERT_EQ(bundles.size(), 2UL);

  //! first bundle is simply the initial funding
  ASSERT_EQ(bundles[0].getTransactions().size(), 1UL);

  const auto& trx = bundles[0].getTransactions()[0];
  EXPECT_EQ(trx.getSignatureFragments(), BUNDLE_2_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx.getCurrentIndex(), BUNDLE_2_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx.getLastIndex(), BUNDLE_2_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx.getNonce(), BUNDLE_2_TRX_1_NONCE);
  EXPECT_EQ(trx.getHash(), BUNDLE_2_TRX_1_HASH);
  EXPECT_EQ(trx.getTag(), BUNDLE_2_TRX_1_TAG);
  EXPECT_EQ(trx.getTimestamp(), BUNDLE_2_TRX_1_TS);
  EXPECT_EQ(trx.getTrunkTransaction(), BUNDLE_2_TRX_1_TRUNK);
  EXPECT_EQ(trx.getBranchTransaction(), BUNDLE_2_TRX_1_BRANCH);
  EXPECT_EQ(trx.getAddress(), BUNDLE_2_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx.getValue(), BUNDLE_2_TRX_1_VALUE);
  EXPECT_EQ(trx.getBundle(), BUNDLE_2_HASH);
  EXPECT_EQ(trx.getPersistence(), true);

  //! second trx is spending from account 2 to account 3
  ASSERT_EQ(bundles[1].getTransactions().size(), 4UL);

  const auto& trx1 = bundles[1].getTransactions()[0];
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
  EXPECT_EQ(trx1.getPersistence(), true);

  const auto& trx2 = bundles[1].getTransactions()[1];
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
  EXPECT_EQ(trx2.getPersistence(), true);

  const auto& trx3 = bundles[1].getTransactions()[2];
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
  EXPECT_EQ(trx3.getPersistence(), true);

  const auto& trx4 = bundles[1].getTransactions()[3];
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
  EXPECT_EQ(trx4.getPersistence(), true);
}

TEST(Extended, BundlesFromAddressesNoPersistentState) {
  auto api     = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundles = api.bundlesFromAddresses({ BUNDLE_1_TRX_1_ADDRESS }, false);

  ASSERT_EQ(bundles.size(), 2UL);

  //! first bundle is simply the initial funding
  ASSERT_EQ(bundles[0].getTransactions().size(), 1UL);

  const auto& trx = bundles[0].getTransactions()[0];
  EXPECT_EQ(trx.getSignatureFragments(), BUNDLE_2_TRX_1_SIGNATURE_FRAGMENT);
  EXPECT_EQ(trx.getCurrentIndex(), BUNDLE_2_TRX_1_CURRENT_INDEX);
  EXPECT_EQ(trx.getLastIndex(), BUNDLE_2_TRX_1_LAST_INDEX);
  EXPECT_EQ(trx.getNonce(), BUNDLE_2_TRX_1_NONCE);
  EXPECT_EQ(trx.getHash(), BUNDLE_2_TRX_1_HASH);
  EXPECT_EQ(trx.getTag(), BUNDLE_2_TRX_1_TAG);
  EXPECT_EQ(trx.getTimestamp(), BUNDLE_2_TRX_1_TS);
  EXPECT_EQ(trx.getTrunkTransaction(), BUNDLE_2_TRX_1_TRUNK);
  EXPECT_EQ(trx.getBranchTransaction(), BUNDLE_2_TRX_1_BRANCH);
  EXPECT_EQ(trx.getAddress(), BUNDLE_2_TRX_1_ADDRESS_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx.getValue(), BUNDLE_2_TRX_1_VALUE);
  EXPECT_EQ(trx.getBundle(), BUNDLE_2_HASH);
  EXPECT_EQ(trx.getPersistence(), false);

  //! second trx is spending from account 2 to account 3
  ASSERT_EQ(bundles[1].getTransactions().size(), 4UL);

  const auto& trx1 = bundles[1].getTransactions()[0];
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

  const auto& trx2 = bundles[1].getTransactions()[1];
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

  const auto& trx3 = bundles[1].getTransactions()[2];
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

  const auto& trx4 = bundles[1].getTransactions()[3];
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

TEST(Extended, BundlesFromAddressesBundleHash) {
  auto api     = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundles = api.bundlesFromAddresses({ BUNDLE_1_HASH }, false);

  EXPECT_EQ(bundles.size(), 0UL);
}

TEST(Extended, BundlesFromAddressesTrxHash) {
  auto api     = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundles = api.bundlesFromAddresses({ BUNDLE_1_TRX_1_HASH }, false);

  EXPECT_EQ(bundles.size(), 0UL);
}

TEST(Extended, BundlesFromAddressesInvalidAddrHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  std::string hash = BUNDLE_1_TRX_1_ADDRESS;
  hash[0]          = '9';

  auto bundles = api.bundlesFromAddresses({ hash }, false);
  EXPECT_EQ(bundles.size(), 0UL);
}

TEST(Extended, BundlesFromAddressesInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.bundlesFromAddresses({ "hello" }, false), IOTA::Errors::BadRequest);
}

TEST(Extended, GetTransactionsObjects) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getTransactionsObjects({ BUNDLE_1_TRX_1_HASH });

  ASSERT_EQ(res.size(), 1UL);

  const auto& trx1 = res[0];
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
}

TEST(Extended, GetTransactionsObjectsInvalidTrxHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  std::string hash = BUNDLE_1_TRX_1_HASH;
  hash[0]          = '9';

  auto res = api.getTransactionsObjects({ hash });

  //! should got empty default trx
  ASSERT_EQ(res.size(), 1UL);
  ASSERT_EQ(
      res[0].toTrytes(),
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999");
}

TEST(Extended, GetTransactionsObjectsInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getTransactionsObjects({ "hello" }), IOTA::Errors::IllegalState);
}

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

TEST(Extended, GetLatestInclusion) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getLatestInclusion(
      { BUNDLE_1_TRX_1_HASH, BUNDLE_1_TRX_2_HASH, BUNDLE_1_TRX_3_HASH, BUNDLE_1_TRX_4_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true, true, true, true }));
}

TEST(Extended, GetLatestInclusionInvalidHash) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto hash = BUNDLE_1_TRX_2_HASH;
  hash[0]   = '9';

  auto res = api.getLatestInclusion(
      { BUNDLE_1_TRX_1_HASH, hash, BUNDLE_1_TRX_3_HASH, BUNDLE_1_TRX_4_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true, false, true, true }));
}

TEST(Extended, GetTransfers) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getTransfers(ACCOUNT_2_SEED, 0, 0, 2, true);

  std::vector<IOTA::Models::Bundle> expectedBundleRes;

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_1_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_2_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_3_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_4_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_1_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_2_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_3_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_5_TRX_4_TRYTES) }));

  ASSERT_EQ(res.getTransfers().size(), expectedBundleRes.size());

  for (size_t i = 0; i < expectedBundleRes.size(); ++i) {
    EXPECT_EQ(res.getTransfers()[i], expectedBundleRes[i]);
  }
}

TEST(Extended, GetTransfersInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getTransfers("hello", 0, 0, 2, true), IOTA::Errors::IllegalState);
}

TEST(Extended, GetTransfersInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getTransfers(ACCOUNT_2_SEED, 0, 0, 42, true), IOTA::Errors::IllegalState);
}

TEST(Extended, GetTransfersStartEnd) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getTransfers(ACCOUNT_2_SEED, 1, 3, 2, true);

  std::vector<IOTA::Models::Bundle> expectedBundleRes;

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_2_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_3_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_2_BUNDLE_4_TRX_1_TRYTES) }));

  ASSERT_EQ(res.getTransfers().size(), expectedBundleRes.size());

  for (size_t i = 0; i < expectedBundleRes.size(); ++i) {
    EXPECT_EQ(res.getTransfers()[i], expectedBundleRes[i]);
  }
}

TEST(Extended, PrepareTransfers) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 4UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 3);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 3);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 3);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 3);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersWithChecksum) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 4UL);
  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 3);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 3);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 3);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 3);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());

  //! should have remove checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersNoRemainderAddress) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers, "", inputs, true);

  ASSERT_EQ(res.size(), 4UL);
  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 3);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 3);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 3);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 3);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersNoTransfer) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfers = std::vector<IOTA::Models::Transfer>{};

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 0UL);
}

TEST(Extended, PrepareTransfersInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers("hello", 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Seed");
}

TEST(Extended, PrepareTransfersInvalidTransferAddress) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ "HELLO", 100, "TESTMSG", "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, PrepareTransfersInvalidTransferTag) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "invalid__" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, PrepareTransfersInvalidTransferMsg) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100,
                                          "invalid__", "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, PrepareTransfersInvalidRemainder) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers, "hello", inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Remainder");
}

TEST(Extended, PrepareTransfersNotEnoughFund) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                          ACCOUNT_1_ADDRESS_1_FUND + 1, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Not enough balance");
}

TEST(Extended, PrepareTransfersNotEnoughFundWithoutCheckAndFakeBalance) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                          ACCOUNT_1_ADDRESS_1_FUND + 1, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND + 1, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, false);

  ASSERT_EQ(res.size(), 3UL);
  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), ACCOUNT_1_ADDRESS_1_FUND + 1);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 2);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -(ACCOUNT_1_ADDRESS_1_FUND + 1));
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 2);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersNotEnoughFundWithFakeBalanceAndCheck) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                          ACCOUNT_1_ADDRESS_1_FUND + 1, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND + 1, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Not enough balance");
}

TEST(Extended, PrepareTransfersNotKnowingBalance) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 0, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 4UL);
  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 3);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 3);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 3);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 3);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersNoInput) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto inputs = std::vector<IOTA::Models::Input>{};

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 4UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 3);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 3);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 3);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 3);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersInputSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 3 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 3, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 5UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 4);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 100);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 4);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  auto trx3 = IOTA::Models::Transaction{ res[2] };
  EXPECT_EQ(trx3.getCurrentIndex(), 2);
  EXPECT_EQ(trx3.getLastIndex(), 4);
  EXPECT_EQ(trx3.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx3.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx3.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), 0);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  auto trx4 = IOTA::Models::Transaction{ res[3] };
  EXPECT_EQ(trx4.getCurrentIndex(), 3);
  EXPECT_EQ(trx4.getLastIndex(), 4);
  EXPECT_EQ(trx4.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx4.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx4.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx4.getValue(), 0);
  EXPECT_EQ(trx4.getPersistence(), false);
  EXPECT_TRUE(trx4.getTimestamp() > 0);
  EXPECT_FALSE(trx4.getHash().empty());
  EXPECT_FALSE(trx4.getBundle().empty());
  EXPECT_FALSE(trx4.getSignatureFragments().empty());

  auto trx5 = IOTA::Models::Transaction{ res[4] };
  EXPECT_EQ(trx5.getCurrentIndex(), 4);
  EXPECT_EQ(trx5.getLastIndex(), 4);
  EXPECT_EQ(trx5.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx5.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx5.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx5.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx5.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx5.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx5.getPersistence(), false);
  EXPECT_TRUE(trx5.getTimestamp() > 0);
  EXPECT_FALSE(trx5.getHash().empty());
  EXPECT_FALSE(trx5.getBundle().empty());
  EXPECT_FALSE(trx5.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx4.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx5.getBundle());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersInvalidSecurityLevel) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 100, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  EXPECT_EXCEPTION(api.prepareTransfers(ACCOUNT_1_SEED, 42, transfers,
                                        ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true),
                   IOTA::Errors::IllegalState, "Invalid Security Level");
}

TEST(Extended, PrepareTransfersZeroTransfer) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 0, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 1UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 0);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 0);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, PrepareTransfersZeroTransferNoInput) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto transfer  = IOTA::Models::Transfer{ ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM, 0, "TESTMSG",
                                          "TESTTAG99999999999999999999" };
  auto transfers = std::vector<IOTA::Models::Transfer>{ transfer };

  auto inputs = std::vector<IOTA::Models::Input>{};

  auto res = api.prepareTransfers(ACCOUNT_1_SEED, 2, transfers,
                                  ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, inputs, true);

  ASSERT_EQ(res.size(), 1UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 0);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), 0);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  //! should keep without the checksum
  EXPECT_EQ(transfers[0].getAddress(), ACCOUNT_2_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, GetNewAddressesInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_EXCEPTION(api.getNewAddresses("false", 0, 1, false, 0, false), IOTA::Errors::IllegalState,
                   "Invalid Seed");
}

TEST(Extended, GetNewAddressesInvalidSecurityLevel) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_EXCEPTION(api.getNewAddresses(ACCOUNT_1_SEED, 0, -1, false, 0, false),
                   IOTA::Errors::IllegalState, "Invalid Security Level");

  EXPECT_EXCEPTION(api.getNewAddresses(ACCOUNT_1_SEED, 0, 4, false, 0, false),
                   IOTA::Errors::IllegalState, "Invalid Security Level");
}

TEST(Extended, GetNewAddressesTotalChecksumReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, true, 7, true);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(7));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH);
}

TEST(Extended, GetNewAddressesTotalNoChecksumReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, false, 7, true);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(7));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, GetNewAddressesTotalChecksumReturnOne) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, false, 7, false);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(1));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, GetNewAddressesNoTotalChecksumReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, true, 0, true);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(7));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH);
}

TEST(Extended, GetNewAddressesNoTotalNoChecksumReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, false, 0, true);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(7));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[1], ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[2], ACCOUNT_1_ADDRESS_3_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[3], ACCOUNT_1_ADDRESS_4_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[4], ACCOUNT_1_ADDRESS_5_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[5], ACCOUNT_1_ADDRESS_6_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(res.getAddresses()[6], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}

TEST(Extended, GetNewAddressesNoTotalNoChecksumReturnOne) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto res = api.getNewAddresses(ACCOUNT_1_SEED, 0, 2, false, 0, false);

  EXPECT_EQ(res.getAddresses().size(), static_cast<unsigned long>(1));
  EXPECT_EQ(res.getAddresses()[0], ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
}
