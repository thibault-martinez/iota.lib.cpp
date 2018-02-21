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

#include <iota/constants.hpp>
#include <iota/models/transfer.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

Transfer::Transfer(const Models::Address& address, int64_t value, const Types::Trytes& message,
                   const Models::Tag& tag)
    : address_(address), value_(value), message_(message), tag_(tag) {
}

const Models::Address&
Transfer::getAddress() const {
  return address_;
}

void
Transfer::setAddress(const Models::Address& address) {
  address_ = address;
}

int64_t
Transfer::getValue() const {
  return value_;
}

void
Transfer::setValue(int64_t value) {
  value_ = value;
}

const Types::Trytes&
Transfer::getMessage() const {
  return message_;
}

void
Transfer::setMessage(const Types::Trytes& message) {
  message_ = message;
}

const Models::Tag&
Transfer::getTag() const {
  return tag_;
}

void
Transfer::setTag(const Models::Tag& tag) {
  tag_ = tag;
}

bool
Transfer::isValid() const {
  // Check if message is correct trytes of any length
  if (!Types::isValidTrytes(getMessage())) {
    return false;
  }

  if (getAddress().empty()) {
    return false;
  }

  return true;
}

bool
Transfer::operator==(const Transfer& rhs) const {
  return address_ == rhs.address_ && value_ == rhs.value_ && tag_ == rhs.tag_ &&
         message_ == rhs.message_;
}

bool
Transfer::operator!=(const Transfer& rhs) const {
  return !operator==(rhs);
}

}  // namespace Models

}  // namespace IOTA
