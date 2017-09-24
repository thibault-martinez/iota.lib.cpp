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

#include <Model/input.hpp>

input::input(const std::string& address, const int64_t& balance, const int32_t& keyIndex,
             const int32_t& security)
    : address_(address), balance_(balance), keyIndex_(keyIndex), security_(security) {
}

input::~input() {
}

const std::string&
input::getAddress() const {
  return this->address_;
}

const int64_t&
input::getBalance() const {
  return this->balance_;
}

void
input::setBalance(const int64_t& balance) {
  this->balance_ = balance;
}

const int32_t&
input::getKeyIndex() const {
  return this->keyIndex_;
}

const int32_t&
input::getSecurity() const {
  return this->security_;
}
