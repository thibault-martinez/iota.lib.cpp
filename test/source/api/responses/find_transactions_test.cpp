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

#include <iota/api/responses/find_transactions.hpp>

TEST(FindTransactionsResponse, DefaultCtorShouldInitFields) {
  const IOTA::API::Responses::FindTransactions res;

  EXPECT_EQ(res.getHashes(), std::vector<IOTA::Types::Trytes>());
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(FindTransactionsResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::FindTransactions res{ std::vector<IOTA::Types::Trytes>(
      { "TESTA", "TESTB" }) };

  EXPECT_EQ(res.getHashes(), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(FindTransactionsResponse, AssignementOperator) {
  const IOTA::API::Responses::FindTransactions res1{ std::vector<IOTA::Types::Trytes>(
      { "TESTA", "TESTB" }) };
  IOTA::API::Responses::FindTransactions       res2;

  res2 = res1;
  EXPECT_EQ(res1.getHashes(), res2.getHashes());
  EXPECT_EQ(res1.getDuration(), res2.getDuration());
}

TEST(FindTransactionsResponse, GetHashesNonConst) {
  IOTA::API::Responses::FindTransactions res;

  res.getHashes().push_back("TEST");

  EXPECT_EQ(res.getHashes(), std::vector<IOTA::Types::Trytes>({ "TEST" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(FindTransactionsResponse, SetHashes) {
  IOTA::API::Responses::FindTransactions res;

  std::vector<IOTA::Types::Trytes> hashes = res.getHashes();
  hashes.push_back("TEST");
  res.setHashes(hashes);

  EXPECT_EQ(res.getHashes(), std::vector<IOTA::Types::Trytes>({ "TEST" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(FindTransactionsResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::FindTransactions res;
  json                                   data;
  std::vector<IOTA::Types::Trytes>       hashes;

  hashes.push_back("TEST");
  data["hashes"] = hashes;
  res.deserialize(data);
  EXPECT_EQ(res.getHashes(), hashes);
}
