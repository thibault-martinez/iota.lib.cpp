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
#include <iota/api/responses/attach_to_tangle.hpp>
#include <iota/api/responses/get_transactions_to_approve.hpp>
#include <iota/models/bundle.hpp>
#include <iota/utils/stop_watch.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Core, AttachToTangleRemotePowOneTx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port(), false);

  IOTA::Models::Bundle b;
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.finalize();
  b.addTrytes({ EMPTY_SIGNATURE_FRAGMENT });
  auto tx  = b[0].toTrytes();
  auto tta = api.getTransactionsToApprove(27);
  auto att =
      api.attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(), POW_LEVEL, { tx });
  auto trytes = att.getTrytes()[0];
  api.storeTransactions({ trytes });
}

TEST(Core, AttachToTangleLocalPowOneTx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::Models::Bundle b;
  b.addTransaction(
      { ACCOUNT_4_ADDRESS_1_HASH, 0, IOTA::EmptyTag, IOTA::Utils::StopWatch::now().count() });
  b.finalize();
  b.addTrytes({ EMPTY_SIGNATURE_FRAGMENT });
  auto tx  = b[0].toTrytes();
  auto tta = api.getTransactionsToApprove(27);
  auto att =
      api.attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(), POW_LEVEL, { tx });
  auto trytes = att.getTrytes()[0];
  api.storeTransactions({ trytes });
}

TEST(Core, AttachToTangleRemotePowManyTx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port(), false);

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
  auto tx  = b[0].toTrytes();
  auto tta = api.getTransactionsToApprove(27);
  auto att =
      api.attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(), POW_LEVEL, { tx });
  auto trytes = att.getTrytes()[0];
  api.storeTransactions({ trytes });
}

TEST(Core, AttachToTangleLocalPowManyTx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

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
  auto tx  = b[0].toTrytes();
  auto tta = api.getTransactionsToApprove(27);
  auto att =
      api.attachToTangle(tta.getTrunkTransaction(), tta.getBranchTransaction(), POW_LEVEL, { tx });
  auto trytes = att.getTrytes()[0];
  api.storeTransactions({ trytes });
}
