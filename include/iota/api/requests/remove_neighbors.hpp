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

#include <iota/api/requests/base.hpp>

#include <vector>

namespace IOTA {

namespace API {

namespace Requests {

/**
 * RemoveNeighbors API call request.
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
   * @param uris List of URI elements.
   */
  explicit RemoveNeighbors(const std::vector<std::string>& uris = {});

  /**
   * Default dtor.
   */
  ~RemoveNeighbors() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  void serialize(json& data) const override;

public:
  /**
   * @return uris.
   */
  const std::vector<std::string>& getUris() const;

  /**
   * @return uris (non const version).
   */
  std::vector<std::string>& getUris();

  /**
   * @param uris new uris for addNeighbors API call.
   */
  void setUris(const std::vector<std::string>& uris);

private:
  /**
   * List of URI elements.
   */
  std::vector<std::string> uris_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
