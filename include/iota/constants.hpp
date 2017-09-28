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

#include <iostream>

namespace IOTA {

const std::string  TryteAlphabet             = "9ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const unsigned int ChecksumLength            = 9;
const unsigned int TryteAlphabetLength       = 27;
const unsigned int FragmentLength            = 27;
const unsigned int TagLength                 = 27;
const unsigned int SeedLength                = 81;
const unsigned int SeedLengthWithChecksum    = 90;
const unsigned int AddressLength             = 81;
const unsigned int AddressLengthWithChecksum = 90;
const unsigned int ByteHashLength            = 48;
const unsigned int TritHashLength            = 243;
const unsigned int MaxTrxMsgLength           = 2187;

const std::string EmptyHash =
    "999999999999999999999999999999999999999999999999999999999999999999999999999999999";

}  // namespace IOTA
