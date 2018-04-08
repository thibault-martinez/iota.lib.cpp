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

#include <iota/api/responses/base.hpp>
#include <iota/utils/json.hpp>

TEST(BaseResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::Base res{ 0 };

  EXPECT_EQ(res.getDuration(), 0);
}

TEST(BaseResponse, SetDuration) {
  IOTA::API::Responses::Base res;

  res.setDuration(42);

  EXPECT_EQ(res.getDuration(), 42);
}

TEST(BaseResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::Base res;
  IOTA::Utils::json          data;

  data.set("duration", 42);
  res.deserialize(data);
  EXPECT_EQ(res.getDuration(), 42);
}
