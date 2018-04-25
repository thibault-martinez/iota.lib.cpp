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
#include <iota/errors/bad_request.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/bundle.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, SendTrytesNothing) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  EXPECT_NO_THROW(api.sendTrytes({}, 27, POW_LEVEL));
}

TEST(Extended, SendTrytesEmpty) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.sendTrytes({ "" }, 27, POW_LEVEL), IOTA::Errors::IllegalState,
                   "Invalid transaction trytes");
}

TEST(Extended, SendTrytesInvalidTrytes) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.sendTrytes({ "INVALIDTRYTES" }, 27, POW_LEVEL), IOTA::Errors::IllegalState,
                   "Invalid transaction trytes");
}

TEST(Extended, SendTrytesOne) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  IOTA::Models::Bundle b;
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.finalize();
  b.addTrytes({ EMPTY_SIGNATURE_FRAGMENT });
  auto tx = b[0].toTrytes();
  EXPECT_NO_THROW(api.sendTrytes({ tx }, 27, POW_LEVEL));
}

TEST(Extended, SendTrytesMulti) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port());

  IOTA::Models::Bundle b;
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.finalize();
  b.addTrytes({ EMPTY_SIGNATURE_FRAGMENT });
  auto tx0 = b[0].toTrytes();
  auto tx1 = b[1].toTrytes();
  auto tx2 = b[2].toTrytes();
  auto tx3 = b[3].toTrytes();
  EXPECT_NO_THROW(api.sendTrytes({ tx0, tx1, tx2, tx3 }, 27, POW_LEVEL));
}
