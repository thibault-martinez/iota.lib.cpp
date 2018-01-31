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

#include <iota/api/responses/get_neighbors.hpp>

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
      obj.setAddress(neighbor.at("address").get<Types::Trytes>());
    }

    if (neighbor.count("numberOfAllTransactions")) {
      obj.setNumberOfAllTransactions(neighbor.at("numberOfAllTransactions").get<int64_t>());
    }

    if (neighbor.count("numberOfInvalidTransactions")) {
      obj.setNumberOfInvalidTransactions(neighbor.at("numberOfInvalidTransactions").get<int64_t>());
    }

    if (neighbor.count("numberOfNewTransactions")) {
      obj.setNumberOfNewTransactions(neighbor.at("numberOfNewTransactions").get<int64_t>());
    }

    neighbors_.push_back(std::move(obj));
  }
}

const std::vector<Models::Neighbor>&
GetNeighbors::getNeighbors() const {
  return neighbors_;
}

std::vector<Models::Neighbor>&
GetNeighbors::getNeighbors() {
  return neighbors_;
}

void
GetNeighbors::setNeighbors(const std::vector<Models::Neighbor>& neighbors) {
  neighbors_ = neighbors;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
