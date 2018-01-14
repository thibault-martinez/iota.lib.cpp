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

  EXPECT_EQ(res.getTransactions().size(), 2UL);

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
  EXPECT_EQ(trx1.getAddress(), BUNDLE_1_TRX_1_ADDRESS);
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
  EXPECT_EQ(trx2.getAddress(), BUNDLE_1_TRX_2_ADDRESS);
  EXPECT_EQ(trx2.getValue(), BUNDLE_1_TRX_2_VALUE);
  EXPECT_EQ(trx2.getBundle(), BUNDLE_1_HASH);
  EXPECT_EQ(trx2.getPersistence(), false);
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

  EXPECT_EQ(res.getTransactions().size(), 2UL);

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

  EXPECT_EQ(res.getTransactions().size(), 2UL);

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

  EXPECT_EXCEPTION(api.traverseBundle("salut", "hello", bundle);
                   , IOTA::Errors::BadRequest, "Invalid hashes input");
}

TEST(Extended, TraverseBundleFullInvalidBundleHash) {
  auto api    = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle = IOTA::Models::Bundle{};
  auto res    = api.traverseBundle(BUNDLE_1_TRX_1_HASH, "yolo", bundle);

  EXPECT_EQ(res.getTransactions().size(), 0UL);
}

TEST(Extended, TraverseBundleFullIntermediateTrxWithAppending) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto bundle =
      IOTA::Models::Bundle{ { IOTA::Models::Transaction{ "address", 42, "obsolete_tag", 21 } } };
  auto res = api.traverseBundle(BUNDLE_1_TRX_2_HASH, BUNDLE_1_HASH, bundle);

  EXPECT_EQ(res.getTransactions().size(), 2UL);

  const auto& trx1 = res.getTransactions()[0];
  EXPECT_EQ(trx1.getAddress(), "address");
  EXPECT_EQ(trx1.getValue(), 42);
  EXPECT_EQ(trx1.getObsoleteTag(), "obsolete_tag");
  EXPECT_EQ(trx1.getTimestamp(), 21);

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
}

TEST(Extended, FindTransactionObjectsByBundle) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionObjectsByBundle({ BUNDLE_1_HASH });

  EXPECT_EQ(res.size(), 2UL);

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

  EXPECT_EXCEPTION(api.findTailTransactionHash("salut");
                   , IOTA::Errors::BadRequest, "Invalid hashes input");
}

TEST(Extended, FindTransactionsByAddresses) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByAddresses({ BUNDLE_1_TRX_1_ADDRESS });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByAddressesInvalidAddress) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByAddresses({ "9999" });
                   , IOTA::Errors::BadRequest, "Invalid addresses input")

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

  EXPECT_EXCEPTION(res = api.findTransactionsByApprovees({ "9999" });
                   , IOTA::Errors::BadRequest, "Invalid approvees input")

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

  EXPECT_EXCEPTION(res = api.findTransactionsByBundles({ "9999" });
                   , IOTA::Errors::BadRequest, "Invalid bundles input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, GetAccountData) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_1_SEED, 0, 2, true, 0, true, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH,
                                               ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH,
                                               ACCOUNT_1_ADDRESS_5_HASH, ACCOUNT_1_ADDRESS_6_HASH,
                                               ACCOUNT_1_ADDRESS_7_HASH }));

  std::vector<IOTA::Models::Bundle> expectedBundleRes;

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_1_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_2_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_3_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_4_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_5_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_6_TRX_1_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_7_TRX_1_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_7_TRX_2_TRYTES) }));

  expectedBundleRes.push_back(
      IOTA::Models::Bundle({ IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_8_TRX_1_TRYTES),
                             IOTA::Models::Transaction(ACCOUNT_1_BUNDLE_8_TRX_2_TRYTES) }));

  ASSERT_EQ(res.getTransfers().size(), expectedBundleRes.size());

  for (size_t i = 0; i < expectedBundleRes.size(); ++i) {
    EXPECT_EQ(res.getTransfers()[i], expectedBundleRes[i]);
  }

  EXPECT_EQ(res.getBalance(), ACCOUNT_1_FUND);
}

