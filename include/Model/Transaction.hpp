
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

#pragma once

#include <string>
#include <utility>

class Transaction {
public:
  Transaction()  = default;
  ~Transaction() = default;

  /**
   * Initializes a new instance of the Transaction class.
   */
  explicit Transaction(const std::string& trytes);

  /**
   * Initializes a new instance of the Transaction class.
   */
  Transaction(const std::string& signatureFragments, int64_t currentIndex, int64_t lastIndex,
              const std::string& nonce, const std::string& hash, const std::string& tag,
              int64_t timestamp, const std::string& trunkTransaction,
              const std::string& branchTransaction, const std::string& address, int64_t value,
              const std::string& bundle);

  /**
   * Initializes a new instance of the Transaction class.
   */
  Transaction(const std::string& address, int64_t value, const std::string& tag, int64_t timestamp);

public:
  /**
   * @return whether the transaction is a tail transaction or not (getIndex == 0)
   */
  bool isTailTransaction() const;

  /**
   * Get the hash.
   *
   * @return The hash.
   */
  const std::string& getHash() const;

  /**
   * Set the hash.
   *
   * @param hash The hash.
   */
  void setHash(const std::string& hash);

  /**
   * Get the signature fragments.
   *
   * @return The signature fragments.
   */
  const std::string& getSignatureFragments() const;

  /**
   * Set the signature fragments.
   *
   * @param signatureFragments The signature fragments.
   */
  void setSignatureFragments(const std::string& signatureFragments);

  /**
   * Get the address.
   *
   * @return The address.
   */
  const std::string& getAddress() const;

  /**
   * Set the address.
   *
   * @param address The address.
   */
  void setAddress(const std::string& address);

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
  const std::string& getTag() const;

  /**
   * Set the tag.
   *
   * @param tag The tag.
   */
  void setTag(const std::string& tag);

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
  const std::string& getBundle() const;

  /**
   * Set the bundle.
   *
   * @param bundle The bundle.
   */
  void setBundle(const std::string& bundle);

  /**
   * Get the trunk transaction.
   *
   * @return The trunk transaction.
   */
  const std::string& getTrunkTransaction() const;

  /**
   * Set the trunk transaction.
   *
   * @param trunkTransaction The trunk transaction.
   */
  void setTrunkTransaction(const std::string& trunkTransaction);

  /**
   * Get the branch transaction.
   *
   * @return The branch transaction.
   */
  const std::string& getBranchTransaction() const;

  /**
   * Set the branch transaction.
   *
   * @param branchTransaction The branch transaction.
   */
  void setBranchTransaction(const std::string& branchTransaction);

  /**
   * Get the nonce.
   *
   * @return The nonce.
   */
  const std::string& getNonce() const;

  /**
   * Set the nonce.
   *
   * @param nonce The trunk nonce.
   */
  void setNonce(const std::string& nonce);

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
   * comparison operator
   *
   * @param rhs other object to compare with
   */
  bool operator==(Transaction rhs) const;

  /**
   * comparison operator
   *
   * @param rhs other object to compare with
   */
  bool operator!=(Transaction rhs) const;

  /**
   * Converts the transaction to the corresponding trytes representation
   */
  std::string toTrytes() const;

  /**
   * Initializes a new instance of the Transaction class based on tryte string.
   */
  void initFromTrytes(const std::string& trytes);

private:
  static const std::pair<int, int> SignatureFragmentsOffset;
  static const std::pair<int, int> AddressOffset;
  static const std::pair<int, int> ValueOffset;
  static const std::pair<int, int> TagOffset;
  static const std::pair<int, int> TimestampOffset;
  static const std::pair<int, int> CurrentIndexOffset;
  static const std::pair<int, int> LastIndexOffset;
  static const std::pair<int, int> BundleOffset;
  static const std::pair<int, int> TrunkOffset;
  static const std::pair<int, int> BranchOffset;
  static const std::pair<int, int> NonceOffset;

private:
  /**
   * hash of the transaction
   */
  std::string hash_;

  /**
   * signature of the transaction
   */
  std::string signatureFragments_;

  /**
   * address of the transaction
   */
  std::string address_;

  /**
   * value sent
   */
  int64_t value_;

  /**
   * tag of the transaction
   */
  std::string tag_;

  /**
   * ts at which transaction was issued
   */
  int64_t timestamp_;

  /**
   * index of the transaction in the bundle
   */
  int64_t currentIndex_;

  /**
   * last transaction index of the bundle
   */
  int64_t lastIndex_;

  /**
   * bundle hash
   */
  std::string bundle_;

  /**
   * trunk transaction hash
   */
  std::string trunkTransaction_;

  /**
   * branch transaction hash
   */
  std::string branchTransaction_;

  /**
   * nounce
   */
  std::string nonce_;

  /**
   * whether transaction is persisted or not
   */
  bool persistence_;
};
