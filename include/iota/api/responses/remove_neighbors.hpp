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

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * RemoveNeighbors API call response.
 *
 * Removes a list of neighbors to your node. This is only temporary, and if you have your
 * neighbors added via the command line, they will be retained after you restart your node.
 *
 * https://iota.readme.io/reference#removeneighors
 */
class RemoveNeighbors : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param removedNeighbors The number of removed neighbors.
   */
  explicit RemoveNeighbors(const int64_t& removedNeighbors = 0);

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit RemoveNeighbors(const json& res);

  /**
   * Default dtor.
   */
  ~RemoveNeighbors() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return Number of removed neighbors.
   */
  const int64_t& getRemovedNeighbors() const;

  /**
   * @param removedNeighbors new nb of removed neighbors for api response.
   */
  void setRemovedNeighbors(const int64_t& removedNeighbors);

private:
  /**
   * Number of removed neighbors.
   */
  int64_t removedNeighbors_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
