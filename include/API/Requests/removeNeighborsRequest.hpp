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

#include "genericRequest.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace IOTA {

namespace API {

/*
 * removeNeighbors API call request.
 * Removes a list of neighbors to your node. This is only temporary, and if you have your neighbors
 * added via the command line, they will be retained after you restart your node.
 * https://iota.readme.io/docs/removeneighors
 */
class removeNeighborsRequest : public genericRequest {
public:
  removeNeighborsRequest(const std::vector<std::string>& uris);
  virtual ~removeNeighborsRequest();

public:
  void serialize(json& res);

private:
  /*
   * List of URI elements.
   */
  std::vector<std::string> uris_;
};

}  // namespace API

}  // namespace IOTA
