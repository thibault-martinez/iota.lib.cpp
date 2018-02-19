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

#include <fstream>

#include <gtest/gtest.h>

#include <iota/crypto/kerl.hpp>
#include <iota/errors/crypto.hpp>
#include <iota/types/trinary.hpp>
#include <test/utils/configuration.hpp>

TEST(Kerl, Exceptions) {
  IOTA::Crypto::Kerl k;
  IOTA::Types::Trits trits = IOTA::Types::trytesToTrits(
      "GYOMKVTSNHVJNCNFBBAH9AAMXLPLLLROQY99QN9DLSJUHDPBLCFFAIQXZA9BKMBJCYSFHFPXAHDWZFEIZ");
  EXPECT_NO_THROW(k.absorb(trits));
  EXPECT_THROW(k.absorb(trits, 0, 42), IOTA::Errors::Crypto);
  EXPECT_NO_THROW(k.squeeze(trits));
  EXPECT_THROW(k.squeeze(trits, 0, 42), IOTA::Errors::Crypto);
}

TEST(Kerl, TrytesAndHashes) {
  std::ifstream file(get_deps_folder() + "/kerlTrytesAndHashes");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto               semicolon = line.find(';');
    auto               trytes    = line.substr(0, semicolon);
    auto               hash      = line.substr(semicolon + 1);
    IOTA::Types::Trits trits     = IOTA::Types::trytesToTrits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, IOTA::Types::tritsToTrytes(trits));
    k.reset();
  }
}

TEST(Kerl, MultiTrytesAndHash) {
  std::ifstream file(get_deps_folder() + "/kerlMultiTrytesAndHash");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto               semicolon = line.find(';');
    auto               trytes    = line.substr(0, semicolon);
    auto               hash      = line.substr(semicolon + 1);
    IOTA::Types::Trits trits     = IOTA::Types::trytesToTrits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash, IOTA::Types::tritsToTrytes(trits));
    k.reset();
  }
}

TEST(Kerl, TrytesAndMultiSqueeze) {
  std::ifstream file(get_deps_folder() + "/kerlTrytesAndMultiSqueeze");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  IOTA::Crypto::Kerl k;
  while (std::getline(file, line)) {
    auto semicolon           = line.find(';');
    auto trytes              = line.substr(0, semicolon);
    auto rest                = line.substr(semicolon + 1);
    semicolon                = rest.find(';');
    auto hash1               = rest.substr(0, semicolon);
    rest                     = rest.substr(semicolon + 1);
    semicolon                = rest.find(';');
    auto hash2               = rest.substr(0, semicolon);
    rest                     = rest.substr(semicolon + 1);
    semicolon                = rest.find(';');
    auto hash3               = rest.substr(0, semicolon);
    rest                     = rest.substr(semicolon + 1);
    IOTA::Types::Trits trits = IOTA::Types::trytesToTrits(trytes);
    k.absorb(trits);
    k.squeeze(trits);
    EXPECT_EQ(hash1, IOTA::Types::tritsToTrytes(trits));
    k.squeeze(trits);
    EXPECT_EQ(hash2, IOTA::Types::tritsToTrytes(trits));
    k.squeeze(trits);
    EXPECT_EQ(hash3, IOTA::Types::tritsToTrytes(trits));
    k.reset();
  }
}
