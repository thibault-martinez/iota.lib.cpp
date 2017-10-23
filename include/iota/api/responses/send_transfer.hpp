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

#include <iota/api/responses/base.hpp>

#include <vector>

namespace IOTA {

namespace API {

namespace Responses {

class SendTransfer : public Base {
public:
  /**
   * default ctor
   */
  SendTransfer() = default;

  /**
   * full init ctor
   */
  SendTransfer(const std::vector<bool>& successful, const int64_t& duration);

  /**
   * default dtor
   */
  ~SendTransfer() = default;

public:
  /**
   * @return successful operations.
   */
  const std::vector<bool>& getSuccessfully() const;

  /**
   * @return successful operations (non-const version).
   */
  std::vector<bool>& getSuccessfully();

  /**
   * @param successful new array of successful operations for SendTransfer response
   */
  void setSuccessfully(const std::vector<bool>& successful);

private:
  std::vector<bool> successfully_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
