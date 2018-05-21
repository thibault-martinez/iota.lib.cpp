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

#include <iota/api/responses/attach_to_tangle.hpp>

TEST(AttachToTangleResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::AttachToTangle res{ std::vector<IOTA::Types::Trytes>(
      { "TESTA", "TESTB" }) };

  EXPECT_EQ(res.getTrytes(), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(AttachToTangleResponse, GetTrytesNonConst) {
  IOTA::API::Responses::AttachToTangle res;

  res.getTrytes().push_back("TEST");

  EXPECT_EQ(res.getTrytes(), std::vector<IOTA::Types::Trytes>({ "TEST" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(AttachToTangleResponse, SetTrytes) {
  IOTA::API::Responses::AttachToTangle res;

  std::vector<IOTA::Types::Trytes> trytes = res.getTrytes();
  trytes.push_back("TEST");
  res.setTrytes(trytes);

  EXPECT_EQ(res.getTrytes(), std::vector<IOTA::Types::Trytes>({ "TEST" }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(AttachToTangleResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::AttachToTangle res;
  json                                 data;
  std::vector<IOTA::Types::Trytes>     trytes;

  trytes.push_back("TEST");
  data["trytes"] = trytes;
  res.deserialize(data);
  EXPECT_EQ(res.getTrytes(), trytes);
}
