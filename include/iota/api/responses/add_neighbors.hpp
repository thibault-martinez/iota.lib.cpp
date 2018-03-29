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

#include <iota/api/responses/base.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * AddNeighbors API call response.
 *
 * Add a list of neighbors to your node. It should be noted that this is only temporary, and the
 * added neighbors will be removed from your set of neighbors after you relaunch IRI.
 *
 * https://iota.readme.io/reference#addneighors
 */
class AddNeighbors : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param addedNeighbors The number of added neighbors.
   */
  explicit AddNeighbors(const int64_t& addedNeighbors = 0);

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit AddNeighbors(const Utils::json& res);

  /**
   * Default dtor.
   */
  ~AddNeighbors() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const Utils::json& res) override;

public:
  /**
   * @return Number of added neighbors.
   */
  const int64_t& getAddedNeighbors() const;

  /**
   * @param addedNeighbors set number of added neighbors.
   */
  void setAddedNeighbors(const int64_t& addedNeighbors);

private:
  /**
   * Number of added neighbors.
   */
  int64_t addedNeighbors_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
