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

#include <iota/api/responses/get_neighbors.hpp>
#include <iota/models/neighbor.hpp>

TEST(GetNeighborsResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetNeighbors res{ std::vector<IOTA::Models::Neighbor>(
      { IOTA::Models::Neighbor{ "addr1", 1, 2, 3 }, IOTA::Models::Neighbor{ "addr2", 4, 5, 6 } }) };

  EXPECT_EQ(res.getNeighbors().size(), 2UL);

  EXPECT_EQ(res.getNeighbors()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfAllTransactions(), 1);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfInvalidTransactions(), 2);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfNewTransactions(), 3);

  EXPECT_EQ(res.getNeighbors()[1].getAddress(), "addr2");
  EXPECT_EQ(res.getNeighbors()[1].getNumberOfAllTransactions(), 4);
  EXPECT_EQ(res.getNeighbors()[1].getNumberOfInvalidTransactions(), 5);
  EXPECT_EQ(res.getNeighbors()[1].getNumberOfNewTransactions(), 6);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNeighborsResponse, GetNeighborsNonConst) {
  IOTA::API::Responses::GetNeighbors res;

  res.getNeighbors().push_back(IOTA::Models::Neighbor{ "addr1", 1, 2, 3 });

  EXPECT_EQ(res.getNeighbors().size(), 1UL);

  EXPECT_EQ(res.getNeighbors()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfAllTransactions(), 1);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfInvalidTransactions(), 2);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfNewTransactions(), 3);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNeighborsResponse, SetNeighbors) {
  IOTA::API::Responses::GetNeighbors res;

  res.setNeighbors({ IOTA::Models::Neighbor{ "addr1", 1, 2, 3 } });

  EXPECT_EQ(res.getNeighbors().size(), 1UL);

  EXPECT_EQ(res.getNeighbors()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfAllTransactions(), 1);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfInvalidTransactions(), 2);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfNewTransactions(), 3);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNeighborsResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::GetNeighbors res;
  json                               data;
  json                               neighbor;

  neighbor["address"]                     = "addr1";
  neighbor["numberOfAllTransactions"]     = 1;
  neighbor["numberOfInvalidTransactions"] = 2;
  neighbor["numberOfNewTransactions"]     = 3;
  data["neighbors"]                       = std::vector<json>{ neighbor };

  res.deserialize(data);

  EXPECT_EQ(res.getNeighbors().size(), 1UL);

  EXPECT_EQ(res.getNeighbors()[0].getAddress(), "addr1");
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfAllTransactions(), 1);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfInvalidTransactions(), 2);
  EXPECT_EQ(res.getNeighbors()[0].getNumberOfNewTransactions(), 3);

  EXPECT_EQ(res.getDuration(), 0);
}
