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

#include <iota/models/bundle.hpp>

TEST(Bundle, CtorDefault) {
  IOTA::Models::Bundle b;

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});
}

TEST(Bundle, CtorFull) {
  IOTA::Models::Bundle b({ { "addr", 0, "tag", 0 } });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{
                                     IOTA::Models::Transaction("addr", 0, "tag", 0) });
}

TEST(Bundle, ConstGetters) {
  const IOTA::Models::Bundle b({ { "addr", 0, "tag", 0 } });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{
                                     IOTA::Models::Transaction("addr", 0, "tag", 0) });
}

TEST(Bundle, TransactionsGetterAndSetter) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});

  b.addTransaction({ "addr", 0, "tag", 0 });
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{
                                     IOTA::Models::Transaction("addr", 0, "tag", 0) });
}

TEST(Bundle, TransactionsNonConstGetter) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});

  auto& trx = b.getTransactions();
  trx.push_back({ "addr", 0, "tag", 0 });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{
                                     IOTA::Models::Transaction("addr", 0, "tag", 0) });
}

TEST(Bundle, IsEmptyWithCtor) {
  IOTA::Models::Bundle b({ { "addr", 0, "tag", 0 } });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, IsEmptyWithDefaultCtor) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);
}

TEST(Bundle, IsEmptyWithAdd) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);

  b.addTransaction({ "addr", 0, "tag", 0 });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, IsEmptyWithPush) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);

  auto& trx = b.getTransactions();
  trx.push_back({ "addr", 0, "tag", 0 });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, GetLengthWithCtor) {
  IOTA::Models::Bundle b({ { "addr", 0, "tag", 0 } });
  EXPECT_EQ(b.getLength(), 1);
}

TEST(Bundle, GetLengthWithDefaultCtor) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0);
}

TEST(Bundle, GetLengthWithAdd) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0);

  b.addTransaction({ "addr", 0, "tag", 0 });
  EXPECT_EQ(b.getLength(), 1);
}

TEST(Bundle, GetLengthWithPush) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0);

  auto& trx = b.getTransactions();
  trx.push_back({ "addr", 0, "tag", 0 });
  EXPECT_EQ(b.getLength(), 1);
}

TEST(Bundle, EqOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs == eq_rhs, true);

  IOTA::Models::Bundle neq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle neq_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(neq_lhs == neq_rhs, false);
}

TEST(Bundle, NeqOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs != eq_rhs, false);

  IOTA::Models::Bundle neq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle neq_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(neq_lhs != neq_rhs, true);
}

TEST(Bundle, LtOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs < eq_rhs, false);

  IOTA::Models::Bundle lt_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle lt_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(lt_lhs < lt_rhs, true);

  IOTA::Models::Bundle gt_lhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle gt_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(gt_lhs < gt_rhs, false);
}

TEST(Bundle, LteOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs <= eq_rhs, true);

  IOTA::Models::Bundle lt_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle lt_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(lt_lhs <= lt_rhs, true);

  IOTA::Models::Bundle gt_lhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle gt_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(gt_lhs <= gt_rhs, false);
}

TEST(Bundle, GtOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs > eq_rhs, false);

  IOTA::Models::Bundle lt_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle lt_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(lt_lhs > lt_rhs, false);

  IOTA::Models::Bundle gt_lhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle gt_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(gt_lhs > gt_rhs, true);
}

TEST(Bundle, GteOperator) {
  IOTA::Models::Bundle eq_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle eq_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(eq_lhs >= eq_rhs, true);

  IOTA::Models::Bundle lt_lhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle lt_rhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(lt_lhs >= lt_rhs, false);

  IOTA::Models::Bundle gt_lhs({ { "addr", 0, "tag", 3 }, { "addr", 0, "tag", 1 } });
  IOTA::Models::Bundle gt_rhs({ { "addr", 0, "tag", 0 }, { "addr", 0, "tag", 2 } });
  EXPECT_EQ(gt_lhs >= gt_rhs, true);
}
