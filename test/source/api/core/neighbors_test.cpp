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
#include <iota/api/responses/add_neighbors.hpp>
#include <iota/api/responses/get_neighbors.hpp>
#include <iota/api/responses/remove_neighbors.hpp>
#include <iota/models/neighbor.hpp>
#include <test/utils/configuration.hpp>

TEST(Core, AddRemoveAndGetNeighbors) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto resGetEmpty = api.getNeighbors();
  EXPECT_GE(resGetEmpty.getDuration(), 0);
  EXPECT_EQ(resGetEmpty.getNeighbors().size(), 0UL);

  auto resAdd = api.addNeighbors({ "udp://8.8.8.8:14265", "udp://8.8.8.5:14265" });
  EXPECT_GE(resAdd.getDuration(), 0);
  EXPECT_EQ(resAdd.getAddedNeighbors(), 2);

  auto resGetAfterAdd = api.getNeighbors();
  EXPECT_GE(resGetAfterAdd.getDuration(), 0);
  ASSERT_EQ(resGetAfterAdd.getNeighbors().size(), 2UL);
  EXPECT_EQ(resGetAfterAdd.getNeighbors()[0].getAddress(), "8.8.8.8:14265");
  EXPECT_EQ(resGetAfterAdd.getNeighbors()[1].getAddress(), "8.8.8.5:14265");

  auto resRemove = api.removeNeighbors({ "udp://8.8.8.8:14265", "udp://8.8.8.5:14265" });
  EXPECT_GE(resRemove.getDuration(), 0);
  EXPECT_EQ(resRemove.getRemovedNeighbors(), 2);

  auto resGetAfterRemove = api.getNeighbors();
  EXPECT_GE(resGetAfterRemove.getDuration(), 0);
  EXPECT_EQ(resGetAfterRemove.getNeighbors().size(), 0UL);
}
