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

#include <iota/constants.hpp>
#include <iota/types/big_int.hpp>
#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Types {

static std::vector<std::vector<int8_t>> trytesTrits = {
  { 0, 0, 0 },  { 1, 0, 0 },  { -1, 1, 0 },   { 0, 1, 0 },   { 1, 1, 0 },   { -1, -1, 1 },
  { 0, -1, 1 }, { 1, -1, 1 }, { -1, 0, 1 },   { 0, 0, 1 },   { 1, 0, 1 },   { -1, 1, 1 },
  { 0, 1, 1 },  { 1, 1, 1 },  { -1, -1, -1 }, { 0, -1, -1 }, { 1, -1, -1 }, { -1, 0, -1 },
  { 0, 0, -1 }, { 1, 0, -1 }, { -1, 1, -1 },  { 0, 1, -1 },  { 1, 1, -1 },  { -1, -1, 0 },
  { 0, -1, 0 }, { 1, -1, 0 }, { -1, 0, 0 }
};

size_t
tryteIndex(const char& tryte) {
  if (tryte == '9') {
    return 0;
  }
  // explicitly excluding '@' here, since by the calculation
  // below this would map to 0, but 0 is the index for '9'
  if (tryte == '@') {
    return -1;
  }
  return tryte - 'A' + 1;
}

bool
isValidTryte(const char& tryte) {
  return tryteIndex(tryte) < 27;
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
isValidAddress(const Trytes& s) {
  return (s.length() == AddressLength || s.length() == AddressLengthWithChecksum) &&
         isValidTrytes(s);
}

bool
isValidHash(const Trytes& s) {
  return s.length() == HashLength && isValidTrytes(s);
}

std::vector<int8_t>
tritsToBytes(const Trits& trits) {
  Types::BigInt decimal;
  decimal.fromTrits(trits);
  return decimal.toBytes();
}

Trits
bytesToTrits(const std::vector<int8_t>& bytes) {
  Types::BigInt decimal;
  decimal.fromBytes(bytes);
  return decimal.toTrits();
}

Trits
trytesToTrits(const Trytes& trytes) {
  Trits trits;
  for (unsigned i = 0; i < trytes.size(); i++) {
    size_t index = tryteIndex(trytes[i]);
    trits.push_back(trytesTrits[index][0]);
    trits.push_back(trytesTrits[index][1]);
    trits.push_back(trytesTrits[index][2]);
  }
  return trits;
}

Trytes
tritsToTrytes(const Trits& trits) {
  return tritsToTrytes(trits, trits.size());
}

Trytes
tritsToTrytes(const Trits& trits, size_t length) {
  Trytes trytes;
  for (size_t i = 0; i < length; i += 3) {
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
  Types::Trits trits;
  uint64_t     absoluteValue = std::abs(value);

  while (absoluteValue > 0) {
    int8_t remainder = absoluteValue % 3;
    absoluteValue    = absoluteValue / 3;

    if (remainder > 1) {
      remainder = -1;
      absoluteValue++;
    }

    trits.push_back(remainder);
  }

  if (value < 0) {
    std::transform(std::begin(trits), std::end(trits), std::begin(trits), std::negate<int>());
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
