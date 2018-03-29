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

#include <iota/crypto/keccak384.hpp>
#include <iota/errors/crypto.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/expect_exception.hpp>

class Keccak384Mock : public IOTA::Crypto::Keccak384 {
protected:
  bool hashUpdate(const uint8_t *, size_t) {
    return false;
  }

  bool hashSqueeze(uint8_t *) {
    return false;
  }

  bool hashInitialize(void) {
    return false;
  }
};

TEST(Keccak384, digest) {
  std::ifstream file(get_deps_folder() + "/keccak384");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  IOTA::Crypto::Keccak384 k;
  while (std::getline(file, line)) {
    auto semicolon = line.find(';');
    auto input     = line.substr(0, semicolon);
    auto digest    = line.substr(semicolon + 1);

    k.absorb(reinterpret_cast<const uint8_t *>(input.data()), input.size());

    std::stringstream stream;
    uint8_t           bytes[IOTA::Crypto::Keccak384::hashBitLength / 8];
    k.squeeze(bytes);
    for (auto &byte : bytes) {
      stream << std::setw(2) << std::hex << std::setfill('0')
             << static_cast<int>(static_cast<uint8_t>(byte));
    };

    EXPECT_EQ(digest, stream.str());
    k.reset();
  }
}

TEST(Keccak384, InitFail) {
  Keccak384Mock mock;

  EXPECT_EXCEPTION(mock.reset(), IOTA::Errors::Crypto, "Keccak384::initialize failed");
}

TEST(Keccak384, AbsorbFail) {
  Keccak384Mock mock;

  EXPECT_EXCEPTION(mock.absorb({}), IOTA::Errors::Crypto, "Keccak384::update failed");
}

TEST(Keccak384, SqueezeFail) {
  Keccak384Mock mock;

  EXPECT_EXCEPTION(mock.squeeze(nullptr), IOTA::Errors::Crypto, "Keccak384::squeeze failed");
}
