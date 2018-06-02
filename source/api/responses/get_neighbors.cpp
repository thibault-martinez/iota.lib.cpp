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

#include <json.hpp>

#include <iota/api/responses/get_neighbors.hpp>
#include <iota/models/neighbor.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetNeighbors::GetNeighbors(const std::vector<Models::Neighbor>& neighbors) : neighbors_(neighbors) {
}

GetNeighbors::GetNeighbors(const json& res) {
  deserialize(res);
}

void
GetNeighbors::deserialize(const json& res) {
  Base::deserialize(res);
  for (const auto& neighbor : res["neighbors"]) {
    Models::Neighbor obj;

    if (neighbor.count("address")) {
      obj.setAddress(
          neighbor.at("address").get<std::remove_reference<decltype(obj.getAddress())>::type>());
    }

    if (neighbor.count("numberOfAllTransactions")) {
      obj.setNumberOfAllTransactions(
          neighbor.at("numberOfAllTransactions")
              .get<std::remove_reference<decltype(obj.getNumberOfAllTransactions())>::type>());
    }

    if (neighbor.count("numberOfInvalidTransactions")) {
      obj.setNumberOfInvalidTransactions(
          neighbor.at("numberOfInvalidTransactions")
              .get<std::remove_reference<decltype(obj.getNumberOfInvalidTransactions())>::type>());
    }

    if (neighbor.count("numberOfNewTransactions")) {
      obj.setNumberOfNewTransactions(
          neighbor.at("numberOfNewTransactions")
              .get<std::remove_reference<decltype(obj.getNumberOfNewTransactions())>::type>());
    }

    neighbors_.push_back(std::move(obj));
  }
}

const std::vector<Models::Neighbor>&
GetNeighbors::getNeighbors() const {
  return neighbors_;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
