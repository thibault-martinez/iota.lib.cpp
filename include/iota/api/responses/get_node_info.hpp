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

#include <json.hpp>

#include <iota/api/responses/base.hpp>

using json = nlohmann::json;

namespace IOTA {

namespace API {

namespace Responses {

/*
 * GetNodeInfo API call response.
 * Returns information about your node.
 * https://iota.readme.io/docs/getnodeinfo
 */
class GetNodeInfo : public Base {
public:
  /**
   * full init ctor
   */
  explicit GetNodeInfo(const std::string& appName = "", const std::string& appVersion = "",
                       int64_t jreAvailableProcessors = 0, int64_t jreFreeMemory = 0,
                       int64_t jreMaxMemory = 0, int64_t jreTotalMemory = 0,
                       const std::string& latestMilestone = "", int64_t latestMilestoneIndex = 0,
                       const std::string& latestSolidSubtangleMilestone = "",
                       int64_t latestSolidSubtangleMilestoneIndex = 0, int64_t neighbors = 0,
                       int64_t packetsQueueSize = 0, int64_t time = 0, int64_t tips = 0,
                       int64_t transactionsToRequest = 0);

  /**
   * default dtor
   */
  ~GetNodeInfo() = default;

public:
  /**
   * init class based on json data
   *
   * @param res json data to be used for deserialization
   */
  void deserialize(const json& res);

public:
  /**
   * @return Name of the IOTA software you're currently using (IRI stands for
   * Initial Reference Implementation).
   */
  const std::string& getAppName() const;

  /**
   * @param appName new app name for api response
   */
  void setAppName(const std::string& appName);

public:
  /**
   * @return The version of the IOTA software you're currently running.
   */
  const std::string& getAppVersion() const;

  /**
   * @param appVersion new app version for api response
   */
  void setAppVersion(const std::string& appVersion);

public:
  /**
   * @return Available cores on your machine for JRE.
   */
  const int64_t& getJreAvailableProcessors() const;

  /**
   * @param jreProc new procs for api response
   */
  void setJreAvailableProcessors(const int64_t& jreProc);

public:
  /**
   * @return the amount of free memory in the Java Virtual Machine.
   */
  const int64_t& getJreFreeMemory() const;

  /**
   * @param jreFreeMem new free mem for api response
   */
  void setJreFreeMemory(const int64_t& jreFreeMem);

public:
  /**
   * @return the maximum amount of memory that the Java virtual machine will
   * attempt to use.
   */
  const int64_t& getJreMaxMemory() const;

  /**
   * @param jreMaxMem new max mem for api response
   */
  void setJreMaxMemory(const int64_t& jreMaxMem);

public:
  /**
   * @return the total amount of memory in the Java virtual machine.
   */
  const int64_t& getJreTotalMemory() const;

  /**
   * @param jreTotalMem new total mem for api response
   */
  void setJreTotalMemory(const int64_t& jreTotalMem);

public:
  /**
   * @return Latest milestone that was signed off by the coordinator.
   */
  const std::string& getLatestMilestone() const;

  /**
   * @param latestMilestone new latest milestone for api response
   */
  void setLatestMilestone(const std::string& latestMilestone);

public:
  /**
   * @return Index of the latest milestone.
   */
  const int64_t& getLatestMilestoneIndex() const;

  /**
   * @param latestMilestoneIndex new latest milestone index for api response
   */
  void setLatestMilestoneIndex(const int64_t& latestMilestoneIndex);

public:
  /**
   * @return The latest milestone which is solid and is used for sending transactions.
   * For a milestone to become solid your local node must basically approve the
   * subtangle of coordinator-approved transactions, and have a consistent view
   * of all referenced transactions.
   */
  const std::string& getLatestSolidSubtangleMilestone() const;

  /**
   * @param latestSolidSubtangleMilestone new latest solid subtangle milestone for api response
   */
  void setLatestSolidSubtangleMilestone(const std::string& latestSolidSubtangleMilestone);

public:
  /**
   * @return Index of the latest solid subtangle.
   */
  const int64_t& getLatestSolidSubtangleMilestoneIndex() const;

  /**
   * @param latestSolidSubtangleMilestoneIndex new latest solid subtangle milestone index for api
   * response
   */
  void setLatestSolidSubtangleMilestoneIndex(const int64_t& latestSolidSubtangleMilestoneIndex);

public:
  /**
   * @return Number of neighbors you are directly connected with.
   */
  const int64_t& getNeighbors() const;

  /**
   * @param neighbors new nb of neighbors for api response
   */
  void setNeighbors(const int64_t& neighbors);

public:
  /**
   * @return Packets which are currently queued up.
   */
  const int64_t& getPacketsQueueSize() const;

  /**
   * @param queueSize new queueSize for api response
   */
  void setPacketsQueueSize(const int64_t& queueSize);

public:
  /**
   * @return Current UNIX timestamp.
   */
  const int64_t& getTime() const;

  /**
   * @param time new time for api response
   */
  void setTime(const int64_t& time);

public:
  /**
   * @return Number of tips in the network.
   */
  const int64_t& getTips() const;

  /**
   * @param tips new tips for api response
   */
  void setTips(const int64_t& tips);

public:
  /**
   * @return Transactions to request during syncing process.
   */
  const int64_t& getTransactionsToRequest() const;

  /**
   * @param transactionsToRequest new nb transactions to requests of api response
   */
  void setTransactionsToRequest(const int64_t& transactionsToRequest);

private:
  std::string appName_;
  std::string appVersion_;
  int64_t     jreAvailableProcessors_;
  int64_t     jreFreeMemory_;
  int64_t     jreMaxMemory_;
  int64_t     jreTotalMemory_;
  std::string latestMilestone_;
  int64_t     latestMilestoneIndex_;
  std::string latestSolidSubtangleMilestone_;
  int64_t     latestSolidSubtangleMilestoneIndex_;
  int64_t     neighbors_;
  int64_t     packetsQueueSize_;
  int64_t     time_;
  int64_t     tips_;
  int64_t     transactionsToRequest_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
