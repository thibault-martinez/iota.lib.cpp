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

#include <nlohmann/json.hpp>

#include <iota/api/responses/check_consistency.hpp>

namespace IOTA {

namespace API {

namespace Responses {

CheckConsistency::CheckConsistency(const bool state, const std::string& info)
    : state_(state), info_(info) {
}

CheckConsistency::CheckConsistency(const json& res) {
  deserialize(res);
}

void
CheckConsistency::deserialize(const json& res) {
  Base::deserialize(res);

  if (res.count("state")) {
    state_ = res.at("state").get<decltype(state_)>();
  }
  if (res.count("info")) {
    info_ = res.at("info").get<decltype(info_)>();
  }
}

bool
CheckConsistency::getState() const {
  return state_;
}

const std::string&
CheckConsistency::getInfo() const {
  return info_;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
