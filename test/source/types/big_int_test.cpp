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

#include <iota/constants.hpp>
#include <iota/types/big_int.hpp>

TEST(BigInt, DefaultCtor) {
  IOTA::Types::BigInt big;

  EXPECT_EQ(big, 0);
}

TEST(BigInt, ValueCtor) {
  IOTA::Types::BigInt big(42);

  EXPECT_EQ(big, 42);
}

TEST(BigInt, FromTrits) {
  IOTA::Types::BigInt b1;
  IOTA::Types::BigInt b2;
  IOTA::Types::BigInt b3;
  IOTA::Types::BigInt b4;
  IOTA::Types::BigInt b5;
  IOTA::Types::BigInt b6;
  IOTA::Types::BigInt b7;

  b1.fromTrits({});
  b2.fromTrits({ 1, 0, 0 });
  b3.fromTrits({ -1, 0, 0 });
  b4.fromTrits({ 0, -1, -1, -1, 1, 0 });
  b5.fromTrits({ 0, 1, 1, 1, -1, 0 });
  b6.fromTrits({ 0, 0, -1, 0, 1, -1, 0, -1, -1, -1, 1, 0, 1, 0, 0, -1, -1, 1, 0, 1, 0 });
  b7.fromTrits({ 0, 0, 1, 0, -1, 1, 0, 1, 1, 1, -1, 0, -1, 0, 0, 1, 1, -1, 0, -1, 0 });
  EXPECT_EQ(b1, 0);
  EXPECT_EQ(b2, 1);
  EXPECT_EQ(b3, -1);
  EXPECT_EQ(b4, 42);
  EXPECT_EQ(b5, -42);
  EXPECT_EQ(b6, 1234567890);
  EXPECT_EQ(b7, -1234567890);
}

TEST(BigInt, ToTrits) {
  IOTA::Types::BigInt b1(0);
  IOTA::Types::BigInt b2(1);
  IOTA::Types::BigInt b3(-1);
  IOTA::Types::BigInt b4(42);
  IOTA::Types::BigInt b5(-42);
  IOTA::Types::BigInt b6(1234567890);
  IOTA::Types::BigInt b7(-1234567890);

  IOTA::Types::Trits t1({});
  t1.insert(std::end(t1), IOTA::TritHashLength - t1.size(), 0);
  IOTA::Types::Trits t2({ 1, 0, 0 });
  t2.insert(std::end(t2), IOTA::TritHashLength - t2.size(), 0);
  IOTA::Types::Trits t3({ -1, 0, 0 });
  t3.insert(std::end(t3), IOTA::TritHashLength - t3.size(), 0);
  IOTA::Types::Trits t4({ 0, -1, -1, -1, 1, 0 });
  t4.insert(std::end(t4), IOTA::TritHashLength - t4.size(), 0);
  IOTA::Types::Trits t5({ 0, 1, 1, 1, -1, 0 });
  t5.insert(std::end(t5), IOTA::TritHashLength - t5.size(), 0);
  IOTA::Types::Trits t6({ 0, 0, -1, 0, 1, -1, 0, -1, -1, -1, 1, 0, 1, 0, 0, -1, -1, 1, 0, 1 });
  t6.insert(std::end(t6), IOTA::TritHashLength - t6.size(), 0);
  IOTA::Types::Trits t7({ 0, 0, 1, 0, -1, 1, 0, 1, 1, 1, -1, 0, -1, 0, 0, 1, 1, -1, 0, -1 });
  t7.insert(std::end(t7), IOTA::TritHashLength - t7.size(), 0);

  EXPECT_EQ(b1.toTrits(), t1);
  EXPECT_EQ(b2.toTrits(), t2);
  EXPECT_EQ(b3.toTrits(), t3);
  EXPECT_EQ(b4.toTrits(), t4);
  EXPECT_EQ(b5.toTrits(), t5);
  EXPECT_EQ(b6.toTrits(), t6);
  EXPECT_EQ(b7.toTrits(), t7);
}

TEST(BigInt, FromBytes) {
  IOTA::Types::BigInt b1;
  IOTA::Types::BigInt b2;
  IOTA::Types::BigInt b3;
  IOTA::Types::BigInt b4;
  IOTA::Types::BigInt b5;
  IOTA::Types::BigInt b6;
  IOTA::Types::BigInt b7;

  b1.fromBytes({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 });
  b2.fromBytes({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x01 });
  b3.fromBytes({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff });
  b4.fromBytes({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x2a });
  b5.fromBytes({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xd6 });
  b6.fromBytes({ (int8_t)0x49, (int8_t)0x96, (int8_t)0x02, (int8_t)0xd2 });
  b7.fromBytes({ (int8_t)0xb6, (int8_t)0x69, (int8_t)0xfd, (int8_t)0x2e });

  EXPECT_EQ(b1, 0);
  EXPECT_EQ(b2, 1);
  EXPECT_EQ(b3, -1);
  EXPECT_EQ(b4, 42);
  EXPECT_EQ(b5, -42);
  EXPECT_EQ(b6, 1234567890);
  EXPECT_EQ(b7, -1234567890);
}

TEST(BigInt, ToBytes) {
  IOTA::Types::BigInt b1(0);
  IOTA::Types::BigInt b2(1);
  IOTA::Types::BigInt b3(-1);
  IOTA::Types::BigInt b4(42);
  IOTA::Types::BigInt b5(-42);
  IOTA::Types::BigInt b6(1234567890);
  IOTA::Types::BigInt b7(-1234567890);

  std::vector<int8_t> by1({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 });
  by1.insert(std::begin(by1), IOTA::ByteHashLength - by1.size(), 0x00);
  std::vector<int8_t> by2({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x01 });
  by2.insert(std::begin(by2), IOTA::ByteHashLength - by2.size(), 0x00);
  std::vector<int8_t> by3({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff });
  by3.insert(std::begin(by3), IOTA::ByteHashLength - by3.size(), 0xff);
  std::vector<int8_t> by4({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x2a });
  by4.insert(std::begin(by4), IOTA::ByteHashLength - by4.size(), 0x00);
  std::vector<int8_t> by5({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xd6 });
  by5.insert(std::begin(by5), IOTA::ByteHashLength - by5.size(), 0xff);
  std::vector<int8_t> by6({ (int8_t)0x49, (int8_t)0x96, (int8_t)0x02, (int8_t)0xd2 });
  by6.insert(std::begin(by6), IOTA::ByteHashLength - by6.size(), 0x00);
  std::vector<int8_t> by7({ (int8_t)0xb6, (int8_t)0x69, (int8_t)0xfd, (int8_t)0x2e });
  by7.insert(std::begin(by7), IOTA::ByteHashLength - by7.size(), 0xff);

  EXPECT_EQ(b1.toBytes(), by1);
  EXPECT_EQ(b2.toBytes(), by2);
  EXPECT_EQ(b3.toBytes(), by3);
  EXPECT_EQ(b4.toBytes(), by4);
  EXPECT_EQ(b5.toBytes(), by5);
  EXPECT_EQ(b6.toBytes(), by6);
  EXPECT_EQ(b7.toBytes(), by7);
}
