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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
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

#include <iostream>
#include <vector>

#include <iota/types/trinary.hpp>

namespace IOTA {

namespace Crypto {

namespace Signing {

Types::Trits key(const Types::Trytes& seed, const unsigned int& index = 0,
                 const unsigned int& security = 1);
Types::Trits digest(const std::vector<int8_t>& normalizedBundleFragment,
                    const Types::Trits&        signatureFragment);
Types::Trits digests(const Types::Trits& key);
Types::Trits address(const Types::Trits& digests);
Types::Trits signatureFragment(const std::vector<int8_t>& normalizedBundleFragment,
                               const Types::Trits&        keyFragment);
bool         validateSignatures(const Types::Trytes&              expectedAddress,
                                const std::vector<Types::Trytes>& signatureFragments,
                                const Types::Trytes&              bundleHash);

};  // namespace Signing

}  // namespace Crypto

}  // namespace IOTA
