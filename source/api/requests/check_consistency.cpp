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

#include <iota/api/requests/check_consistency.hpp>

namespace IOTA {

namespace API {

namespace Requests {

CheckConsistency::CheckConsistency(const std::vector<Types::Trytes>& tails)
    : Base("checkConsistency"), tails_(tails) {
}

void
CheckConsistency::serialize(json& data) const {
  Base::serialize(data);
  data["tails"] = tails_;
}

const std::vector<Types::Trytes>&
CheckConsistency::getTails() const {
  return tails_;
}

std::vector<Types::Trytes>&
CheckConsistency::getTails() {
  return tails_;
}

void
CheckConsistency::setTails(const std::vector<Types::Trytes>& tails) {
  tails_ = tails;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
