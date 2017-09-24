//
// MIT License
//
// Copyright (c) 2017 Thibault Martinez
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

#pragma once

#include <chrono>

namespace IOTA {

namespace Utils {

class StopWatch {
public:
  /**
   * StopWatch constructor: automatically starts the timer
   */
  StopWatch();

public:
  /**
   * restart timer
   */
  void restart();

  /**
   * stop the timer
   */
  void stop();

  /**
   * pause the timer
   */
  void pause();

  /**
   * resume the timer after pausing it
   */
  void resume();

  /**
   * @return Elapsed time in milliseconds.
   */
  std::chrono::milliseconds getElapsedTimeMiliSeconds();

  /**
   * @return Elapsed time in seconds.
   */
  std::chrono::seconds getElapsedTimeSeconds();

  /**
   * @return Elapsed time in minutes.
   */
  std::chrono::minutes getElapsedTimeMinutes();

  /**
   * @return Elapsed time in hours.
   */
  std::chrono::hours getElapsedTimeHours();

public:
  /**
   * @return Current ts
   */
  std::chrono::milliseconds now();

private:
  /**
   * time at which the timer started
   */
  std::chrono::milliseconds startTime_;

  /**
   * whether the timer is running or not
   */
  bool running_;

  /**
   * current tick when pausing timer
   */
  std::chrono::milliseconds currentTime_;
};

}  // namespace Utils

}  // namespace IOTA
