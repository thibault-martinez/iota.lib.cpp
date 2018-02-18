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

#pragma once

#include <utility>

#include <iota/types/trytes.hpp>

namespace IOTA {

namespace Models {

/**
 * Transaction model.
 */
class Transaction {
public:
  /**
   * Default ctor.
   */
  Transaction() = default;

  /**
   * Default dtor.
   */
  ~Transaction() = default;

  /**
   * Initializes a new instance of the Transaction class from trytes.
   *
   * @param trytes The trytes.
   */
  explicit Transaction(const Types::Trytes& trytes);

  /**
   * Initializes a new instance of the Transaction class.
   *
   * @param signatureFragments Signature fragments of the transaction.
   * @param currentIndex Index of the transaction in the bundle.
   * @param lastIndex Last transaction index of the bundle.
   * @param nonce Nonce.
   * @param hash Hash of the transaction.
   * @param timestamp Timestamp at which transaction was issued.
   * @param trunkTransaction Trunk transaction hash.
   * @param branchTransaction Branch transaction hash.
   * @param address Address of the transaction.
   * @param value Value sent.
   * @param bundle Bundle hash.
   * @param tag Tag of the transaction.
   * @param attachmentTimestamp Attachment timestamp.
   * @param attachmentTimestampLowerBound Lower bound of the attachment timestamp.
   * @param attachmentTimestampUpperBound Index of the transaction in the bundle.
   */
  Transaction(const Types::Trytes& signatureFragments, int64_t currentIndex, int64_t lastIndex,
              const Types::Trytes& nonce, const Types::Trytes& hash, int64_t timestamp,
              const Types::Trytes& trunkTransaction, const Types::Trytes& branchTransaction,
              const Types::Trytes& address, int64_t value, const Types::Trytes& bundle,
              const Types::Trytes& tag, int64_t attachmentTimestamp,
              int64_t attachmentTimestampLowerBound, int64_t attachmentTimestampUpperBound);

  /**
   * Initializes a new instance of the Transaction class.
   *
   * @param address Address of the transaction.
   * @param value Value sent.
   * @param tag Tag of the transaction.
   * @param timestamp Timestamp at which transaction was issued.
   * @param attachmentTimestamp Attachment timestamp.
   * @param attachmentTimestampLowerBound Lower bound of the attachment timestamp.
   * @param attachmentTimestampUpperBound Index of the transaction in the bundle.
   */
  Transaction(const Types::Trytes& address, int64_t value, const Types::Trytes& tag,
              int64_t timestamp, int64_t attachmentTimestamp = 0,
              int64_t attachmentTimestampLowerBound = 0, int64_t attachmentTimestampUpperBound = 0);

public:
  /**
   * @return Whether the transaction is a tail transaction or not (getIndex == 0).
   */
  bool isTailTransaction() const;

  /**
   * Get the hash.
   *
   * @return The hash.
   */
  const Types::Trytes& getHash() const;

  /**
   * Set the hash.
   *
   * @param hash The hash.
   */
  void setHash(const Types::Trytes& hash);

  /**
   * Get the signature fragments.
   *
   * @return The signature fragments.
   */
  const Types::Trytes& getSignatureFragments() const;

  /**
   * Set the signature fragments.
   *
   * @param signatureFragments The signature fragments.
   */
  void setSignatureFragments(const Types::Trytes& signatureFragments);

  /**
   * Get the address.
   *
   * @return The address.
   */
  const Types::Trytes& getAddress() const;

  /**
   * Set the address.
   *
   * @param address The address.
   */
  void setAddress(const Types::Trytes& address);

  /**
   * Get the value.
   *
   * @return The value.
   */
  int64_t getValue() const;
  /**
   * Set the value.
   *
   * @param value The value.
   */
  void setValue(int64_t value);

  /**
   * Get the tag.
   *
   * @return The tag.
   */
  const Types::Trytes& getTag() const;

