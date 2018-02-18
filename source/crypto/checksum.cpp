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

#include <iota/constants.hpp>
#include <iota/crypto/checksum.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

namespace Checksum {

Types::Trytes
add(const Types::Trytes& address) {
  return address + check(address);
}

Types::Trytes
remove(const Types::Trytes& address) {
  if (address.empty()) {
    return "";
  }

  return address.substr(0, SeedLength);
}

Types::Trytes
check(const Types::Trytes& address, const SpongeType& type) {
  //! skip invalid address, critical error
  if (!Types::isValidAddress(address)) {
    throw Errors::IllegalState("Invalid address, can not compute checksum");
  }

  auto         sponge = create(type);
  Types::Trits checksumTrits(TritHashLength);

  sponge->absorb(Types::trytesToTrits(address.substr(0, AddressLength)));
  sponge->squeeze(checksumTrits);

  auto checksum = Types::tritsToTrytes(checksumTrits);
  return checksum.substr(AddressLength - ChecksumLength);
}

bool
isValid(const Types::Trytes& addressWithChecksum) {
  //! skip invalid address
  if (!Types::isValidAddress(addressWithChecksum)) {
    return false;
  }

  //! if we do have an address without checksum, also skip
  if (addressWithChecksum.length() != AddressLengthWithChecksum) {
    return false;
  }

  auto addressWithoutChecksum         = remove(addressWithChecksum);
  auto addressWithRecalculateChecksum = add(addressWithoutChecksum);

  return addressWithRecalculateChecksum == addressWithChecksum;
}

}  // namespace Checksum

}  // namespace Crypto

}  // namespace IOTA
