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

#include <iota/api/responses/get_bundle.hpp>
#include <iota/models/transaction.hpp>
#include <test/utils/constants.hpp>

TEST(GetBundleResponse, DefaultCtorShouldInitFields) {
  const IOTA::API::Responses::GetBundle res{};

  EXPECT_EQ(res.getTransactions(), std::vector<IOTA::Models::Transaction>{});
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBundleResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetBundle res({ { ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 },
                                              { ACCOUNT_1_ADDRESS_2_HASH, 2, "TAGTRXTWO", 2 },
                                              { ACCOUNT_1_ADDRESS_3_HASH, 3, "TAGTRXTHREE", 3 } },
                                            42);

  EXPECT_EQ(res.getTransactions(), std::vector<IOTA::Models::Transaction>(
                                       { { ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 },
                                         { ACCOUNT_1_ADDRESS_2_HASH, 2, "TAGTRXTWO", 2 },
                                         { ACCOUNT_1_ADDRESS_3_HASH, 3, "TAGTRXTHREE", 3 } }));
  EXPECT_EQ(res.getDuration(), 42);
}

TEST(GetBundleResponse, GetTransactionsNonConst) {
  IOTA::API::Responses::GetBundle res;

  res.getTransactions().push_back({ ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 });

  EXPECT_EQ(res.getTransactions(), std::vector<IOTA::Models::Transaction>(
                                       { { ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 } }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetBundleResponse, SetTransactions) {
  IOTA::API::Responses::GetBundle res;

  std::vector<IOTA::Models::Transaction> transactions = res.getTransactions();
  transactions.push_back({ ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 });
  res.setTransactions(transactions);

  EXPECT_EQ(res.getTransactions(), std::vector<IOTA::Models::Transaction>(
                                       { { ACCOUNT_1_ADDRESS_1_HASH, 1, "TAGTRXONE", 1 } }));
  EXPECT_EQ(res.getDuration(), 0);
}
