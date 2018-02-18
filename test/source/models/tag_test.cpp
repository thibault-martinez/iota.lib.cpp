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

#include <iota/errors/illegal_state.hpp>
#include <iota/models/tag.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Tag, FromCtor) {
  IOTA::Models::Tag tagEmptyCtor;
  EXPECT_EQ(tagEmptyCtor.empty(), true);
  EXPECT_EQ(tagEmptyCtor.toTrytes(), "");
  EXPECT_EQ(tagEmptyCtor.toTrytesWithPadding(), "999999999999999999999999999");

  IOTA::Models::Tag tagFullValidTag("9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(tagFullValidTag.empty(), false);
  EXPECT_EQ(tagFullValidTag.toTrytes(), "9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(tagFullValidTag.toTrytesWithPadding(), "9ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  IOTA::Models::Tag tagShortTag("ABC");
  EXPECT_EQ(tagShortTag.empty(), false);
  EXPECT_EQ(tagShortTag.toTrytes(), "ABC");
  EXPECT_EQ(tagShortTag.toTrytesWithPadding(), "ABC999999999999999999999999");

  IOTA::Models::Tag tagTrailing9s("ABC999");
  EXPECT_EQ(tagTrailing9s.empty(), false);
  EXPECT_EQ(tagTrailing9s.toTrytes(), "ABC");
  EXPECT_EQ(tagTrailing9s.toTrytesWithPadding(), "ABC999999999999999999999999");

  EXPECT_EXCEPTION(IOTA::Models::Tag tagTooLongTag("9ABCDEFGHIJKLMNOPQRSTUVWXYZZ"),
                   IOTA::Errors::IllegalState, "tag is too long");

  EXPECT_EXCEPTION(IOTA::Models::Tag tagInvalid("9ABCDEFGHIJKLMNOPQRSTUVWXY8"),
                   IOTA::Errors::IllegalState, "tag is not a valid trytes string");
}

TEST(Tag, FromSetter) {
  IOTA::Models::Tag tag;

  tag.setTag("");
  EXPECT_EQ(tag.empty(), true);
  EXPECT_EQ(tag.toTrytes(), "");
  EXPECT_EQ(tag.toTrytesWithPadding(), "999999999999999999999999999");

  tag.setTag("9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "9ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  EXPECT_EQ(tag.toTrytesWithPadding(), "9ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  tag.setTag("ABC");
  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "ABC");
  EXPECT_EQ(tag.toTrytesWithPadding(), "ABC999999999999999999999999");

  tag.setTag("ABC999");
  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "ABC");
  EXPECT_EQ(tag.toTrytesWithPadding(), "ABC999999999999999999999999");

  EXPECT_EXCEPTION(tag.setTag("9ABCDEFGHIJKLMNOPQRSTUVWXYZZ"), IOTA::Errors::IllegalState,
                   "tag is too long");
  //! keeps previous value
  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "ABC");
  EXPECT_EQ(tag.toTrytesWithPadding(), "ABC999999999999999999999999");

  EXPECT_EXCEPTION(tag.setTag("9ABCDEFGHIJKLMNOPQRSTUVWXY8"), IOTA::Errors::IllegalState,
                   "tag is not a valid trytes string");
  //! keeps previous value
  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "ABC");
  EXPECT_EQ(tag.toTrytesWithPadding(), "ABC999999999999999999999999");
}

TEST(Tag, ImplicitConversion) {
  std::string       tagStr = "ABC999";
  IOTA::Models::Tag tag    = tagStr;

  EXPECT_EQ(tag.empty(), false);
  EXPECT_EQ(tag.toTrytes(), "ABC");
  EXPECT_EQ(tag.toTrytesWithPadding(), "ABC999999999999999999999999");
}

TEST(Tag, OperatorEq) {
  IOTA::Models::Tag lhs_eq("TAG");
  IOTA::Models::Tag rhs_eq("TAG999");
  EXPECT_TRUE(lhs_eq == rhs_eq);

  IOTA::Models::Tag lhs_neq("TAGONE");
  IOTA::Models::Tag rhs_neq("TAGTWO999");
  EXPECT_FALSE(lhs_neq == rhs_neq);
}

TEST(Tag, OperatorNEq) {
  IOTA::Models::Tag lhs_eq("TAG");
  IOTA::Models::Tag rhs_eq("TAG999");
  EXPECT_FALSE(lhs_eq != rhs_eq);

  IOTA::Models::Tag lhs_neq("TAGONE");
  IOTA::Models::Tag rhs_neq("TAGTWO999");
  EXPECT_TRUE(lhs_neq != rhs_neq);
}
