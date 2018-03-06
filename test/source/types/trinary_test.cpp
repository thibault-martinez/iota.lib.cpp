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

#include <thread>

#include <gtest/gtest.h>

#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/types/trinary.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Trinary, IsValidTryte) {
  for (char c : IOTA::TryteAlphabet) {
    EXPECT_TRUE(IOTA::Types::isValidTryte(c));
  }

  EXPECT_FALSE(IOTA::Types::isValidTryte('8'));
}

TEST(Trinary, IsValidTrytes) {
  EXPECT_TRUE(IOTA::Types::isValidTrytes(IOTA::TryteAlphabet));
  EXPECT_FALSE(IOTA::Types::isValidTrytes("8"));
}

TEST(Trinary, IsArrayOfHashes) {
  EXPECT_TRUE(IOTA::Types::isArrayOfHashes(
      { "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
        "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "9" }));

  EXPECT_FALSE(IOTA::Types::isArrayOfHashes(
      { "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
        "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "8" }));

  EXPECT_FALSE(IOTA::Types::isArrayOfHashes(
      { "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
        "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "9" }));

  EXPECT_FALSE(IOTA::Types::isArrayOfHashes(
      { "999999999999999999999999999999999999999999999999999999999999999999999999999999999",
        "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "9",
        "9" }));
}

TEST(Trinary, IsValidHash) {
  EXPECT_TRUE(IOTA::Types::isValidHash(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999999"));

  EXPECT_FALSE(IOTA::Types::isValidHash(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999998"));

  EXPECT_FALSE(IOTA::Types::isValidHash("9"));
}

TEST(Trinary, charToTrytes) {
  const std::string cset(
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./"
      ":;<=>?@[\\]^_`{|}~ \t\n");
  const std::string tset(
      "UAVAWAXAYAZA9BABBBCBPCQCRCSCTCUCVCWCXCYCZC9DADBDCDDDEDFDGDHDIDJDKDLDMDNDKBLBMBNBOBPBQB"
      "RBSBTBUBVBWBXBYBZB9CACBCCCDCECFCGCHCICFAGAHAIAJAKALAMANAOAPAQARASATADBEBFBGBHBIBJBJCKC"
      "LCMCNCOCODPDQDRDEAI9J9");

  for (size_t i = 0; i < cset.size(); ++i) {
    EXPECT_EQ(IOTA::Types::charToTrytes(cset[i]), tset.substr(2 * i, 2));
  }
}

TEST(Trinary, stringToTrytes) {
  EXPECT_EQ(IOTA::Types::stringToTrytes(""), IOTA::Types::Trytes{ "" });
  EXPECT_EQ(IOTA::Types::stringToTrytes("ASCII Message to Trytes"),
            "KBBCMBSBSBEAWBTCGDGDPCVCTCEAHDCDEACCFDMDHDTCGD");
  EXPECT_EQ(IOTA::Types::stringToTrytes("Lorem ipsum dolor sit amet, consectetur adipiscing elit."),
            "VBCDFDTCADEAXCDDGDIDADEASCCD9DCDFDEAGDXCHDEAPCADTCHDQAEARCCDBDGDTCRCHDTCHDIDFDEAPCSCXC"
            "DDXCGDRCXCBDVCEATC9DXCHDSA");
  EXPECT_EQ(
      IOTA::Types::stringToTrytes("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW"
                                  "XYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n"),
      "UAVAWAXAYAZA9BABBBCBPCQCRCSCTCUCVCWCXCYCZC9DADBDCDDDEDFDGDHDIDJDKDLDMDNDKBLBMBNBOBPBQB"
      "RBSBTBUBVBWBXBYBZB9CACBCCCDCECFCGCHCICFAGAHAIAJAKALAMANAOAPAQARASATADBEBFBGBHBIBJBJCKC"
      "LCMCNCOCODPDQDRDEAI9J9");
}

TEST(Trinary, trytesToString) {
  EXPECT_EXCEPTION(IOTA::Types::trytesToString("ABC"), IOTA::Errors::IllegalState,
                   "Odd number of trytes provided");
  EXPECT_EQ(IOTA::Types::trytesToString("KBBCMBSBSBEAWBTCGDGDPCVCTCEAHDCDEACCFDMDHDTCGD"),
            "ASCII Message to Trytes");
  EXPECT_EQ(
      IOTA::Types::trytesToString(
          "VBCDFDTCADEAXCDDGDIDADEASCCD9DCDFDEAGDXCHDEAPCADTCHDQAEARCCDBDGDTCRCHDTCHDIDFDEAPCSCXC"
          "DDXCGDRCXCBDVCEATC9DXCHDSA"),
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
  EXPECT_EQ(
      IOTA::Types::trytesToString(
          "UAVAWAXAYAZA9BABBBCBPCQCRCSCTCUCVCWCXCYCZC9DADBDCDDDEDFDGDHDIDJDKDLDMDNDKBLBMBNBOBPBQB"
          "RBSBTBUBVBWBXBYBZB9CACBCCCDCECFCGCHCICFAGAHAIAJAKALAMANAOAPAQARASATADBEBFBGBHBIBJBJCKC"
          "LCMCNCOCODPDQDRDEAI9J9"),
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW"
      "XYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n");
}

TEST(Trinary, tritsToBytes) {
  std::vector<int8_t> b0(IOTA::ByteHashLength, 0);
  std::vector<int8_t> b1({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 });
  b1.insert(std::begin(b1), IOTA::ByteHashLength - b1.size(), 0x00);
  std::vector<int8_t> b2({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x01 });
  b2.insert(std::begin(b2), IOTA::ByteHashLength - b2.size(), 0x00);
  std::vector<int8_t> b3({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff });
  b3.insert(std::begin(b3), IOTA::ByteHashLength - b3.size(), 0xff);
  std::vector<int8_t> b4({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x2a });
  b4.insert(std::begin(b4), IOTA::ByteHashLength - b4.size(), 0x00);
  std::vector<int8_t> b5({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xd6 });
  b5.insert(std::begin(b5), IOTA::ByteHashLength - b5.size(), 0xff);
  std::vector<int8_t> b6({ (int8_t)0x49, (int8_t)0x96, (int8_t)0x02, (int8_t)0xd2 });
  b6.insert(std::begin(b6), IOTA::ByteHashLength - b6.size(), 0x00);
  std::vector<int8_t> b7({ (int8_t)0xb6, (int8_t)0x69, (int8_t)0xfd, (int8_t)0x2e });
  b7.insert(std::begin(b7), IOTA::ByteHashLength - b7.size(), 0xff);
  std::vector<int8_t> b8({ (int8_t)0x01, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 });
  b8.insert(std::begin(b8), IOTA::ByteHashLength - b8.size(), 0x00);
  std::vector<int8_t> b9({ (int8_t)0x08, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff,
                           (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff });
  b9.insert(std::begin(b9), IOTA::ByteHashLength - b9.size(), 0x00);

  EXPECT_EXCEPTION(IOTA::Types::tritsToBytes({ -1, 0, 1, 2, 1, 0, -1 }), IOTA::Errors::IllegalState,
                   "Invalid trits provided");
  EXPECT_EQ(IOTA::Types::tritsToBytes({}), b0);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ 0 }), b1);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ 1 }), b2);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ -1 }), b3);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ 0, -1, -1, -1, 1 }), b4);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ 0, 1, 1, 1, -1 }), b5);
  EXPECT_EQ(IOTA::Types::tritsToBytes(
                { 0, 0, -1, 0, 1, -1, 0, -1, -1, -1, 1, 0, 1, 0, 0, -1, -1, 1, 0, 1 }),
            b6);
  EXPECT_EQ(IOTA::Types::tritsToBytes(
                { 0, 0, 1, 0, -1, 1, 0, 1, 1, 1, -1, 0, -1, 0, 0, 1, 1, -1, 0, -1 }),
            b7);
  EXPECT_EQ(IOTA::Types::tritsToBytes(
                { 1, 1, -1, -1, -1, -1, -1, 0, 0, -1, 1, -1, 0, 0, 1, -1, 1, 0, -1, 1, 1 }),
            b8);
  EXPECT_EQ(IOTA::Types::tritsToBytes({ -1, 0,  1, -1, 0, -1, -1, 0,  1,  1,  -1, 1,  1,  -1, 1,
                                        -1, -1, 1, -1, 1, 1,  1,  -1, -1, 1,  1,  0,  -1, -1, 0,
                                        0,  -1, 0, 0,  1, 0,  -1, 0,  0,  -1, -1, -1, -1, 1 }),
            b9);
}

