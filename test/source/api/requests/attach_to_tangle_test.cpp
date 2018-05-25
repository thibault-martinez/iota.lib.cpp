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
#include <json.hpp>

#include <iota/api/requests/attach_to_tangle.hpp>

TEST(AttachToTangleRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };

  EXPECT_EQ(req.getTrunkTransaction(), "trunk");
  EXPECT_EQ(req.getBranchTransaction(), "branch");
  EXPECT_EQ(req.getMinWeightMagnitude(), 42);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}

TEST(AttachToTangleRequest, GetTrytesNonConst) {
  IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1" } };

  req.getTrytes().push_back("trytes2");

  EXPECT_EQ(req.getTrunkTransaction(), "trunk");
  EXPECT_EQ(req.getBranchTransaction(), "branch");
  EXPECT_EQ(req.getMinWeightMagnitude(), 42);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}

TEST(AttachToTangleRequest, setTrunkTransaction) {
  IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };

  req.setTrunkTransaction("null");

  EXPECT_EQ(req.getTrunkTransaction(), "null");
  EXPECT_EQ(req.getBranchTransaction(), "branch");
  EXPECT_EQ(req.getMinWeightMagnitude(), 42);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}

TEST(AttachToTangleRequest, setBranchTransaction) {
  IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };

  req.setBranchTransaction("null");

  EXPECT_EQ(req.getTrunkTransaction(), "trunk");
  EXPECT_EQ(req.getBranchTransaction(), "null");
  EXPECT_EQ(req.getMinWeightMagnitude(), 42);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}

TEST(AttachToTangleRequest, setMinWeightMagnitude) {
  IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };

  req.setMinWeightMagnitude(84);

  EXPECT_EQ(req.getTrunkTransaction(), "trunk");
  EXPECT_EQ(req.getBranchTransaction(), "branch");
  EXPECT_EQ(req.getMinWeightMagnitude(), 84);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}

TEST(AttachToTangleRequest, setTrytes) {
  IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };

  req.setTrytes({ "null1", "null2" });

  EXPECT_EQ(req.getTrunkTransaction(), "trunk");
  EXPECT_EQ(req.getBranchTransaction(), "branch");
  EXPECT_EQ(req.getMinWeightMagnitude(), 42);
  EXPECT_EQ(req.getTrytes(), std::vector<IOTA::Types::Trytes>({ "null1", "null2" }));
}

TEST(AttachToTangleRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::AttachToTangle req{ "trunk", "branch", 42, { "trytes1", "trytes2" } };
  json                                      data;

  req.serialize(data);

  EXPECT_EQ(data["command"], "attachToTangle");
  EXPECT_EQ(data["trunkTransaction"], "trunk");
  EXPECT_EQ(data["branchTransaction"], "branch");
  EXPECT_EQ(data["minWeightMagnitude"], 42);
  EXPECT_EQ(data["trytes"], std::vector<IOTA::Types::Trytes>({ "trytes1", "trytes2" }));
}
