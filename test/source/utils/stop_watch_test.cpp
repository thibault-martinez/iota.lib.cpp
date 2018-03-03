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

#include <thread>

#include <gtest/gtest.h>

#include <iota/utils/stop_watch.hpp>

TEST(StopWatch, CtorShouldStartTimer) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 1010);
}

TEST(StopWatch, NowShouldReturnCurrentTime) {
  IOTA::Utils::StopWatch s;

  auto current = std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now().time_since_epoch());
  auto res = std::chrono::duration_cast<std::chrono::seconds>(s.now());

  //! there might be a little delay in ms, but switching to seconds should give same
  EXPECT_TRUE(current == res || current + std::chrono::seconds(1) == res)
      << "Where current: " << current.count() << " and res: " << res.count();
}

TEST(StopWatch, NowShouldIncreaseOverTime) {
  IOTA::Utils::StopWatch s;

  auto res_before = std::chrono::duration_cast<std::chrono::seconds>(s.now());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  auto res_after = std::chrono::duration_cast<std::chrono::seconds>(s.now());

  //! there might be a little delay in ms, but switching to seconds should give same
  EXPECT_LE(res_before + std::chrono::seconds(1), res_after);
}

TEST(StopWatch, RestartShouldRestartTimer) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.restart();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 1010);
}

TEST(StopWatch, PauseShouldStopTimer) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.pause();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 1010);
}

TEST(StopWatch, MultiplePauseShouldNotReset) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.pause();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.pause();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 1010);
}

TEST(StopWatch, ResumeShouldResumePausedTimer) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.pause();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.resume();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 1990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 2010);
}

TEST(StopWatch, ResumeShouldDoNothingIfRunning) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  s.resume();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 1990);
  EXPECT_TRUE(s.getElapsedTime().count() <= 2010);
}

TEST(StopWatch, GetElapsedTimeMiliSeconds) {
  IOTA::Utils::StopWatch s;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_TRUE(s.getElapsedTime().count() >= 1000);
  EXPECT_TRUE(s.getElapsedTime().count() < 2000);
}
