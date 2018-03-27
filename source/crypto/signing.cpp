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
#include <iota/crypto/kerl.hpp>
#include <iota/crypto/signing.hpp>
#include <iota/models/bundle.hpp>
#include <iota/models/seed.hpp>
#include <iota/types/big_int.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

namespace Signing {

//! When a tryte value is normalized, it is converted into a list of integers.
//! The int values ranged from -13 to 13 (giving a set of 27 values, matching the alphabet length)
//! This characteristic is used in the Signing algorithm
static constexpr int NormalizedTryteUpperBound = 13;

std::vector<uint8_t>
key(const std::vector<uint8_t>& seedBytes, uint32_t index, uint32_t security) {
  Kerl k;

  Types::Bigint        b;
  std::vector<uint8_t> seedIndexBytes(ByteHashLength);

  b.fromBytes(seedBytes);
  b.addU32(index);
  b.toBytes(seedIndexBytes);

  k.absorb(seedIndexBytes);
  k.finalSqueeze(seedIndexBytes);
  k.reset();
  k.absorb(seedIndexBytes);

  std::vector<uint8_t> keyBytes(security * FragmentLength * ByteHashLength);

  unsigned int offset = 0;
  for (unsigned int i = 0; i < security; ++i) {
    for (unsigned int j = 0; j < FragmentLength; ++j) {
      k.squeeze(keyBytes, offset);
      offset += ByteHashLength;
    }
  }
  return keyBytes;
}

std::vector<uint8_t>
digests(const std::vector<uint8_t>& key) {
  Kerl                 k1;
  Kerl                 k2;
  unsigned int         security = key.size() / (ByteHashLength * FragmentLength);
  std::vector<uint8_t> digests(security * ByteHashLength);

  for (unsigned int i = 0; i < security; ++i) {
    std::vector<uint8_t> keyFragment(key.begin() + (i * ByteHashLength * FragmentLength),
                                     key.begin() + ((i + 1) * ByteHashLength * FragmentLength));
    for (unsigned j = 0; j < FragmentLength; ++j) {
      auto fragmentOffset = j * ByteHashLength;
      for (unsigned int l = 0; l < FragmentLength - 1; ++l) {
        k1.reset();
        k1.absorb(keyFragment, fragmentOffset, ByteHashLength);
        k1.finalSqueeze(keyFragment, fragmentOffset);
      }
      k2.absorb(keyFragment, fragmentOffset, ByteHashLength);
    }
    k2.finalSqueeze(digests, i * ByteHashLength);
    k2.reset();
  }
  return digests;
}

std::vector<uint8_t>
address(const std::vector<uint8_t>& digests) {
  Kerl                 k;
  std::vector<uint8_t> addressBytes(ByteHashLength);

  k.absorb(digests);
  k.finalSqueeze(addressBytes);
  return addressBytes;
}

std::vector<uint8_t>
digest(const std::vector<int8_t>&  normalizedBundleFragment,
       const std::vector<uint8_t>& signatureFragment) {
  Kerl k1;
  Kerl k2;

  for (unsigned int i = 0; i < FragmentLength; i++) {
    std::vector<uint8_t> buffer(&signatureFragment[i * ByteHashLength],
                                &signatureFragment[(i + 1) * ByteHashLength]);
    for (unsigned int j = normalizedBundleFragment[i] + NormalizedTryteUpperBound; j > 0; --j) {
      k2.reset();
      k2.absorb(buffer);
      k2.finalSqueeze(buffer);
    }
    k1.absorb(buffer);
  }
  std::vector<uint8_t> buffer(ByteHashLength);
  k1.finalSqueeze(buffer);
  return buffer;
}

// TODO(Optimize)
Types::Trits
signatureFragment(const std::vector<int8_t>& normalizedBundleFragment,
                  const Types::Trits&        keyFragment) {
  Kerl         k;
  Types::Trits signatureFragment{};

  for (unsigned int i = 0; i < FragmentLength; ++i) {
    Types::Trits buffer(keyFragment.begin() + i * TritHashLength,
                        keyFragment.begin() + (i + 1) * TritHashLength);
    auto         bytes = Types::tritsToBytes(buffer);
    for (int j = 0; j < NormalizedTryteUpperBound - normalizedBundleFragment[i]; ++j) {
      k.reset();
      k.absorb(bytes);
      k.finalSqueeze(bytes);
    }
    auto buff = Types::bytesToTrits(bytes);
    signatureFragment.insert(std::end(signatureFragment), std::begin(buff), std::end(buff));
  }

  return signatureFragment;
}

bool
validateSignatures(const Models::Address&            expectedAddress,
                   const std::vector<Types::Trytes>& signatureFragments,
                   const Types::Trytes&              bundleHash) {
  Models::Bundle                   bundle;
  auto                             normalizedBundleHash = bundle.normalizedBundle(bundleHash);
  std::vector<std::vector<int8_t>> normalizedBundleFragments;
  std::vector<uint8_t>             digests;

  for (unsigned int i = 0; i < 3; i++) {
    normalizedBundleFragments.emplace_back(normalizedBundleHash.begin() + i * FragmentLength,
                                           normalizedBundleHash.begin() + (i + 1) * FragmentLength);
  }

  for (unsigned int i = 0; i < signatureFragments.size(); ++i) {
    auto digestBuffer =
        digest(normalizedBundleFragments[i % 3], Types::trytesToBytes(signatureFragments[i]));

    digests.insert(std::end(digests), std::begin(digestBuffer), std::end(digestBuffer));
  }

  return expectedAddress == Types::bytesToTrytes(address(digests));
}

}  // namespace Signing

}  // namespace Crypto

}  // namespace IOTA
