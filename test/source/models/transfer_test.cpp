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

#include <iota/models/transfer.hpp>
#include <test/utils/constants.hpp>

TEST(Transfer, CtorDefault) {
  IOTA::Models::Transfer t;

  EXPECT_EQ(t.getAddress(), "");
  EXPECT_EQ(t.getValue(), 0);
  EXPECT_EQ(t.getMessage(), "");
  EXPECT_EQ(t.getTag(), "");
}

TEST(Transfer, CtorShort) {
  IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, ConstGetters) {
  const IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, AddressGetterAndSetter) {
  IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  t.setAddress("edited");

  EXPECT_EQ(t.getAddress(), "edited");
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, ValueGetterAndSetter) {
  IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  t.setValue(42);

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getValue(), 42);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, MessageGetterAndSetter) {
  IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  t.setMessage("edited");

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "edited");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, TagGetterAndSetter) {
  IOTA::Models::Transfer t = { "addr", 1, "msg", "tag" };

  t.setTag("edited");

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "edited");
}

TEST(Transfer, IsValid) {
  IOTA::Models::Transfer t = { BUNDLE_1_TRX_1_ADDRESS, BUNDLE_1_TRX_1_VALUE, BUNDLE_1_TRX_1_TAG,
                               BUNDLE_1_TRX_1_TAG };

  EXPECT_TRUE(t.isValid());
}

TEST(Transfer, IsValidInvalidAddress) {
  IOTA::Models::Transfer t = { "abc", BUNDLE_1_TRX_1_VALUE, BUNDLE_1_TRX_1_TAG,
                               BUNDLE_1_TRX_1_TAG };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidInvalidMessage) {
  IOTA::Models::Transfer t = { BUNDLE_1_TRX_1_ADDRESS, BUNDLE_1_TRX_1_VALUE, "z&7",
                               BUNDLE_1_TRX_1_TAG };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidInvalidTag) {
  IOTA::Models::Transfer t = { BUNDLE_1_TRX_1_ADDRESS, BUNDLE_1_TRX_1_VALUE, BUNDLE_1_TRX_1_TAG,
                               "*&7" };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidInvalidTagLength) {
  IOTA::Models::Transfer t = { BUNDLE_1_TRX_1_ADDRESS, BUNDLE_1_TRX_1_VALUE, BUNDLE_1_TRX_1_TAG,
                               "9" };

  EXPECT_FALSE(t.isValid());
}
