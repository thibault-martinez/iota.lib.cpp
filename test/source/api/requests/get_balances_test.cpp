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

#include <iota/api/requests/get_balances.hpp>
#include <test/utils/constants.hpp>

TEST(GetBalancesRequest, DefaultCtorShouldInitFields) {
  const IOTA::API::Requests::GetBalances req{};

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>({}));
  EXPECT_EQ(req.getThreshold(), 0);
}

TEST(GetBalancesRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::GetBalances req{
    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }, 42
  };

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getThreshold(), 42);
}

TEST(GetBalancesRequest, GetAddressesNonConst) {
  IOTA::API::Requests::GetBalances req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                        42 };

  req.getAddresses().push_back(ACCOUNT_1_ADDRESS_3_HASH);

  EXPECT_EQ(req.getAddresses(),
            std::vector<IOTA::Models::Address>(
                { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH, ACCOUNT_1_ADDRESS_3_HASH }));
  EXPECT_EQ(req.getThreshold(), 42);
}

TEST(GetBalancesRequest, SetAddresses) {
  IOTA::API::Requests::GetBalances req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                        42 };

  req.setAddresses({ ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH }));
  EXPECT_EQ(req.getThreshold(), 42);
}

TEST(GetBalancesRequest, SetThreshold) {
  IOTA::API::Requests::GetBalances req{ { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH },
                                        42 };

  req.setThreshold(84);

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
  EXPECT_EQ(req.getThreshold(), 84);
}

TEST(GetBalancesRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::GetBalances req{
    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }, 42
  };
  json data;

  req.serialize(data);

  EXPECT_EQ(data["command"].get<std::string>(), "getBalances");
  EXPECT_EQ(data["addresses"],
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                               ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM }));
  EXPECT_EQ(data["threshold"], 42);
}
