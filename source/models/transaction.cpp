
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
#include <iota/crypto/curl.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/transaction.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

const std::pair<int, int> Transaction::SignatureFragmentsOffset            = { 0, 2187 };
const std::pair<int, int> Transaction::AddressOffset                       = { 2187, 2268 };
const std::pair<int, int> Transaction::ValueOffset                         = { 6804, 6837 };
const std::pair<int, int> Transaction::TagOffset                           = { 2592, 2619 };
const std::pair<int, int> Transaction::TimestampOffset                     = { 6966, 6993 };
const std::pair<int, int> Transaction::CurrentIndexOffset                  = { 6993, 7020 };
const std::pair<int, int> Transaction::LastIndexOffset                     = { 7020, 7047 };
const std::pair<int, int> Transaction::BundleOffset                        = { 2349, 2430 };
const std::pair<int, int> Transaction::TrunkOffset                         = { 2430, 2511 };
const std::pair<int, int> Transaction::BranchOffset                        = { 2511, 2592 };
const std::pair<int, int> Transaction::NonceOffset                         = { 2646, 2673 };
const std::pair<int, int> Transaction::ObsoleteTagOffset                   = { 2295, 2322 };
const std::pair<int, int> Transaction::AttachmentTimestampOffset           = { 7857, 7884 };
const std::pair<int, int> Transaction::AttachmentTimestampLowerBoundOffset = { 7884, 7911 };
const std::pair<int, int> Transaction::AttachmentTimestampUpperBoundOffset = { 7911, 7938 };
const std::pair<int, int> Transaction::ValidityChunkOffset                 = { 2279, 2295 };

Transaction::Transaction(const Types::Trytes& trytes) {
  initFromTrytes(trytes);
}

Transaction::Transaction(const Types::Trytes& signatureFragments, int64_t currentIndex,
                         int64_t lastIndex, const Types::Trytes& nonce, const Types::Trytes& hash,
                         int64_t timestamp, const Types::Trytes& trunkTransaction,
                         const Types::Trytes& branchTransaction, const Models::Address& address,
                         int64_t value, const Types::Trytes& bundle, const Models::Tag& tag,
                         int64_t attachmentTimestamp, int64_t attachmentTimestampLowerBound,
                         int64_t attachmentTimestampUpperBound)
    : hash_(hash),
      signatureFragments_(signatureFragments),
      address_(address),
      value_(value),
      tag_(tag),
      obsoleteTag_(tag),
      timestamp_(timestamp),
      attachmentTimestamp_(attachmentTimestamp),
      attachmentTimestampLowerBound_(attachmentTimestampLowerBound),
      attachmentTimestampUpperBound_(attachmentTimestampUpperBound),
      currentIndex_(currentIndex),
      lastIndex_(lastIndex),
      bundle_(bundle),
      trunkTransaction_(trunkTransaction),
      branchTransaction_(branchTransaction),
      nonce_(nonce),
      persistence_(false) {
}

Transaction::Transaction(const Models::Address& address, int64_t value, const Models::Tag& tag,
                         int64_t timestamp, int64_t attachmentTimestamp,
                         int64_t attachmentTimestampLowerBound,
                         int64_t attachmentTimestampUpperBound)
    : address_(address),
      value_(value),
      tag_(tag),
      obsoleteTag_(tag),
      timestamp_(timestamp),
      attachmentTimestamp_(attachmentTimestamp),
      attachmentTimestampLowerBound_(attachmentTimestampLowerBound),
      attachmentTimestampUpperBound_(attachmentTimestampUpperBound),
      currentIndex_(0),
      lastIndex_(0),
      persistence_(false) {
}

bool
Transaction::isTailTransaction() const {
  return getCurrentIndex() == 0;
}

const Types::Trytes&
Transaction::getHash() const {
  return hash_;
}

void
Transaction::setHash(const Types::Trytes& hash) {
  hash_ = hash;
}

const Types::Trytes&
Transaction::getSignatureFragments() const {
  return signatureFragments_;
}

