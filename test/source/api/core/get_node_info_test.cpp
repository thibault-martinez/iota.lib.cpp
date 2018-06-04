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

#include <iota/api/core.hpp>
#include <iota/api/responses/get_node_info.hpp>
#include <test/utils/configuration.hpp>

TEST(Core, GetNodeInfo) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getNodeInfo();

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_FALSE(res.getAppName().empty());
  EXPECT_FALSE(res.getAppVersion().empty());
  EXPECT_GE(res.getJreAvailableProcessors(), 0);
  EXPECT_GE(res.getJreFreeMemory(), 0);
  EXPECT_GE(res.getJreMaxMemory(), 0);
  EXPECT_GE(res.getJreTotalMemory(), 0);
  EXPECT_FALSE(res.getLatestMilestone().empty());
  EXPECT_GE(res.getLatestMilestoneIndex(), 0);
  EXPECT_FALSE(res.getLatestSolidSubtangleMilestone().empty());
  EXPECT_GE(res.getLatestSolidSubtangleMilestoneIndex(), 0);
  EXPECT_GE(res.getNeighbors(), 0);
  EXPECT_GE(res.getPacketsQueueSize(), 0);
  EXPECT_GE(res.getTime(), 0);
  EXPECT_GE(res.getTips(), 0);
  EXPECT_GE(res.getTransactionsToRequest(), 0);
}
