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

#include <iota/constants.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/address.hpp>

namespace IOTA {

namespace Models {

Address::Address(const Types::Trytes& address, const int64_t& balance, const int32_t& keyIndex,
                 const int32_t& security, Type type)
    : balance_(balance), keyIndex_(keyIndex), type_(type) {
  setAddress(address);
  setSecurity(security);
}

Address::Address(const char* address, const int64_t& balance, const int32_t& keyIndex,
                 const int32_t& security, Type type)
    : Address(Types::Trytes(address), balance, keyIndex, security, type) {
}

Address::Address(Type type) : Address("", 0, 0, 0, type) {
}

const Types::Trytes&
Address::toTrytes() const {
  return address_;
}

Types::Trytes
Address::toTrytesWithChecksum(bool validChecksum) {
  return address_ + getChecksum(validChecksum);
}

bool
Address::empty() const {
  return address_.empty();
}

void
Address::absorbDigests(const std::vector<uint8_t>& digests) {
  if (type_ != MULTISIG)
    return;
  security_ += digests.size() / ByteHashLength;
  k_.absorb(digests);
}

void
Address::finalize() {
  if (type_ != MULTISIG)
    return;
  std::vector<uint8_t> addressBytes(ByteHashLength);

  k_.squeeze(addressBytes);
  setAddress(IOTA::Types::bytesToTrytes(addressBytes));
}

bool
Address::validate(const std::vector<std::vector<uint8_t>> digests) {
  if (type_ != MULTISIG)
    return false;
  Crypto::Kerl k;

  for (const auto& digest : digests) {
    k.absorb(digest);
  }

  std::vector<uint8_t> addressBytes(ByteHashLength);
  k.squeeze(addressBytes);

  return IOTA::Types::bytesToTrytes(addressBytes) == address_;
}

void
Address::setAddress(const Types::Trytes& address) {
  if (!address.empty() && address.length() != AddressLength &&
      address.length() != AddressLengthWithChecksum) {
    throw Errors::IllegalState("address has invalid length");
  }

  if (!Types::isValidTrytes(address)) {
    throw Errors::IllegalState("address is not a valid trytes string");
  }

  address_ = address.substr(0, AddressLength);

  if (address.length() == AddressLengthWithChecksum) {
    checksum_ = address.substr(AddressLength);
  } else {
    checksum_ = "";
  }
}

const Types::Trytes&
Address::getChecksum(bool validChecksum) {
  //! note that we do not do anything for empty address
  if (!empty() && (checksum_.empty() || validChecksum)) {
    Crypto::Kerl         k;
    std::vector<uint8_t> checksumBytes(ByteHashLength);

    k.absorb(Types::trytesToBytes(address_));
    k.finalSqueeze(checksumBytes);

    checksum_ = Types::bytesToTrytes(checksumBytes).substr(AddressLength - ChecksumLength);
  }

  return checksum_;
}

const int64_t&
Address::getBalance() const {
  return balance_;
}

void
Address::setBalance(const int64_t& balance) {
  balance_ = balance;
}

const int32_t&
Address::getKeyIndex() const {
  return keyIndex_;
}

void
Address::setKeyIndex(const int32_t& keyIndex) {
  keyIndex_ = keyIndex;
}

const int32_t&
Address::getSecurity() const {
  return security_;
}

void
Address::setSecurity(const int32_t& security) {
  //! Validate the security level
  if ((type_ == MULTISIG && security < 0) || (type_ == NORMAL && (security < 1 || security > 3))) {
    throw Errors::IllegalState("Invalid Security Level");
  }
  security_ = security;
}

bool
Address::operator==(const Address& rhs) const {
  return address_ == rhs.address_;
}

bool
Address::operator!=(const Address& rhs) const {
  return !operator==(rhs);
}

bool
Address::operator==(const Types::Trytes& rhs) const {
  return operator==(Address{ rhs });
}

bool
Address::operator!=(const Types::Trytes& rhs) const {
  return operator!=(Address{ rhs });
}

std::ostream&
operator<<(std::ostream& os, const Address& address) {
  return os << address.toTrytes();
}

}  // namespace Models

}  // namespace IOTA
