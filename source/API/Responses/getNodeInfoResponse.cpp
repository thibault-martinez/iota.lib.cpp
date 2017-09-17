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

#include <API/Responses/getNodeInfoResponse.hpp>

getNodeInfoResponse::getNodeInfoResponse() {
}

getNodeInfoResponse::~getNodeInfoResponse() {
}

void
getNodeInfoResponse::deserialize(const json& res) {
  duration_                           = res.at("duration").get<int64_t>();
  appName_                            = res.at("appName").get<std::string>();
  appVersion_                         = res.at("appVersion").get<std::string>();
  jreAvailableProcessors_             = res.at("jreAvailableProcessors").get<int64_t>();
  jreFreeMemory_                      = res.at("jreFreeMemory").get<int64_t>();
  jreMaxMemory_                       = res.at("jreMaxMemory").get<int64_t>();
  jreTotalMemory_                     = res.at("jreTotalMemory").get<int64_t>();
  latestMilestone_                    = res.at("latestMilestone").get<std::string>();
  latestMilestoneIndex_               = res.at("latestMilestoneIndex").get<int64_t>();
  latestSolidSubtangleMilestone_      = res.at("latestSolidSubtangleMilestone").get<std::string>();
  latestSolidSubtangleMilestoneIndex_ = res.at("latestSolidSubtangleMilestoneIndex").get<int64_t>();
  neighbors_                          = res.at("neighbors").get<int64_t>();
  packetsQueueSize_                   = res.at("packetsQueueSize").get<int64_t>();
  time_                               = res.at("time").get<int64_t>();
  tips_                               = res.at("tips").get<int64_t>();
  transactionsToRequest_              = res.at("transactionsToRequest").get<int64_t>();
}

const std::string&
getNodeInfoResponse::getAppName() const {
  return this->appName_;
}

const std::string&
getNodeInfoResponse::getAppVersion() const {
  return this->appVersion_;
}

const int64_t&
getNodeInfoResponse::getjreAvailableProcessors() const {
  return this->jreAvailableProcessors_;
}

const int64_t&
getNodeInfoResponse::getJreFreeMemory() const {
  return this->jreFreeMemory_;
}

const int64_t&
getNodeInfoResponse::getJreMaxMemory() const {
  return this->jreMaxMemory_;
}

const int64_t&
getNodeInfoResponse::getJreTotalMemory() const {
  return this->jreTotalMemory_;
}

const std::string&
getNodeInfoResponse::getLatestMilestone() const {
  return this->latestMilestone_;
}

const int64_t&
getNodeInfoResponse::getLatestMilestoneIndex() const {
  return this->latestMilestoneIndex_;
}

const std::string&
getNodeInfoResponse::getLatestSolidSubtangleMilestone() const {
  return this->latestSolidSubtangleMilestone_;
}

const int64_t&
getNodeInfoResponse::getLatestSolidSubtangleMilestoneIndex() const {
  return this->latestSolidSubtangleMilestoneIndex_;
}

const int64_t&
getNodeInfoResponse::getNeighbors() const {
  return this->neighbors_;
}

const int64_t&
getNodeInfoResponse::getPacketsQueueSize() const {
  return this->packetsQueueSize_;
}

const int64_t&
getNodeInfoResponse::getTime() const {
  return this->time_;
}

const int64_t&
getNodeInfoResponse::getTips() const {
  return this->tips_;
}

const int64_t&
getNodeInfoResponse::getTransactionsToRequest() const {
  return this->transactionsToRequest_;
}
