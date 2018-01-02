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

#include <iota/utils/stop_watch.hpp>

namespace IOTA {

namespace Utils {

StopWatch::StopWatch() {
  restart();
}

void
StopWatch::restart() {
  startTime_ = now();
  running_   = true;
}

std::chrono::milliseconds
StopWatch::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
}

void
StopWatch::pause() {
  if (!running_) {
    return;
  }

  currentTime_ = getElapsedTimeMilliSeconds();
  running_     = false;
}

void
StopWatch::resume() {
  if (running_) {
    return;
  }

  running_   = true;
  startTime_ = now() - currentTime_;
}

std::chrono::milliseconds
StopWatch::getElapsedTimeMilliSeconds() const {
  if (running_) {
    return now() - startTime_;
  }

  return currentTime_;
}

std::chrono::seconds
StopWatch::getElapsedTimeSeconds() const {
  return std::chrono::duration_cast<std::chrono::seconds>(getElapsedTimeMilliSeconds());
}

}  // namespace Utils

}  // namespace IOTA
