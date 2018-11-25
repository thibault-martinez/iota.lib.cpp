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
#include <nlohmann/json.hpp>

#include <iota/api/requests/find_transactions.hpp>
#include <test/utils/constants.hpp>

TEST(FindTransactionsRequest, ConstructAndSerialize) {
  const IOTA::API::Requests::FindTransactions req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                     ACCOUNT_1_ADDRESS_2_HASH },
                                                   { { "TAGONE" }, { "TAGTWO" } },
                                                   { "approvee1", "approvee2" },
                                                   { "bundle1", "bundle2" } };
  json                                        data;

  req.serialize(data);

  EXPECT_EQ(data["command"], "findTransactions");
  EXPECT_EQ(data["addresses"],
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                               ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM }));
  EXPECT_EQ(data["tags"], std::vector<IOTA::Types::Trytes>(
                              { "TAGONE999999999999999999999", "TAGTWO999999999999999999999" }));
  EXPECT_EQ(data["approvees"], std::vector<IOTA::Types::Trytes>({ "approvee1", "approvee2" }));
  EXPECT_EQ(data["bundles"], std::vector<IOTA::Types::Trytes>({ "bundle1", "bundle2" }));
}
