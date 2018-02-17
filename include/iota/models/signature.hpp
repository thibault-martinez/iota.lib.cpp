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

#include <string>
#include <vector>

#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Models {

/**
 * Signature model.
 */
class Signature {
public:
  /**
   * Default ctor.
   */
  Signature() = default;

  /**
   * Full init ctor.
   *
   * @param addr The address.
   * @param signatureFragments The signature fragments.
   */
  Signature(const Types::Trytes& addr, const std::vector<Types::Trytes>& signatureFragments);

  /**
   * Default dtor.
   */
  ~Signature() = default;

public:
  /**
   * @return The address.
   */
  const Types::Trytes& getAddress() const;

  /**
   * @param address The address.
   */
  void setAddress(const Types::Trytes& address);

public:
  /**
   * @return The signature fragments.
   */
  const std::vector<Types::Trytes>& getSignatureFragments() const;

  /**
   * @return The signature fragments.
   */
  std::vector<Types::Trytes>& getSignatureFragments();

  /**
   * @param signatureFragments The signature fragments.
   */
  void setSignatureFragments(const std::vector<Types::Trytes>& signatureFragments);

public:
  /**
   * @param rhs An object to compare with this object.
   *
   * @return whether the current signature is the same as the given one.
   */
  bool operator==(const Signature& rhs) const;

  /**
   * @param rhs An object to compare with this object.
   *
   * @return whether the current signature is different from the given one.
   */
  bool operator!=(const Signature& rhs) const;

private:
  /**
   * The adress.
   */
  Types::Trytes address_;
  /**
   * The signature fragments.
   */
  std::vector<Types::Trytes> signatureFragments_;
};

}  // namespace Models

}  // namespace IOTA
