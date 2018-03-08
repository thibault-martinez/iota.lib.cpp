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

#include <iota/types/trits.hpp>
#include <iota/types/trytes.hpp>

namespace IOTA {

namespace Types {

/**
 * @return the index of the tryte character in the tryte alphabet the range for valid tryte
 * characters is [0, 26], for invalid characters -1 is returned
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

/**
 * Conversion of an ascii character to trytes.
 *
 * How the conversion works:
 * 2 trytes === 1 ASCII character.
 * There are a total of 27 different tryte values: 9ABCDEFGHIJKLMNOPQRSTUVWXYZ.
 *
 * 1. We get the decimal value of an individual ASCII character.
 * 2. From the decimal value, we then derive the two tryte values by basically calculating the tryte
 * equivalent (e.g. 100 === 19 + 3 * 27)
 *    a. The first tryte value is the decimal value modulo 27 (27
 * trytes).
 *    b. The second value is the remainder (decimal value - first value), divided by 27
 * 3. The two values returned from Step 2. are then input as indices into the available values list
 * ('9ABCDEFGHIJKLMNOPQRSTUVWXYZ') to get the correct tryte value
 *
 * EXAMPLES
 *      Lets say we want to convert the ASCII character "Z".
 *        1. 'Z' has a decimal value of 90.
 *        2. 90 can be represented as 9 + 3 * 27. To make it simpler:
 *           a. First value: 90 modulo 27 is 9. This is now our first value
 *           b. Second value: (90 - 9) / 27 is 3. This is our second value.
 *        3. Our two values are now 9 and 3. To get the tryte value now we simply insert it as
 * indices into '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'
 *           a. The first tryte value is '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'[9] === "I"
 *           b. The second tryte value is '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'[3] === "C"
 *        Our tryte pair is "IC"
 *
 *      RESULT:
 *        The ASCII char "Z" is represented as "IC" in trytes.
 *
 * @param c The ascii encoded byte.
 *
 * @return The converted trytes.
 *
 */
Trytes charToTrytes(const char c);

/**
 * Encode an ASCII string to trytes.
 * Reverse operation from the trytesToString function.
 * 1 ASCII character = 2 trytes (see charToTrytes).
 *
 * @param str ASCII string to be encoded.
 *
 * @return The encoded trytes.
 */
Trytes stringToTrytes(const std::string& str);

/**
 * Decode trytes to ascii string.
 * Reverse operation from the stringToTrytes function.
 * 2 trytes == 1 ASCII character (see charToTrytes).
 *
 * @param trytes Trytes to be decoded.
 *
 * @return The decoded ASCII string.
 */
std::string trytesToString(const Trytes& trytes);

std::vector<int8_t> tritsToBytes(const Trits& trits);
Trits               bytesToTrits(const std::vector<int8_t>& bytes);

Trits  trytesToTrits(const Trytes& trytes);
Trytes tritsToTrytes(const Trits& trits);
Trytes tritsToTrytes(const Trits& trits, std::size_t length);

Types::Trits intToTrits(const int64_t& value);
Types::Trits intToTrits(const int64_t& value, std::size_t length);

template <typename T>
T
tritsToInt(const Trits& trits) {
  T res = 0;

  for (std::size_t i = trits.size(); i > 0; --i) {
    res = res * 3 + trits[i - 1];
  }

  return res;
}

}  // namespace Types

}  // namespace IOTA
