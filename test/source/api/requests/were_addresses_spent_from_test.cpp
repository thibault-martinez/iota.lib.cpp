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

#include <iota/api/requests/were_addresses_spent_from.hpp>
#include <test/utils/constants.hpp>

TEST(WereAddressesSpentFromRequest, DefaultCtorShouldInitFields) {
  const IOTA::API::Requests::WereAddressesSpentFrom req{};

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>({}));
}

TEST(WereAddressesSpentFromRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::WereAddressesSpentFrom req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                           ACCOUNT_1_ADDRESS_2_HASH } };

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH }));
}

TEST(WereAddressesSpentFromRequest, GetAddressesNonConst) {
  IOTA::API::Requests::WereAddressesSpentFrom req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                     ACCOUNT_1_ADDRESS_2_HASH } };

  req.getAddresses().push_back(ACCOUNT_1_ADDRESS_3_HASH);

  EXPECT_EQ(req.getAddresses(),
            std::vector<IOTA::Models::Address>(
                { ACCOUNT_1_ADDRESS_1_HASH, ACCOUNT_1_ADDRESS_2_HASH, ACCOUNT_1_ADDRESS_3_HASH }));
}

TEST(WereAddressesSpentFromRequest, SetAddresses) {
  IOTA::API::Requests::WereAddressesSpentFrom req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                     ACCOUNT_1_ADDRESS_2_HASH } };

  req.setAddresses({ ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH });

  EXPECT_EQ(req.getAddresses(), std::vector<IOTA::Models::Address>(
                                    { ACCOUNT_1_ADDRESS_3_HASH, ACCOUNT_1_ADDRESS_4_HASH }));
}

TEST(WereAddressesSpentFromRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::WereAddressesSpentFrom req{ { ACCOUNT_1_ADDRESS_1_HASH,
                                                           ACCOUNT_1_ADDRESS_2_HASH } };
  json                                              data;

  req.serialize(data);

  EXPECT_EQ(data["command"], "wereAddressesSpentFrom");
  EXPECT_EQ(data["addresses"],
            std::vector<IOTA::Types::Trytes>({ ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM,
                                               ACCOUNT_1_ADDRESS_2_HASH_WITHOUT_CHECKSUM }));
}
