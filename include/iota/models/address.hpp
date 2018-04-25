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
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

/**
 * Used to store addresses.
 * Provides validity checks at construction / value set.
 * Provides checksum generation.
 * Any addresses stored represented with this class are ensured to be valid.
 */
class Address {
public:
  enum Type { NORMAL, MULTISIG };

public:
  /**
   * Ctor.
   *
   * @param address the address value. It must be a valid address. Checksum can be included.
   * @param balance The balance associated of the address.
   * @param keyIndex The key index of the address.
   * @param security The security level of the address.
   */
  Address(const Types::Trytes& address = "", const int64_t& balance = 0,
          const int32_t& keyIndex = 0, const int32_t& security = 2, Type type = NORMAL);

  /**
   * Ctor, char* based to make implicitly convertion to Address more flexible.
   *
   * @param address the address value. It must be a valid address. Checksum can be included.
   * @param balance The balance associated of the address.
   * @param keyIndex The key index of the address.
   * @param security The security level of the address.
   */
  Address(const char* address, const int64_t& balance = 0, const int32_t& keyIndex = 0,
          const int32_t& security = 2, Type type = NORMAL);

  /**
   * Ctor - mainly to used to build multisig addresses.
   *
   * @param type The address type, normal or multisig.
   */
  explicit Address(Type type);

  /**
   * Default dtor.
   */
  ~Address() = default;

public:
  /**
   * @return address as a trytes string, without the checksum
   */
  const Types::Trytes& toTrytes() const;

  /**
   * This function returns the address as a trytes string, including a checksum.
   * The returned checksum is generated the first time this function, or getChecksum, is called.
   * If the object was built with an address containing a checksum, this checksum will be used even
   * though it may be invalid, unless validChecksum is set to true.
   *
   * @param validChecksum if true, ensure the returned checksum is valid by regenerating it (see
   * explanations above)
   * @return address as a trytes string including a checksum.
   */
  Types::Trytes toTrytesWithChecksum(bool validChecksum = false);

  /**
   * Set the address value
   *
   * @param address the address value. It must be a valid address. Checksum can be included.
   */
  void setAddress(const Types::Trytes& address);

  /**
   * This function returns the address checksum.
   * The returned checksum is generated the first time this function, or toTrytesWithChecksum, is
   * called.
   * If the object was built with an address containing a checksum, this checksum will be
   * used even though it may be invalid, unless validChecksum is set to true.
   *
   * @param validChecksum if true, ensure the returned checksum is valid by regenerating it (see
   * explanations above)
   * @return address checksum as trytes string.
   */
  const Types::Trytes& getChecksum(bool validChecksum = false);

  /**
   * @return whether the address is empty or not.
   */
  bool empty() const;

  /**
   * Multisig address related methods.
   */
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
   * @return Balance.
   */
  const int64_t& getBalance() const;

  /**
   * @param balance set new balance for input.
   */
  void setBalance(const int64_t& balance);

public:
  /**
   * @return Key Index.
   */
  const int32_t& getKeyIndex() const;

  /**
   * @param keyIndex set new keyIndex for input in transaction.
   */
  void setKeyIndex(const int32_t& keyIndex);

public:
  /**
   * @return Security.
   */
  const int32_t& getSecurity() const;

  /**
   * @param security set new security level for input.
   */
  void setSecurity(const int32_t& security);

public:
  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Address& rhs) const;

  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Address& rhs) const;

public:
  /**
   * Comparison operator, trytes-based for convenient use
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Types::Trytes& rhs) const;

  /**
   * Comparison operator, trytes-based for convenient use
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Types::Trytes& rhs) const;

private:
  /**
   * address value without checksum
   */
  Types::Trytes address_;

  /**
   * address checksum
   */
  Types::Trytes checksum_;

  /**
   * The balance.
   */
  int64_t balance_ = 0;

  /**
   * The key index.
   */
  int32_t keyIndex_ = 0;

  /**
   * The security.
   */
  int32_t security_ = 2;

  /**
   * Type of the address (normal/multisig)
   */
  Type type_;

  /**
   * Instance of Kerl for multisig addresses.
   */
  Crypto::Kerl k_;
};

}  // namespace Models

}  // namespace IOTA
