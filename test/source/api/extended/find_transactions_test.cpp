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

#include <iota/api/extended.hpp>
#include <iota/errors/illegal_state.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, FindTransactionsByAddresses) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByAddresses({ BUNDLE_1_TRX_1_ADDRESS });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByAddressesInvalidAddress) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByAddresses({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid addresses input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, FindTransactionsByTags) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByTags({ BUNDLE_1_TRX_1_TAG });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByApprovees) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByApprovees({ BUNDLE_1_TRX_2_HASH });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByApproveesInvalidApprovee) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByApprovees({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid approvees input")

  EXPECT_GE(res.getDuration(), 0);
}

TEST(Extended, FindTransactionsByBundles) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  auto res = api.findTransactionsByBundles({ BUNDLE_1_HASH });

  EXPECT_FALSE(res.getHashes().empty());
}

TEST(Extended, FindTransactionsByBundlesInvalidBundle) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  IOTA::API::Responses::FindTransactions res;

  EXPECT_EXCEPTION(res = api.findTransactionsByBundles({ "9999" }), IOTA::Errors::BadRequest,
                   "Invalid bundles input")

  EXPECT_GE(res.getDuration(), 0);
}
