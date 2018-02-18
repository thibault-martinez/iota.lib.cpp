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

#include <string>

#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/tag.hpp>
#include <iota/types/utils.hpp>

namespace IOTA {

namespace Models {

Tag::Tag(const Types::Trytes& tag) {
  setTag(tag);
}

const Types::Trytes&
Tag::toTrytes() const {
  return tag_;
}

const Types::Trytes&
Tag::toTrytesWithPadding() const {
  return paddedTag_;
}

void
Tag::setTag(const Types::Trytes& tag) {
  if (tag.length() > TagLength) {
    throw Errors::IllegalState("tag is too long");
  }

  if (!Types::isValidTrytes(tag)) {
    throw Errors::IllegalState("tag is not a valid trytes string");
  }

  tag_       = tag.substr(0, tag.rfind('9'));
  paddedTag_ = Types::Utils::rightPad(tag_, TagLength, '9');
}

bool
Tag::empty() const {
  return tag_.empty();
}

bool
Tag::operator==(const Tag& rhs) const {
  return tag_ == rhs.tag_;
}

bool
Tag::operator!=(const Tag& rhs) const {
  return !operator==(rhs);
}

bool
Tag::operator==(const Types::Trytes& rhs) const {
  return operator==(Tag{ rhs });
}

bool
Tag::operator!=(const Types::Trytes& rhs) const {
  return operator!=(Tag{ rhs });
}

}  // namespace Models

}  // namespace IOTA
