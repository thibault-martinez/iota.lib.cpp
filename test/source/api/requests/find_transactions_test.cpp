// //
// // MIT License
// //
// // Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
// //
// // Permission is hereby granted, free of charge, to any person obtaining a copy
// // of this software and associated documentation files (the "Software"), to deal
// // in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// // copies of the Software, and to permit persons to whom the Software is
// // furnished to do so, subject to the following conditions:
// //
// // The above copyright notice and this permission notice shall be included in all
// // copies or substantial portions of the Software.
// //
// // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// // IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// // FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// // AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// // LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// // OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// // SOFTWARE.
// //
// //
//
#include <gtest/gtest.h>

#include <iota/api/requests/find_transactions.hpp>
#include <test/utils/constants.hpp>

TEST(FindTransactionsRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                     ACCOUNT_1_ADDRESS_2_HASH },
                                                   { { "TAGONE" }, { "TAGTWO" } },
                                                   { "approvee1", "approvee2" },
                                                   { "bundle1", "bundle2" } };

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, GetAddressesNonConst) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.getAddresses().push_back(ACCOUNT_1_ADDRESS_3_HASH);

  EXPECT_EQ(req.getAddresses(),
            std::vector<IOTA::Models::Address>(
                { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH, ACCOUNT_1_ADDRESS_3_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, GetTagsNonConst) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.getTags().push_back({ "TAGTHREE" });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(),
            std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" }, { "TAGTHREE" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, GetApproveesNonConst) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.getApprovees().push_back("approvee3");

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(),
            std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2", "approvee3" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, GetBundlesNonConst) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.getBundles().push_back("bundle3");

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(),
            std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2", "bundle3" }));
}

TEST(FindTransactionsRequest, SetAddresses) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.setAddresses({ ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, SetTags) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.setTags({ { "NULLONE" }, { "NULLTWO" } });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "NULLONE" }, { "NULLTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, SetApprovees) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.setApprovees({ ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>(
                                    { ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}

TEST(FindTransactionsRequest, SetBundles) {
  IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                             { { "TAGONE" }, { "TAGTWO" } },
                                             { "approvee1", "approvee2" },
                                             { "bundle1", "bundle2" } };

  req.setBundles({ "null1", "null2" });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getTags(), std::vector<IOTA::Models::Tag>({ { "TAGONE" }, { "TAGTWO" } }));
  EXPECT_EQ(req.getApprovees(), std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(req.getBundles(), std::vector<IOTA::Types::Trytes>({ "null1", "null2" }));
}

TEST(FindTransactionsRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                     ACCOUNT_1_ADDRESS_2_HASH },
                                                   { { "TAGONE" }, { "TAGTWO" } },
                                                   { "approvee1", "approvee2" },
                                                   { "bundle1", "bundle2" } };
  json                                        data;

  req.serialize(data);

  EXPECT_EQ(data["command"].get<std::string>(), "findTransactions");
  EXPECT_EQ(data["addresses"],
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                               ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM }));
  EXPECT_EQ(data["tags"], std::vector<IOTA::Types::Trytes>(
                              { "TAGONE999999999999999999999", "TAGTWO999999999999999999999" }));
  EXPECT_EQ(data["approvees"], std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(data["bundles"], std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}