TEST(Extended, GetAccountDataInvalidSeed) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData("hello", 0, 2, true, 0, true, 0, 0, true, 0),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetAccountDataInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData(ACCOUNT_1_SEED, 0, 42, true, 0, true, 0, 0, true, 0),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetAccountDataWithoutChechsum) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_1_SEED, 0, 2, false, 0, true, 0, 0, true, 0);

  EXPECT_EQ(
      res.getAddresses(),
      std::vector<IOTA::Types::Trytes>(
          { ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_1_ADDRESS_3_HASH_WITHOUT_CHECKSUM, ACCOUNT_1_ADDRESS_4_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_1_ADDRESS_5_HASH_WITHOUT_CHECKSUM, ACCOUNT_1_ADDRESS_6_HASH_WITHOUT_CHECKSUM,
            ACCOUNT_1_ADDRESS_7_HASH_WITHOUT_CHECKSUM }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_1_FUND);
}

TEST(Extended, GetAccountDataTotal) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_1_SEED, 0, 2, true, 3, true, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>(
                { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH, ACCOUNT_1_ADDRESS_3_HASH }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_1_FUND);
}

TEST(Extended, GetAccountDataReturnAll) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_1_SEED, 0, 2, true, 0, false, 0, 0, true, 0);

  EXPECT_EQ(res.getAddresses(), std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_7_HASH }));
  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_1_FUND);
}

TEST(Extended, GetAccountDataStartEnd) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.getAccountData(ACCOUNT_1_SEED, 0, 2, true, 0, true, 1, 3, true, 0);

  EXPECT_EQ(res.getAddresses(),
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH,
                                               ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH,
                                               ACCOUNT_1_ADDRESS_5_HASH, ACCOUNT_1_ADDRESS_6_HASH,
                                               ACCOUNT_1_ADDRESS_7_HASH }));

  EXPECT_FALSE(res.getTransfers().empty());
  EXPECT_EQ(res.getBalance(), ACCOUNT_1_ADDRESS_2_FUND + ACCOUNT_1_ADDRESS_3_FUND);
}

TEST(Extended, GetAccountDataMin) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getAccountData(ACCOUNT_1_SEED, 0, 2, true, 0, true, 0, 0, true, 1000000),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormat) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res =
      api.getBalancesAndFormat({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }, 0, 0, 2);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_1_ADDRESS_1_FUND + ACCOUNT_1_ADDRESS_2_FUND);
  EXPECT_EQ(res.getInput().size(), 2UL);

  const auto& input_1 = res.getInput()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 0);
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInput()[1];
  EXPECT_EQ(input_2.getAddress(), ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(input_2.getBalance(), ACCOUNT_1_ADDRESS_2_FUND);
  EXPECT_EQ(input_2.getKeyIndex(), 1);
  EXPECT_EQ(input_2.getSecurity(), 2);
}

TEST(Extended, GetBalancesAndFormatInvalidSecurity) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(
      api.getBalancesAndFormat({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }, 0, 0, 0),
      IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormatInvalidBalance) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  EXPECT_THROW(api.getBalancesAndFormat({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                        717650144175136, 0, 2),
               IOTA::Errors::IllegalState);
}

TEST(Extended, GetBalancesAndFormatStart) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res =
      api.getBalancesAndFormat({ ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }, 0, 10, 2);

  EXPECT_EQ(res.getTotalBalance(), ACCOUNT_1_ADDRESS_1_FUND + ACCOUNT_1_ADDRESS_2_FUND);
  EXPECT_EQ(res.getInput().size(), 2UL);

  const auto& input_1 = res.getInput()[0];
  EXPECT_EQ(input_1.getAddress(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(input_1.getBalance(), ACCOUNT_1_ADDRESS_1_FUND);
  EXPECT_EQ(input_1.getKeyIndex(), 10);
  EXPECT_EQ(input_1.getSecurity(), 2);

  const auto& input_2 = res.getInput()[1];
  EXPECT_EQ(input_2.getAddress(), ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_EQ(input_2.getBalance(), ACCOUNT_1_ADDRESS_2_FUND);
  EXPECT_EQ(input_2.getKeyIndex(), 11);
  EXPECT_EQ(input_2.getSecurity(), 2);
}
