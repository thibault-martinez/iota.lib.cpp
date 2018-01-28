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
#include <iota/errors/bad_request.hpp>
#include <iota/errors/illegal_state.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, AddRemainder) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderInvalidSeed) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_EXCEPTION(
      api.addRemainder("hello", 2, inputs, bundle, "TESTTAG99999999999999999999", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT }),
      IOTA::Errors::IllegalState, "Invalid Seed");
}

TEST(Extended, AddRemainderInvalidTag) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_EXCEPTION(
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "hello", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT }),
      IOTA::Errors::IllegalState, "Invalid Tag");
}

TEST(Extended, AddRemainderTooShortTag) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderNotInput) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto inputs = std::vector<IOTA::Models::Input>{};
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_EXCEPTION(
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT }),
      IOTA::Errors::IllegalState, "Not enough balance");
}

TEST(Extended, AddRemainderNotEnoughBalance) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  EXPECT_EXCEPTION(
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999",
                       ACCOUNT_1_ADDRESS_1_FUND + 1, ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                       { EMPTY_SIGNATURE_FRAGMENT }),
      IOTA::Errors::IllegalState, "Not enough balance");
}

TEST(Extended, AddRemainderMultipleInputs) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input1 = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                     ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto input2 = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                                     ACCOUNT_1_ADDRESS_2_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input1, input2 };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999",
                       ACCOUNT_1_ADDRESS_1_FUND + 1, ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                       { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 5UL);
  ASSERT_EQ(bundle.getTransactions().size(), 5UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 4);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), -ACCOUNT_1_ADDRESS_2_FUND);
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
  EXPECT_EQ(trx4.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
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
  EXPECT_EQ(trx5.getValue(), ACCOUNT_1_ADDRESS_2_FUND - 1);
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
}

TEST(Extended, AddRemainderMultipleUnecessaryInputs) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input1 = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                     ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto input2 = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                                     ACCOUNT_1_ADDRESS_2_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input1, input2 };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderZeroValue) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999", 0,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderMatchingInput) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res = api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999",
                              ACCOUNT_1_ADDRESS_1_FUND, ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                              { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 2UL);
  ASSERT_EQ(bundle.getTransactions().size(), 2UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 1);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(trx1.getPersistence(), false);
  EXPECT_TRUE(trx1.getTimestamp() > 0);
  EXPECT_FALSE(trx1.getHash().empty());
  EXPECT_FALSE(trx1.getBundle().empty());
  EXPECT_FALSE(trx1.getSignatureFragments().empty());

  auto trx2 = IOTA::Models::Transaction{ res[1] };
  EXPECT_EQ(trx2.getCurrentIndex(), 1);
  EXPECT_EQ(trx2.getLastIndex(), 1);
  EXPECT_EQ(trx2.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx2.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx2.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx2.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx2.getValue(), 0);
  EXPECT_EQ(trx2.getPersistence(), false);
  EXPECT_TRUE(trx2.getTimestamp() > 0);
  EXPECT_FALSE(trx2.getHash().empty());
  EXPECT_FALSE(trx2.getBundle().empty());
  EXPECT_FALSE(trx2.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
}

TEST(Extended, AddRemainderNoRemainderAddress) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res = api.addRemainder(ACCOUNT_1_SEED, 2, inputs, bundle, "TESTTAG99999999999999999999", 100,
                              "", { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderSecurity) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res =
      api.addRemainder(ACCOUNT_1_SEED, 3, inputs, bundle, "TESTTAG99999999999999999999", 100,
                       ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM, { EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}

TEST(Extended, AddRemainderMultipleFragments) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  auto input  = IOTA::Models::Input{ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                    ACCOUNT_1_ADDRESS_1_FUND, 0, 2 };
  auto inputs = std::vector<IOTA::Models::Input>{ input };
  auto bundle = IOTA::Models::Bundle{};

  auto res = api.addRemainder(ACCOUNT_1_SEED, 3, inputs, bundle, "TESTTAG99999999999999999999", 100,
                              ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                              { EMPTY_SIGNATURE_FRAGMENT, EMPTY_SIGNATURE_FRAGMENT });

  ASSERT_EQ(res.size(), 3UL);
  ASSERT_EQ(bundle.getTransactions().size(), 3UL);

  auto trx1 = IOTA::Models::Transaction{ res[0] };
  EXPECT_EQ(trx1.getCurrentIndex(), 0);
  EXPECT_EQ(trx1.getLastIndex(), 2);
  EXPECT_EQ(trx1.getTag(), "TESTTAG99999999999999999999");
  EXPECT_EQ(trx1.getNonce(), IOTA::EmptyNonce);
  EXPECT_EQ(trx1.getTrunkTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getBranchTransaction(), IOTA::EmptyHash);
  EXPECT_EQ(trx1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx1.getValue(), -ACCOUNT_1_ADDRESS_1_FUND);
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
  EXPECT_EQ(trx2.getValue(), 0);
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
  EXPECT_EQ(trx3.getAddress(), ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(trx3.getValue(), ACCOUNT_1_ADDRESS_1_FUND - 100);
  EXPECT_EQ(trx3.getPersistence(), false);
  EXPECT_TRUE(trx3.getTimestamp() > 0);
  EXPECT_FALSE(trx3.getHash().empty());
  EXPECT_FALSE(trx3.getBundle().empty());
  EXPECT_FALSE(trx3.getSignatureFragments().empty());

  //! should have same bundle
  EXPECT_EQ(trx1.getBundle(), trx2.getBundle());
  EXPECT_EQ(trx1.getBundle(), trx3.getBundle());
}
