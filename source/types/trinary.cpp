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

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>

#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/types/big_int.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Types {

static constexpr std::array<std::array<int8_t, 3>, TryteAlphabetLength> trytesTrits{
  { { { 0, 0, 0 } },   { { 1, 0, 0 } },   { { -1, 1, 0 } },  { { 0, 1, 0 } },   { { 1, 1, 0 } },
    { { -1, -1, 1 } }, { { 0, -1, 1 } },  { { 1, -1, 1 } },  { { -1, 0, 1 } },  { { 0, 0, 1 } },
    { { 1, 0, 1 } },   { { -1, 1, 1 } },  { { 0, 1, 1 } },   { { 1, 1, 1 } },   { { -1, -1, -1 } },
    { { 0, -1, -1 } }, { { 1, -1, -1 } }, { { -1, 0, -1 } }, { { 0, 0, -1 } },  { { 1, 0, -1 } },
    { { -1, 1, -1 } }, { { 0, 1, -1 } },  { { 1, 1, -1 } },  { { -1, -1, 0 } }, { { 0, -1, 0 } },
    { { 1, -1, 0 } },  { { -1, 0, 0 } } }
};

int8_t
tryteIndex(const char& tryte) {
  if (tryte == '9') {
    return 0;
  }
  if ('A' <= tryte && tryte <= 'Z') {
    return tryte - 'A' + 1;
  }
  return -1;
}

bool
isValidTryte(const char& tryte) {
  return tryteIndex(tryte) >= 0;
}

bool
isValidTrytes(const Trytes& trytes) {
  return std::find_if_not(trytes.begin(), trytes.end(), &isValidTryte) == trytes.end();
}

bool
isArrayOfHashes(const std::vector<Trytes>& hashes) {
  for (const auto& hash : hashes) {
    if (hash.length() != SeedLength && hash.length() != SeedLengthWithChecksum) {
      return false;
    }

    if (!isValidTrytes(hash)) {
      return false;
    }
  }

  return true;
}

bool
isValidHash(const Trytes& s) {
  return s.length() == HashLength && isValidTrytes(s);
}

Trytes
charToTrytes(const char c) {
  return Trytes{ TryteAlphabet[c % 27], TryteAlphabet[c / 27] };
}

Trytes
stringToTrytes(const std::string& str) {
  Trytes t;
  for (const auto& c : str) {
    t += charToTrytes(c);
  }
  return t;
}

std::string
trytesToString(const Trytes& trytes) {
  if (trytes.size() % 2 != 0)
    throw Errors::IllegalState("Odd number of trytes provided");

  std::string str;
  for (size_t i = 0; i < trytes.size(); i += 2) {
    str += TryteAlphabet.find(trytes[i]) + TryteAlphabet.find(trytes[i + 1]) * 27;
  }
  return str;
}

std::vector<int8_t>
tritsToBytes(const Trits& trits) {
  Bigint b;

  b.fromTrits(trits);
  return b.toBytes();
}

Trits
bytesToTrits(const std::vector<int8_t>& bytes) {
  Bigint b;

  b.fromBytes(bytes);
  return b.toTrits();
}

Trits
trytesToTrits(const Trytes& trytes) {
  Trits trits;
  trits.reserve(trytes.size() * 3);
  for (std::size_t i = 0; i < trytes.size(); i++) {
    std::size_t index = tryteIndex(trytes[i]);
    trits.insert(std::end(trits), std::begin(trytesTrits[index]), std::end(trytesTrits[index]));
  }
  return trits;
}

Trytes
tritsToTrytes(const Trits& trits) {
  return tritsToTrytes(trits, trits.size());
}

Trytes
tritsToTrytes(const Trits& trits, std::size_t length) {
  Trytes trytes;
  for (std::size_t i = 0; i < length; i += 3) {
    int8_t idx = trits[i] + trits[i + 1] * 3 + trits[i + 2] * 9;
    if (idx < 0) {
      idx += TryteAlphabetLength;
    }
    trytes += TryteAlphabet[idx];
  }
  return trytes;
}

Types::Trits
intToTrits(const int64_t& value) {
  if (value == 0)
    return {};

  Types::Trits trits;
  int          sign          = (value > 0) - (value < 0);
  uint64_t     absoluteValue = value * sign;

  // pre-computed log3(e)
  static const double log3e = 0.91023922662683739361;
  // predict number of digits of value in base 3 with basic logarithms
  const int size = std::ceil(std::log(absoluteValue) * log3e) + 1;
  // reserving the right size will avoid reallocating in the loop, saving up time
  trits.reserve(size);
  while (absoluteValue > 0) {
    int8_t remainder = absoluteValue % 3;
    absoluteValue    = absoluteValue / 3;

    if (remainder > 1) {
      remainder = -1;
      absoluteValue++;
    }

    trits.push_back(remainder * sign);
  }

  return trits;
}

Types::Trits
intToTrits(const int64_t& value, std::size_t length) {
  auto res = intToTrits(value);

  res.resize(length, 0);

  return res;
}

}  // namespace Types

}  // namespace IOTA
