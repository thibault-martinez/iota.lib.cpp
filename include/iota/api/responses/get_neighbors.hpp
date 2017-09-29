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

#include <iota/api/responses/base.hpp>
#include <iota/models/neighbor.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * GetNeighbors API call response.
 * Returns the set of neighbors you are connected with, as well as their activity count. The
 * activity counter is reset after restarting IRI.
 * https://iota.readme.io/docs/getneighborsactivity
 */
class GetNeighbors : public Base {
public:
  /**
   * full init ctor
   */
  explicit GetNeighbors(const std::vector<Models::Neighbor>& neighbors = {});

  /**
   * default dtor
   */
  ~GetNeighbors() = default;

public:
  /**
   * init class based on json data
   *
   * @param res json data to be used for deserialization
   */
  void deserialize(const json& res);

public:
  /**
   * @return neighbors.
   */
  const std::vector<Models::Neighbor>& getNeighbors() const;

  /**
   * @return neighbors. (non const version)
   */
  std::vector<Models::Neighbor>& getNeighbors();

  /**
   * @param neighbors new neighbors for api response
   */
  void setNeighbors(const std::vector<Models::Neighbor>& neighbors);

private:
  std::vector<Models::Neighbor> neighbors_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
