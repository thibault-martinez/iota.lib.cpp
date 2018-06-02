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
#include <iota/api/responses/base.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Core, BroadcastTransactionsEmpty) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.broadcastTransactions({ "" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsInvalidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_EXCEPTION(res = api.broadcastTransactions({ "INVALIDTRYTES" }), IOTA::Errors::BadRequest,
                   "Invalid trytes input")
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsValidTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.broadcastTransactions({ UNUSED_TRYTES_1 }));
  EXPECT_GE(res.getDuration(), 0);
}

TEST(Core, BroadcastTransactionsValidMultiTrytes) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::Base res;
  EXPECT_NO_THROW(res = api.broadcastTransactions(
                      { UNUSED_TRYTES_1, UNUSED_TRYTES_2, UNUSED_TRYTES_3, UNUSED_TRYTES_4 }));
  EXPECT_GE(res.getDuration(), 0);
}
