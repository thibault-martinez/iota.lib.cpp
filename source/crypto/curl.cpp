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

#include <iota/crypto/curl.hpp>
#include <iota/errors/crypto.hpp>

namespace IOTA {

namespace Crypto {

int Curl::TruthTable[] = { 1, 0, -1, 2, 1, -1, 0, 2, -1, 1, 0 };

Curl::Curl() : state_(StateLength, 0), scratchpad_(StateLength, 0) {
}

void
Curl::reset() {
  state_ = std::vector<int8_t>(StateLength, 0);
}

void
Curl::absorb(const Types::Trits& trits, std::size_t offset, std::size_t length) {
  if (length == 0) {
    length = trits.size();
  }

  if (length % TritHashLength != 0) {
    throw Errors::Crypto("Curl::absorb failed: illegal length");
  }

  do {
    arrayCopy<int8_t>(trits.cbegin() + offset, state_.begin(),
                      length < TritHashLength ? length : TritHashLength);

    transform();

    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

void
Curl::squeeze(Types::Trits& trits, std::size_t offset, std::size_t length) {
  if (length == 0) {
    length = trits.size();
  }

  if (length % TritHashLength != 0) {
    throw Errors::Crypto("Curl::squeeze failed: illegal length");
  }

  do {
    arrayCopy<int8_t>(state_.cbegin(), trits.begin() + offset,
                      length < TritHashLength ? length : TritHashLength);

    transform();

    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

void
Curl::transform() {
  std::size_t scratchpadIndex      = 0;
  std::size_t prev_scratchpadIndex = 0;

  for (std::size_t round = 0; round < NumberOfRounds; round++) {
    arrayCopy<int8_t>(state_.cbegin(), scratchpad_.begin(), StateLength);

    for (std::size_t stateIndex = 0; stateIndex < StateLength; stateIndex++) {
      prev_scratchpadIndex = scratchpadIndex;
      scratchpadIndex += (scratchpadIndex < 365 ? 364 : -365);

      state_[stateIndex] =
          TruthTable[scratchpad_[prev_scratchpadIndex] + (scratchpad_[scratchpadIndex] << 2) + 5];
    }
  }
}

}  // namespace Crypto

}  // namespace IOTA
