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

#include <iota/api/responses/were_addresses_spent_from.hpp>

TEST(WereAddressesSpentFromResponse, CtorShouldInitFields) {
  const IOTA::API::Responses::WereAddressesSpentFrom res{ std::vector<bool>(
      { true, false, true }) };

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true, false, true }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(WereAddressesSpentFromResponse, GetSetStates) {
  IOTA::API::Responses::WereAddressesSpentFrom res{ std::vector<bool>({ true, false, true }) };

  std::vector<bool> states = res.getStates();
  states.push_back(true);
  res.setStates(states);

  EXPECT_EQ(res.getStates(), std::vector<bool>({ true, false, true, true }));
  EXPECT_EQ(res.getDuration(), 0);
}

TEST(WereAddressesSpentFromResponse, DeserializeShouldSetFields) {
  IOTA::API::Responses::WereAddressesSpentFrom res;
  json                                         data;
  std::vector<bool>                            states;

  states.push_back(true);
  data["states"] = states;
  res.deserialize(data);
  EXPECT_EQ(res.getStates(), states);
}
