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

#include <cstring>

#include <iota/crypto/pow.hpp>
#include <iota/types/trinary.hpp>
#include <iota/utils/parallel_for.hpp>

namespace IOTA {

namespace Crypto {

static constexpr int indices[] = {
  364, 728, 363, 727, 362, 726, 361, 725, 360, 724, 359, 723, 358, 722, 357, 721, 356, 720, 355,
  719, 354, 718, 353, 717, 352, 716, 351, 715, 350, 714, 349, 713, 348, 712, 347, 711, 346, 710,
  345, 709, 344, 708, 343, 707, 342, 706, 341, 705, 340, 704, 339, 703, 338, 702, 337, 701, 336,
  700, 335, 699, 334, 698, 333, 697, 332, 696, 331, 695, 330, 694, 329, 693, 328, 692, 327, 691,
  326, 690, 325, 689, 324, 688, 323, 687, 322, 686, 321, 685, 320, 684, 319, 683, 318, 682, 317,
  681, 316, 680, 315, 679, 314, 678, 313, 677, 312, 676, 311, 675, 310, 674, 309, 673, 308, 672,
  307, 671, 306, 670, 305, 669, 304, 668, 303, 667, 302, 666, 301, 665, 300, 664, 299, 663, 298,
  662, 297, 661, 296, 660, 295, 659, 294, 658, 293, 657, 292, 656, 291, 655, 290, 654, 289, 653,
  288, 652, 287, 651, 286, 650, 285, 649, 284, 648, 283, 647, 282, 646, 281, 645, 280, 644, 279,
  643, 278, 642, 277, 641, 276, 640, 275, 639, 274, 638, 273, 637, 272, 636, 271, 635, 270, 634,
  269, 633, 268, 632, 267, 631, 266, 630, 265, 629, 264, 628, 263, 627, 262, 626, 261, 625, 260,
  624, 259, 623, 258, 622, 257, 621, 256, 620, 255, 619, 254, 618, 253, 617, 252, 616, 251, 615,
  250, 614, 249, 613, 248, 612, 247, 611, 246, 610, 245, 609, 244, 608, 243, 607, 242, 606, 241,
  605, 240, 604, 239, 603, 238, 602, 237, 601, 236, 600, 235, 599, 234, 598, 233, 597, 232, 596,
  231, 595, 230, 594, 229, 593, 228, 592, 227, 591, 226, 590, 225, 589, 224, 588, 223, 587, 222,
  586, 221, 585, 220, 584, 219, 583, 218, 582, 217, 581, 216, 580, 215, 579, 214, 578, 213, 577,
  212, 576, 211, 575, 210, 574, 209, 573, 208, 572, 207, 571, 206, 570, 205, 569, 204, 568, 203,
  567, 202, 566, 201, 565, 200, 564, 199, 563, 198, 562, 197, 561, 196, 560, 195, 559, 194, 558,
  193, 557, 192, 556, 191, 555, 190, 554, 189, 553, 188, 552, 187, 551, 186, 550, 185, 549, 184,
  548, 183, 547, 182, 546, 181, 545, 180, 544, 179, 543, 178, 542, 177, 541, 176, 540, 175, 539,
  174, 538, 173, 537, 172, 536, 171, 535, 170, 534, 169, 533, 168, 532, 167, 531, 166, 530, 165,
  529, 164, 528, 163, 527, 162, 526, 161, 525, 160, 524, 159, 523, 158, 522, 157, 521, 156, 520,
  155, 519, 154, 518, 153, 517, 152, 516, 151, 515, 150, 514, 149, 513, 148, 512, 147, 511, 146,
  510, 145, 509, 144, 508, 143, 507, 142, 506, 141, 505, 140, 504, 139, 503, 138, 502, 137, 501,
  136, 500, 135, 499, 134, 498, 133, 497, 132, 496, 131, 495, 130, 494, 129, 493, 128, 492, 127,
  491, 126, 490, 125, 489, 124, 488, 123, 487, 122, 486, 121, 485, 120, 484, 119, 483, 118, 482,
  117, 481, 116, 480, 115, 479, 114, 478, 113, 477, 112, 476, 111, 475, 110, 474, 109, 473, 108,
  472, 107, 471, 106, 470, 105, 469, 104, 468, 103, 467, 102, 466, 101, 465, 100, 464, 99,  463,
  98,  462, 97,  461, 96,  460, 95,  459, 94,  458, 93,  457, 92,  456, 91,  455, 90,  454, 89,
  453, 88,  452, 87,  451, 86,  450, 85,  449, 84,  448, 83,  447, 82,  446, 81,  445, 80,  444,
  79,  443, 78,  442, 77,  441, 76,  440, 75,  439, 74,  438, 73,  437, 72,  436, 71,  435, 70,
  434, 69,  433, 68,  432, 67,  431, 66,  430, 65,  429, 64,  428, 63,  427, 62,  426, 61,  425,
  60,  424, 59,  423, 58,  422, 57,  421, 56,  420, 55,  419, 54,  418, 53,  417, 52,  416, 51,
  415, 50,  414, 49,  413, 48,  412, 47,  411, 46,  410, 45,  409, 44,  408, 43,  407, 42,  406,
  41,  405, 40,  404, 39,  403, 38,  402, 37,  401, 36,  400, 35,  399, 34,  398, 33,  397, 32,
  396, 31,  395, 30,  394, 29,  393, 28,  392, 27,  391, 26,  390, 25,  389, 24,  388, 23,  387,
  22,  386, 21,  385, 20,  384, 19,  383, 18,  382, 17,  381, 16,  380, 15,  379, 14,  378, 13,
  377, 12,  376, 11,  375, 10,  374, 9,   373, 8,   372, 7,   371, 6,   370, 5,   369, 4,   368,
  3,   367, 2,   366, 1,   365, 0
};

Types::Trytes
Pow::operator()(const Types::Trytes& trytes, int minWeightMagnitude, int threads) {
  IOTA::Types::Trits    trits = IOTA::Types::trytesToTrits(trytes);
  std::vector<uint64_t> stateLow(stateSize);
  std::vector<uint64_t> stateHigh(stateSize);
  IOTA::Types::Trytes   result;

  stop_ = false;

  initialize(stateLow.data(), stateHigh.data(), trits);

  Utils::parallel_for(
      threads, [this, stateLow, stateHigh, minWeightMagnitude, &result](uint32_t i, uint32_t) {
        uint64_t stateLowCpy[stateSize];
        uint64_t stateHighCpy[stateSize];

        std::memcpy(stateLowCpy, stateLow.data(), stateSize * sizeof(uint64_t));
        std::memcpy(stateHighCpy, stateHigh.data(), stateSize * sizeof(uint64_t));

        for (uint32_t j = 0; j < i; ++j) {
          increment(stateLowCpy, stateHighCpy, nonceOffset + TritHashLength / 9,
                    nonceOffset + (TritHashLength / 9) * 2);
        }

        auto trits = loop(stateLowCpy, stateHighCpy, minWeightMagnitude);
        if (!trits.empty())
          result = IOTA::Types::tritsToTrytes(trits);
      });
  return result;
}

void
Pow::initialize(uint64_t* stateLow, uint64_t* stateHigh, const IOTA::Types::Trits& trits) {
  for (int i = TritHashLength; i < stateSize; ++i) {
    stateLow[i]  = hBits;
    stateHigh[i] = hBits;
  }

  int      offset = 0;
  uint64_t scratchpadLow[stateSize];
  uint64_t scratchpadHigh[stateSize];
  for (unsigned int i = (TxLength - TritHashLength) / TritHashLength; i > 0; --i) {
    for (unsigned int j = 0; j < TritHashLength; j++) {
      switch (trits[offset++]) {
        case 0: {
          stateLow[j]  = hBits;
          stateHigh[j] = hBits;
          break;
        }
        case 1: {
          stateLow[j]  = lBits;
          stateHigh[j] = hBits;
          break;
        }
        case -1: {
          stateLow[j]  = hBits;
          stateHigh[j] = lBits;
          break;
        }
      }
    }

    transform(stateLow, stateHigh, scratchpadLow, scratchpadHigh);
  }

  for (unsigned int i = 0; i < nonceOffset; ++i) {
    switch (trits[offset++]) {
      case 0: {
        stateLow[i]  = hBits;
        stateHigh[i] = hBits;
        break;
      }
      case 1: {
        stateLow[i]  = lBits;
        stateHigh[i] = hBits;
        break;
      }
      case -1: {
        stateLow[i]  = hBits;
        stateHigh[i] = lBits;
      }
    }
  }

  stateLow[nonceOffset + 0]  = low0;
  stateHigh[nonceOffset + 0] = high0;
  stateLow[nonceOffset + 1]  = low1;
  stateHigh[nonceOffset + 1] = high1;
  stateLow[nonceOffset + 2]  = low2;
  stateHigh[nonceOffset + 2] = high2;
  stateLow[nonceOffset + 3]  = low3;
  stateHigh[nonceOffset + 3] = high3;
}

void
Pow::transform(uint64_t* stateLow, uint64_t* stateHigh, uint64_t* scratchpadLow,
               uint64_t* scratchpadHigh) {
  int scratchpadIndex = 0;
  for (int round = 0; round < numberOfRounds; ++round) {
    std::memcpy(scratchpadLow, stateLow, stateSize * sizeof(uint64_t));
    std::memcpy(scratchpadHigh, stateHigh, stateSize * sizeof(uint64_t));

    for (int stateIndex = 0; stateIndex < stateSize; ++stateIndex) {
      uint64_t alpha  = scratchpadLow[scratchpadIndex];
      uint64_t beta   = scratchpadHigh[scratchpadIndex];
      scratchpadIndex = indices[stateIndex];
      uint64_t gamma  = scratchpadHigh[scratchpadIndex];
      uint64_t delta  = (alpha | (~gamma)) & (scratchpadLow[scratchpadIndex] ^ beta);

      stateLow[stateIndex]  = ~delta;
      stateHigh[stateIndex] = (alpha ^ gamma) | delta;
    }
  }
}

void
Pow::increment(uint64_t* stateLow, uint64_t* stateHigh, int fromIndex, int toIndex) {
  for (int i = fromIndex; i < toIndex; ++i) {
    if (stateLow[i] == lBits) {
      stateLow[i]  = hBits;
      stateHigh[i] = lBits;
    } else {
      if (stateHigh[i] == lBits) {
        stateHigh[i] = hBits;
      } else {
        stateLow[i] = lBits;
      }
      break;
    }
  }
}

Types::Trits
Pow::loop(uint64_t* stateLow, uint64_t* stateHigh, int minWeightMagnitude) {
  uint64_t stateLowCpy[stateSize];
  uint64_t stateHighCpy[stateSize];
  uint64_t scratchpadLow[stateSize];
  uint64_t scratchpadHigh[stateSize];
  uint64_t mask    = 1;
  uint64_t outMask = 1;
  while (stop_ == false) {
    increment(stateLow, stateHigh, 162 + (TritHashLength / 9) * 2, TritHashLength);

    std::memcpy(stateLowCpy, stateLow, stateSize * sizeof(uint64_t));
    std::memcpy(stateHighCpy, stateHigh, stateSize * sizeof(uint64_t));
    transform(stateLowCpy, stateHighCpy, scratchpadLow, scratchpadHigh);

    mask = hBits;
    for (int i = minWeightMagnitude; i-- > 0;) {
      mask &= ~(stateLowCpy[TritHashLength - 1 - i] ^ stateHighCpy[TritHashLength - 1 - i]);
      if (mask == 0) {
        break;
      }
    }
    if (mask == 0) {
      continue;
    }

    {
      std::lock_guard<std::mutex> lock(mtx_);
      if (stop_ == false) {
        stop_ = true;
        while ((outMask & mask) == 0) {
          outMask <<= 1;
        }
        Types::Trits nonceTrits(TritNonceLength);
        for (unsigned int i = 0; i < TritNonceLength; i++) {
          nonceTrits[i] = (stateLow[nonceOffset + i] & outMask) == 0
                              ? 1
                              : (stateHigh[nonceOffset + i] & outMask) == 0 ? -1 : 0;
        }
        return nonceTrits;
      }
    }
    break;
  }
  return {};
}

}  // namespace Crypto

}  // namespace IOTA
