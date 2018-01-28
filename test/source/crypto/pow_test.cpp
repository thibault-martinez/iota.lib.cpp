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
#include <iota/crypto/pow.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Pow, OneThread1) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = BUNDLE_1_TRX_1_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14, 1);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, OneThread2) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = BUNDLE_1_TRX_2_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14, 1);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, OneThread3) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = BUNDLE_1_TRX_3_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14, 1);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, OneThread4) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = BUNDLE_1_TRX_4_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14, 1);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, MaxThreads1) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = ACCOUNT_2_BUNDLE_1_TRX_1_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, MaxThreads2) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = ACCOUNT_2_BUNDLE_2_TRX_1_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, MaxThreads3) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = ACCOUNT_2_BUNDLE_3_TRX_1_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}

TEST(Pow, MaxThreads4) {
  IOTA::API::Core   api(get_proxy_host(), get_proxy_port());
  IOTA::Crypto::Pow p;
  auto              tx = ACCOUNT_2_BUNDLE_4_TRX_1_TRYTES;

  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, IOTA::NonceLength, '9');
  auto nonce = p(tx, 14);
  tx.replace(IOTA::TrxTrytesLength - IOTA::NonceLength, IOTA::NonceLength, nonce);
  EXPECT_NO_THROW(api.storeTransactions({ tx }));
}
