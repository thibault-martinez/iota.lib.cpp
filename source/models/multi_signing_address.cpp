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
#include <iota/errors/illegal_state.hpp>
#include <iota/models/multi_signing_address.hpp>

namespace IOTA {

namespace Models {

MultiSigningAddress::MultiSigningAddress(const Types::Trytes& address, const int64_t& balance,
                                         const int32_t& keyIndex, const int32_t& security) {
  setAddress(address);
  setSecurity(security);
  balance_  = balance;
  keyIndex_ = keyIndex;
}

MultiSigningAddress::MultiSigningAddress(const char* address, const int64_t& balance,
                                         const int32_t& keyIndex, const int32_t& security)
    : MultiSigningAddress(Types::Trytes(address), balance, keyIndex, security) {
}

void
MultiSigningAddress::absorbDigests(const std::vector<uint8_t>& digests) {
  security_ += digests.size() / ByteHashLength;
  k_.absorb(digests);
}

void
MultiSigningAddress::finalize() {
  std::vector<uint8_t> addressBytes(ByteHashLength);

  k_.squeeze(addressBytes);
  setAddress(IOTA::Types::bytesToTrytes(addressBytes));
}

bool
MultiSigningAddress::validate(const std::vector<std::vector<uint8_t>> digests) {
  Crypto::Kerl k;

  for (const auto& digest : digests) {
    k.absorb(digest);
  }

  std::vector<uint8_t> addressBytes(ByteHashLength);
  k.squeeze(addressBytes);

  return IOTA::Types::bytesToTrytes(addressBytes) == address_;
}

void
MultiSigningAddress::setSecurity(const int32_t& security) {
  //! Validate the security level
  if (security < 0) {
    throw Errors::IllegalState("Invalid Security Level");
  }
  security_ = security;
}

}  // namespace Models

}  // namespace IOTA
