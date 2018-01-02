// //
// // MIT License
// //
// // Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
// //
// // Permission is hereby granted, free of charge, to any person obtaining a copy
// // of this software and associated documentation files (the "Software"), to deal
// // in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// // copies of the Software, and to permit persons to whom the Software is
// // furnished to do so, subject to the following conditions:
// //
// // The above copyright notice and this permission notice shall be included in all
// // copies or substantial portions of the Software.
// //
// // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// // IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// // FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// // AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// // LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// // OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// // SOFTWARE.
// //
// //
//
// #include "Trits.hpp"
// #include "gtest/gtest.h"
//
// // TEST(TritsTest, isValidTrit) {
// //   ASSERT_EQ(IOTA::Types::Utils::isValidTrit(-1), true);
// //   ASSERT_EQ(IOTA::Types::isValidTrit(0), true);
// //   ASSERT_EQ(IOTA::Types::isValidTrit(1), true);
// //   ASSERT_EQ(IOTA::Types::isValidTrit(-2), false);
// //   ASSERT_EQ(IOTA::Types::isValidTrit(2), false);
// // }
//
// TEST(TritsTest, fromVector) {
//   std::vector<int8_t> values_ok{ -1, 0, 1, 1, 0, -1 };
//   std::vector<int8_t> values_ko{ -1, 0, 2, 1, 0, -1 };
//
//   EXPECT_NO_THROW(IOTA::Types::Trits trits_ok(values_ok));
//   EXPECT_THROW(IOTA::Types::Trits trits_ko(values_ko), std::exception);
// }
//
// TEST(TritsTest, fromInt) {
//   std::vector<int8_t> values1{ 0, -1, -1, -1, 1 };
//   IOTA::Types::Trits   trits1_int(42);
//   IOTA::Types::Trits   trits1_vec(values1);
//   std::vector<int8_t> values2{ 0, 1, 1, 1, -1 };
//   IOTA::Types::Trits   trits2_int(-42);
//   IOTA::Types::Trits   trits2_vec(values2);
//   std::vector<int8_t> values3{ 1, 0, -1, 1, 0, -1, -1, 1 };
//   IOTA::Types::Trits   trits3_int(1234);
//   IOTA::Types::Trits   trits3_vec(values3);
//   std::vector<int8_t> values4{ 1, 1, 0, 1, 0, -1, 0, 0, 1, -1, 0, -1, -1, 1 };
//   IOTA::Types::Trits   trits4_int(872401);
//   IOTA::Types::Trits   trits4_vec(values4);
//
//   EXPECT_EQ(trits1_int, trits1_vec);
//   EXPECT_EQ(trits2_int, trits2_vec);
//   EXPECT_EQ(trits3_int, trits3_vec);
//   EXPECT_EQ(trits4_int, trits4_vec);
// }
//
// TEST(TritsTest, size) {
//   std::vector<int8_t> values1{ -1, 0, 1, 1, 0, -1, -1 };
//   std::vector<int8_t> values2{ -1, 0, 1, 0, 1, 0, 1, 0, -1, 0, 1 };
//
//   IOTA::Types::Trits trits1(values1);
//   IOTA::Types::Trits trits2(values2);
//
//   EXPECT_EQ(values1.size(), trits1.size());
//   EXPECT_EQ(values2.size(), trits2.size());
// }
//
// TEST(TritsTest, values) {
//   std::vector<int8_t> values{ -1, 0, 1, 1, 0, -1 };
//   IOTA::Types::Trits   trits(values);
//
//   EXPECT_EQ(values.size(), trits.values().size());
//   for (size_t i = 0; i < values.size(); ++i) {
//     EXPECT_EQ(values[i], trits.values()[i]);
//   }
// }
//
// // TEST(TritsTest, isValid) {
// //   IOTA::Types::Trits validTrits1({ 1, 0, -1, -1, 0, 1 });
// //   ASSERT_EQ(validTrits1.isValid(), true);
// //   IOTA::Types::Trits validTrits2({ 1, 1, 0, 1, -1, -1, -1, -1, 0, 0, 1, 1, -1 });
// //   ASSERT_EQ(validTrits2.isValid(), true);
// //   IOTA::Types::Trits invalidTrits1({ 1, 0, 2, -1, 0, 1 });
// //   ASSERT_EQ(invalidTrits1.isValid(), false);
// //   IOTA::Types::Trits invalidTrits2({ 1, 0, 0, -4, 0, 4 });
// //   ASSERT_EQ(invalidTrits2.isValid(), false);
// // }
// //
//
// TEST(TritsTest, canTrytes) {
//   IOTA::Types::Trits trits2({ 0, 0 });
//   IOTA::Types::Trits trits3({ 0, 0, 0 });
//   IOTA::Types::Trits trits4({ 0, 0, 0, 0 });
//   IOTA::Types::Trits trits5({ 0, 0, 0, 0, 0 });
//   IOTA::Types::Trits trits6({ 0, 0, 0, 0, 0, 0 });
//
//   EXPECT_FALSE(trits2.canTrytes());
//   EXPECT_TRUE(trits3.canTrytes());
//   EXPECT_FALSE(trits4.canTrytes());
//   EXPECT_FALSE(trits5.canTrytes());
//   EXPECT_TRUE(trits6.canTrytes());
// }
//
// TEST(TritsTest, toInt) {
//   IOTA::Types::Trits trits1({ 0, -1, -1, -1, 1 });
//   IOTA::Types::Trits trits2({ 0, 1, 1, 1, -1 });
//   IOTA::Types::Trits trits3({ 1, 0, -1, 1, 0, -1, -1, 1 });
//   IOTA::Types::Trits trits4({ 1, 1, 0, 1, 0, -1, 0, 0, 1, -1, 0, -1, -1, 1 });
//
//   EXPECT_EQ(trits1.toInt(), 42);
//   EXPECT_EQ(trits2.toInt(), -42);
//   EXPECT_EQ(trits3.toInt(), 1234);
//   EXPECT_EQ(trits4.toInt(), 872401);
// }
//
// TEST(TritsTest, equalityOperator) {
//   IOTA::Types::Trits trits1({ -1, 0, 0, 1 });
//   IOTA::Types::Trits trits2({ -1, 0, 0, 1 });
//   IOTA::Types::Trits trits3({ 1, 1, -1, 0 });
//   EXPECT_EQ(trits1, trits1);
//   EXPECT_EQ(trits1, trits2);
//   EXPECT_NE(trits1, trits3);
// }
