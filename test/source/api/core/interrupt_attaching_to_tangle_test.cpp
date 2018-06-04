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
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Core, InterruptAttachingToTangleRemotePow) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port(), false);

  IOTA::API::Responses::AttachToTangle attachToTangleRes;

  //! run attach in background
  std::thread t([&] {
    attachToTangleRes = api.attachToTangle(BUNDLE_2_TRX_1_TRUNK, BUNDLE_2_TRX_1_BRANCH, 18,
                                           { BUNDLE_2_TRX_1_TRYTES });
  });

  //! wait 2 sec to make sure thread started and request was sent
  std::this_thread::sleep_for(std::chrono::seconds(2));

  //! interrup
  api.interruptAttachingToTangle();

  //! wait for attach completion
  t.join();

  //! check that attach indeed failed
  EXPECT_EQ(attachToTangleRes.getTrytes().size(), 0UL);
}

TEST(Core, InterruptAttachingToTangleLocalPow) {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  IOTA::API::Responses::AttachToTangle attachToTangleRes;

  //! run attach in background
  std::thread t([&] {
    attachToTangleRes = api.attachToTangle(BUNDLE_2_TRX_1_TRUNK, BUNDLE_2_TRX_1_BRANCH, POW_LEVEL,
                                           { BUNDLE_2_TRX_1_TRYTES });
  });

  //! wait 2 sec to make sure thread started and request was sent
  std::this_thread::sleep_for(std::chrono::seconds(2));

  //! interrup
  api.interruptAttachingToTangle();

  //! wait for attach completion
  t.join();

  //! check that attach indeed failed
  EXPECT_EQ(attachToTangleRes.getTrytes().size(), 1UL);
}
