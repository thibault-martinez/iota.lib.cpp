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
 * @param seed The seed.
 * @param index The index of the key.
 * @param security The security level of the key.
 *
 * @return The key as trits.
 */
Types::Trits key(const Types::Trytes& seed, const unsigned int& index = 0,
                 const unsigned int& security = 1);

/**
 * Compute hash x normalizedBundleFragment[i] for each fragment in the signature.
 *
 * @param normalizedBundleFragment The bundle fragment.
 * @param signatureFragment The signature fragment.
 *
 * @return The digest.
 */
Types::Trits digest(const std::vector<int8_t>& normalizedBundleFragment,
                    const Types::Trits&        signatureFragment);

/**
 * Compute digests from key.
 *
 * @param key The key.
 *
 * @return The digests.
 */
Types::Trits digests(const Types::Trits& key);

/**
 * Compute address from digests.
 *
 * @param digests The digests.
 *
 * @return The address.
 */
Types::Trits address(const Types::Trits& digests);

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

/**
 * Validate signature fragments.
 *
 * @param expectedAddress The expected address.
 * @param signatureFragments The signature fragments.
 * @param bundleHash The bundle hash.
 *
 * @return whether signature fragment are valid or not.
 */
bool validateSignatures(const Types::Trytes&              expectedAddress,
                        const std::vector<Types::Trytes>& signatureFragments,
                        const Types::Trytes&              bundleHash);

};  // namespace Signing

}  // namespace Crypto

}  // namespace IOTA
