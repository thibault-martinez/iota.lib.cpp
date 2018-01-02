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

class Signature {
public:
  /**
   * default ctor
   */
  Signature() = default;

  /**
   * full init ctor
   */
  Signature(const IOTA::Types::Trytes&              addr,
            const std::vector<IOTA::Types::Trytes>& signatureFragments);

  /**
   * default dtor
   */
  ~Signature() = default;

public:
  /**
   * @return The address.
   */
  const IOTA::Types::Trytes& getAddress() const;

  /**
   * @param address The address.
   */
  void setAddress(const IOTA::Types::Trytes& address);

public:
  /**
   * @return The signatureFragments.
   */
  const std::vector<IOTA::Types::Trytes>& getSignatureFragments() const;

  /**
   * @return The signatureFragments.
   */
  std::vector<IOTA::Types::Trytes>& getSignatureFragments();

  /**
   * @param signatureFragments The signatureFragments.
   */
  void setSignatureFragments(const std::vector<IOTA::Types::Trytes>& signatureFragments);

private:
  IOTA::Types::Trytes              address_;
  std::vector<IOTA::Types::Trytes> signatureFragments_;
};

}  // namespace Models

}  // namespace IOTA
