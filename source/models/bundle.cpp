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

#include <iomanip>
#include <sstream>

#include <iota/constants.hpp>
#include <iota/crypto/sponge_factory.hpp>
#include <iota/models/bundle.hpp>
#include <iota/types/trinary.hpp>
#include <iota/types/utils.hpp>

namespace IOTA {

namespace Models {

Bundle::Bundle(const std::vector<Models::Transaction>& transactions) : transactions_(transactions) {
}

const std::vector<Models::Transaction>&
Bundle::getTransactions() const {
  return transactions_;
}

std::vector<Models::Transaction>&
Bundle::getTransactions() {
  return transactions_;
}

uint32_t
Bundle::getLength() const {
  return transactions_.size();
}

bool
Bundle::empty() const {
  return getLength() == 0;
}

void
Bundle::addTransaction(int32_t signatureMessageLength, const std::string& address, int64_t value,
                       const std::string& tag, int64_t timestamp) {
  for (int i = 0; i < signatureMessageLength; i++) {
    transactions_.push_back({ address, i == 0 ? value : 0, tag, timestamp });
  }
}

void
Bundle::addTransaction(const Transaction& transaction) {
  transactions_.push_back(transaction);
}

void
Bundle::finalize(const std::shared_ptr<IOTA::Crypto::ISponge>& customSponge) {
  std::shared_ptr<IOTA::Crypto::ISponge> sponge =
      customSponge ? customSponge : IOTA::Crypto::create(IOTA::Crypto::SpongeType::KERL);

  //! ensure sponge is reset
  sponge->reset();

  for (std::size_t i = 0; i < transactions_.size(); i++) {
    auto& trx = transactions_[i];

    trx.setCurrentIndex(i);
    trx.setLastIndex(transactions_.size() - 1);

    auto value = IOTA::Types::tritsToTrytes(IOTA::Types::intToTrits((int)trx.getValue(), SeedLength));
    auto timestamp = IOTA::Types::tritsToTrytes(
        IOTA::Types::intToTrits((int)trx.getTimestamp(), TryteAlphabetLength));
    auto currentIndex = IOTA::Types::tritsToTrytes(
        IOTA::Types::intToTrits((int)trx.getCurrentIndex(), TryteAlphabetLength));
    auto lastIndexTrits = IOTA::Types::tritsToTrytes(
        IOTA::Types::intToTrits((int)trx.getLastIndex(), TryteAlphabetLength));

    auto t = IOTA::Types::trytesToTrits(trx.getAddress() + value + trx.getTag() + timestamp +
                                        currentIndex + lastIndexTrits);

    sponge->absorb(t);
  }

  IOTA::Types::Trits hash(TritHashLength);
  sponge->squeeze(hash);

  std::string hashInTrytes = IOTA::Types::tritsToTrytes(hash);
  for (std::size_t i = 0; i < transactions_.size(); i++) {
    transactions_[i].setBundle(hashInTrytes);
  }
}

void
Bundle::addTrytes(const std::vector<std::string>& signatureFragments) {
  std::string emptySignatureFragment = IOTA::Types::Utils::rightPad("", 2187, '9');

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
    transaction.setNonce(EmptyHash);
  }
}

std::vector<int8_t>
Bundle::normalizedBundle(const std::string& bundleHash) {
  std::vector<int8_t> normalizedBundle(SeedLength, 0);

  for (int i = 0; i < 3; i++) {
    long sum = 0;
    for (unsigned int j = 0; j < TryteAlphabetLength; j++) {
      sum += (normalizedBundle[i * TryteAlphabetLength + j] =
                  IOTA::Types::tritsToInt<int32_t>(IOTA::Types::trytesToTrits(
                      std::string(1, bundleHash[i * TryteAlphabetLength + j]))));
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
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getTimestamp();

  return lhsTS < rhsTS;
}

bool
Bundle::operator>(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getTimestamp();

  return lhsTS > rhsTS;
}

bool
Bundle::operator<=(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getTimestamp();

  return lhsTS <= rhsTS;
}

bool
Bundle::operator>=(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getTimestamp();

  return lhsTS >= rhsTS;
}

bool
Bundle::operator==(const Bundle& rhs) const {
  int64_t lhsTS = empty() ? 0 : getTransactions()[0].getTimestamp();
  int64_t rhsTS = rhs.empty() ? 0 : rhs.getTransactions()[0].getTimestamp();

  return lhsTS == rhsTS;
}

bool
Bundle::operator!=(const Bundle& rhs) const {
  return !operator==(rhs);
}

}  // namespace Models

}  // namespace IOTA
