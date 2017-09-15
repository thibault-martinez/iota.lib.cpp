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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
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

#pragma once

#include <Crypto/ISponge.hpp>
// TODO remove
#include <Crypto/Kerl.hpp>
#include <iostream>
#include <vector>

namespace IOTA {

namespace Crypto {

class Signing {
public:
  Signing();
  // TODO sponge ctor
  virtual ~Signing();

public:
  Type::Trits      key(const std::string& seed, const unsigned int& index = 0,
                       const unsigned int& security = 1);
  std::vector<int> digest(const std::vector<int>& normalizedBundleFragment,
                          const std::vector<int>& signatureFragment);
  std::vector<int> digests(const std::vector<int>& key);
  std::vector<int> address(const std::vector<int>& digests);
  std::vector<int> signatureFragment(const std::vector<int>& normalizedBundleFragment,
                                     const std::vector<int>& keyFragment);
  void             validateSignatures(const std::string&              expectedAddress,
                                      const std::vector<std::string>& signatureFragments,
                                      const std::string&              bundleHash);

private:
  Kerl kerl_;
  // TODO Sponge
  // ISponge sponge_;
};

}  // namespace Crypto

}  // namespace IOTA
