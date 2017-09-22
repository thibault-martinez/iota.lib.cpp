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

#include <Utils/StopWatch.hpp>

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
StopWatch::stop() {
  running_ = false;
}

void
StopWatch::pause() {
  running_     = false;
  currentTime_ = getElapsedTimeMiliSeconds();
}

void
StopWatch::resume() {
  running_   = true;
  startTime_ = now() - currentTime_;
}

std::chrono::milliseconds
StopWatch::getElapsedTimeMiliSeconds() {
  if (!running_) {
    return {};
  }

  return now() - startTime_;
}

std::chrono::seconds
StopWatch::getElapsedTimeSeconds() {
  return std::chrono::duration_cast<std::chrono::seconds>(getElapsedTimeMiliSeconds());
}

std::chrono::minutes
StopWatch::getElapsedTimeMinutes() {
  return std::chrono::duration_cast<std::chrono::minutes>(getElapsedTimeMiliSeconds());
}

std::chrono::hours
StopWatch::getElapsedTimeHours() {
  return std::chrono::duration_cast<std::chrono::hours>(getElapsedTimeMiliSeconds());
}

}  // namespace Utils

}  // namespace IOTA
