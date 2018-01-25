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

#include <iota/crypto/curl.hpp>
#include <iota/crypto/pow.hpp>
#include <iota/utils/parallel_for.hpp>
#include <iota/utils/stop_watch.hpp>

namespace IOTA {

namespace Crypto {

// TODO
static constexpr int indices[] = {
  0,   364, 728, 363, 727, 362, 726, 361, 725, 360, 724, 359, 723, 358, 722, 357, 721, 356, 720,
  355, 719, 354, 718, 353, 717, 352, 716, 351, 715, 350, 714, 349, 713, 348, 712, 347, 711, 346,
  710, 345, 709, 344, 708, 343, 707, 342, 706, 341, 705, 340, 704, 339, 703, 338, 702, 337, 701,
  336, 700, 335, 699, 334, 698, 333, 697, 332, 696, 331, 695, 330, 694, 329, 693, 328, 692, 327,
  691, 326, 690, 325, 689, 324, 688, 323, 687, 322, 686, 321, 685, 320, 684, 319, 683, 318, 682,
  317, 681, 316, 680, 315, 679, 314, 678, 313, 677, 312, 676, 311, 675, 310, 674, 309, 673, 308,
  672, 307, 671, 306, 670, 305, 669, 304, 668, 303, 667, 302, 666, 301, 665, 300, 664, 299, 663,
  298, 662, 297, 661, 296, 660, 295, 659, 294, 658, 293, 657, 292, 656, 291, 655, 290, 654, 289,
  653, 288, 652, 287, 651, 286, 650, 285, 649, 284, 648, 283, 647, 282, 646, 281, 645, 280, 644,
  279, 643, 278, 642, 277, 641, 276, 640, 275, 639, 274, 638, 273, 637, 272, 636, 271, 635, 270,
  634, 269, 633, 268, 632, 267, 631, 266, 630, 265, 629, 264, 628, 263, 627, 262, 626, 261, 625,
  260, 624, 259, 623, 258, 622, 257, 621, 256, 620, 255, 619, 254, 618, 253, 617, 252, 616, 251,
  615, 250, 614, 249, 613, 248, 612, 247, 611, 246, 610, 245, 609, 244, 608, 243, 607, 242, 606,
  241, 605, 240, 604, 239, 603, 238, 602, 237, 601, 236, 600, 235, 599, 234, 598, 233, 597, 232,
  596, 231, 595, 230, 594, 229, 593, 228, 592, 227, 591, 226, 590, 225, 589, 224, 588, 223, 587,
  222, 586, 221, 585, 220, 584, 219, 583, 218, 582, 217, 581, 216, 580, 215, 579, 214, 578, 213,
  577, 212, 576, 211, 575, 210, 574, 209, 573, 208, 572, 207, 571, 206, 570, 205, 569, 204, 568,
  203, 567, 202, 566, 201, 565, 200, 564, 199, 563, 198, 562, 197, 561, 196, 560, 195, 559, 194,
  558, 193, 557, 192, 556, 191, 555, 190, 554, 189, 553, 188, 552, 187, 551, 186, 550, 185, 549,
  184, 548, 183, 547, 182, 546, 181, 545, 180, 544, 179, 543, 178, 542, 177, 541, 176, 540, 175,
  539, 174, 538, 173, 537, 172, 536, 171, 535, 170, 534, 169, 533, 168, 532, 167, 531, 166, 530,
  165, 529, 164, 528, 163, 527, 162, 526, 161, 525, 160, 524, 159, 523, 158, 522, 157, 521, 156,
  520, 155, 519, 154, 518, 153, 517, 152, 516, 151, 515, 150, 514, 149, 513, 148, 512, 147, 511,
  146, 510, 145, 509, 144, 508, 143, 507, 142, 506, 141, 505, 140, 504, 139, 503, 138, 502, 137,
  501, 136, 500, 135, 499, 134, 498, 133, 497, 132, 496, 131, 495, 130, 494, 129, 493, 128, 492,
  127, 491, 126, 490, 125, 489, 124, 488, 123, 487, 122, 486, 121, 485, 120, 484, 119, 483, 118,
  482, 117, 481, 116, 480, 115, 479, 114, 478, 113, 477, 112, 476, 111, 475, 110, 474, 109, 473,
  108, 472, 107, 471, 106, 470, 105, 469, 104, 468, 103, 467, 102, 466, 101, 465, 100, 464, 99,
  463, 98,  462, 97,  461, 96,  460, 95,  459, 94,  458, 93,  457, 92,  456, 91,  455, 90,  454,
  89,  453, 88,  452, 87,  451, 86,  450, 85,  449, 84,  448, 83,  447, 82,  446, 81,  445, 80,
  444, 79,  443, 78,  442, 77,  441, 76,  440, 75,  439, 74,  438, 73,  437, 72,  436, 71,  435,
  70,  434, 69,  433, 68,  432, 67,  431, 66,  430, 65,  429, 64,  428, 63,  427, 62,  426, 61,
  425, 60,  424, 59,  423, 58,  422, 57,  421, 56,  420, 55,  419, 54,  418, 53,  417, 52,  416,
  51,  415, 50,  414, 49,  413, 48,  412, 47,  411, 46,  410, 45,  409, 44,  408, 43,  407, 42,
  406, 41,  405, 40,  404, 39,  403, 38,  402, 37,  401, 36,  400, 35,  399, 34,  398, 33,  397,
  32,  396, 31,  395, 30,  394, 29,  393, 28,  392, 27,  391, 26,  390, 25,  389, 24,  388, 23,
  387, 22,  386, 21,  385, 20,  384, 19,  383, 18,  382, 17,  381, 16,  380, 15,  379, 14,  378,
  13,  377, 12,  376, 11,  375, 10,  374, 9,   373, 8,   372, 7,   371, 6,   370, 5,   369, 4,
  368, 3,   367, 2,   366, 1,   365, 0
};

Pow::Pow() : stop_(true) {
}

Pow::~Pow() {
}

Types::Trytes
Pow::operator()(const Types::Trytes& trytes, int minWeightMagnitude) {
  stop_ = false;
  IOTA::Crypto::Curl c;

  // TODO Harcoded value, should be kept with Transaction
  IOTA::Types::Trits trits = IOTA::Types::trytesToTrits(trytes.substr(0, 2592));
  c.absorb(trits);
  auto state = c.getState();
  auto tr    = IOTA::Types::trytesToTrits(trytes);
  // TODO Harcoded value, should be kept with Transaction
  std::copy(std::begin(tr) + 7776, std::end(tr), std::begin(state));

  IOTA::Types::Trytes result;

  Utils::parallel_for([this, &result, state, minWeightMagnitude](uint32_t i) {
    uint64_t lmid[stateSize];
    uint64_t hmid[stateSize];

    para(lmid, hmid, state);

    lmid[nonceOffset]     = low0;
    hmid[nonceOffset]     = high0;
    lmid[nonceOffset + 1] = low1;
    hmid[nonceOffset + 1] = high1;
    lmid[nonceOffset + 2] = low2;
    hmid[nonceOffset + 2] = high2;
    lmid[nonceOffset + 3] = low3;
    hmid[nonceOffset + 3] = high3;

    for (uint32_t j = 0; j < i; ++j) {
      incr(lmid, hmid);
    }

    IOTA::Types::Trits nonce = loop(lmid, hmid, minWeightMagnitude);

    {
      std::lock_guard<std::mutex> lock(mtx_);
      if (nonce.empty() == false) {
        result = IOTA::Types::tritsToTrytes(nonce);
        stop_  = true;
      }
    }
  });
  return result;
}

void
Pow::transform64(uint64_t* lmid, uint64_t* hmid) const {
  uint64_t*  ltmp  = new uint64_t[stateSize];
  uint64_t*  htmp  = new uint64_t[stateSize];
  uint64_t** lfrom = &lmid;
  uint64_t** hfrom = &hmid;
  uint64_t** lto   = &ltmp;
  uint64_t** hto   = &htmp;

  for (int r = 0; r < numberOfRounds - 1; ++r) {
    for (int j = 0; j < stateSize; ++j) {
      int t1 = indices[j];
      int t2 = indices[j + 1];

      uint64_t alpha = (*lfrom)[t1];
      uint64_t beta  = (*hfrom)[t1];
      uint64_t gamma = (*hfrom)[t2];
      uint64_t delta = (alpha | (~gamma)) & ((*lfrom)[t2] ^ beta);

      (*lto)[j] = ~delta;
      (*hto)[j] = (alpha ^ gamma) | delta;
    }
    uint64_t* tmp;
    tmp    = *lto;
    *lto   = *lfrom;
    *lfrom = tmp;

    tmp    = *hto;
    *hto   = *hfrom;
    *hfrom = tmp;
  }

  for (int j = 0; j < stateSize; ++j) {
    int t1 = indices[j];
    int t2 = indices[j + 1];

    uint64_t alpha = (*lfrom)[t1];
    uint64_t beta  = (*hfrom)[t1];
    uint64_t gamma = (*hfrom)[t2];
    uint64_t delta = (alpha | (~gamma)) & ((*lfrom)[t2] ^ beta);

    (*lto)[j] = ~delta;
    (*hto)[j] = (alpha ^ gamma) | delta;
  }

  std::memcpy(lmid, ltmp, sizeof(*ltmp) * stateSize);
  std::memcpy(hmid, htmp, sizeof(*htmp) * stateSize);
  delete[] ltmp;
  delete[] htmp;
}

bool
Pow::incr(uint64_t* lmid, uint64_t* hmid) const {
  uint64_t carry = 1;
  uint32_t i;

  for (i = nonceInitStart; i < TritHashLength && carry != 0; ++i) {
    uint64_t low  = lmid[i];
    uint64_t high = hmid[i];
    lmid[i]       = high ^ low;
    hmid[i]       = low;
    carry         = high & (~low);
  }
  return i == TritHashLength;
}

Types::Trits
Pow::seri(const uint64_t* l, const uint64_t* h, uint64_t n) const {
  Types::Trits r(TritNonceLength);

  for (uint32_t i = nonceOffset; i < TritHashLength; ++i) {
    uint64_t ll = (l[i] >> n) & 1;
    uint64_t hh = (h[i] >> n) & 1;
    if (hh == 0 && ll == 1) {
      r[i - nonceOffset] = -1;
    }
    if (hh == 1 && ll == 1) {
      r[i - nonceOffset] = 0;
    }
    if (hh == 1 && ll == 0) {
      r[i - nonceOffset] = 1;
    }
  }
  return r;
}

int64_t
Pow::check(const uint64_t* l, const uint64_t* h, int m) const {
  uint64_t nonceProbe = hBits;

  for (uint32_t i = TritHashLength - m; i < TritHashLength; ++i) {
    nonceProbe &= ~(l[i] ^ h[i]);
    if (nonceProbe == 0) {
      return -1;
    }
  }
  for (int64_t i = 0; i < 64; i++) {
    if (((nonceProbe >> i) & 1) == 1) {
      return i;
    }
  }
  return -1;
}

Types::Trits
Pow::loop(uint64_t* lmid, uint64_t* hmid, int m) const {
  uint64_t lcpy[stateSize];
  uint64_t hcpy[stateSize];
  for (uint64_t i = 0; !stop_ && !incr(lmid, hmid); ++i) {
    std::memcpy(lcpy, lmid, sizeof(lcpy));
    std::memcpy(hcpy, hmid, sizeof(hcpy));
    transform64(lcpy, hcpy);
    int64_t n = check(lcpy, hcpy, m);
    if (n >= 0) {
      return seri(lmid, hmid, static_cast<uint64_t>(n));
    }
  }
  return {};
}

void
Pow::para(uint64_t* l, uint64_t* h, const Types::Trits& in) const {
  for (int i = 0; i < stateSize; ++i) {
    switch (in[i]) {
      case 0:
        l[i] = hBits;
        h[i] = hBits;
        break;
      case 1:
        l[i] = lBits;
        h[i] = hBits;
        break;
      case -1:
        l[i] = hBits;
        h[i] = lBits;
        break;
    }
  }
}

}  // namespace Crypto

}  // namespace IOTA
