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

bool
isValidTryte(const char& tryte) {
  return TryteAlphabet.find(tryte) != Types::Trytes::npos;
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
  size_t i = trits.size();
  // strip leading zeroes;
  while (i && !trits[i - 1]) {
    i--;
  }
  if (i == 0) {
    return std::vector<int8_t>(ByteHashLength, 0);
  }
  std::vector<uint32_t> data(1, 0);
  int8_t sign = trits[i - 1];
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
    switch (sign*trits[i - 1]) {
    case 1:
      // increment by 1
      for (size_t j = 0; j < data.size(); ++j) {
        data[j] = data[j] + 1;
        if (data[j]) {
          break;
        }
      }
      if (!data.back()) {
        data.push_back(1);
      }
      break;
    case -1:
      // decrement by 1
      uint8_t carry = 0;
      for (size_t j = 0; j < data.size(); ++j) {
        data[j] = data[j] + 0xffffffff + carry;
        carry = data[j] != 0xffffffff;
      }
      if (!data.back()) {
        data.pop_back();
      }
      break;
    }
  }

  uint32_t msdw = data.back();
  size_t j = 32;
  for (; j > 0 && !(msdw & (0x1 << (j - 1))); --j);
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
  uint32_t dw = 0;
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
  if (!bytes.size()) {
    return std::vector<int8_t>(TritHashLength, 0);
  }
  int8_t sign = bytes[0] >= 0 ? 1 : -1;
  size_t nr_bytes = bytes.size();
  size_t size = (nr_bytes + 3) >> 2;
  std::vector<uint32_t> div(size, 0);
  uint32_t dw = sign == 1 ? 0 : (0xffffffff << 8);
  for (size_t i = 0; i < nr_bytes; ++i) {
    dw |= static_cast<uint8_t>(bytes[i]);
    if (!((nr_bytes - i - 1) & 0x3)) {
      div[(nr_bytes - i - 1) >> 2] = dw;
      dw = 0;
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

  // strip leading zeroes
  while (!div.back()) {
    div.pop_back();
  }

  size_t j = div.size();
  while (j) {
    // divide by 3
    uint64_t rem = 0;
    for (size_t k = j; k > 0; --k) {
      rem <<= 32;
      rem += div[k - 1];
      div[k - 1] = static_cast<uint32_t>(rem / 3);
      rem %= 3;
    }

    if (!div.back()) {
      div.pop_back();
      j--;
    }

    if (rem > 1) {
      // increment by 1
      for (size_t k = 0; k < div.size(); ++k) {
        div[k] = div[k] + 1;
        if (div[k]) {
          break;
        }
      }
      if (!j || !div.back()) {
        div.push_back(1);
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
  for (unsigned i = 0; i < trytes.size(); i++) {
    unsigned int index = TryteAlphabet.find(trytes[i]);
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
tritsToTrytes(const Trits& trits, unsigned int length) {
  Trytes trytes;
  for (unsigned int i = 0; i < length; i += 3) {
    for (unsigned int j = 0; j < TryteAlphabet.size(); j++) {
      if (trytesTrits[j][0] == trits[i] && trytesTrits[j][1] == trits[i + 1] &&
          trytesTrits[j][2] == trits[i + 2]) {
        trytes += TryteAlphabet[j];
        break;
      }
    }
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
