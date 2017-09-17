
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

#include <Crypto/SpongeFactory.hpp>
#include <Model/Transaction.hpp>
#include <Type/Trinary.hpp>
#include <constants.hpp>

const std::pair<int, int> Transaction::SignatureFragmentsOffset = { 0, 2187 };
const std::pair<int, int> Transaction::AddressOffset            = { 2187, 2268 };
const std::pair<int, int> Transaction::ValueOffset              = { 6804, 6837 };
const std::pair<int, int> Transaction::TagOffset                = { 2295, 2322 };
const std::pair<int, int> Transaction::TimestampOffset          = { 6966, 6993 };
const std::pair<int, int> Transaction::CurrentIndexOffset       = { 6993, 7020 };
const std::pair<int, int> Transaction::LastIndexOffset          = { 7020, 7047 };
const std::pair<int, int> Transaction::BundleOffset             = { 2349, 2430 };
const std::pair<int, int> Transaction::TrunkOffset              = { 2430, 2511 };
const std::pair<int, int> Transaction::BranchOffset             = { 2511, 2592 };
const std::pair<int, int> Transaction::NonceOffset              = { 2592, 2673 };

Transaction::Transaction(const std::string& trytes) {
  initFromTrytes(trytes);
}

Transaction::Transaction(const std::string& signatureFragments, int64_t currentIndex,
                         int64_t lastIndex, const std::string& nonce, const std::string& hash,
                         const std::string& tag, int64_t timestamp,
                         const std::string& trunkTransaction, const std::string& branchTransaction,
                         const std::string& address, int64_t value, const std::string& bundle)
    : hash_(hash),
      signatureFragments_(signatureFragments),
      address_(address),
      value_(value),
      tag_(tag),
      timestamp_(timestamp),
      currentIndex_(currentIndex),
      lastIndex_(lastIndex),
      bundle_(bundle),
      trunkTransaction_(trunkTransaction),
      branchTransaction_(branchTransaction),
      nonce_(nonce) {
}

Transaction::Transaction(const std::string& address, int64_t value, const std::string& tag,
                         int64_t timestamp)
    : address_(address), value_(value), tag_(tag), timestamp_(timestamp) {
}

const std::string&
Transaction::getHash() const {
  return hash_;
}

void
Transaction::setHash(const std::string& hash) {
  hash_ = hash;
}

const std::string&
Transaction::getSignatureFragments() const {
  return signatureFragments_;
}

void
Transaction::setSignatureFragments(const std::string& signatureFragments) {
  signatureFragments_ = signatureFragments;
}

const std::string&
Transaction::getAddress() const {
  return address_;
}

void
Transaction::setAddress(const std::string& address) {
  address_ = address;
}

int64_t
Transaction::getValue() const {
  return value_;
}

void
Transaction::setValue(int64_t value) {
  value_ = value;
}

const std::string&
Transaction::getTag() const {
  return tag_;
}

void
Transaction::setTag(const std::string& tag) {
  tag_ = tag;
}

int64_t
Transaction::getTimestamp() const {
  return timestamp_;
}

void
Transaction::setTimestamp(int64_t timestamp) {
  timestamp_ = timestamp;
}

int64_t
Transaction::getCurrentIndex() const {
  return currentIndex_;
}

void
Transaction::setCurrentIndex(int64_t currentIndex) {
  currentIndex_ = currentIndex;
}

int64_t
Transaction::getLastIndex() const {
  return lastIndex_;
}

void
Transaction::setLastIndex(int64_t lastIndex) {
  lastIndex_ = lastIndex;
}

const std::string&
Transaction::getBundle() const {
  return bundle_;
}

void
Transaction::setBundle(const std::string& bundle) {
  bundle_ = bundle;
}

const std::string&
Transaction::getTrunkTransaction() const {
  return trunkTransaction_;
}

void
Transaction::setTrunkTransaction(const std::string& trunkTransaction) {
  trunkTransaction_ = trunkTransaction;
}

const std::string&
Transaction::getBranchTransaction() const {
  return branchTransaction_;
}

