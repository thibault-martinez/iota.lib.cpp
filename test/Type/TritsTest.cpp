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

#include "Trits.hpp"
#include "gtest/gtest.h"

TEST(TritsTest, isValidTrit) {
  ASSERT_EQ(IOTA::Type::isValidTrit(-1), true);
  ASSERT_EQ(IOTA::Type::isValidTrit(0), true);
  ASSERT_EQ(IOTA::Type::isValidTrit(1), true);
  ASSERT_EQ(IOTA::Type::isValidTrit(-2), false);
  ASSERT_EQ(IOTA::Type::isValidTrit(2), false);
}

TEST(TritsTest, vectorConstructor) {
  std::vector<int8_t> values{ -1, 0, 1, 1, 0, -1 };
  IOTA::Type::Trits   trits(values);
  ASSERT_EQ(values.size(), trits.values().size());
  for (size_t i = 0; i < values.size(); ++i) {
    ASSERT_EQ(values[i], trits.values()[i]);
  }
}

TEST(TritsTest, IntConstructor) {
}

TEST(TritsTest, isValid) {
  IOTA::Type::Trits validTrits1({ 1, 0, -1, -1, 0, 1 });
  ASSERT_EQ(validTrits1.isValid(), true);
  IOTA::Type::Trits validTrits2({ 1, 1, 0, 1, -1, -1, -1, -1, 0, 0, 1, 1, -1 });
  ASSERT_EQ(validTrits2.isValid(), true);
  IOTA::Type::Trits invalidTrits1({ 1, 0, 2, -1, 0, 1 });
  ASSERT_EQ(invalidTrits1.isValid(), false);
  IOTA::Type::Trits invalidTrits2({ 1, 0, 0, -4, 0, 4 });
  ASSERT_EQ(invalidTrits2.isValid(), false);
}

TEST(TritsTest, equalityOperator) {
  IOTA::Type::Trits trits1({ -1, 0, 0, 1 });
  IOTA::Type::Trits trits2({ -1, 0, 0, 1 });
  IOTA::Type::Trits trits3({ 1, 1, -1, 0 });
  ASSERT_EQ(trits1 == trits1, true);
  ASSERT_EQ(trits1 == trits2, true);
  ASSERT_EQ(trits1 == trits3, false);
}
