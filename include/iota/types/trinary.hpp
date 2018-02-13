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

#include <cstdint>
#include <iostream>
#include <vector>

namespace IOTA {

namespace Types {

using Trits  = std::vector<int8_t>;
using Trytes = std::string;

/**
 * @return the index of the tryte character in the tryte alphabet
 * the range for valid tryte characters is [0, 26], 
 * for invalid characters -1 is returned
 */
int8_t tryteIndex(const char& tryte);

bool isValidTryte(const char& tryte);

/**
 * @return whether the given tryte is valid or not
 */
bool isValidTrytes(const Trytes& trytes);

/**
 * @return whether the given trit is valid or not
 */
bool isValidTrit(const int8_t& trit);

/**
 * @return whether the given address is valid or not
 */
bool isValidAddress(const Trytes& s);

/**
 * @return whether the given hash is valid or not
 */
bool isValidHash(const Trytes& s);

/**
 * Determines whether the specified array contains only valid hashes.
 *
 * @param hashes The hashes array to validate.
 * @return <code>true</code> the specified array contains only valid hashes; otherwise,
 * <code>false</code>.
 **/
bool isArrayOfHashes(const std::vector<Trytes>& hashes);

std::vector<int8_t> tritsToBytes(const Trits& trits);
Trits               bytesToTrits(const std::vector<int8_t>& bytes);

Trits  trytesToTrits(const Trytes& trytes);
Trytes tritsToTrytes(const Trits& trits);
Trytes tritsToTrytes(const Trits& trits, size_t length);

Types::Trits intToTrits(const int64_t& value);
Types::Trits intToTrits(const int64_t& value, std::size_t length);

template <typename T>
T
tritsToInt(const Trits& trits) {
  T res = 0;

  for (int i = trits.size() - 1; i >= 0; --i) {
    res = res * 3 + trits[i];
  }

  return res;
}

}  // namespace Types

}  // namespace IOTA
