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

#include <iota/models/multi_signing_address.hpp>

namespace IOTA {

namespace Crypto {

/**
 * Multi signing related functions.
 */
namespace MultiSigning {

/**
 * Derive a private key from a seed.
 *
 * @param seedBytes Seed in bytes to be used for address generation.
 * @param index     The index to start the generation from.
 * @param security  The security to use for address generation.
 *
 * @return The key as bytes.
 */
std::vector<uint8_t> key(const std::vector<uint8_t>& seedBytes, uint32_t index, uint32_t security);

/**
 * Compute digests from key.
 *
 * @param keyBytes The key in bytes.
 *
 * @return The digests.
 */
std::vector<uint8_t> digests(const std::vector<uint8_t>& keyBytes);

/**
 * Adds the cosigner signatures to the corresponding bundle transaction
 *
 * @param bundleToSign  Bundle to be signed.
 * @param inputAddress  Input address.
 * @param key           Key to sign with.
 */
void addSignature(Models::Bundle& bundleToSign, const Models::MultiSigningAddress& inputAddress,
                  const std::vector<uint8_t>& key);

/**
 * Validate the signature fragment.
 *
 * @param signedBundle The bundle.
 * @param inputAddress The address.
 *
 * @return whether the signatures are valid or not.
 */
bool validateSignatures(const Models::Bundle&              signedBundle,
                        const Models::MultiSigningAddress& inputAddress);

}  // namespace MultiSigning

}  // namespace Crypto

}  // namespace IOTA
