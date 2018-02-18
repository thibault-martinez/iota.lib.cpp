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
#include <iota/crypto/checksum.hpp>
#include <iota/errors/bad_request.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/input.hpp>
#include <iota/models/transfer.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Extended, SendTransfer) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 4UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true }));
}

TEST(Extended, SendTransferNoMessage) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 4UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true }));
}

TEST(Extended, SendTransferInvalidTransferAddress) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { "invalid__", 42, "TESTMSG", "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, SendTransferInvalidTransferMessage) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "invalid__",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, SendTransferInvalidTransferTag) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "invalid__" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Invalid Transfer");
}

TEST(Extended, SendTransferNotEnoughFund) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer              transfer  = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM,
                                      ACCOUNT_5_ADDRESS_1_FUND + 1, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Not enough balance");
}

TEST(Extended, SendTransferZeroTransfer) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 0, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 1UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true }));
}

TEST(Extended, SendTransferInvalidRemainderAddress) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(
      api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs, "invalid__"),
      IOTA::Errors::IllegalState, "Invalid Remainder");
}

TEST(Extended, SendTransferInvalidSeed) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer("invalid__", 2, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Invalid Seed");
}

TEST(Extended, SendTransferNoInput) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  std::vector<IOTA::Models::Input> inputs = {};

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 4UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true }));
}

TEST(Extended, SendTransferNoRemainderAddress) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs, "");

  ASSERT_EQ(res.getSuccessfully().size(), 4UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true }));
}

TEST(Extended, SendTransferSecurity) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 3 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 5UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true, true }));
}

TEST(Extended, SendTransferLongMessage) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = {
    ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42,
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZ",
    "TESTTAG99999999999999999999"
  };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  auto res = api.sendTransfer(ACCOUNT_5_SEED, 2, 27, POW_LEVEL, transfers, inputs,
                              ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM);

  ASSERT_EQ(res.getSuccessfully().size(), 5UL);
  EXPECT_EQ(res.getSuccessfully(), std::vector<bool>({ true, true, true, true, true }));
}

TEST(Extended, SendTransferInvalidSecurity) {
  IOTA::API::Extended api(get_proxy_host(), get_proxy_port(), true, 380);

  IOTA::Models::Transfer transfer = { ACCOUNT_5_ADDRESS_2_HASH_WITHOUT_CHECKSUM, 42, "TESTMSG",
                                      "TESTTAG99999999999999999999" };
  std::vector<IOTA::Models::Transfer> transfers = { transfer };

  IOTA::Models::Input input = { ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM, ACCOUNT_5_ADDRESS_1_FUND,
                                0, 2 };
  std::vector<IOTA::Models::Input> inputs = { input };

  EXPECT_EXCEPTION(api.sendTransfer(ACCOUNT_5_SEED, 42, 27, POW_LEVEL, transfers, inputs,
                                    ACCOUNT_5_ADDRESS_1_HASH_WITHOUT_CHECKSUM),
                   IOTA::Errors::IllegalState, "Invalid Security Level");
}