void
Transaction::setBranchTransaction(const std::string& branchTransaction) {
  branchTransaction_ = branchTransaction;
}

const std::string&
Transaction::getNonce() const {
  return nonce_;
}

void
Transaction::setNonce(const std::string& nonce) {
  nonce_ = nonce;
}

bool
Transaction::getPersistence() const {
  return persistence_;
}

void
Transaction::setPersistence(bool persistence) {
  persistence_ = persistence;
}

bool
Transaction::operator==(Transaction rhs) const {
  return hash_ == rhs.getHash();
}

bool
Transaction::operator!=(Transaction rhs) const {
  return !operator==(rhs);
}

std::string
Transaction::toTrytes() const {
  auto value = IOTA::Type::tritsToTrytes(IOTA::Type::intToTrits(getValue()), SeedLength);
  auto timestamp =
      IOTA::Type::tritsToTrytes(IOTA::Type::intToTrits(getTimestamp()), TryteAlphabetLength);
  auto currentIndex =
      IOTA::Type::tritsToTrytes(IOTA::Type::intToTrits(getCurrentIndex()), TryteAlphabetLength);
  auto lastIndex =
      IOTA::Type::tritsToTrytes(IOTA::Type::intToTrits(getLastIndex()), TryteAlphabetLength);

  return getSignatureFragments() + getAddress() + value + getTag() + timestamp + currentIndex +
         lastIndex + getBundle() + getTrunkTransaction() + getBranchTransaction() + getNonce();
}

void
Transaction::initFromTrytes(const std::string& trytes) {
  if (trytes.empty()) {
    return;
  }

  //! TODO: length check
  //! what length are we supposed to receive?

  // validity check
  for (int i = 2279; i < 2295; i++) {
    if (trytes[i] != '9') {
      return;
    }
  }

  auto transactionTrits = IOTA::Type::trytesToTrits(trytes);
  auto hash             = IOTA::Type::Trits(TritHashLength);

  // generate the correct transaction hash
  auto curl = IOTA::Crypto::create(IOTA::Crypto::Type::CURL);
  curl->absorb(transactionTrits);
  curl->squeeze(hash);

  //! Hash
  setHash(IOTA::Type::tritsToTrytes(hash));
  //! Signature
  setSignatureFragments(
      trytes.substr(SignatureFragmentsOffset.first, SignatureFragmentsOffset.second));
  //! Address
  setAddress(trytes.substr(AddressOffset.first, AddressOffset.second));
  //! Value
  setValue(IOTA::Type::tritsToInt<int64_t>(
      IOTA::Type::Trits(std::vector<int8_t>{ std::begin(transactionTrits) + ValueOffset.first,
                                             std::begin(transactionTrits) + ValueOffset.second })));
  //! Tag
  setTag(trytes.substr(TagOffset.first, TagOffset.second));
  //! Timestamp
  setTimestamp(IOTA::Type::tritsToInt<int64_t>(IOTA::Type::Trits(
      std::vector<int8_t>{ std::begin(transactionTrits) + TimestampOffset.first,
                           std::begin(transactionTrits) + TimestampOffset.second })));
  //! Current Index
  setCurrentIndex(IOTA::Type::tritsToInt<int64_t>(IOTA::Type::Trits(
      std::vector<int8_t>{ std::begin(transactionTrits) + CurrentIndexOffset.first,
                           std::begin(transactionTrits) + CurrentIndexOffset.second })));
  //! Last Index
  setLastIndex(IOTA::Type::tritsToInt<int64_t>(IOTA::Type::Trits(
      std::vector<int8_t>{ std::begin(transactionTrits) + LastIndexOffset.first,
                           std::begin(transactionTrits) + LastIndexOffset.second })));
  //! Bundle
  setBundle(trytes.substr(BundleOffset.first, BundleOffset.second));
  //! Trunk Transaction
  setTrunkTransaction(trytes.substr(TrunkOffset.first, TrunkOffset.second));
  //! Branch Transaction
  setBranchTransaction(trytes.substr(BranchOffset.first, BranchOffset.second));
  //! Nonce
  setNonce(trytes.substr(NonceOffset.first, NonceOffset.second));
}
