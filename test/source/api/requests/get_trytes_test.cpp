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

#include <iota/api/requests/get_trytes.hpp>
#include <iota/utils/json.hpp>

TEST(GetTrytesRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::GetTrytes req{ { "TESTA", "TESTB" } };

  EXPECT_EQ(req.getHashes(), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
}

TEST(GetTrytesRequest, GetHashesNonConst) {
  IOTA::API::Requests::GetTrytes req{ { "TESTA" } };

  req.getHashes().push_back("TESTB");

  EXPECT_EQ(req.getHashes(), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
}

TEST(GetTrytesRequest, SetHashes) {
  IOTA::API::Requests::GetTrytes req{ { "TESTA" } };

  std::vector<IOTA::Types::Trytes> hashes = req.getHashes();
  hashes.push_back("TESTB");
  req.setHashes(hashes);

  EXPECT_EQ(req.getHashes(), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
}

TEST(GetTrytesRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::GetTrytes req{ { "TESTA", "TESTB" } };
  IOTA::Utils::json                    data;

  req.serialize(data);

  EXPECT_EQ(data.getString("command"), "getTrytes");
  EXPECT_EQ(data.getStringVector("hashes"), std::vector<IOTA::Types::Trytes>({ "TESTA", "TESTB" }));
}
