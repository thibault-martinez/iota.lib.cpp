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

#include <iota/api/responses/base.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace API {

namespace Responses {

/**
 * GetNodeInfo API call response.
 *
 * Returns information about your node.
 *
 * https://iota.readme.io/reference#getnodeinfo
 */
class GetNodeInfo : public Base {
public:
  /**
   * Full init ctor.
   *
   * @param appName Name of the IOTA software you're currently using (IRI stands for Initial
   * Reference Implementation).
   * @param appVersion The version of the IOTA software you're currently running.
   * @param jreAvailableProcessors Available cores on your machine for JRE.
   * @param jreFreeMemory The amount of free memory in the Java Virtual Machine.
   * @param jreMaxMemory The maximum amount of memory the Java virtual machine will attempt to use.
   * @param jreTotalMemory The total amount of memory in the Java virtual machine.
   * @param latestMilestone Latest milestone that was signed off by the coordinator.
   * @param latestMilestoneIndex Index of the latest milestone.
   * @param latestSolidSubtangleMilestone The latest milestone which is solid and is used for
   * sending transactions. For a milestone to become solid your local node must basically approve
   * the subtangle of coordinator-approved transactions, and have a consistent view of all
   * referenced transactions.
   * @param latestSolidSubtangleMilestoneIndex Index of the latest solid subtangle.
   * @param neighbors Number of neighbors you are directly connected with.
   * @param packetsQueueSize Packets which are currently queued up.
   * @param time Current UNIX timestamp.
   * @param tips Number of tips in the network.
   * @param transactionsToRequest Transactions to request during syncing process.
   */
  explicit GetNodeInfo(const std::string& appName = "", const std::string& appVersion = "",
                       int64_t jreAvailableProcessors = 0, int64_t jreFreeMemory = 0,
                       int64_t jreMaxMemory = 0, int64_t jreTotalMemory = 0,
                       const Types::Trytes& latestMilestone = "", int64_t latestMilestoneIndex = 0,
                       const Types::Trytes& latestSolidSubtangleMilestone = "",
                       int64_t latestSolidSubtangleMilestoneIndex = 0, int64_t neighbors = 0,
                       int64_t packetsQueueSize = 0, int64_t time = 0, int64_t tips = 0,
                       int64_t transactionsToRequest = 0);

  /**
   * Json-based ctor.
   *
   * @param res json to be used for deserialization.
   */
  explicit GetNodeInfo(const json& res);

  /**
   * Default dtor.
   */
  ~GetNodeInfo() = default;

public:
  /**
   * Initialization based on json data.
   *
   * @param res json data to be used for deserialization.
   */
  void deserialize(const json& res) override;

public:
  /**
   * @return Name of the IOTA software you're currently using (IRI stands for Initial Reference
   * Implementation).
   */
  const std::string& getAppName() const;

  /**
   * @param appName new app name for api response.
   */
  void setAppName(const std::string& appName);

public:
  /**
   * @return The version of the IOTA software you're currently running.
   */
  const std::string& getAppVersion() const;

  /**
   * @param appVersion new app version for api response.
   */
  void setAppVersion(const std::string& appVersion);

public:
  /**
   * @return Available cores on your machine for JRE.
   */
  const int64_t& getJreAvailableProcessors() const;

  /**
   * @param jreAvailableProcessors new procs for api response.
   */
  void setJreAvailableProcessors(const int64_t& jreAvailableProcessors);

public:
  /**
   * @return The amount of free memory in the Java Virtual Machine.
   */
  const int64_t& getJreFreeMemory() const;

  /**
   * @param jreFreeMemory new free mem for api response.
   */
  void setJreFreeMemory(const int64_t& jreFreeMemory);

public:
  /**
   * @return The maximum amount of memory that the Java virtual machine will attempt to use.
   */
  const int64_t& getJreMaxMemory() const;

  /**
   * @param jreMaxMemory new max mem for api response.
   */
  void setJreMaxMemory(const int64_t& jreMaxMemory);

public:
  /**
   * @return The total amount of memory in the Java virtual machine.
   */
  const int64_t& getJreTotalMemory() const;

  /**
   * @param jreTotalMemory new total mem for api response.
   */
  void setJreTotalMemory(const int64_t& jreTotalMemory);

public:
  /**
   * @return Latest milestone that was signed off by the coordinator.
   */
  const Types::Trytes& getLatestMilestone() const;