TEST(Trinary, bytesToTrits) {
  IOTA::Types::Trits t0(IOTA::TritHashLength, 0);
  IOTA::Types::Trits t1({ 0 });
  t1.insert(std::end(t1), IOTA::TritHashLength - t1.size(), 0x00);
  IOTA::Types::Trits t2({ 1 });
  t2.insert(std::end(t2), IOTA::TritHashLength - t2.size(), 0x00);
  IOTA::Types::Trits t3({ -1 });
  t3.insert(std::end(t3), IOTA::TritHashLength - t3.size(), 0x00);
  IOTA::Types::Trits t4({ 0, -1, -1, -1, 1 });
  t4.insert(std::end(t4), IOTA::TritHashLength - t4.size(), 0x00);
  IOTA::Types::Trits t5({ 0, 1, 1, 1, -1 });
  t5.insert(std::end(t5), IOTA::TritHashLength - t5.size(), 0x00);
  IOTA::Types::Trits t6({ 0, 0, -1, 0, 1, -1, 0, -1, -1, -1, 1, 0, 1, 0, 0, -1, -1, 1, 0, 1 });
  t6.insert(std::end(t6), IOTA::TritHashLength - t6.size(), 0x00);
  IOTA::Types::Trits t7({ 0, 0, 1, 0, -1, 1, 0, 1, 1, 1, -1, 0, -1, 0, 0, 1, 1, -1, 0, -1 });
  t7.insert(std::end(t7), IOTA::TritHashLength - t7.size(), 0x00);
  IOTA::Types::Trits t8({ 1, 1, -1, -1, -1, -1, -1, 0, 0, -1, 1, -1, 0, 0, 1, -1, 1, 0, -1, 1, 1 });
  t8.insert(std::end(t8), IOTA::TritHashLength - t8.size(), 0x00);
  IOTA::Types::Trits t9({ -1, 0,  1, -1, 0, -1, -1, 0,  1,  1,  -1, 1,  1,  -1, 1,
                          -1, -1, 1, -1, 1, 1,  1,  -1, -1, 1,  1,  0,  -1, -1, 0,
                          0,  -1, 0, 0,  1, 0,  -1, 0,  0,  -1, -1, -1, -1, 1 });
  t9.insert(std::end(t9), IOTA::TritHashLength - t9.size(), 0x00);

  EXPECT_EQ(IOTA::Types::bytesToTrits({}), t0);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 }),
            t1);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x01 }),
            t2);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff }),
            t3);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x2a }),
            t4);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xd6 }),
            t5);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0x49, (int8_t)0x96, (int8_t)0x02, (int8_t)0xd2 }),
            t6);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0xb6, (int8_t)0x69, (int8_t)0xfd, (int8_t)0x2e }),
            t7);
  EXPECT_EQ(IOTA::Types::bytesToTrits(
                { (int8_t)0x01, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00, (int8_t)0x00 }),
            t8);
  EXPECT_EQ(IOTA::Types::bytesToTrits({ (int8_t)0x08, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff,
                                        (int8_t)0xff, (int8_t)0xff, (int8_t)0xff, (int8_t)0xff,
                                        (int8_t)0xff }),
            t9);
}

