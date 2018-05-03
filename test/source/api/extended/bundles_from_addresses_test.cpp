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

TEST(Extended, BundlesFromAddresses) {
  auto api     = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundles = api.bundlesFromAddresses({ BUNDLE_1_TRX_1_ADDRESS }, true);

  ASSERT_EQ(bundles.size(), 2UL);

  //! first bundle is simply the initial funding
  ASSERT_EQ(bundles[0].getTransactions().size(), 1UL);

  const auto& trx = bundles[0][0];
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

  const auto& trx1 = bundles[1][0];
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

  const auto& trx2 = bundles[1][1];
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

  const auto& trx3 = bundles[1][2];
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

  const auto& trx4 = bundles[1][3];
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

  const auto& trx = bundles[0][0];
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

  const auto& trx1 = bundles[1][0];
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

  const auto& trx2 = bundles[1][1];
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

  const auto& trx3 = bundles[1][2];
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

  const auto& trx4 = bundles[1][3];
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

  EXPECT_EXCEPTION(api.bundlesFromAddresses({ "hello" }, false), IOTA::Errors::IllegalState,
                   "address has invalid length");
}
