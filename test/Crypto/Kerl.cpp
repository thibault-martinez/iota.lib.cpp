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

#include <Crypto/Kerl.hpp>
#include <Errors/Crypto.hpp>
#include <fstream>
#include "gtest/gtest.h"

TEST(KerlTest, Exceptions) {
  IOTA::Crypto::Kerl k;
  IOTA::Type::Trits  trits(
      "GYOMKVTSNHVJNCNFBBAH9AAMXLPLLLROQY99QN9DLSJUHDPBLCFFAIQXZA9BKMBJCYSFHFPXAHDWZFEIZ");
  EXPECT_NO_THROW(k.absorb(trits));
  EXPECT_THROW(k.absorb(trits, 0, 42), IOTA::Errors::Crypto);
  EXPECT_NO_THROW(k.squeeze(trits));
  EXPECT_THROW(k.squeeze(trits, 0, 42), IOTA::Errors::Crypto);
}

TEST(KerlTest, TrytesAndHashes) {
  std::ifstream file("/root/iota.lib.cpp/test/files/kerlTrytesAndHashes");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto              semicolon = line.find(';');
    auto              trytes    = line.substr(0, semicolon);
    auto              hash      = line.substr(semicolon + 1);
    IOTA::Type::Trits trits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, trits.toTryteString());
    k.reset();
  }
}

TEST(KerlTest, MultiTrytesAndHash) {
  std::ifstream file("/root/iota.lib.cpp/test/files/kerlMultiTrytesAndHash");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto              semicolon = line.find(';');
    auto              trytes    = line.substr(0, semicolon);
    auto              hash      = line.substr(semicolon + 1);
    IOTA::Type::Trits trits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, trits.toTryteString());
    k.reset();
  }
}

TEST(KerlTest, TrytesAndMultiSqueeze) {
  std::ifstream file("/root/iota.lib.cpp/test/files/kerlTrytesAndMultiSqueeze");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto semicolon = line.find(';');
    auto trytes    = line.substr(0, semicolon);
    auto rest      = line.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto hash1     = rest.substr(0, semicolon);
    rest           = rest.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto hash2     = rest.substr(0, semicolon);
    rest           = rest.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto hash3     = rest.substr(0, semicolon);
    rest           = rest.substr(semicolon + 1);
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