  /**
   * Set the tag.
   *
   * @param tag The tag.
   */
  void setTag(const Types::Trytes& tag);

  /**
   * Get the obsolete tag.
   *
   * @return The obsolete tag.
   */
  const Types::Trytes& getObsoleteTag() const;

  /**
   * Set the obsolete tag.
   *
   * @param tag The obsolete tag.
   */
  void setObsoleteTag(const Types::Trytes& tag);

  /**
   * Get the timestamp.
   *
   * @return The timestamp.
   */
  int64_t getTimestamp() const;

  /**
   * Set the timestamp.
   *
   * @param timestamp The timestamp.
   */
  void setTimestamp(int64_t timestamp);

  /**
   * Get the attachment timestamp.
   *
   * @return The attachment timestamp.
   */
  int64_t getAttachmentTimestamp() const;

  /**
   * Set the attachment timestamp.
   *
   * @param timestamp The attachment timestamp.
   */
  void setAttachmentTimestamp(int64_t timestamp);

  /**
   * Get the attachment timestamp lower bound.
   *
   * @return The attachment timestamp lower bound.
   */
  int64_t getAttachmentTimestampLowerBound() const;

  /**
   * Set the attachment timestamp lower bound.
   *
   * @param timestamp The attachment timestamp lower bound.
   */
  void setAttachmentTimestampLowerBound(int64_t timestamp);

  /**
   * Get the attachment timestamp upper bound.
   *
   * @return The attachment timestamp upper bound.
   */
  int64_t getAttachmentTimestampUpperBound() const;

  /**
   * Set the attachment timestamp upper bound.
   *
   * @param timestamp The attachment timestamp upper bound.
   */
  void setAttachmentTimestampUpperBound(int64_t timestamp);

  /**
   * Get the current index.
   *
   * @return The current index.
   */
  int64_t getCurrentIndex() const;

  /**
   * Set the current index.
   *
   * @param currentIndex The current index.
   */
  void setCurrentIndex(int64_t currentIndex);

  /**
   * Get the last index.
   *
   * @return The last index.
   */
  int64_t getLastIndex() const;

  /**
   * Set the last index.
   *
   * @param lastIndex The last index.
   */
  void setLastIndex(int64_t lastIndex);

  /**
   * Get the bundle.
   *
   * @return The bundle.
   */
  const Types::Trytes& getBundle() const;

  /**
   * Set the bundle.
   *
   * @param bundle The bundle.
   */
  void setBundle(const Types::Trytes& bundle);

  /**
   * Get the trunk transaction.
   *
   * @return The trunk transaction.
   */
  const Types::Trytes& getTrunkTransaction() const;

  /**
   * Set the trunk transaction.
   *
   * @param trunkTransaction The trunk transaction.
   */
  void setTrunkTransaction(const Types::Trytes& trunkTransaction);

  /**
   * Get the branch transaction.
   *
   * @return The branch transaction.
   */
  const Types::Trytes& getBranchTransaction() const;

  /**
   * Set the branch transaction.
   *
   * @param branchTransaction The branch transaction.
   */
  void setBranchTransaction(const Types::Trytes& branchTransaction);

  /**
   * Get the nonce.
   *
   * @return The nonce.
   */
  const Types::Trytes& getNonce() const;

  /**
   * Set the nonce.
   *
   * @param nonce The trunk nonce.
   */
  void setNonce(const Types::Trytes& nonce);

  /**
   * Get the persistence.
   *
   * @return The persistence.
   */
  bool getPersistence() const;

  /**
   * Set the persistence.
   *
   * @param persistence The persistence.
   */
  void setPersistence(bool persistence);

  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator==(const Transaction& rhs) const;

  /**
   * Comparison operator.
   *
   * @param rhs other object to compare with.
   *
   * @return Whether the two transactions are equal or not.
   */
  bool operator!=(const Transaction& rhs) const;

  /**
   * Converts the transaction to the corresponding trytes representation.
   *
   * @return The trytes.
   */
  Types::Trytes toTrytes() const;

