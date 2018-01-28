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

#include <chrono>
#include <thread>

#include <iota/constants.hpp>
#include <iota/types/trinary.hpp>

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

TEST(Trinary, IsValidAddress) {
  EXPECT_TRUE(IOTA::Types::isValidAddress(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999999"));

  EXPECT_TRUE(
      IOTA::Types::isValidAddress("9999999999999999999999999999999999999999999999999999999999999999"
                                  "99999999999999999999999999"));

  EXPECT_FALSE(IOTA::Types::isValidAddress(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999998"));

  EXPECT_FALSE(IOTA::Types::isValidAddress("9"));
}

TEST(Trinary, IsValidHash) {
  EXPECT_TRUE(IOTA::Types::isValidHash(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999999"));

  EXPECT_FALSE(IOTA::Types::isValidHash(
      "999999999999999999999999999999999999999999999999999999999999999999999999999999998"));

  EXPECT_FALSE(IOTA::Types::isValidHash("9"));
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
