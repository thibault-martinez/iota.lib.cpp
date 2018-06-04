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
#include <json.hpp>

#include <iota/api/responses/get_node_info.hpp>

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

TEST(GetNodeInfoResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::GetNodeInfo res;
  json                              data;

  data["appName"]                            = "appname";
  data["appVersion"]                         = "appversion";
  data["jreAvailableProcessors"]             = 1;
  data["jreFreeMemory"]                      = 2;
  data["jreMaxMemory"]                       = 3;
  data["jreTotalMemory"]                     = 4;
  data["latestMilestone"]                    = "milestone";
  data["latestMilestoneIndex"]               = 5;
  data["latestSolidSubtangleMilestone"]      = "submilestone";
  data["latestSolidSubtangleMilestoneIndex"] = 6;
  data["neighbors"]                          = 7;
  data["packetsQueueSize"]                   = 8;
  data["time"]                               = 9;
  data["tips"]                               = 10;
  data["transactionsToRequest"]              = 11;

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
