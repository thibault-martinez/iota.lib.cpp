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

#include <Crypto/Signing.hpp>
#include <fstream>
#include "gtest/gtest.h"

TEST(SigningTest, Key) {
  std::ifstream file("/root/iota.lib.cpp/test/files/signingKey");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Signing s;
  while (std::getline(file, line)) {
    auto semicolon = line.find(';');
    auto seed      = line.substr(0, semicolon);
    auto rest      = line.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto index     = std::stoi(rest.substr(0, semicolon));
    rest           = rest.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto security  = std::stoi(rest.substr(0, semicolon));
    rest           = rest.substr(semicolon + 1);
    semicolon      = rest.find(';');
    auto key       = rest.substr(0, semicolon);
    rest           = rest.substr(semicolon + 1);
    EXPECT_EQ(key, IOTA::Type::tritsToTrytes(s.key(seed, index, security)));
  }
}

TEST(SigningTest, Address) {
  std::ifstream file("/root/iota.lib.cpp/test/files/signingAddress");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Signing s;
  while (std::getline(file, line)) {
    auto              semicolon    = line.find(';');
    auto              digests      = line.substr(0, semicolon);
    auto              address      = line.substr(semicolon + 1);
    IOTA::Type::Trits digestsTrits = IOTA::Type::trytesToTrits(digests);
    IOTA::Type::Trits addressTrits = s.address(digestsTrits);
    EXPECT_EQ(address, IOTA::Type::tritsToTrytes(addressTrits));
  }
}

TEST(SigningTest, Digests) {
  std::ifstream file("/root/iota.lib.cpp/test/files/signingDigests");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Signing s;
  while (std::getline(file, line)) {
    auto              semicolon    = line.find(';');
    auto              key          = line.substr(0, semicolon);
    auto              digests      = line.substr(semicolon + 1);
    IOTA::Type::Trits keyTrits     = IOTA::Type::trytesToTrits(key);
    IOTA::Type::Trits digestsTrits = s.digests(keyTrits);
    EXPECT_EQ(digests, IOTA::Type::tritsToTrytes(digestsTrits));
  }
}
