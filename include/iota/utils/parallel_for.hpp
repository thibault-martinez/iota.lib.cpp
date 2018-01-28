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

#include <atomic>
#include <future>
#include <iostream>
#include <vector>

namespace IOTA {

namespace Utils {

template <typename F>
void
parallel_for(int begin, int end, F fn) {
  std::atomic<int>               idx(begin);
  int                            num_cpus = std::thread::hardware_concurrency();
  std::vector<std::future<void>> futures(num_cpus);

  for (int cpu = 0; cpu != num_cpus; ++cpu) {
    futures[cpu] = std::async(std::launch::async, [&idx, end, &fn]() {
      for (;;) {
        int i = idx++;
        if (i >= end)
          break;
        fn(i);
      }
    });
  }
  for (int cpu = 0; cpu != num_cpus; ++cpu) {
    futures[cpu].get();
  }
}

template <typename F>
void
parallel_for(int threads, F fn) {
  int num_cpus = threads == 0 ? std::thread::hardware_concurrency() : threads;
  std::vector<std::future<void>> futures(num_cpus);

  for (int cpu = 0; cpu != num_cpus; ++cpu) {
    futures[cpu] = std::async(std::launch::async, fn, cpu);
  }
  for (int cpu = 0; cpu != num_cpus; ++cpu) {
    futures[cpu].get();
  }
}

}  // namespace Utils

}  // namespace IOTA
