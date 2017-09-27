//
// MIT License
//
// Copyright (c) 2017 Thibault Martinez
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

#include <Model/Signature.hpp>

TEST(Signature, CtorDefault) {
  Signature s;

  EXPECT_EQ(s.getAddress(), "");
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>());
}

TEST(Signature, CtorFull) {
  Signature s = { "addr", { "abc", "def", "ghi" } };

  EXPECT_EQ(s.getAddress(), "addr");
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, ConstGetters) {
  const Signature s = { "addr", { "abc", "def", "ghi" } };

  EXPECT_EQ(s.getAddress(), "addr");
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, AddressGetterAndSetter) {
  Signature s;
  EXPECT_EQ(s.getAddress(), "");

  s.setAddress("addr");
  EXPECT_EQ(s.getAddress(), "addr");
}

TEST(Signature, SignatureFragmentsGetterAndSetter) {
  Signature s;
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>());

  s.setSignatureFragments({ "abc", "def", "ghi" });
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>({ "abc", "def", "ghi" }));
}

TEST(Signature, SignatureFragmentsNonConstGetter) {
  Signature s;
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>());

  s.getSignatureFragments().push_back("abc");
  EXPECT_EQ(s.getSignatureFragments(), std::vector<IOTA::Type::Trytes>({ "abc" }));
}
