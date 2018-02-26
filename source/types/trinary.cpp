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

std::vector<int8_t>
tritsToBytes(const Trits& trits) {
  size_t i = trits.size();
  // strip leading zeroes;
  while (i && !trits[i - 1]) {
    i--;
  }
  if (i == 0) {
    return std::vector<int8_t>(ByteHashLength, 0);
  }
  std::vector<uint32_t> data(1, 0);
  int8_t                sign = trits[i - 1];
  for (; i > 0; --i) {
    // multiply by 3
    uint64_t sum = 0;
    for (size_t j = 0; j < data.size(); ++j) {
      sum += data[j] + (static_cast<uint64_t>(data[j]) << 1);
      data[j] = static_cast<uint32_t>(sum & 0xffffffff);
      sum >>= 32;
    }
    if (sum != 0) {
      data.push_back(static_cast<uint32_t>(sum & 0xffffffff));
    }
    switch (sign * trits[i - 1]) {
      case 1:
        // increment by 1
        for (size_t j = 0; j < data.size(); ++j) {
          data[j] = data[j] + 1;
          if (data[j]) {
            break;
          }
        }
        if (!data.back()) {
          // if the 32 most significant bits all got flipped to 0 by the increment (i.e. data
          // represented 2^(32*k) - 1, where k is the size of data), we need to expand data by the
          // carry
          // Note: data always represents a multiple of 3 and since 2^(32*k) - 1 = 4^(16*k) - 1 is
          // divisible by 3 for any k (by the fact of 4^n - 1 being divisible by 3 for any n), the
          // carry might be required for any k
          data.push_back(1);
        }
        break;
      case -1:
        // decrement by 1
        uint8_t carry = 0;
        for (size_t j = 0; j < data.size(); ++j) {
          data[j] = data[j] + 0xffffffff + carry;
          carry   = data[j] != 0xffffffff;
        }
        if (!data.back()) {
          data.pop_back();
        }
        break;
    }
  }

  uint32_t msdw = data.back();
  size_t   j    = 32;
  for (; j > 0 && !(msdw & (0x1 << (j - 1))); --j)
    ;
  size_t nr_bytes = ((data.size() - 1) << 2) + ((j + 7) >> 3);

  // negate two's complement if sign is negative
  if (sign == -1) {
    size_t i = 0;
    for (; i < data.size(); ++i) {
      data[i] = ~data[i] + 1;
      if (data[i]) {
        ++i;
        break;
      }
    }
    for (; i < data.size(); ++i) {
      data[i] = ~data[i];
    }
  }

  // read out the bytes
  std::vector<int8_t> bytes(nr_bytes);
  uint32_t            dw = 0;
  for (size_t i = 0; i < nr_bytes; ++i) {
    if (!(i & 0x3)) {
      dw = data[i >> 2];
    }
    bytes[nr_bytes - i - 1] = static_cast<int8_t>(dw & 0xff);
    dw >>= 8;
  }

  std::vector<int8_t> res(48, sign == 1 ? 0 : -1);
  std::copy(bytes.begin(), bytes.end(), res.begin() + ByteHashLength - nr_bytes);

  return res;
}

Trits
bytesToTrits(const std::vector<int8_t>& bytes) {
  int8_t                sign     = bytes.empty() || bytes[0] >= 0 ? 1 : -1;
  size_t                nr_bytes = bytes.size();
  size_t                j        = (nr_bytes + 3) >> 2;
  std::vector<uint32_t> div(j, 0);
  uint32_t              dw = sign == 1 ? 0 : (0xffffffff << 8);
  for (size_t i = 0; i < nr_bytes; ++i) {
    dw |= static_cast<uint8_t>(bytes[i]);
    if (!((nr_bytes - i - 1) & 0x3)) {
      div[(nr_bytes - i - 1) >> 2] = dw;
      dw                           = 0;
    }
    dw <<= 8;
  }

  // negate two's complement if sign is negative
  if (sign == -1) {
    size_t i = 0;
    for (; i < div.size(); ++i) {
      div[i] = ~div[i] + 1;
      if (div[i]) {
        ++i;
        break;
      }
    }
    for (; i < div.size(); ++i) {
      div[i] = ~div[i];
    }
  }

  std::vector<int8_t> trits;

  // strip leading zeros
  while (j && !div[j - 1]) {
    --j;
  }

  while (j) {
    // divide by 3
    uint64_t rem = 0;
    for (size_t k = j; k > 0; --k) {
      rem <<= 32;
      rem += div[k - 1];
      div[k - 1] = static_cast<uint32_t>(rem / 3);
      rem %= 3;
    }

    if (!div[j - 1]) {
      j--;
    }

    if (rem > 1) {
      // increment by 1
      for (size_t k = 0; k < j; ++k) {
        div[k] = div[k] + 1;
        if (div[k]) {
          break;
        }
      }
      if (!j || !div[j - 1]) {
        div[j] = 1;
        j++;
      }
      rem -= 3;
    }

    trits.push_back(sign * static_cast<int8_t>(rem));
  }

  trits.resize(TritHashLength, 0);
  return trits;
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
