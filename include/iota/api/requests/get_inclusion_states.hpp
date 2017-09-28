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

#include <json.hpp>

#include <iota/api/requests/base.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {
/*
 * GetInclusionStates API call request.
 * Get the inclusion states of a set of transactions. This is for determining if a transaction was
 * accepted and confirmed by the network or not. You can search for multiple tips (and thus,
 * milestones) to get past inclusion states of transactions.
 * This API call simply returns a list of boolean values in the same order as the transaction list
 * you submitted, thus you get a true/false whether a transaction is confirmed or not.
 * https://iota.readme.io/docs/getinclusionstates
 */
class GetInclusionStates : public Base {
public:
  GetInclusionStates(const std::vector<std::string>& transactions,
                     const std::vector<std::string>& tips);
  ~GetInclusionStates() = default;

public:
  void serialize(json& res);

private:
  /*
   * List of transactions you want to get the inclusion state for.
   */
  std::vector<std::string> transactions_;
  /*
   * List of tips (including milestones) you want to search for the inclusion state.
   */
  std::vector<std::string> tips_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
