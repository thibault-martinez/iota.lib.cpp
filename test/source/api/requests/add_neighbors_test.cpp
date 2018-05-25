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

#include <iota/api/requests/add_neighbors.hpp>

TEST(AddNeighborsRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::AddNeighbors req{ { "uri1", "uri2" } };

  EXPECT_EQ(req.getUris(), std::vector<std::string>({ "uri1", "uri2" }));
}

TEST(AddNeighborsRequest, GetUrisNonConst) {
  IOTA::API::Requests::AddNeighbors req{ { "uri1", "uri2" } };

  req.getUris().push_back("uri3");

  EXPECT_EQ(req.getUris(), std::vector<std::string>({ "uri1", "uri2", "uri3" }));
}

TEST(AddNeighborsRequest, SetUris) {
  IOTA::API::Requests::AddNeighbors req;

  req.setUris({ "uri1", "uri2" });

  EXPECT_EQ(req.getUris(), std::vector<std::string>({ "uri1", "uri2" }));
}

TEST(AddNeighborsRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::AddNeighbors req{ { "uri1", "uri2" } };
  json                                    data;

  req.serialize(data);

  EXPECT_EQ(data["command"], "addNeighbors");
  EXPECT_EQ(data["uris"], std::vector<std::string>({ "uri1", "uri2" }));
}