  /**
   * @param latestMilestone new latest milestone for api response.
   */
  void setLatestMilestone(const Types::Trytes& latestMilestone);

public:
  /**
   * @return Index of the latest milestone.
   */
  const int64_t& getLatestMilestoneIndex() const;

  /**
   * @param latestMilestoneIndex new latest milestone index for api response.
   */
  void setLatestMilestoneIndex(const int64_t& latestMilestoneIndex);

public:
  /**
   * @return The latest milestone which is solid and is used for sending transactions. For a
   * milestone to become solid your local node must basically approve the subtangle of
   * coordinator-approved transactions, and have a consistent view of all referenced transactions.
   */
  const Types::Trytes& getLatestSolidSubtangleMilestone() const;

  /**
   * @param latestSolidSubtangleMilestone new latest solid subtangle milestone for api response.
   */
  void setLatestSolidSubtangleMilestone(const Types::Trytes& latestSolidSubtangleMilestone);

public:
  /**
   * @return Index of the latest solid subtangle.
   */
  const int64_t& getLatestSolidSubtangleMilestoneIndex() const;

  /**
   * @param latestSolidSubtangleMilestoneIndex new latest solid subtangle milestone index for api
   * response.
   */
  void setLatestSolidSubtangleMilestoneIndex(const int64_t& latestSolidSubtangleMilestoneIndex);

public:
  /**
   * @return Number of neighbors you are directly connected with.
   */
  const int64_t& getNeighbors() const;

  /**
   * @param neighbors new nb of neighbors for api response.
   */
  void setNeighbors(const int64_t& neighbors);

public:
  /**
   * @return Packets which are currently queued up.
   */
  const int64_t& getPacketsQueueSize() const;

  /**
   * @param packetsQueueSize new queueSize for api response.
   */
  void setPacketsQueueSize(const int64_t& packetsQueueSize);

public:
  /**
   * @return Current UNIX timestamp.
   */
  const int64_t& getTime() const;

  /**
   * @param time new time for api response.
   */
  void setTime(const int64_t& time);

public:
  /**
   * @return Number of tips in the network.
   */
  const int64_t& getTips() const;

  /**
   * @param tips new tips for api response.
   */
  void setTips(const int64_t& tips);

public:
  /**
   * @return Transactions to request during syncing process.
   */
  const int64_t& getTransactionsToRequest() const;

  /**
   * @param transactionsToRequest new nb transactions to requests of api response.
   */
  void setTransactionsToRequest(const int64_t& transactionsToRequest);

private:
  /**
   * Name of the IOTA software you're currently using (IRI stands for Initial Reference
   * Implementation).
   */
  std::string appName_;
  /**
   * The version of the IOTA software you're currently running.
   */
  std::string appVersion_;
  /**
   * Available cores on your machine for JRE.
   */
  int64_t jreAvailableProcessors_;
  /**
   * Returns the amount of free memory in the Java Virtual Machine.
   */
  int64_t jreFreeMemory_;
  /**
   * Returns the maximum amount of memory that the Java virtual machine will attempt to use.
   */
  int64_t jreMaxMemory_;
  /**
   * Returns the total amount of memory in the Java virtual machine.
   */
  int64_t jreTotalMemory_;
  /**
   * Latest milestone that was signed off by the coordinator.
   */
  Types::Trytes latestMilestone_;
  /**
   * Index of the latest milestone.
   */
  int64_t latestMilestoneIndex_;
  /**
   * The latest milestone which is solid and is used for sending transactions. For a milestone to
   * become solid your local node must basically approve the subtangle of coordinator-approved
   * transactions, and have a consistent view of all referenced transactions.
   */
  Types::Trytes latestSolidSubtangleMilestone_;
  /**
   * Index of the latest solid subtangle.
   */
  int64_t latestSolidSubtangleMilestoneIndex_;
  /**
   * Number of neighbors you are directly connected with.
   */
  int64_t neighbors_;
  /**
   * Packets which are currently queued up.
   */
  int64_t packetsQueueSize_;
  /**
   * Current UNIX timestamp.
   */
  int64_t time_;
  /**
   * Number of tips in the network.
   */
  int64_t tips_;
  /**
   * Transactions to request during syncing process.
   */
  int64_t transactionsToRequest_;
};

}  // namespace Responses

}  // namespace API

}  // namespace IOTA
