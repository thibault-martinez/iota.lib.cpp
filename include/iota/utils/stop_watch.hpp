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

#pragma once

#include <chrono>

namespace IOTA {

namespace Utils {

/**
 * Measures elapsed time.
 */
class StopWatch {
public:
  /**
   * StopWatch constructor: automatically starts the timer.
   */
  StopWatch();

public:
  /**
   * Restart timer.
   */
  void restart();

  /**
   * Pause the timer.
   */
  void pause();

  /**
   * Resume the timer after pausing it.
   */
  void resume();

  /**
   * @return Elapsed time in milliseconds.
   */
  std::chrono::milliseconds getElapsedTime() const;

public:
  /**
   * @return Current ts.
   */
  static std::chrono::milliseconds now();

private:
  /**
   * Time at which the timer started.
   */
  std::chrono::milliseconds startTime_;

  /**
   * Whether the timer is running or not.
   */
  bool running_;

  /**
   * Current tick when pausing timer.
   */
  std::chrono::milliseconds currentTime_;
};

}  // namespace Utils

}  // namespace IOTA
