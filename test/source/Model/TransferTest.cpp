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

#include <Model/Transfer.hpp>

TEST(Transfer, CtorDefault) {
  Transfer t;

  EXPECT_EQ(t.getAddress(), "");
  EXPECT_EQ(t.getHash(), "");
  EXPECT_EQ(t.getPersistence(), false);
  EXPECT_EQ(t.getTimestamp(), "");
  EXPECT_EQ(t.getValue(), 0);
  EXPECT_EQ(t.getMessage(), "");
  EXPECT_EQ(t.getTag(), "");
  EXPECT_EQ(t.isValid(), false);
}

TEST(Transfer, CtorFull) {
  Transfer t = { "ts", "addr", "hash", true, 42, "msg", "tag" };

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getHash(), "hash");
  EXPECT_EQ(t.getPersistence(), true);
  EXPECT_EQ(t.getTimestamp(), "ts");
  EXPECT_EQ(t.getValue(), 42);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
  EXPECT_EQ(t.isValid(), false);
}

TEST(Transfer, CtorShort) {
  Transfer t = { "addr", 42, "msg", "tag" };

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getHash(), "");
  EXPECT_EQ(t.getPersistence(), false);
  EXPECT_EQ(t.getTimestamp(), "");
  EXPECT_EQ(t.getValue(), 42);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
  EXPECT_EQ(t.isValid(), false);
}

TEST(Transfer, ConstGetters) {
  const Transfer t = { "ts", "addr", "hash", true, 42, "msg", "tag" };

  EXPECT_EQ(t.getAddress(), "addr");
  EXPECT_EQ(t.getHash(), "hash");
  EXPECT_EQ(t.getPersistence(), true);
  EXPECT_EQ(t.getTimestamp(), "ts");
  EXPECT_EQ(t.getValue(), 42);
  EXPECT_EQ(t.getMessage(), "msg");
  EXPECT_EQ(t.getTag(), "tag");
  EXPECT_EQ(t.isValid(), false);
}

TEST(Transfer, AddressGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getAddress(), "");

  t.setAddress("addr");
  EXPECT_EQ(t.getAddress(), "addr");
}

TEST(Transfer, HashGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getHash(), "");

  t.setHash("hash");
  EXPECT_EQ(t.getHash(), "hash");
}

TEST(Transfer, PersistenceGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getPersistence(), false);

  t.setPersistence(true);
  EXPECT_EQ(t.getPersistence(), true);
}

TEST(Transfer, TimestampGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getTimestamp(), "");

  t.setTimestamp("ts");
  EXPECT_EQ(t.getTimestamp(), "ts");
}

TEST(Transfer, ValueGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getValue(), 0);

  t.setValue(42);
  EXPECT_EQ(t.getValue(), 42);
}

TEST(Transfer, MessageGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getMessage(), "");

  t.setMessage("msg");
  EXPECT_EQ(t.getMessage(), "msg");
}

TEST(Transfer, TagGetterAndSetter) {
  Transfer t;
  EXPECT_EQ(t.getTag(), "");

  t.setTag("tag");
  EXPECT_EQ(t.getTag(), "tag");
}

TEST(Transfer, IsValidWithValidTransfer) {
  const Transfer t = {
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
    "9ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  };

  EXPECT_TRUE(t.isValid());
}

TEST(Transfer, IsValidWithInvalidAddressInvalidTrytes) {
  const Transfer t = {
    "999999999999999999999999999999999999999999999999999999999999999999999999999999991", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
    "9ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidWithInvalidAddressInvalidLength) {
  const Transfer t = {
    "99999999999999999999999999999999999999999999999999999999999999999999999999999999", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
    "9ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidWithInvalidMessageInvalidTrytes) {
  const Transfer t = {
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999991",
    "9ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidWithInvalidTagInvalidTrytes) {
  const Transfer t = {
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
    "9ABCDEFGHIJKLMNOPQRSTUVWXY1"
  };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, IsValidWithInvalidTagInvalidLength) {
  const Transfer t = {
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999", 0,
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
    "9ABCDEFGHIJKLMNOPQRSTUVWXY"
  };

  EXPECT_FALSE(t.isValid());
}
