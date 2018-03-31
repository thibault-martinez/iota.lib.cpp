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

#include <algorithm>

#include <iota/constants.hpp>
#include <iota/crypto/kerl.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>
#include <iota/types/utils.hpp>

namespace IOTA {

namespace Models {

Bundle::Bundle(const std::vector<Models::Transaction>& transactions) : transactions_(transactions) {
  if (!empty()) {
    hash_ = getTransactions()[0].getBundle();
  }
}

const std::vector<Models::Transaction>&
Bundle::getTransactions() const {
  return transactions_;
}

std::vector<Models::Transaction>&
Bundle::getTransactions() {
  return transactions_;
}

std::size_t
Bundle::getLength() const {
  return transactions_.size();
}

bool
Bundle::empty() const {
  return getLength() == 0;
}

const Types::Trytes&
Bundle::getHash() const {
  return hash_;
}

void
Bundle::setHash(const Types::Trytes& hash) {
  hash_ = hash;
}

void
Bundle::addTransaction(const Transaction& transaction, int32_t signatureMessageLength) {
  if (empty()) {
    hash_ = transaction.getBundle();
  }

  transactions_.push_back(transaction);

  if (signatureMessageLength > 1) {
    Transaction signatureTransaction = { transaction.getAddress(), 0, transaction.getTag(),
                                         transaction.getTimestamp() };

    for (int i = 1; i < signatureMessageLength; i++) {
      transactions_.push_back(signatureTransaction);
    }
  }
}

void
Bundle::finalize() {
  Crypto::Kerl k;
  bool         validBundle = false;

  while (!validBundle) {
    k.reset();
    for (std::size_t i = 0; i < transactions_.size(); i++) {
      auto& trx = transactions_[i];

      trx.setCurrentIndex(i);
      trx.setLastIndex(transactions_.size() - 1);

      auto value = Types::tritsToTrytes(Types::intToTrits(trx.getValue(), SeedLength));
      auto timestamp =
          Types::tritsToTrytes(Types::intToTrits(trx.getTimestamp(), TryteAlphabetLength));
      auto currentIndex =
          Types::tritsToTrytes(Types::intToTrits(trx.getCurrentIndex(), TryteAlphabetLength));
      auto lastIndexTrits =
          Types::tritsToTrytes(Types::intToTrits(trx.getLastIndex(), TryteAlphabetLength));

      auto bytes = Types::trytesToBytes(trx.getAddress().toTrytes() + value +
                                        trx.getObsoleteTag().toTrytesWithPadding() + timestamp +
                                        currentIndex + lastIndexTrits);
      k.absorb(bytes);
    }

    std::vector<uint8_t> hash(ByteHashLength);
    k.finalSqueeze(hash);

    //! set bundle hash for each underlying transaction
    hash_               = Types::bytesToTrytes(hash);
    auto normalizedHash = normalizedBundle(hash_);
    if (transactions_.size() != 0 && std::find(std::begin(normalizedHash), std::end(normalizedHash),
                                               13 /* = M */) != std::end(normalizedHash)) {
      // Insecure bundle. Increment Tag and recompute bundle hash.
      auto tagTrits = Types::trytesToTrits(transactions_[0].getObsoleteTag().toTrytesWithPadding());
      Types::incrementTrits(tagTrits);
      transactions_[0].setObsoleteTag(Types::tritsToTrytes(tagTrits));
    } else {
      validBundle = true;
    }
  }
  for (std::size_t i = 0; i < transactions_.size(); i++) {
    transactions_[i].setBundle(hash_);
  }
}

void
Bundle::addTrytes(const std::vector<Types::Trytes>& signatureFragments) {
  Types::Trytes emptySignatureFragment = Types::Utils::rightPad("", 2187, '9');

  for (unsigned int i = 0; i < transactions_.size(); i++) {
    auto& transaction = transactions_[i];

    // Fill empty signatureMessageFragment
    transaction.setSignatureFragments(
        (signatureFragments.size() <= i || signatureFragments[i].empty()) ? emptySignatureFragment
                                                                          : signatureFragments[i]);

    // Fill empty trunkTransaction
    transaction.setTrunkTransaction(EmptyHash);

    // Fill empty branchTransaction
    transaction.setBranchTransaction(EmptyHash);

    // Fill empty nonce
    transaction.setNonce(EmptyNonce);
  }
}

std::vector<int8_t>
Bundle::normalizedBundle(const Types::Trytes& bundleHash) {
  std::vector<int8_t> normalizedBundle(SeedLength, 0);

  for (int i = 0; i < 3; i++) {
    long sum = 0;
    for (unsigned int j = 0; j < TryteAlphabetLength; j++) {
      sum += (normalizedBundle[i * TryteAlphabetLength + j] = Types::tritsToInt<int32_t>(
                  Types::trytesToTrits(Types::Trytes(1, bundleHash[i * TryteAlphabetLength + j]))));
    }

    if (sum >= 0) {
      while (sum-- > 0) {
        for (unsigned int j = 0; j < TryteAlphabetLength; j++) {
          if (normalizedBundle[i * TryteAlphabetLength + j] > -13) {
            normalizedBundle[i * TryteAlphabetLength + j]--;
            break;
          }
        }
      }
    } else {
      while (sum++ < 0) {
        for (unsigned int j = 0; j < TryteAlphabetLength; j++) {
          if (normalizedBundle[i * TryteAlphabetLength + j] < 13) {
            normalizedBundle[i * TryteAlphabetLength + j]++;
            break;
          }
        }
      }
    }
  }

  return normalizedBundle;
}

bool
Bundle::operator<(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getAttachmentTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getAttachmentTimestamp();

  return lhsTS < rhsTS;
}

bool
Bundle::operator>(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getAttachmentTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getAttachmentTimestamp();

  return lhsTS > rhsTS;
}

bool
Bundle::operator==(const Bundle& rhs) const {
  return getHash() == rhs.getHash();
}

bool
Bundle::operator!=(const Bundle& rhs) const {
  return !operator==(rhs);
}

}  // namespace Models

}  // namespace IOTA
