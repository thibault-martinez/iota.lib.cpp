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

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Requests {

/**
 * Generic API call request.
 */
class Base {
public:
  /**
   * Full init ctor.
   *
   * @param command The command name.
   */
  explicit Base(const std::string& command);

  /**
   * Default dtor.
   */
  virtual ~Base() = default;

public:
  /**
   * Serialize object.
   *
   * @param data where to store serialisation.
   */
  virtual void serialize(json& data) const;

public:
  /**
   * @return The command name.
   */
  const std::string& getCommandName() const;

private:
  /**
   * The command name.
   */
  std::string command_;
};

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
