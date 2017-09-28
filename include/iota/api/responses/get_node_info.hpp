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
  GetNodeInfo();
  ~GetNodeInfo() = default;

public:
  void deserialize(const json& res);

public:
  /*
   * Name of the IOTA software you're currently using (IRI stands for
   * Initial Reference Implementation).
   */
  const std::string& getAppName() const;
  /*
   * The version of the IOTA software you're currently running.
   */
  const std::string& getAppVersion() const;
  /*
   * Available cores on your machine for JRE.
   */
  const int64_t& getjreAvailableProcessors() const;
  /*
   * Returns the amount of free memory in the Java Virtual Machine.
   */
  const int64_t& getJreFreeMemory() const;
  /*
   * Returns the maximum amount of memory that the Java virtual machine will
   * attempt to use.
   */
  const int64_t& getJreMaxMemory() const;
  /*
   * Returns the total amount of memory in the Java virtual machine.
   */
  const int64_t& getJreTotalMemory() const;
  /*
   * Latest milestone that was signed off by the coordinator.
   */
  const std::string& getLatestMilestone() const;
  /*
   * Index of the latest milestone.
   */
  const int64_t& getLatestMilestoneIndex() const;
  /*
   * The latest milestone which is solid and is used for sending transactions.
   * For a milestone to become solid your local node must basically approve the
   * subtangle of coordinator-approved transactions, and have a consistent view
   * of all referenced transactions.
   */
  const std::string& getLatestSolidSubtangleMilestone() const;
  /*
   *  Index of the latest solid subtangle.
   */
  const int64_t& getLatestSolidSubtangleMilestoneIndex() const;
  /*
   * Number of neighbors you are directly connected with.
   */
  const int64_t& getNeighbors() const;
  /*
   * Packets which are currently queued up.
   */
  const int64_t& getPacketsQueueSize() const;
  /*
   * Current UNIX timestamp.
   */
  const int64_t& getTime() const;
  /*
   * Number of tips in the network.
   */
  const int64_t& getTips() const;
  /*
   * Transactions to request during syncing process.
   */
  const int64_t& getTransactionsToRequest() const;

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
