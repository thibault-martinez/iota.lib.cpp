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

GetNodeInfo::GetNodeInfo(const std::string& appName, const std::string& appVersion,
                         int64_t jreAvailableProcessors, int64_t jreFreeMemory,
                         int64_t jreMaxMemory, int64_t jreTotalMemory,
                         const std::string& latestMilestone, int64_t latestMilestoneIndex,
                         const std::string& latestSolidSubtangleMilestone,
                         int64_t latestSolidSubtangleMilestoneIndex, int64_t neighbors,
                         int64_t packetsQueueSize, int64_t time, int64_t tips,
                         int64_t transactionsToRequest)
    : appName_(appName),
      appVersion_(appVersion),
      jreAvailableProcessors_(jreAvailableProcessors),
      jreFreeMemory_(jreFreeMemory),
      jreMaxMemory_(jreMaxMemory),
      jreTotalMemory_(jreTotalMemory),
      latestMilestone_(latestMilestone),
      latestMilestoneIndex_(latestMilestoneIndex),
      latestSolidSubtangleMilestone_(latestSolidSubtangleMilestone),
      latestSolidSubtangleMilestoneIndex_(latestSolidSubtangleMilestoneIndex),
      neighbors_(neighbors),
      packetsQueueSize_(packetsQueueSize),
      time_(time),
      tips_(tips),
      transactionsToRequest_(transactionsToRequest) {
}

void
GetNodeInfo::deserialize(const json& res) {
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

void
GetNodeInfo::setAppName(const std::string& appName) {
  this->appName_ = appName;
}

const std::string&
GetNodeInfo::getAppVersion() const {
  return this->appVersion_;
}

void
GetNodeInfo::setAppVersion(const std::string& appVersion) {
  this->appVersion_ = appVersion;
}

const int64_t&
GetNodeInfo::getJreAvailableProcessors() const {
  return this->jreAvailableProcessors_;
}

void
GetNodeInfo::setJreAvailableProcessors(const int64_t& jreAvailableProcessors) {
  this->jreAvailableProcessors_ = jreAvailableProcessors;
}

const int64_t&
GetNodeInfo::getJreFreeMemory() const {
  return this->jreFreeMemory_;
}

void
GetNodeInfo::setJreFreeMemory(const int64_t& jreFreeMemory) {
  this->jreFreeMemory_ = jreFreeMemory;
}

const int64_t&
GetNodeInfo::getJreMaxMemory() const {
  return this->jreMaxMemory_;
}

void
GetNodeInfo::setJreMaxMemory(const int64_t& jreMaxMemory) {
  this->jreMaxMemory_ = jreMaxMemory;
}

const int64_t&
GetNodeInfo::getJreTotalMemory() const {
  return this->jreTotalMemory_;
}

void
GetNodeInfo::setJreTotalMemory(const int64_t& jreTotalMemory) {
  this->jreTotalMemory_ = jreTotalMemory;
}

const std::string&
GetNodeInfo::getLatestMilestone() const {
  return this->latestMilestone_;
}

void
GetNodeInfo::setLatestMilestone(const std::string& latestMilestone) {
  this->latestMilestone_ = latestMilestone;
}

const int64_t&
GetNodeInfo::getLatestMilestoneIndex() const {
  return this->latestMilestoneIndex_;
}

void
GetNodeInfo::setLatestMilestoneIndex(const int64_t& latestMilestoneIndex) {
  this->latestMilestoneIndex_ = latestMilestoneIndex;
}

const std::string&
GetNodeInfo::getLatestSolidSubtangleMilestone() const {
  return this->latestSolidSubtangleMilestone_;
}

void
GetNodeInfo::setLatestSolidSubtangleMilestone(const std::string& latestSolidSubtangleMilestone) {
  this->latestSolidSubtangleMilestone_ = latestSolidSubtangleMilestone;
}

const int64_t&
GetNodeInfo::getLatestSolidSubtangleMilestoneIndex() const {
  return this->latestSolidSubtangleMilestoneIndex_;
}

void
GetNodeInfo::setLatestSolidSubtangleMilestoneIndex(
    const int64_t& latestSolidSubtangleMilestoneIndex) {
  this->latestSolidSubtangleMilestoneIndex_ = latestSolidSubtangleMilestoneIndex;
}

const int64_t&
GetNodeInfo::getNeighbors() const {
  return this->neighbors_;
}

void
GetNodeInfo::setNeighbors(const int64_t& neighbors) {
  this->neighbors_ = neighbors;
}

const int64_t&
GetNodeInfo::getPacketsQueueSize() const {
  return this->packetsQueueSize_;
}

void
GetNodeInfo::setPacketsQueueSize(const int64_t& packetsQueueSize) {
  this->packetsQueueSize_ = packetsQueueSize;
}

const int64_t&
GetNodeInfo::getTime() const {
  return this->time_;
}

void
GetNodeInfo::setTime(const int64_t& time) {
  this->time_ = time;
}

const int64_t&
GetNodeInfo::getTips() const {
  return this->tips_;
}

void
GetNodeInfo::setTips(const int64_t& tips) {
  this->tips_ = tips;
}

const int64_t&
GetNodeInfo::getTransactionsToRequest() const {
  return this->transactionsToRequest_;
}

void
GetNodeInfo::setTransactionsToRequest(const int64_t& transactionsToRequest) {
  this->transactionsToRequest_ = transactionsToRequest;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