void
Transaction::setSignatureFragments(const Types::Trytes& signatureFragments) {
  signatureFragments_ = signatureFragments;
}

const Models::Address&
Transaction::getAddress() const {
  return address_;
}

void
Transaction::setAddress(const Models::Address& address) {
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

const Models::Tag&
Transaction::getTag() const {
  return tag_;
}

void
Transaction::setTag(const Models::Tag& tag) {
  tag_ = tag;
}

const Models::Tag&
Transaction::getObsoleteTag() const {
  return obsoleteTag_;
}

void
Transaction::setObsoleteTag(const Models::Tag& tag) {
  obsoleteTag_ = tag;
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
Transaction::getAttachmentTimestamp() const {
  return attachmentTimestamp_;
}

void
Transaction::setAttachmentTimestamp(int64_t timestamp) {
  attachmentTimestamp_ = timestamp;
}

int64_t
Transaction::getAttachmentTimestampLowerBound() const {
  return attachmentTimestampLowerBound_;
}

void
Transaction::setAttachmentTimestampLowerBound(int64_t timestamp) {
  attachmentTimestampLowerBound_ = timestamp;
}

int64_t
Transaction::getAttachmentTimestampUpperBound() const {
  return attachmentTimestampUpperBound_;
}

void
Transaction::setAttachmentTimestampUpperBound(int64_t timestamp) {
  attachmentTimestampUpperBound_ = timestamp;
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

const Types::Trytes&
Transaction::getBundle() const {
  return bundle_;
}

void
Transaction::setBundle(const Types::Trytes& bundle) {
  bundle_ = bundle;
}

const Types::Trytes&
Transaction::getTrunkTransaction() const {
  return trunkTransaction_;
}

void
Transaction::setTrunkTransaction(const Types::Trytes& trunkTransaction) {
  trunkTransaction_ = trunkTransaction;
}

const Types::Trytes&
Transaction::getBranchTransaction() const {
  return branchTransaction_;
}

void
Transaction::setBranchTransaction(const Types::Trytes& branchTransaction) {
  branchTransaction_ = branchTransaction;
}

const Types::Trytes&
Transaction::getNonce() const {
  return nonce_;
}

void
Transaction::setNonce(const Types::Trytes& nonce) {
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
Transaction::operator==(const Transaction& rhs) const {
  return hash_ == rhs.getHash();
}

bool
Transaction::operator!=(const Transaction& rhs) const {
  return !operator==(rhs);
}

Types::Trytes
Transaction::toTrytes() const {
  auto value     = Types::tritsToTrytes(Types::intToTrits(getValue(), SeedLength));
  auto timestamp = Types::tritsToTrytes(Types::intToTrits(getTimestamp(), TryteAlphabetLength));
  auto currentIndex =
      Types::tritsToTrytes(Types::intToTrits(getCurrentIndex(), TryteAlphabetLength));
  auto lastIndex = Types::tritsToTrytes(Types::intToTrits(getLastIndex(), TryteAlphabetLength));
  auto attachmentTimestamp =
      Types::tritsToTrytes(Types::intToTrits(getAttachmentTimestamp(), TryteAlphabetLength));
  auto attachmentTimestampLowerBound = Types::tritsToTrytes(
      Types::intToTrits(getAttachmentTimestampLowerBound(), TryteAlphabetLength));
  auto attachmentTimestampUpperBound = Types::tritsToTrytes(
      Types::intToTrits(getAttachmentTimestampUpperBound(), TryteAlphabetLength));
  auto tag = getTag().empty() ? getObsoleteTag() : getTag();

  return getSignatureFragments() + getAddress().toTrytes() + value +
         getObsoleteTag().toTrytesWithPadding() + timestamp + currentIndex + lastIndex +
         getBundle() + getTrunkTransaction() + getBranchTransaction() + tag.toTrytesWithPadding() +
         attachmentTimestamp + attachmentTimestampLowerBound + attachmentTimestampUpperBound +
         getNonce();
}

void
Transaction::initFromTrytes(const Types::Trytes& trytes) {
  if (trytes.size() != TrxTrytesLength) {
    throw Errors::IllegalState("Invalid transaction trytes");
  }

  // validity check
  for (int i = ValidityChunkOffset.first; i < ValidityChunkOffset.second; i++) {
    if (trytes[i] != '9') {
      return;
    }
  }

  auto transactionTrits = Types::trytesToTrits(trytes);
  auto hash             = Types::Trits(TritHashLength);

  // generate the correct transaction hash
  Crypto::Curl curl;
  curl.absorb(transactionTrits);
  curl.squeeze(hash);

  //! Hash
  setHash(Types::tritsToTrytes(hash));
  //! Signature
  setSignatureFragments(
      trytes.substr(SignatureFragmentsOffset.first,
                    SignatureFragmentsOffset.second - SignatureFragmentsOffset.first));
  //! Address
  setAddress(trytes.substr(AddressOffset.first, AddressOffset.second - AddressOffset.first));
  //! Value
  setValue(IOTA::Types::tritsToInt<int64_t>(
      Types::Trits(std::vector<int8_t>{ std::begin(transactionTrits) + ValueOffset.first,
                                        std::begin(transactionTrits) + ValueOffset.second })));
  //! Obsolete Tag
  setObsoleteTag(
      trytes.substr(ObsoleteTagOffset.first, ObsoleteTagOffset.second - ObsoleteTagOffset.first));
  //! Tag
  setTag(trytes.substr(TagOffset.first, TagOffset.second - TagOffset.first));
  //! Timestamp
  setTimestamp(Types::tritsToInt<int64_t>(
      Types::Trits(std::vector<int8_t>{ std::begin(transactionTrits) + TimestampOffset.first,
                                        std::begin(transactionTrits) + TimestampOffset.second })));
  //! Attachment Timestamp
  setAttachmentTimestamp(Types::tritsToInt<int64_t>(Types::Trits(
      std::vector<int8_t>{ std::begin(transactionTrits) + AttachmentTimestampOffset.first,
                           std::begin(transactionTrits) + AttachmentTimestampOffset.second })));
  //! Attachment Timestamp Lower Bound
  setAttachmentTimestampLowerBound(Types::tritsToInt<int64_t>(Types::Trits(std::vector<int8_t>{
      std::begin(transactionTrits) + AttachmentTimestampLowerBoundOffset.first,
      std::begin(transactionTrits) + AttachmentTimestampLowerBoundOffset.second })));
  //! Attachment Timestamp Upper Bound
  setAttachmentTimestampUpperBound(Types::tritsToInt<int64_t>(Types::Trits(std::vector<int8_t>{
      std::begin(transactionTrits) + AttachmentTimestampUpperBoundOffset.first,
      std::begin(transactionTrits) + AttachmentTimestampUpperBoundOffset.second })));
  //! Current Index
  setCurrentIndex(Types::tritsToInt<int64_t>(Types::Trits(
      std::vector<int8_t>{ std::begin(transactionTrits) + CurrentIndexOffset.first,
                           std::begin(transactionTrits) + CurrentIndexOffset.second })));
  //! Last Index
  setLastIndex(Types::tritsToInt<int64_t>(
      Types::Trits(std::vector<int8_t>{ std::begin(transactionTrits) + LastIndexOffset.first,
                                        std::begin(transactionTrits) + LastIndexOffset.second })));
  //! Bundle
  setBundle(trytes.substr(BundleOffset.first, BundleOffset.second - BundleOffset.first));
  //! Trunk Transaction
  setTrunkTransaction(trytes.substr(TrunkOffset.first, TrunkOffset.second - TrunkOffset.first));
  //! Branch Transaction
  setBranchTransaction(trytes.substr(BranchOffset.first, BranchOffset.second - BranchOffset.first));
  //! Nonce
  setNonce(trytes.substr(NonceOffset.first, NonceOffset.second - NonceOffset.first));
}

std::ostream&
operator<<(std::ostream& os, const Transaction& transaction) {
  return os << transaction.toTrytes();
}

}  // namespace Models

}  // namespace IOTA
