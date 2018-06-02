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

#include <json.hpp>

#include <iota/api/responses/get_node_info.hpp>

namespace IOTA {

namespace API {

namespace Responses {

GetNodeInfo::GetNodeInfo(const std::string& appName, const std::string& appVersion,
                         int64_t jreAvailableProcessors, int64_t jreFreeMemory,
                         int64_t jreMaxMemory, int64_t jreTotalMemory,
                         const Types::Trytes& latestMilestone, int64_t latestMilestoneIndex,
                         const Types::Trytes& latestSolidSubtangleMilestone,
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

GetNodeInfo::GetNodeInfo(const json& res) {
  deserialize(res);
}

void
GetNodeInfo::deserialize(const json& res) {
  Base::deserialize(res);

  if (res.count("appName")) {
    appName_ = res.at("appName").get<std::string>();
  }

  if (res.count("appVersion")) {
    appVersion_ = res.at("appVersion").get<std::string>();
  }

  if (res.count("jreAvailableProcessors")) {
    jreAvailableProcessors_ = res.at("jreAvailableProcessors").get<int64_t>();
  }

  if (res.count("jreFreeMemory")) {
    jreFreeMemory_ = res.at("jreFreeMemory").get<int64_t>();
  }

  if (res.count("jreMaxMemory")) {
    jreMaxMemory_ = res.at("jreMaxMemory").get<int64_t>();
  }

  if (res.count("jreTotalMemory")) {
    jreTotalMemory_ = res.at("jreTotalMemory").get<int64_t>();
  }

  if (res.count("latestMilestone")) {
    latestMilestone_ = res.at("latestMilestone").get<Types::Trytes>();
  }

  if (res.count("latestMilestoneIndex")) {
    latestMilestoneIndex_ = res.at("latestMilestoneIndex").get<int64_t>();
  }

  if (res.count("latestSolidSubtangleMilestone")) {
    latestSolidSubtangleMilestone_ = res.at("latestSolidSubtangleMilestone").get<Types::Trytes>();
  }

  if (res.count("latestSolidSubtangleMilestoneIndex")) {
    latestSolidSubtangleMilestoneIndex_ =
        res.at("latestSolidSubtangleMilestoneIndex").get<int64_t>();
  }

  if (res.count("neighbors")) {
    neighbors_ = res.at("neighbors").get<int64_t>();
  }

  if (res.count("packetsQueueSize")) {
    packetsQueueSize_ = res.at("packetsQueueSize").get<int64_t>();
  }

  if (res.count("time")) {
    time_ = res.at("time").get<int64_t>();
  }

  if (res.count("tips")) {
    tips_ = res.at("tips").get<int64_t>();
  }

  if (res.count("transactionsToRequest")) {
    transactionsToRequest_ = res.at("transactionsToRequest").get<int64_t>();
  }
}

const std::string&
GetNodeInfo::getAppName() const {
  return appName_;
}

const std::string&
GetNodeInfo::getAppVersion() const {
  return appVersion_;
}

const int64_t&
GetNodeInfo::getJreAvailableProcessors() const {
  return jreAvailableProcessors_;
}

const int64_t&
GetNodeInfo::getJreFreeMemory() const {
  return jreFreeMemory_;
}

const int64_t&
GetNodeInfo::getJreMaxMemory() const {
  return jreMaxMemory_;
}

const int64_t&
GetNodeInfo::getJreTotalMemory() const {
  return jreTotalMemory_;
}

const Types::Trytes&
GetNodeInfo::getLatestMilestone() const {
  return latestMilestone_;
}

const int64_t&
GetNodeInfo::getLatestMilestoneIndex() const {
  return latestMilestoneIndex_;
}

const Types::Trytes&
GetNodeInfo::getLatestSolidSubtangleMilestone() const {
  return latestSolidSubtangleMilestone_;
}

const int64_t&
GetNodeInfo::getLatestSolidSubtangleMilestoneIndex() const {
  return latestSolidSubtangleMilestoneIndex_;
}

const int64_t&
GetNodeInfo::getNeighbors() const {
  return neighbors_;
}

const int64_t&
GetNodeInfo::getPacketsQueueSize() const {
  return packetsQueueSize_;
}

const int64_t&
GetNodeInfo::getTime() const {
  return time_;
}

const int64_t&
GetNodeInfo::getTips() const {
  return tips_;
}

const int64_t&
GetNodeInfo::getTransactionsToRequest() const {
  return transactionsToRequest_;
}

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
