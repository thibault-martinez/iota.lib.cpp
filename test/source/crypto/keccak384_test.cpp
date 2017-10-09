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

#include <fstream>

#include <gtest/gtest.h>

#include <iota/crypto/keccak384.hpp>
#include <test/utils/configuration.hpp>

TEST(Keccak384Test, digest) {
  std::ifstream file(get_deps_folder() + "/keccak384");
  std::string   line;
  ASSERT_TRUE(file.is_open());
  IOTA::Crypto::Keccak384 k;
  while (std::getline(file, line)) {
    auto                semicolon = line.find(';');
    auto                input     = line.substr(0, semicolon);
    auto                digest    = line.substr(semicolon + 1);
    std::vector<int8_t> vinput(std::begin(input), std::end(input));
    k.update(vinput);
    EXPECT_EQ(digest, k.digest());
    k.reset();
  }
}
