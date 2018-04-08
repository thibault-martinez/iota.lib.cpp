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

#include <gtest/gtest.h>

#include <iota/api/responses/get_node_info.hpp>
#include <iota/utils/json.hpp>

TEST(GetNodeInfoResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetAppName) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setAppName("edited");

  EXPECT_EQ(res.getAppName(), "edited");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetAppVersion) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setAppVersion("edited");

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "edited");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetLatestMilestone) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setLatestMilestone("edited");

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "edited");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetLatestSolidSubtangleMilestone) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setLatestSolidSubtangleMilestone("edited");

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "edited");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetJreAvailableProcessors) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setJreAvailableProcessors(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 42);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetJreFreeMemory) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setJreFreeMemory(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 42);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetJreMaxMemory) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setJreMaxMemory(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 42);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetJreTotalMemory) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setJreTotalMemory(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 42);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetLatestMilestoneIndex) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setLatestMilestoneIndex(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 42);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetLatestSolidSubtangleMilestoneIndex) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setLatestSolidSubtangleMilestoneIndex(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 42);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetNeighbors) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setNeighbors(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 42);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetPacketsQueueSize) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setPacketsQueueSize(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 42);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetTime) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setTime(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 42);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetTips) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setTips(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 42);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, SetTransactionsToRequest) {
  IOTA::API::Responses::GetNodeInfo res{
    "appname", "appversion", 1, 2, 3, 4, "milestone", 5, "submilestone", 6, 7, 8, 9, 10, 11
  };

  res.setTransactionsToRequest(42);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 42);

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(GetNodeInfoResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::GetNodeInfo res;
  IOTA::Utils::json                 data;

  data.set("appName", "appname");
  data.set("appVersion", "appversion");
  data.set("jreAvailableProcessors", 1);
  data.set("jreFreeMemory", 2);
  data.set("jreMaxMemory", 3);
  data.set("jreTotalMemory", 4);
  data.set("latestMilestone", "milestone");
  data.set("latestMilestoneIndex", 5);
  data.set("latestSolidSubtangleMilestone", "submilestone");
  data.set("latestSolidSubtangleMilestoneIndex", 6);
  data.set("neighbors", 7);
  data.set("packetsQueueSize", 8);
  data.set("time", 9);
  data.set("tips", 10);
  data.set("transactionsToRequest", 11);

  res.deserialize(data);

  EXPECT_EQ(res.getAppName(), "appname");
  EXPECT_EQ(res.getAppVersion(), "appversion");
  EXPECT_EQ(res.getJreAvailableProcessors(), 1);
  EXPECT_EQ(res.getJreFreeMemory(), 2);
  EXPECT_EQ(res.getJreMaxMemory(), 3);
  EXPECT_EQ(res.getJreTotalMemory(), 4);
  EXPECT_EQ(res.getLatestMilestone(), "milestone");
  EXPECT_EQ(res.getLatestMilestoneIndex(), 5);
  EXPECT_EQ(res.getLatestSolidSubtangleMilestone(), "submilestone");
  EXPECT_EQ(res.getLatestSolidSubtangleMilestoneIndex(), 6);
  EXPECT_EQ(res.getNeighbors(), 7);
  EXPECT_EQ(res.getPacketsQueueSize(), 8);
  EXPECT_EQ(res.getTime(), 9);
  EXPECT_EQ(res.getTips(), 10);
  EXPECT_EQ(res.getTransactionsToRequest(), 11);

  EXPECT_EQ(res.getDuration(), 0);
}
