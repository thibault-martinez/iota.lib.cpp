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

#pragma once

#include <iota/crypto/kerl.hpp>
#include <iota/models/address.hpp>

namespace IOTA {

namespace Models {

/**
 * Used to store multi signing addresses.
 * Provides validity checks at construction / value set.
 * Provides checksum generation.
 * Any multi signing addresses stored represented with this class are ensured to be valid.
 */
class MultiSigningAddress : public Address {
public:
  /**
   * Ctor.
   *
   * @param address the address value. It must be a valid address. Checksum can be included.
   * @param balance The balance associated of the address.
   * @param keyIndex The key index of the address.
   * @param security The security level of the address.
   */
  MultiSigningAddress(const Types::Trytes& address = "", const int64_t& balance = 0,
                      const int32_t& keyIndex = 0, const int32_t& security = 0);

  /**
   * Ctor, char* based to make implicitly convertion to Address more flexible.
   *
   * @param address the address value. It must be a valid address. Checksum can be included.
   * @param balance The balance associated of the address.
   * @param keyIndex The key index of the address.
   * @param security The security level of the address.
   */
  MultiSigningAddress(const char* address, const int64_t& balance = 0, const int32_t& keyIndex = 0,
                      const int32_t& security = 0);

public:
  /**
   * Absorbs key digests
   * Increments security according to digests.
   *
   * @param digests The key digests in bytes.
   **/
  void absorbDigests(const std::vector<uint8_t>& digests);

  /**
   * Finalizes and set the multisig address.
   **/
  void finalize();

  /**
   * Validates a generated multisig address.
   *
   * @param digests The keys digests.
   *
   * @return whether the multisig address is valid or not.
   **/
  bool validate(const std::vector<std::vector<uint8_t>> digests);

public:
  /**
   * Set the security level of the address.
   */
  void setSecurity(const int32_t& security);

private:
  Crypto::Kerl k_;
};

}  // namespace Models

}  // namespace IOTA
