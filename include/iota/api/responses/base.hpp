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

#include <cstdint>

#include <json.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * generic API call response.
 */
class Base {
public:
  /**
   * full init ctor
   */
  explicit Base(const int64_t& duration = 0);

  /**
   * default dtor
   */
  virtual ~Base() = default;

public:
  /**
   * init class based on json data
   *
   * @param res json data to be used for deserialization
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

  /**
   * @return status code of operation
   */
  const int16_t& getStatusCode() const;

  /**
   * @param statusCode set statusCode of operation
   */
  void setStatusCode(const int16_t& statusCode);

  /**
   * @return error of operation
   */
  const std::string& getError() const;

  /**
   * @param error set error of operation
   */
  void setError(const std::string& error);

private:
  int64_t     duration_;
  int16_t     statusCode_;
  std::string error_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
