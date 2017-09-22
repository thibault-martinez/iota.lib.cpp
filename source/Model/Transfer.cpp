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

#include <Model/Transfer.hpp>

Transfer::Transfer(const std::string& timestamp, const IOTA::Type::Trytes& address,
                   const IOTA::Type::Trytes& hash, bool persistence, int64_t value,
                   const std::string& message, const std::string& tag)
    : timestamp_(timestamp),
      address_(address),
      hash_(hash),
      persistence_(persistence),
      value_(value),
      message_(message),
      tag_(tag) {
}

Transfer::Transfer(const IOTA::Type::Trytes& address, int64_t value, const std::string& message,
                   const std::string& tag)
    : address_(address), value_(value), message_(message), tag_(tag) {
}

const IOTA::Type::Trytes&
Transfer::getAddress() {
  return address_;
}

void
Transfer::setAddress(const IOTA::Type::Trytes& address) {
  address_ = address;
}

const IOTA::Type::Trytes&
Transfer::getHash() {
  return hash_;
}

void
Transfer::setHash(const IOTA::Type::Trytes& hash) {
  hash_ = hash;
}

bool
Transfer::getPersistence() {
  return persistence_;
}

void
Transfer::setPersistence(bool persistence) {
  persistence_ = persistence;
}

const std::string&
Transfer::getTimestamp() {
  return timestamp_;
}

void
Transfer::setTimestamp(const std::string& timestamp) {
  timestamp_ = timestamp;
}

int64_t
Transfer::getValue() {
  return value_;
}

void
Transfer::setValue(int64_t value) {
  value_ = value;
}

const std::string&
Transfer::getMessage() {
  return message_;
}

void
Transfer::setMessage(const std::string& message) {
  message_ = message;
}

const std::string&
Transfer::getTag() {
  return tag_;
}

void
Transfer::setTag(const std::string& tag) {
  tag_ = tag;
}
