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

#pragma once

#include <string>
#include <vector>

#include <Type/Trinary.hpp>

class Signature {
public:
  Signature()  = default;
  ~Signature() = default;

public:
  /**
   * Get the address.
   *
   * @return The address.
   */
  const IOTA::Type::Trytes& getAddress() const;

  /**
   * Set the address.
   *
   * @param address The address.
   */
  void setAddress(const IOTA::Type::Trytes& address);

  /**
   * Get the signatureFragments.
   *
   * @return The signatureFragments.
   */
  const std::vector<std::string>& getSignatureFragments() const;

  /**
   * Get the signatureFragments. (non-const version)
   *
   * @return The signatureFragments.
   */
  std::vector<std::string>& getSignatureFragments();

  /**
   * Set the signatureFragments.
   *
   * @param signatureFragments The signatureFragments.
   */
  void setSignatureFragments(const std::vector<std::string>& signatureFragments);

private:
  IOTA::Type::Trytes       address_;
  std::vector<std::string> signatureFragments_;
};
