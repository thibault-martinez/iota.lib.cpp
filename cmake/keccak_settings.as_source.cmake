#
# MIT License
#
# Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#

#
# For windows platforms, we can't build keccak because its buildchain relies on Makefile
# A good alternative would be mingw32-make, which is not installed on most windows environment
#
# So, until keccak provides a cmake-based buildchain, the only reliable alternative for windows
# is to include its sources into our own sources and to build everything altogether
#
if (WIN32)

  include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/common)
  include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/high/Keccak)
  include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/high/Keccak/FIPS202)
  include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/low/common)

  set(KECCAK_SOURCE ${CMAKE_SOURCE_DIR}/external/keccak/lib/high/Keccak/FIPS202/KeccakHash.c
                    ${CMAKE_SOURCE_DIR}/external/keccak/lib/high/Keccak/KeccakSpongeWidth1600.c)

  if (ARCH EQUAL "64")
    # 64 bits
    include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Optimized)
    include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Optimized64)
    include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Optimized64/ufull)

    set(KECCAK_SOURCE ${KECCAK_SOURCE}
                      ${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Optimized64/KeccakP-1600-opt64.c)
  else ()
    # 32 bits
    include_directories(${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Inplace32BI)

    set(KECCAK_SOURCE ${KECCAK_SOURCE}
                      ${CMAKE_SOURCE_DIR}/external/keccak/lib/low/KeccakP-1600/Inplace32BI/KeccakP-1600-inplace32BI.c)
  endif ()

  set(PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES} ${KECCAK_SOURCE})

endif()
