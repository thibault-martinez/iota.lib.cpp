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

#include <iota/crypto/curl.hpp>
#include <iota/errors/crypto.hpp>

namespace IOTA {

namespace Crypto {

constexpr int Curl::TruthTable[];

Curl::Curl()
    : state_(StateLength, 0),
      stateLow_(StateLength, 0xFFFFFFFFFFFFFFFFL),
      stateHigh_(StateLength, 0xFFFFFFFFFFFFFFFFL),
      scratchpad_(StateLength, 0),
      scratchpadLow_(StateLength, 0),
      scratchpadHigh_(StateLength, 0) {
}

void
Curl::reset() {
  state_     = std::vector<int8_t>(StateLength, 0);
  stateLow_  = std::vector<int64_t>(StateLength, 0xFFFFFFFFFFFFFFFFL);
  stateHigh_ = std::vector<int64_t>(StateLength, 0xFFFFFFFFFFFFFFFFL);
}

void
Curl::absorb(const Types::Trits& trits, unsigned int offset, unsigned int length) {
  if (length == 0) {
    length = trits.size();
  }

  if (length % TritHashLength != 0) {
    throw Errors::Crypto("Curl::absorb failed: illegal length");
  }

  do {
    arrayCopy(trits, state_, offset, length < TritHashLength ? length : TritHashLength);
    transform();
    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

void
Curl::squeeze(Types::Trits& trits, unsigned int offset, unsigned int length) {
  if (length == 0) {
    length = trits.size();
  }

  if (length % TritHashLength != 0) {
    throw Errors::Crypto("Curl::squeeze failed: illegal length");
  }

  do {
    arrayCopy(state_, trits, offset, length < TritHashLength ? length : TritHashLength);
    transform();
    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

Types::Trits
Curl::getState() const {
  return Types::Trits{ state_ };
}

std::pair<std::vector<int64_t>, std::vector<int64_t>>
Curl::getPairedState() const {
  return { stateLow_, stateHigh_ };
}

void
Curl::transform() {
  int scratchpadIndex      = 0;
  int prev_scratchpadIndex = 0;

  for (int round = 0; round < NumberOfRounds; round++) {
    arrayCopy(state_, scratchpad_, 0, StateLength);

    for (int stateIndex = 0; stateIndex < StateLength; stateIndex++) {
      prev_scratchpadIndex = scratchpadIndex;
      scratchpadIndex += (scratchpadIndex < 365 ? 364 : -365);

      state_[stateIndex] =
          TruthTable[scratchpad_[prev_scratchpadIndex] + (scratchpad_[scratchpadIndex] << 2) + 5];
    }
  }
}

void
Curl::pairTransform() {
  int scratchpadIndex = 0;

  for (int round = 0; round < NumberOfRounds; round++) {
    arrayCopy(stateLow_, scratchpadLow_, 0, StateLength);
    arrayCopy(stateHigh_, scratchpadHigh_, 0, StateLength);

    for (int stateIndex = 0; stateIndex < StateLength; stateIndex++) {
      int64_t alpha = scratchpadLow_[scratchpadIndex];
      int64_t beta  = scratchpadHigh_[scratchpadIndex];
      int64_t gamma = scratchpadHigh_[scratchpadIndex += (scratchpadIndex < 365 ? 364 : -365)];
      int64_t delta = (alpha | (~gamma)) & (scratchpadLow_[scratchpadIndex] ^ beta);

      stateLow_[stateIndex]  = ~delta;
      stateHigh_[stateIndex] = (alpha ^ gamma) | delta;
    }
  }
}

void
Curl::absorb(const std::vector<int64_t>& rawLowTrits, const std::vector<int64_t>& rawHighTrits,
             int offset, unsigned int length) {
  do {
    arrayCopy(rawLowTrits, stateLow_, offset, length < TritHashLength ? length : TritHashLength);
    arrayCopy(rawHighTrits, stateHigh_, offset, length < TritHashLength ? length : TritHashLength);
    pairTransform();
    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

void
Curl::squeeze(std::vector<int64_t>& rawLowTrits, std::vector<int64_t>& rawHighTrits, int offset,
              unsigned int length) {
  do {
    arrayCopy(stateLow_, rawLowTrits, offset, length < TritHashLength ? length : TritHashLength);
    arrayCopy(stateHigh_, rawHighTrits, offset, length < TritHashLength ? length : TritHashLength);
    pairTransform();
    offset += TritHashLength;
  } while ((length -= TritHashLength) > 0);
}

}  // namespace Crypto

}  // namespace IOTA
