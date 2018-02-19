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

#include <iota/crypto/signing.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>
#include <test/utils/configuration.hpp>

TEST(SigningTest, Key) {
  std::ifstream file(get_deps_folder() + "/signingKey");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
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
    EXPECT_EQ(key, IOTA::Types::tritsToTrytes(IOTA::Crypto::Signing::key(seed, index, security)));
  }
}

TEST(SigningTest, Digest) {
  std::ifstream file(get_deps_folder() + "/signingDigest");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  while (std::getline(file, line)) {
    auto semicolon         = line.find(';');
    auto bundleHash        = line.substr(0, semicolon);
    auto rest              = line.substr(semicolon + 1);
    semicolon              = rest.find(';');
    auto signatureFragment = rest.substr(0, semicolon);
    rest                   = rest.substr(semicolon + 1);
    semicolon              = rest.find(';');
    auto digest            = rest.substr(0, semicolon);
    rest                   = rest.substr(semicolon + 1);

    IOTA::Models::Bundle bundle;
    auto                 normalizedBundleHash = bundle.normalizedBundle(bundleHash);
    EXPECT_EQ(digest,
              IOTA::Types::tritsToTrytes(IOTA::Crypto::Signing::digest(
                  std::vector<int8_t>{ &normalizedBundleHash[0], &normalizedBundleHash[27] },
                  IOTA::Types::trytesToTrits(signatureFragment))));
  }
}

TEST(SigningTest, Digests) {
  std::ifstream file(get_deps_folder() + "/signingDigests");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  while (std::getline(file, line)) {
    auto               semicolon    = line.find(';');
    auto               key          = line.substr(0, semicolon);
    auto               digests      = line.substr(semicolon + 1);
    IOTA::Types::Trits keyTrits     = IOTA::Types::trytesToTrits(key);
    IOTA::Types::Trits digestsTrits = IOTA::Crypto::Signing::digests(keyTrits);
    EXPECT_EQ(digests, IOTA::Types::tritsToTrytes(digestsTrits));
  }
}

TEST(SigningTest, Address) {
  std::ifstream file(get_deps_folder() + "/signingAddress");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  while (std::getline(file, line)) {
    auto               semicolon    = line.find(';');
    auto               digests      = line.substr(0, semicolon);
    auto               address      = line.substr(semicolon + 1);
    IOTA::Types::Trits digestsTrits = IOTA::Types::trytesToTrits(digests);
    IOTA::Types::Trits addressTrits = IOTA::Crypto::Signing::address(digestsTrits);
    EXPECT_EQ(address, IOTA::Types::tritsToTrytes(addressTrits));
  }
}

TEST(SigningTest, SignatureFragments) {
  std::ifstream file(get_deps_folder() + "/signingSignatureFragments");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  while (std::getline(file, line)) {
    auto semicolon        = line.find(';');
    auto keyTrytes        = line.substr(0, semicolon);
    auto rest             = line.substr(semicolon + 1);
    semicolon             = rest.find(';');
    auto bundleHashTrytes = rest.substr(0, semicolon);
    rest                  = rest.substr(semicolon + 1);
    semicolon             = rest.find(';');
    auto sign0Trytes      = rest.substr(0, semicolon);
    rest                  = rest.substr(semicolon + 1);
    semicolon             = rest.find(';');
    auto sign1Trytes      = rest.substr(0, semicolon);
    rest                  = rest.substr(semicolon + 1);

    IOTA::Models::Bundle bundle;
    auto                 normalizedBundleHash = bundle.normalizedBundle(bundleHashTrytes);
    auto                 keyTrits             = IOTA::Types::trytesToTrits(keyTrytes);
    auto                 sign0Trits           = IOTA::Crypto::Signing::signatureFragment(
        std::vector<int8_t>{ &normalizedBundleHash[0], &normalizedBundleHash[27] },
        std::vector<int8_t>{ &keyTrits[0], &keyTrits[6561] });
    auto sign1Trits = IOTA::Crypto::Signing::signatureFragment(
        std::vector<int8_t>{ &normalizedBundleHash[27], &normalizedBundleHash[27 * 2] },
        std::vector<int8_t>{ &keyTrits[6561], &keyTrits[6561 * 2] });
    EXPECT_EQ(sign0Trytes, IOTA::Types::tritsToTrytes(sign0Trits));
    EXPECT_EQ(sign1Trytes, IOTA::Types::tritsToTrytes(sign1Trits));
  }
}

TEST(SigningTest, ValidateSignatures) {
  std::ifstream file(get_deps_folder() + "/signingvalidateSignatures");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  std::getline(file, line);
  while (std::getline(file, line)) {
    auto semicolon  = line.find(';');
    auto addr       = line.substr(0, semicolon);
    auto rest       = line.substr(semicolon + 1);
    semicolon       = rest.find(';');
    auto sign0      = rest.substr(0, semicolon);
    rest            = rest.substr(semicolon + 1);
    semicolon       = rest.find(';');
    auto sign1      = rest.substr(0, semicolon);
    rest            = rest.substr(semicolon + 1);
    semicolon       = rest.find(';');
    auto bundleHash = rest.substr(0, semicolon);
    rest            = rest.substr(semicolon + 1);
    semicolon       = rest.find(';');
    auto valid      = rest.substr(0, semicolon);
    rest            = rest.substr(semicolon + 1);

    IOTA::Models::Bundle bundle;
    auto                 normalizedBundleHash = bundle.normalizedBundle(bundleHash);
    auto res = IOTA::Crypto::Signing::validateSignatures(addr, { sign0, sign1 }, bundleHash);
    EXPECT_EQ(static_cast<int>(res), std::stoi(valid));
  }
}