TEST(Trinary, TrytesToTrits) {
  EXPECT_EQ(IOTA::Types::trytesToTrits("9ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
            std::vector<int8_t>({ 0,  0,  0,  1, 0, 0,  -1, 1,  0,  0,  1,  0,  1,  1,  0,  -1, -1,
                                  1,  0,  -1, 1, 1, -1, 1,  -1, 0,  1,  0,  0,  1,  1,  0,  1,  -1,
                                  1,  1,  0,  1, 1, 1,  1,  1,  -1, -1, -1, 0,  -1, -1, 1,  -1, -1,
                                  -1, 0,  -1, 0, 0, -1, 1,  0,  -1, -1, 1,  -1, 0,  1,  -1, 1,  1,
                                  -1, -1, -1, 0, 0, -1, 0,  1,  -1, 0,  -1, 0,  0 }));
}

TEST(Trinary, TritsToTrytes) {
  EXPECT_EQ(IOTA::Types::tritsToTrytes(
                { 0,  0, 0,  1,  0,  0,  -1, 1,  0, 0,  1,  0,  1,  1, 0, -1, -1, 1, 0,  -1, 1,  1,
                  -1, 1, -1, 0,  1,  0,  0,  1,  1, 0,  1,  -1, 1,  1, 0, 1,  1,  1, 1,  1,  -1, -1,
                  -1, 0, -1, -1, 1,  -1, -1, -1, 0, -1, 0,  0,  -1, 1, 0, -1, -1, 1, -1, 0,  1,  -1,
                  1,  1, -1, -1, -1, 0,  0,  -1, 0, 1,  -1, 0,  -1, 0, 0 }),
            "9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(Trinary, IntToTrits) {
  EXPECT_EQ(IOTA::Types::intToTrits(42), std::vector<int8_t>({ 0, -1, -1, -1, 1 }));
  EXPECT_EQ(IOTA::Types::intToTrits(0), std::vector<int8_t>({}));
  EXPECT_EQ(IOTA::Types::intToTrits(-42), std::vector<int8_t>({ 0, 1, 1, 1, -1 }));

  EXPECT_EQ(IOTA::Types::intToTrits(42, 6), std::vector<int8_t>({ 0, -1, -1, -1, 1, 0 }));
  EXPECT_EQ(IOTA::Types::intToTrits(0, 6), std::vector<int8_t>({ 0, 0, 0, 0, 0, 0 }));
  EXPECT_EQ(IOTA::Types::intToTrits(-42, 6), std::vector<int8_t>({ 0, 1, 1, 1, -1, 0 }));
}
