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

#include <iota/api/requests/attach_to_tangle.hpp>

namespace IOTA {

namespace API {

namespace Requests {

AttachToTangle::AttachToTangle(const std::string& trunkTransaction,
                               const std::string& branchTransaction, const int& minWeightMagnitude,
                               const std::vector<std::string>& trytes)
    : Base("attachToTangle"),
      trunkTransaction_(trunkTransaction),
      branchTransaction_(branchTransaction),
      minWeightMagnitude_(minWeightMagnitude),
      trytes_(trytes) {
}

void
AttachToTangle::serialize(json& data) {
  data["trunkTransaction"]   = this->trunkTransaction_;
  data["branchTransaction"]  = this->branchTransaction_;
  data["minWeightMagnitude"] = this->minWeightMagnitude_;
  data["trytes"]             = this->trytes_;
}

const std::string&
AttachToTangle::getTrunkTransaction() const {
  return trunkTransaction_;
}

void
AttachToTangle::setTrunkTransaction(const std::string& trx) {
  trunkTransaction_ = trx;
}

const std::string&
AttachToTangle::getBranchTransaction() const {
  return branchTransaction_;
}

void
AttachToTangle::setBranchTransaction(const std::string& trx) {
  branchTransaction_ = trx;
}

int
AttachToTangle::getMinWeightMagnitude() const {
  return minWeightMagnitude_;
}

void
AttachToTangle::setMinWeightMagnitude(int weight) {
  minWeightMagnitude_ = weight;
}

const std::vector<std::string>&
AttachToTangle::getTrytes() const {
  return trytes_;
}

std::vector<std::string>&
AttachToTangle::getTrytes() {
  return trytes_;
}

void
AttachToTangle::setTrytes(const std::vector<std::string>& trytes) {
  trytes_ = trytes;
}

}  // namespace Requests

}  // namespace API

}  // namespace IOTA
