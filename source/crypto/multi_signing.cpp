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
#include <iota/models/multi_signing_address.hpp>

namespace IOTA {

namespace Crypto {

namespace MultiSigning {

/**
 *   Gets the key value of a seed
 *
 *   @method getKey
 *   @param {string} seed
 *   @param {int} index
 *   @param {int} security Security level to be used for the private key / address. Can be 1, 2 or 3
 *   @returns {string} digest trytes
 **/
std::vector<uint8_t>
key(const std::vector<uint8_t>& seedBytes, uint32_t index, uint32_t security) {
  return Signing::key(seedBytes, index, security);
}

std::vector<uint8_t>
getDigest(const std::vector<uint8_t>& seedBytes, uint32_t index, uint32_t security) {
  auto keyBytes = Signing::key(seedBytes, index, security);
  return Signing::digests(keyBytes);
}

// /**
//  * Gets the key value of a seed
//  *
//  * @param seed  Tryte-encoded seed. It should be noted that this seed is not transferred
//  * @param index Key index to start search from. If the index is provided, the generation of the
//  *address is not deterministic.
//  * @return trytes.
//  * @throws ArgumentException is thrown when the specified security level is not valid.
//  **/
//
// public
// String
// getKey(String seed, int index, int security) throws ArgumentException {
//   return Converter.trytes(
//       signingInstance.key(Converter.trits(seed, 81 * security), index, security));
// }
//

// TODO here ?
bool
validateAddress(const Models::MultiSigningAddress&      msa,
                const std::vector<std::vector<uint8_t>> digests) {
  Kerl k;

  for (const auto& digest : digests) {
    k.absorb(digest);
  }

  std::vector<uint8_t> addressBytes(ByteHashLength);
  k.squeeze(addressBytes);

  return IOTA::Types::bytesToTrytes(addressBytes) == msa.toTrytes();
}

/**
 *   Adds the cosigner signatures to the corresponding bundle transaction
 *
 *   @method addSignature
 *   @param {array} bundleToSign
 *   @param {int} cosignerIndex
 *   @param {string} inputAddress
 *   @param {string} key
 *   @param {function} callback
 *   @returns {array} trytes Returns bundle trytes
 **/
void
addSignature(Models::Bundle& bundleToSign, const Models::MultiSigningAddress& inputAddress,
             const std::vector<uint8_t>& key) {
  // Get the security used for the private key
  // 1 security level = 2187 trytes
  unsigned int security = key.size() / (ByteHashLength * FragmentLength);

  // convert private key trytes into trits
  auto keyTrits = Types::bytesToTrits(key);  // TODO optimize

  // First get the total number of already signed transactions
  // use that for the bundle hash calculation as well as knowing
  // where to add the signature
  unsigned int numSignedTxs = 0;

  for (unsigned int i = 0; i < bundleToSign.getLength(); ++i) {
    if (bundleToSign.getTransactions()[i].getAddress() == inputAddress.toTrytes()) {
      // If transaction is already signed, increase counter
      if (bundleToSign.getTransactions()[i].getSignatureFragments().find_first_not_of("9") !=
          std::string::npos) {
        numSignedTxs++;
      }
      // Else sign the transactionse
      else {
        auto bundleHash = bundleToSign.getTransactions()[i].getBundle();

        //  First 6561 trits for the firstFragment
        std::vector<int8_t> firstFragment(&keyTrits[0], &keyTrits[6561]);

        //  Get the normalized bundle hash
        auto normalizedBundleHash = bundleToSign.normalizedBundle(bundleHash);
        std::vector<std::vector<int8_t>> normalizedBundleFragments;

        // Split hash into 3 fragments
        for (unsigned int k = 0; k < 3; ++k) {
          normalizedBundleFragments.emplace_back(&normalizedBundleHash[k * 27],
                                                 &normalizedBundleHash[(k + 1) * 27]);
        }

        //  First bundle fragment uses 27 trytes
        auto firstBundleFragment = normalizedBundleFragments[numSignedTxs % 3];

        //  Calculate the new signatureFragment with the first bundle fragment
        auto firstSignedFragment = Signing::signatureFragment(firstBundleFragment, firstFragment);

        //  Convert signature to trytes and assign the new signatureFragment
        bundleToSign.getTransactions()[i].setSignatureFragments(
            Types::tritsToTrytes(firstSignedFragment));

        for (unsigned int j = 1; j < security; ++j) {
          //  Next 6561 trits for the firstFragment
          std::vector<int8_t> nextFragment(&keyTrits[j * 6561], &keyTrits[(j + 1) * 6561]);

          //  Use the next 27 trytes
          auto nextBundleFragment = normalizedBundleFragments[(numSignedTxs + j) % 3];

          //  Calculate the new signatureFragment with the first bundle fragment
          auto nextSignedFragment = Signing::signatureFragment(nextBundleFragment, nextFragment);

          //  Convert signature to trytes and add new bundle entry at i + j position
          // Assign the signature fragment
          bundleToSign.getTransactions()[i + j].setSignatureFragments(
              Types::tritsToTrytes(nextSignedFragment));
        }

        break;
      }
    }
  }
}

bool
validateSignatures(const Models::Bundle&              signedBundle,
                   const Models::MultiSigningAddress& inputAddress) {
  Types::Trytes              bundleHash;
  std::vector<Types::Trytes> signatureFragments;

  for (unsigned int i = 0; i < signedBundle.getLength(); ++i) {
    auto& tx = signedBundle.getTransactions()[i];

    if (tx.getAddress() == inputAddress) {
      bundleHash = tx.getBundle();

      // if we reached remainder bundle
      auto& signatureFragment = tx.getSignatureFragments();
      if (signatureFragment.find_first_not_of("9") == std::string::npos) {
        break;
      }
      signatureFragments.push_back(signatureFragment);
    }
  }

  return Signing::validateSignatures(inputAddress, signatureFragments, bundleHash);
}

}  // namespace MultiSigning

};  // namespace Crypto

}  // namespace IOTA
