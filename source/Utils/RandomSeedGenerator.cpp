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

#include <algorithm>
#include <random>

#include <Utils/RandomSeedGenerator.hpp>
#include <constants.hpp>

namespace IOTA {

namespace Utils {

RandomSeedGenerator::RandomSeedGenerator() {
}

RandomSeedGenerator::~RandomSeedGenerator() {
}

std::string
RandomSeedGenerator::operator()() {
  std::random_device                 rd;
  std::default_random_engine         dre(rd());
  std::uniform_int_distribution<int> uid(0, TryteAlphabetLength - 1);

  std::string str;
  str.reserve(SeedLength);
  std::generate_n(std::back_inserter(str), SeedLength, [&]() { return TryteAlphabet[uid(dre)]; });
  return str;
}

}  // namespace Utils

}  // namespace IOTA
