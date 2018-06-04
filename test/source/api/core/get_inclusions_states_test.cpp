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
#include <iota/api/responses/get_inclusion_states.hpp>
#include <iota/errors/illegal_state.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Core, GetInclusionStates) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true }));
}

TEST(Core, GetInclusionStatesNoTrx) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({}, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({}));
}

TEST(Core, GetInclusionStatesOlderMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  //! bundle 2 is initial funding which occured before bundle 1 (additional trx)
  auto res = api.getInclusionStates({ BUNDLE_1_TRX_1_HASH }, { BUNDLE_2_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false }));
}

TEST(Core, GetInclusionStatesNoMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, {});
                   , IOTA::Errors::IllegalState, "Empty list of tips")
}

TEST(Core, GetInclusionStatesInvalidMilestone) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  EXPECT_EXCEPTION(api.getInclusionStates({ BUNDLE_2_TRX_1_HASH }, { "hello" }),
                   IOTA::Errors::BadRequest, "Invalid tips input")
}

TEST(Core, GetInclusionStatesInvalidHash) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  auto hash = BUNDLE_2_TRX_1_HASH;
  hash[0]   = '9';

  auto res = api.getInclusionStates({ hash }, { BUNDLE_1_TRX_1_HASH });

  EXPECT_EQ(res.getStates(), std::vector<bool>({ false }));
}
