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


if (ARCH MATCHES "32")
  set(CMAKE_C_FLAGS -m32 ${CMAKE_C_FLAGS})
  set(CMAKE_CXX_FLAGS -m32 ${CMAKE_CXX_FLAGS})
  set(FORWARD_FLAGS -m32 ${FORWARD_FLAGS})

elseif (ARCH MATCHES "64")
  set(CMAKE_C_FLAGS -m64 ${CMAKE_C_FLAGS})
  set(CMAKE_CXX_FLAGS -m64 ${CMAKE_CXX_FLAGS})
  set(FORWARD_FLAGS -m64 ${FORWARD_FLAGS})

else ()
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits
    set (ARCH "64")
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    set (ARCH "32")
  endif ()
endif ()
