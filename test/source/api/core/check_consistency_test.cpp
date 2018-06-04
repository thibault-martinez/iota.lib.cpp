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
#include <iota/api/responses/check_consistency.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Core, CheckConsistencyEmpty) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto res = api.checkConsistency({});

  EXPECT_EQ(res.getState(), true);
  EXPECT_EQ(res.getInfo(), "");
}

TEST(Core, CheckConsistencyInvalidTail) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(auto res = api.checkConsistency({ "invalid tail" }), IOTA::Errors::BadRequest,
                   "Invalid tails input")
}

TEST(Core, CheckConsistencyNotTail) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(auto res = api.checkConsistency({ BUNDLE_1_TRX_2_HASH }),
                   IOTA::Errors::BadRequest,
                   std::string("Invalid transaction, not a tail: " + BUNDLE_1_TRX_2_HASH).c_str())
}

TEST(Core, CheckConsistencyOneTail) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto res = api.checkConsistency({ BUNDLE_1_TRX_1_HASH });
  EXPECT_EQ(res.getState(), true);
  EXPECT_EQ(res.getInfo(), "");
}

TEST(Core, CheckConsistencyMultipleTails) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto res =
      api.checkConsistency({ BUNDLE_1_TRX_1_HASH, BUNDLE_1_TRX_1_HASH, BUNDLE_1_TRX_1_HASH });
  EXPECT_EQ(res.getState(), true);
  EXPECT_EQ(res.getInfo(), "");
}

TEST(Core, CheckConsistencyMissingTail) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(auto res = api.checkConsistency({ IOTA::EmptyHash }), IOTA::Errors::BadRequest,
                   std::string("Invalid transaction, missing: " + IOTA::EmptyHash).c_str())
}
