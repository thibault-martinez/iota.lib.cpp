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
#include <iota/api/responses/get_transactions_to_approve.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Core, GetTransactionsToApprove) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTransactionsToApprove(27);

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getTrunkTransaction()));
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getBranchTransaction()));
}

TEST(Core, GetTransactionsToApproveWithReference) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());
  auto            res = api.getTransactionsToApprove(27, BUNDLE_1_TRX_1_HASH);

  EXPECT_GE(res.getDuration(), 0);
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getTrunkTransaction()));
  EXPECT_TRUE(IOTA::Types::isValidHash(res.getBranchTransaction()));
}

TEST(Core, GetTransactionsToApproveInvalidReference) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(auto res = api.getTransactionsToApprove(27, "ref");
                   , IOTA::Errors::BadRequest, "Invalid reference input")
}
