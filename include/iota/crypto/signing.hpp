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

#pragma once

#include <iota/models/fwd.hpp>
#include <iota/types/trits.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Signing related functions.
 */
namespace Signing {

/**
 * Derive a private key from a seed.
 *
 * @param seedBytes Seed in bytes to be used for address generation.
 * @param index     The index to start the generation from.
 * @param security  The security to use for address generation.
 *
 * @return The key as bytes.
 */
std::vector<uint8_t> key(const std::vector<uint8_t>& seedBytes, uint32_t index = 0,
                         uint32_t security = 2);

/**
 * Compute digests from key.
 *
 * @param keyBytes The key in bytes.
 *
 * @return The digests.
 */
std::vector<uint8_t> digests(const std::vector<uint8_t>& keyBytes);

/**
 * Compute address from digests.
 *
 * @param digests The digests.
 *
 * @return The address.
 */
std::vector<uint8_t> address(const std::vector<uint8_t>& digests);

/**
 * Compute hash x normalizedBundleFragment[i] for each fragment in the signature.
 *
 * @param normalizedBundleFragment The bundle fragment.
 * @param signatureFragment The signature fragment.
 *
 * @return The digest.
 */
std::vector<uint8_t> digest(const std::vector<int8_t>&  normalizedBundleFragment,
                            const std::vector<uint8_t>& signatureFragment);

/**
 * Compute signature from bundle fragment and key fragment.
 *
 * @param normalizedBundleFragment The bundle fragment.
 * @param keyFragment The key fragment.
 *
 * @return The signature fragment.
 */
Types::Trits signatureFragment(const std::vector<int8_t>& normalizedBundleFragment,
                               const Types::Trits&        keyFragment);

std::vector<Types::Trytes> signInputs(const Models::Seed&                 seed,
                                      const std::vector<Models::Address>& inputs,
                                      Models::Bundle&                     bundle,
                                      const std::vector<Types::Trytes>&   signatureFragments);

/**
 * Validate signature fragments.
 *
 * @param expectedAddress The expected address.
 * @param signatureFragments The signature fragments.
 * @param bundleHash The bundle hash.
 *
 * @return whether signature fragment are valid or not.
 */
bool validateSignatures(const Models::Address&            expectedAddress,
                        const std::vector<Types::Trytes>& signatureFragments,
                        const Types::Trytes&              bundleHash);

};  // namespace Signing

}  // namespace Crypto

}  // namespace IOTA
