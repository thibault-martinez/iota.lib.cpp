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

#include <stdint.h>

#include <iota/types/big_int.hpp>

#define swap_u32(u32)                                                                    \
  (((unsigned long int)(u32) >> 24) | (((unsigned long int)(u32) << 8) & 0x00FF0000UL) | \
   (((unsigned long int)(u32) >> 8) & 0x0000FF00UL) | ((unsigned long int)(u32) << 24))

// base of the ternary system
#define BASE 3

namespace IOTA {

namespace Types {

// the middle of the domain described by 242 trits, i.e. \sum_{k=0}^{241} 3^k
static constexpr uint32_t HALF_3[WordHashLength] = {
  0xa5ce8964, 0x9f007669, 0x1484504f, 0x3ade00d9, 0x0c24486e, 0x50979d57,
  0x79a4c702, 0x48bbae36, 0xa9f6808b, 0xaa06a805, 0xa87fabdf, 0x5e69ebef
};

// the two's complement of HALF_3_u, i.e. ~HALF_3_u + 1
static constexpr uint32_t NEG_HALF_3[WordHashLength] = { 0x5a31769c, 0x60ff8996, 0xeb7bafb0,
                                                         0xc521ff26, 0xf3dbb791, 0xaf6862a8,
                                                         0x865b38fd, 0xb74451c9, 0x56097f74,
                                                         0x55f957fa, 0x57805420, 0xa1961410 };

// representing the value of the highes trit in the feasible domain, i.e 3^242
static constexpr uint32_t LAST_TRIT[WordHashLength] = { 0x4b9d12c9, 0x3e00ecd3, 0x2908a09f,
                                                        0x75bc01b2, 0x184890dc, 0xa12f3aae,
                                                        0xf3498e04, 0x91775c6c, 0x53ed0116,
                                                        0x540d500b, 0x50ff57bf, 0xbcd3d7df };

static inline bool
addcarry_u32(uint32_t *r, uint32_t a, uint32_t b, bool c_in) {
  const uint32_t sum   = a + b + (c_in ? 1 : 0);
  const bool     carry = (sum < a) || (c_in && (sum <= a));

  *r = sum;
  return carry;
}

Bigint::Bigint() : data{ 0 } {
}

Bigint::~Bigint() {
}

void
Bigint::fromTrits(const Trits &trits) {
  unsigned int ms_index = 0;  // initialy there is no most significant word >0
  std::memset(data, 0, WordHashLength * sizeof(data[0]));

  // ignore the 243th trit, as it cannot be fully represented in 48 bytes
  for (unsigned int i = TritHashLength - 1; i-- > 0;) {
    // convert to non-balanced ternary
    const uint8_t trit = trits[i] + 1;

    const uint32_t carry = mul(BASE, ms_index);
    if (carry > 0) {
      // if there is carry we need to use the next higher byte
      data[++ms_index] = carry;
    }

    if (trit == 0) {
      // nothing to add
      continue;
    }

    const unsigned int last_changed_index = add_u32(trit);
    if (last_changed_index > ms_index) {
      ms_index = last_changed_index;
    }
  }

  // convert to balanced ternary using two's complement
  if (cmp(HALF_3) >= 0) {
    sub(data, HALF_3);
  } else {
    // equivalent to bytes := ~(HALF_3 - bytes) + 1
    add(NEG_HALF_3, data);
  }
}

void
Bigint::fromBytes(const std::vector<int8_t> &bytes) {
  const uint32_t *p = (const uint32_t *)bytes.data();

  // reverse word order
  for (unsigned int i = WordHashLength; i-- > 0;) {
    // convert byte order if necessary
    data[i] = swap_u32(*p);
    p++;
  }
}

Trits
Bigint::toTrits() {
  Trits trits(TritHashLength);
  // the two's complement represention is only correct, if the number fits
  // into 48 bytes, i.e. has the 243th trit set to 0
  set_last_trit_zero();

  // convert to the (positive) number representing non-balanced ternary
  if (is_negative()) {
    sub(data, NEG_HALF_3);
  } else {
    add(data, HALF_3);
  }

  // ignore the 243th trit, as it cannot be fully represented in 48 bytes
  for (unsigned int i = 0; i < TritHashLength - 1; i++) {
    const uint32_t rem = div(BASE);
    trits[i]           = rem - 1;  // convert back to balanced
  }
  // set the last trit to zero for consistency
  trits[TritHashLength - 1] = 0;
  return trits;
}

std::vector<int8_t>
Bigint::toBytes() const {
  std::vector<int8_t> bytes(ByteHashLength);
  uint32_t *          p = (uint32_t *)bytes.data();

  // reverse word order
  for (unsigned int i = WordHashLength; i-- > 0;) {
    // convert byte order if necessary
    *p++ = swap_u32(data[i]);
  }
  return bytes;
}

/**
 * Private methods.
 */

bool
Bigint::is_negative() const {
  // whether the most significant bit of the most significant byte is set
  return (data[WordHashLength - 1] >> (sizeof(data[0]) * 8 - 1) != 0);
}

uint32_t
Bigint::mul(uint8_t factor, unsigned int ms_index) {
  uint32_t carry = 0;

  for (unsigned int i = 0; i <= ms_index; i++) {
    const uint64_t v = (uint64_t)factor * data[i] + carry;

    carry   = v >> 32;
    data[i] = v & 0xFFFFFFFF;
  }

  return carry;
}

uint32_t
Bigint::div(uint8_t divisor) {
  uint32_t remainder = 0;

  for (unsigned int i = WordHashLength; i-- > 0;) {
    const uint64_t v = (uint64_t)0x100000000 * remainder + data[i];

    remainder = v % divisor;
    data[i]   = (v / divisor) & 0xFFFFFFFF;
  }

  return remainder;
}

bool
Bigint::add(const uint32_t *a, const uint32_t *b) {
  bool carry = false;
  for (unsigned int i = 0; i < WordHashLength; i++) {
    carry = addcarry_u32(&data[i], a[i], b[i], carry);
  }

  return carry;
}

bool
Bigint::sub(const uint32_t *a, const uint32_t *b) {
  bool carry = true;
  for (unsigned int i = 0; i < WordHashLength; i++) {
    carry = addcarry_u32(&data[i], a[i], ~b[i], carry);
  }

  return carry;
}

unsigned int
Bigint::add_u32(uint32_t summand) {
  bool carry = addcarry_u32(&data[0], data[0], summand, false);
  if (carry == false) {
    return 0;
  }

  for (unsigned int i = 1; i < WordHashLength; i++) {
    carry = addcarry_u32(&data[i], data[i], 0, true);
    if (carry == false) {
      return i;
    }
  }

  // overflow
  return WordHashLength;
}

int
Bigint::cmp(const uint32_t *b) const {
  for (unsigned int i = WordHashLength; i-- > 0;) {
    if (data[i] < b[i]) {
      return -1;
    }
    if (data[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

bool
Bigint::set_last_trit_zero() {
  if (is_negative()) {
    if (cmp(NEG_HALF_3) < 0) {
      add(data, LAST_TRIT);
      return true;
    }
  } else {
    if (cmp(HALF_3) > 0) {
      sub(data, LAST_TRIT);
      return true;
    }
  }
  return false;
}

}  // namespace Types

}  // namespace IOTA
