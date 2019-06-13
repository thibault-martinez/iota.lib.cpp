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

#include <cstdint>

#include <nlohmann/json_fwd.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/**
 * Generic API call response.
 */
class Base {
public:
  /**
   * Full init ctor.
   *
   * @param duration Duration of operation.
   */
  explicit Base(const int64_t& duration = 0);

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit Base(const json& res);

  /**
   * Default dtor.
   */
  virtual ~Base() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  virtual void deserialize(const json& res);

public:
  /**
   * @return duration of operation
   */
  const int64_t& getDuration() const;

  /**
   * @param duration set duration of operation
   */
  void setDuration(const int64_t& duration);

private:
  /**
   * Duration of operation.
   */
  int64_t duration_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
