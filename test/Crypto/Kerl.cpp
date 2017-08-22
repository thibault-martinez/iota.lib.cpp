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

#include "Kerl.hpp"
#include <fstream>
#include "gtest/gtest.h"

TEST(KerlTest, trytesAndHashes) {
  std::ifstream file("/root/iota.lib.cpp/test/files/generateTrytesAndHashes");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto              comma  = line.find(',');
    auto              trytes = line.substr(0, comma);
    auto              hash   = line.substr(comma + 1);
    IOTA::Type::Trits trits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, trits.toTryteString());
    k.reset();
  }
}

TEST(KerlTest, multiTrytesAndHash) {
  std::ifstream file("/root/iota.lib.cpp/test/files/generateMultiTrytesAndHash");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto              comma  = line.find(',');
    auto              trytes = line.substr(0, comma);
    auto              hash   = line.substr(comma + 1);
    IOTA::Type::Trits trits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, trits.toTryteString());
    k.reset();
  }
}

TEST(KerlTest, TrytesAndMultiSqueeze) {
  std::ifstream file("/root/iota.lib.cpp/test/files/generateTrytesAndMultiSqueeze");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto comma  = line.find(',');
    auto trytes = line.substr(0, comma);
    auto rest   = line.substr(comma + 1);
    comma       = rest.find(',');
    auto hash1  = rest.substr(0, comma);
    rest        = rest.substr(comma + 1);
    comma       = rest.find(',');
    auto hash2  = rest.substr(0, comma);
    rest        = rest.substr(comma + 1);
    comma       = rest.find(',');
    auto hash3  = rest.substr(0, comma);
    rest        = rest.substr(comma + 1);
    IOTA::Type::Trits trits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash1, trits.toTryteString());
    k.squeeze(trits);
    EXPECT_EQ(hash2, trits.toTryteString());
    k.squeeze(trits);
    EXPECT_EQ(hash3, trits.toTryteString());
    k.reset();
  }
}
