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

#include <unordered_map>
#include "Keccak384.hpp"
#include "gtest/gtest.h"

static std::unordered_map<std::string, std::string> hashes = {
  { "Message",
    "0c8d6ff6e6a1cf18a0d55b20f0bca160d0d1c914"
    "a5e842f3707a25eeb20a279f6b4e83eda8e43a67"
    "697832c7f69f53ca" },
  { "Keccak-384",
    "924bd16d2ae40f6b93d58f488002de88f9288a75"
    "986c60944005e99b55fec03b1f55ff91186142c6"
    "4c2547de5a85815e" },
  { "IOTA",
    "7ea0e8132692844c737a527baedb3045900d8ef7"
    "102e4aaec87c47450717c0cfa7b23db6429e8359"
    "09ca4393c5a171d5" },
  { "Crypto",
    "29c016cf4476900cc2d17e3255137f45af2e4836"
    "ac8281bf6f6d76978dec2926c386723b7bf65e73"
    "01b5a062686bd227" },
  { "Input",
    "fad2b6d11d8b32a8554775321441091eecbe13fc"
    "3aa4f835eb81449303d8bd8f0407838bc265a4cf"
    "60261133e4da9a22" },
  { "Tangle",
    "5c7685f3c667c8a2c44d6d85174af11c57bbf9c7"
    "6260af885588e6bcd05b8e485de284e24c3614c0"
    "3f9072b5f67675bd" },
  { "Hash",
    "b6cea85560278fa023f1ceea13b434c45d223529e8c6760473c2f6f6a9f2c566aa0407d6ada26256945a595bfe07df"
    "c6" },
  { "b6cea85560278fa023f1ceea13b434c45d223529e8c6760473c2f6f6a9f2c566aa0407d6ada26256945a595bfe07df"
    "c6",
    "674d7600f0596b2074a19c6eb5ef785d5fc6a1e1b7af81cd776eb1296e1e10de7f11926be182509538f2eb5225e3d6"
    "2a" },
  { "674d7600f0596b2074a19c6eb5ef785d5fc6a1e1b7af81cd776eb1296e1e10de7f11926be182509538f2eb5225e3d6"
    "2a",
    "1d48d470066949b60ad2a0929be916f4e32743cbeba99bcb7178e5ee46f6ed6ee513e26c812a8a16ec8210cfa51556"
    "8f" },
  { "1d48d470066949b60ad2a0929be916f4e32743cbeba99bcb7178e5ee46f6ed6ee513e26c812a8a16ec8210cfa51556"
    "8f",
    "2ed08bff9d7d000275911940152c7f7ab5b05b36be1904004eef366f63febde86b0bf86de8ea4a8896f2fbb8427d35"
    "c1" },
  { "2ed08bff9d7d000275911940152c7f7ab5b05b36be1904004eef366f63febde86b0bf86de8ea4a8896f2fbb8427d35"
    "c1",
    "3fa3a52ad49e76a3545f7e8d19fa2a328637dc017357729f465a03d91e7e6d5a1cb923a737a76752eeecd5c4ad73f7"
    "49" }
};

TEST(Keccak384Test, Hash) {
  IOTA::Crypto::Keccak384 k;

  for (auto& input : hashes) {
    std::vector<int8_t> vinput(std::begin(input.first), std::end(input.first));
    std::vector<int8_t> voutput(48);
    k.update(vinput);
    k.finalize(voutput);
    std::stringstream stream;
    for (unsigned int i = 0; i < voutput.capacity(); i++) {
      stream << std::setw(2) << std::hex << std::setfill('0')
             << static_cast<int>(static_cast<uint8_t>(voutput[i]));
    }
    EXPECT_EQ(input.second, stream.str());
    k.reset();
  }
}
