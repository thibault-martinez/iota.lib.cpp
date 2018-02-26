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
#include <iota/errors/illegal_state.hpp>
#include <iota/models/seed.hpp>
#include <iota/types/trinary.hpp>
#include <test/utils/expect_exception.hpp>

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

TEST(Seed, FromCtor) {
  IOTA::Models::Seed seedEmptyCtor;
  EXPECT_EQ(seedEmptyCtor.toTrytes(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seedEmptyCtor.getSecurity(), 2);

  IOTA::Models::Seed seedFullValidSeed("9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(seedFullValidSeed.toTrytes(),
            "9ABCDEFGHIJKLMNOPQRSTUVWXYZ999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seedFullValidSeed.getSecurity(), 2);

  IOTA::Models::Seed seedShortSeed("ABC");
  EXPECT_EQ(seedShortSeed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seedShortSeed.getSecurity(), 2);

  IOTA::Models::Seed seedTrailing9s("ABC999");
  EXPECT_EQ(seedTrailing9s.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seedTrailing9s.getSecurity(), 2);

  EXPECT_EXCEPTION(
      IOTA::Models::Seed seedTooLongSeed(
          "9999999999999999999999999999999999999999999999999999999999999999999999999999999999"),
      IOTA::Errors::IllegalState, "seed is too long");

  EXPECT_EXCEPTION(
      IOTA::Models::Seed seedInvalid(
          "999999999999999999999999999999999999999999999999999999999999999999999999999999998"),
      IOTA::Errors::IllegalState, "seed is not a valid trytes string");
}

TEST(Seed, FromSetter) {
  IOTA::Models::Seed seed;

  seed.setSeed("");
  EXPECT_EQ(seed.toTrytes(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);

  seed.setSeed("9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(seed.toTrytes(),
            "9ABCDEFGHIJKLMNOPQRSTUVWXYZ999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);

  seed.setSeed("ABC");
  EXPECT_EQ(seed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);

  seed.setSeed("ABC999");
  EXPECT_EQ(seed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);

  EXPECT_EXCEPTION(
      seed.setSeed(
          "ABC9999999999999999999999999999999999999999999999999999999999999999999999999999999"),
      IOTA::Errors::IllegalState, "seed is too long");
  //! keeps previous value
  EXPECT_EQ(seed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);

  EXPECT_EXCEPTION(seed.setSeed("ABC8"), IOTA::Errors::IllegalState,
                   "seed is not a valid trytes string");
  //! keeps previous value
  EXPECT_EQ(seed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(seed.getSecurity(), 2);
}

TEST(Transaction, SecurityGetterAndSetter) {
  IOTA::Models::Seed seed = { "", 3 };
  EXPECT_EQ(seed.getSecurity(), 3);

  seed.setSecurity(1);
  EXPECT_EQ(seed.getSecurity(), 1);

  EXPECT_EXCEPTION(seed.setSecurity(5), IOTA::Errors::IllegalState, "Invalid Security Level");
}

TEST(Seed, ImplicitConversion) {
  std::string        seedStr = "ABC999";
  IOTA::Models::Seed seed    = seedStr;

  EXPECT_EQ(seed.toTrytes(),
            "ABC999999999999999999999999999999999999999999999999999999999999999999999999999999");
}

TEST(Seed, OperatorEq) {
  IOTA::Models::Seed lhs_eq("SEED");
  IOTA::Models::Seed rhs_eq("SEED999");
  EXPECT_TRUE(lhs_eq == rhs_eq);

  IOTA::Models::Seed lhs_neq("SEEDONE");
  IOTA::Models::Seed rhs_neq("SEEDTWO999");
  EXPECT_FALSE(lhs_neq == rhs_neq);
}

TEST(Seed, OperatorNEq) {
  IOTA::Models::Seed lhs_eq("SEED");
  IOTA::Models::Seed rhs_eq("SEED999");
  EXPECT_FALSE(lhs_eq != rhs_eq);

  IOTA::Models::Seed lhs_neq("SEEDONE");
  IOTA::Models::Seed rhs_neq("SEEDTWO999");
  EXPECT_TRUE(lhs_neq != rhs_neq);
}

TEST(Seed, OperatorEqTrytes) {
  IOTA::Models::Seed  lhs_eq("SEED");
  IOTA::Types::Trytes rhs_eq("SEED999");
  EXPECT_TRUE(lhs_eq == rhs_eq);

  IOTA::Models::Seed  lhs_neq("SEEDONE");
  IOTA::Types::Trytes rhs_neq("SEEDTWO999");
  EXPECT_FALSE(lhs_neq == rhs_neq);
}

TEST(Seed, OperatorNEqTrytes) {
  IOTA::Models::Seed  lhs_eq("SEED");
  IOTA::Types::Trytes rhs_eq("SEED999");
  EXPECT_FALSE(lhs_eq != rhs_eq);

  IOTA::Models::Seed  lhs_neq("SEEDONE");
  IOTA::Types::Trytes rhs_neq("SEEDTWO999");
  EXPECT_TRUE(lhs_neq != rhs_neq);
}
