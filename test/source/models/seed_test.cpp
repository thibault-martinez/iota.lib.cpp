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
#include <iota/models/seed.hpp>
#include <iota/types/trinary.hpp>

TEST(Seed, GenerateOne) {
  auto seed = IOTA::Models::Seed::generateRandomSeed();

  EXPECT_EQ(seed.toTrytes().size(), IOTA::SeedLength);
  EXPECT_TRUE(IOTA::Types::isValidTrytes(seed.toTrytes()));
}

TEST(Seed, GenerateMultiple) {
  auto seed1 = IOTA::Models::Seed::generateRandomSeed();
  auto seed2 = IOTA::Models::Seed::generateRandomSeed();
  auto seed3 = IOTA::Models::Seed::generateRandomSeed();

  EXPECT_NE(seed1.toTrytes(), seed2.toTrytes());
  EXPECT_NE(seed1.toTrytes(), seed3.toTrytes());
  EXPECT_NE(seed2.toTrytes(), seed3.toTrytes());
}
