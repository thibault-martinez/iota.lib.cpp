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

#include <iota/api/responses/get_node_info.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetNodeInfo::GetNodeInfo()
    : jreAvailableProcessors_(0),
      jreFreeMemory_(0),
      jreMaxMemory_(0),
      jreTotalMemory_(0),
      latestMilestoneIndex_(0),
      latestSolidSubtangleMilestoneIndex_(0),
      neighbors_(0),
      packetsQueueSize_(0),
      time_(0),
      tips_(0),
      transactionsToRequest_(0) {
}

void
GetNodeInfo::deserialize(const json& res) {
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
GetNodeInfo::getAppName() const {
  return this->appName_;
}

const std::string&
GetNodeInfo::getAppVersion() const {
  return this->appVersion_;
}

const int64_t&
GetNodeInfo::getjreAvailableProcessors() const {
  return this->jreAvailableProcessors_;
}

const int64_t&
GetNodeInfo::getJreFreeMemory() const {
  return this->jreFreeMemory_;
}

const int64_t&
GetNodeInfo::getJreMaxMemory() const {
  return this->jreMaxMemory_;
}

const int64_t&
GetNodeInfo::getJreTotalMemory() const {
  return this->jreTotalMemory_;
}

const std::string&
GetNodeInfo::getLatestMilestone() const {
  return this->latestMilestone_;
}

const int64_t&
GetNodeInfo::getLatestMilestoneIndex() const {
  return this->latestMilestoneIndex_;
}

const std::string&
GetNodeInfo::getLatestSolidSubtangleMilestone() const {
  return this->latestSolidSubtangleMilestone_;
}

const int64_t&
GetNodeInfo::getLatestSolidSubtangleMilestoneIndex() const {
  return this->latestSolidSubtangleMilestoneIndex_;
}

const int64_t&
GetNodeInfo::getNeighbors() const {
  return this->neighbors_;
}

const int64_t&
GetNodeInfo::getPacketsQueueSize() const {
  return this->packetsQueueSize_;
}

const int64_t&
GetNodeInfo::getTime() const {
  return this->time_;
}

const int64_t&
GetNodeInfo::getTips() const {
  return this->tips_;
}

const int64_t&
GetNodeInfo::getTransactionsToRequest() const {
  return this->transactionsToRequest_;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
