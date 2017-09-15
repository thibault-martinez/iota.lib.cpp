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

#pragma once

#include <Crypto/Curl.hpp>

#include <string>

namespace IOTA {

namespace Utils {

class RandomAddressGenerator {
public:
  RandomAddressGenerator()  = default;
  ~RandomAddressGenerator() = default;

public:
  /**
   * Generates a new address
   *
   * @param seed     The tryte-encoded seed. It should be noted that this seed is not transferred.
   * @param security The secuirty level of private key / seed.
   * @param index    The index to start search from. If the index is provided, the generation of the
   * address is not deterministic.
   * @param checksum The adds 9-tryte address checksum
   * @param curl     The curl instance.
   * @return An String with address.
   */
  std::string operator()(const std::string& seed, const int32_t& security, const int32_t& index,
                         bool checksum, Crypto::Curl curl);
};

}  // namespace Utils

}  // namespace IOTA
