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

#include <iota/models/signature.hpp>
#include <test/utils/constants.hpp>

TEST(Signature, CtorDefault) {
  IOTA::Models::Signature s;

  EXPECT_EQ(s.getAddress(), IOTA::Models::Address{ "" });
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>());
}

TEST(Signature, CtorFull) {
  IOTA::Models::Signature s = { ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" } };

  EXPECT_EQ(s.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, ConstGetters) {
  const IOTA::Models::Signature s = { ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" } };

  EXPECT_EQ(s.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, AddressGetterAndSetter) {
  IOTA::Models::Signature s;
  EXPECT_EQ(s.getAddress(), IOTA::Models::Address{ "" });

  s.setAddress(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(s.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
}

TEST(Signature, SignatureFragmentsGetterAndSetter) {
  IOTA::Models::Signature s;
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>());

  s.setSignatureFragments({ "abc", "def", "ghi" });
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, SignatureFragmentsNonConstGetter) {
  IOTA::Models::Signature s;
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>());

  s.getSignatureFragments().push_back("abc");
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Types::Trytes>({ "abc" }));
}

TEST(Signature, EqOperator) {
  IOTA::Models::Signature lhs_eq(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_eq(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  EXPECT_TRUE(lhs_eq == rhs_eq);

  IOTA::Models::Signature lhs_neq_1(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_neq_1(ACCOUNT_1_ADDRESS_2_HASH, { "abc", "def", "ghi" });
  EXPECT_FALSE(lhs_neq_1 == rhs_neq_1);

  IOTA::Models::Signature lhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "neq_def", "ghi" });
  EXPECT_FALSE(lhs_neq_2 == rhs_neq_2);
}

TEST(Signature, NEqOperator) {
  IOTA::Models::Signature lhs_eq(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_eq(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  EXPECT_FALSE(lhs_eq != rhs_eq);

  IOTA::Models::Signature lhs_neq_1(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_neq_1(ACCOUNT_1_ADDRESS_2_HASH, { "abc", "def", "ghi" });
  EXPECT_TRUE(lhs_neq_1 != rhs_neq_1);

  IOTA::Models::Signature lhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "def", "ghi" });
  IOTA::Models::Signature rhs_neq_2(ACCOUNT_1_ADDRESS_1_HASH, { "abc", "neq_def", "ghi" });
  EXPECT_TRUE(lhs_neq_2 != rhs_neq_2);
}
