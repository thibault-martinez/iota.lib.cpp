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

#include <json.hpp>

#include <iota/api/responses/base.hpp>
#include <iota/types/trinary.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/**
 * GetNewAddresses API call response.
 *
 * Generates a new address from a seed and returns the remainderAddress. This is either done
 * deterministically, or by providing the index of the new remainderAddress.
 */
class GetNewAddresses : public Base {
public:
  /**
   * Default ctor.
   */
  GetNewAddresses() = default;

  /**
   * Full init ctor.
   *
   * @param addresses New addresses.
   * @param duration Request duration.
   */
  GetNewAddresses(const std::vector<Types::Trytes>& addresses, const int64_t& duration);

  /**
   * Default dtor.
   */
  ~GetNewAddresses() = default;

public:
  /**
   * @return The addresses.
   */
  const std::vector<Types::Trytes>& getAddresses() const;

  /**
   * @return The addresses. (non const version)
   */
  std::vector<Types::Trytes>& getAddresses();

  /**
   * @param addresses new addresses for api response
   */
  void setAddresses(const std::vector<Types::Trytes>& addresses);

private:
  std::vector<Types::Trytes> addresses_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