  /**
   * Initializes a new instance of the Transaction class based on tryte string.
   *
   * @param trytes The trytes from which to initialize the transaction.
   */
  void initFromTrytes(const Types::Trytes& trytes);

private:
  /**
   * Offset of signature fragments in the transaction trytes.
   */
  static const std::pair<int, int> SignatureFragmentsOffset;
  /**
   * Offset of address in the transaction trytes.
   */
  static const std::pair<int, int> AddressOffset;
  /**
   * Offset of value in the transaction trytes.
   */
  static const std::pair<int, int> ValueOffset;
  /**
   * Offset of tag in the transaction trytes.
   */
  static const std::pair<int, int> TagOffset;
  /**
   * Offset of timestamp in the transaction trytes.
   */
  static const std::pair<int, int> TimestampOffset;
  /**
   * Offset of current index in the transaction trytes.
   */
  static const std::pair<int, int> CurrentIndexOffset;
  /**
   * Offset of last index in the transaction trytes.
   */
  static const std::pair<int, int> LastIndexOffset;
  /**
   * Offset of bundle in the transaction trytes.
   */
  static const std::pair<int, int> BundleOffset;
  /**
   * Offset of trunk in the transaction trytes.
   */
  static const std::pair<int, int> TrunkOffset;
  /**
   * Offset of branch in the transaction trytes.
   */
  static const std::pair<int, int> BranchOffset;
  /**
   * Offset of nonce in the transaction trytes.
   */
  static const std::pair<int, int> NonceOffset;
  /**
   * Offset of obsolete tag in the transaction trytes.
   */
  static const std::pair<int, int> ObsoleteTagOffset;
  /**
   * Offset of attachment timestamp in the transaction trytes.
   */
  static const std::pair<int, int> AttachmentTimestampOffset;
  /**
   * Offset of attachment timestamp lower bound in the transaction trytes.
   */
  static const std::pair<int, int> AttachmentTimestampLowerBoundOffset;
  /**
   * Offset of attachment timestamp upper bound in the transaction trytes.
   */
  static const std::pair<int, int> AttachmentTimestampUpperBoundOffset;
  /**
   * Offset of validity chunk in the transaction trytes.
   */
  static const std::pair<int, int> ValidityChunkOffset;

private:
  /**
   * Hash of the transaction.
   */
  Types::Trytes hash_;
  /**
   * Signature of the transaction.
   */
  Types::Trytes signatureFragments_;
  /**
   * Address of the transaction.
   */
  Types::Trytes address_;
  /**
   * Value sent.
   */
  int64_t value_ = 0;
  /**
   * Tag of the transaction.
   */
  Types::Trytes tag_;
  /**
   * Obsolete tag of the transaction.
   */
  Types::Trytes obsoleteTag_;
  /**
   * Timestamp at which transaction was issued.
   */
  int64_t timestamp_ = 0;
  /**
   * Attachment timestamp.
   */
  int64_t attachmentTimestamp_ = 0;
  /**
   * Lower bound of the attachment timestamp.
   */
  int64_t attachmentTimestampLowerBound_ = 0;
  /**
   * Upper bound of the attachment timestamp.
   */
  int64_t attachmentTimestampUpperBound_ = 0;
  /**
   * Index of the transaction in the bundle.
   */
  int64_t currentIndex_ = 0;
  /**
   * Last transaction index of the bundle.
   */
  int64_t lastIndex_ = 0;
  /**
   * Bundle hash.
   */
  Types::Trytes bundle_;
  /**
   * Trunk transaction hash.
   */
  Types::Trytes trunkTransaction_;
  /**
   * Branch transaction hash.
   */
  Types::Trytes branchTransaction_;
  /**
   * Nonce.
   */
  Types::Trytes nonce_;
  /**
   * Whether transaction is persisted or not.
   */
  bool persistence_ = false;
};

}  // namespace Models

}  // namespace IOTA
