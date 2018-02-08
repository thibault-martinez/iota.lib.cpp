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
 * GetTips API call response.
 *
 * Returns the list of tips.
 *
 * https://iota.readme.io/reference#gettips
 */
class GetTips : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param hashes The list of tips.
   */
  explicit GetTips(const std::vector<Types::Trytes>& hashes = {});

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit GetTips(const json& res);

  /**
   * Default dtor.
   */
  ~GetTips() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return hashes.
   */
  const std::vector<Types::Trytes>& getHashes() const;

  /**
   * @return hashes (non const version).
   */
  std::vector<Types::Trytes>& getHashes();

  /**
   * @param hashes new hashes for api call.
   */
  void setHashes(const std::vector<Types::Trytes>& hashes);

private:
  /**
   * List of tips.
   */
  std::vector<Types::Trytes> hashes_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
