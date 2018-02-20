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
#include <iota/crypto/sponge_factory.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/address.hpp>

namespace IOTA {

namespace Models {

Address::Address(const Types::Trytes& address) {
  setAddress(address);
}

Address::Address(const char* address) : Address(Types::Trytes(address)) {
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
    auto         sponge = Crypto::create(Crypto::SpongeType::KERL);
    Types::Trits checksumTrits(TritHashLength);

    sponge->absorb(Types::trytesToTrits(address_));
    sponge->squeeze(checksumTrits);

    checksum_ = Types::tritsToTrytes(checksumTrits).substr(AddressLength - ChecksumLength);
  }

  return checksum_;
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

}  // namespace Models

}  // namespace IOTA
