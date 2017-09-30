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

#include <iota/crypto/kerl.hpp>
#include <iota/crypto/sponge_factory.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Defines utility methods to add/remove the checksum to/from an address.
 */
namespace Checksum {

/**
 * Add the checksum to the specified address.
 *
 * @param address The address without checksum.
 *
 * @return The address with checksum.
 **/
Types::Trytes add(const Types::Trytes& address);

/**
 * Remove the checksum from the specified address.
 *
 * @param address The address with checksum.
 *
 * @return The address without checksum.
 **/
Types::Trytes remove(const Types::Trytes& address);

/**
 * Actual computation of the address checksum.
 *
 * @param address The address.
 * @param type The sponge type to be used for checksum.
 *
 * @return The checksum.
 **/
Types::Trytes check(const Types::Trytes& address, const SpongeType& type = SpongeType::KERL);

/**
 * Determine whether the specified address with checksum has a valid checksum.
 *
 * @param address The address with checksum.
 *
 * @return true if the specified address with checksum has a valid checksum otherwise,
 * false.
 **/
bool isValid(const Types::Trytes& address);

}  // namespace Checksum

}  // namespace Crypto

}  // namespace IOTA
