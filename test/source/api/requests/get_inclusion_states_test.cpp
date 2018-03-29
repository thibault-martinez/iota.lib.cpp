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

#include <iota/api/requests/get_inclusion_states.hpp>
#include <iota/utils/json.hpp>

TEST(GetInclusionStatesRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::GetInclusionStates req(
      std::vector<IOTA::Types::Trytes>({ "tx1", "tx2" }),
      std::vector<IOTA::Types::Trytes>({ "tip1", "tip2" }));

  EXPECT_EQ(req.getTransactions(), std::vector<IOTA::Types::Trytes>({ "tx1", "tx2" }));
  EXPECT_EQ(req.getTips(), std::vector<IOTA::Types::Trytes>({ "tip1", "tip2" }));
}

TEST(GetInclusionStatesRequest, GetTransactionsNonConst) {
  IOTA::API::Requests::GetInclusionStates req{ { "tx1", "tx2" }, { "tip1", "tip2" } };

  req.getTransactions().push_back("tx3");

  EXPECT_EQ(req.getTransactions(), std::vector<IOTA::Types::Trytes>({ "tx1", "tx2", "tx3" }));
  EXPECT_EQ(req.getTips(), std::vector<IOTA::Types::Trytes>({ "tip1", "tip2" }));
}

TEST(GetInclusionStatesRequest, GetTipsNonConst) {
  IOTA::API::Requests::GetInclusionStates req{ { "tx1", "tx2" }, { "tip1", "tip2" } };

  req.getTips().push_back("tip3");

  EXPECT_EQ(req.getTransactions(), std::vector<IOTA::Types::Trytes>({ "tx1", "tx2" }));
  EXPECT_EQ(req.getTips(), std::vector<IOTA::Types::Trytes>({ "tip1", "tip2", "tip3" }));
}

TEST(GetInclusionStatesRequest, SetTransactions) {
  IOTA::API::Requests::GetInclusionStates req{ { "tx1", "tx2" }, { "tip1", "tip2" } };

  req.setTransactions({ "null1", "null2" });

  EXPECT_EQ(req.getTransactions(), std::vector<IOTA::Types::Trytes>({ "null1", "null2" }));
  EXPECT_EQ(req.getTips(), std::vector<IOTA::Types::Trytes>({ "tip1", "tip2" }));
}

TEST(GetInclusionStatesRequest, SetTips) {
  IOTA::API::Requests::GetInclusionStates req{ { "tx1", "tx2" }, { "tip1", "tip2" } };

  req.setTips({ "null1", "null2" });

  EXPECT_EQ(req.getTransactions(), std::vector<IOTA::Types::Trytes>({ "tx1", "tx2" }));
  EXPECT_EQ(req.getTips(), std::vector<IOTA::Types::Trytes>({ "null1", "null2" }));
}

TEST(GetInclusionStatesRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::GetInclusionStates req{ { "tx1", "tx2" }, { "tip1", "tip2" } };
  IOTA::Utils::json                             data;

  req.serialize(data);

  EXPECT_EQ(data.getString("command"), "getInclusionStates");
  EXPECT_EQ(data.getStringVector("transactions"),
            std::vector<IOTA::Types::Trytes>({ "tx1", "tx2" }));
  EXPECT_EQ(data.getStringVector("tips"), std::vector<IOTA::Types::Trytes>({ "tip1", "tip2" }));
}
