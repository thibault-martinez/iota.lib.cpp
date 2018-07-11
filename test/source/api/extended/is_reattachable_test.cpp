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
#include <iota/api/responses/send_transfer.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/address.hpp>
#include <iota/models/seed.hpp>
#include <iota/models/transfer.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, IsReattachable) {
  auto api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };

  auto unconfirmedTransactionAddr = IOTA::Models::Address{ ACCOUNT_5_ADDRESS_1_HASH };
  auto noFundAddress              = IOTA::Models::Address{ ACCOUNT_5_ADDRESS_2_HASH };
  auto confirmedTransactionAddr   = IOTA::Models::Address{ ACCOUNT_2_ADDRESS_1_HASH };
  auto fundAddress                = IOTA::Models::Address{ ACCOUNT_4_ADDRESS_1_HASH };

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH, 42, "TESTMSG", "TESTTAG" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Address input = { ACCOUNT_5_ADDRESS_1_HASH, ACCOUNT_5_ADDRESS_1_FUND, 0, 2 };
  std::vector<IOTA::Models::Address> inputs = { input };

  api.sendTransfer(ACCOUNT_5_SEED, 3, POW_LEVEL, transfers, inputs, ACCOUNT_5_ADDRESS_1_HASH);

  EXPECT_EQ(api.isReattachable({ unconfirmedTransactionAddr, noFundAddress,
                                 confirmedTransactionAddr, fundAddress }),
            std::vector<bool>({ true, true, false, true }));
}
