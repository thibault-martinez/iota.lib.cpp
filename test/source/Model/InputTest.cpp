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

#include <Model/input.hpp>

TEST(Input, CtorDefault) {
  Input i;

  EXPECT_EQ(i.getAddress(), "");
  EXPECT_EQ(i.getBalance(), 0);
  EXPECT_EQ(i.getKeyIndex(), 0);
  EXPECT_EQ(i.getSecurity(), 0);
}

TEST(Input, CtorFull) {
  Input i = { "addr", 1, 2, 3 };

  EXPECT_EQ(i.getAddress(), "addr");
  EXPECT_EQ(i.getBalance(), 1);
  EXPECT_EQ(i.getKeyIndex(), 2);
  EXPECT_EQ(i.getSecurity(), 3);
}

TEST(Input, ConstGetters) {
  const Input i = { "addr", 1, 2, 3 };

  EXPECT_EQ(i.getAddress(), "addr");
  EXPECT_EQ(i.getBalance(), 1);
  EXPECT_EQ(i.getKeyIndex(), 2);
  EXPECT_EQ(i.getSecurity(), 3);
}

TEST(Input, AddressGetterAndSetter) {
  Input i;
  EXPECT_EQ(i.getAddress(), "");

  i.setAddress("addr");
  EXPECT_EQ(i.getAddress(), "addr");
}

TEST(Input, BalanceGetterAndSetter) {
  Input i;
  EXPECT_EQ(i.getBalance(), 0);

  i.setBalance(1);
  EXPECT_EQ(i.getBalance(), 1);
}

TEST(Input, KeyIndexGetterAndSetter) {
  Input i;
  EXPECT_EQ(i.getKeyIndex(), 0);

  i.setKeyIndex(1);
  EXPECT_EQ(i.getKeyIndex(), 1);
}

TEST(Input, SecurityGetterAndSetter) {
  Input i;
  EXPECT_EQ(i.getSecurity(), 0);

  i.setSecurity(1);
  EXPECT_EQ(i.getSecurity(), 1);
}
