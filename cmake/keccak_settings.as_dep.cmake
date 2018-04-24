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
# For non-windows platforms, we can use the keccak repository and its cmake to build keccak and link it
#
if (NOT WIN32)

  if (NOT KECCAK_ARCH_OPTIMIZATION)
    if (ARCH EQUAL "64")
      # 64 bits
      set (KECCAK_ARCH_OPTIMIZATION "generic64")
    else ()
      # 32 bits
      set (KECCAK_ARCH_OPTIMIZATION "generic32")
    endif ()
  endif ()

  ExternalProject_Add("keccak_dep"
                      GIT_SUBMODULES ""
                      SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/keccak"
                      CONFIGURE_COMMAND ""
                      UPDATE_COMMAND ""
                      BUILD_COMMAND cd ${CMAKE_SOURCE_DIR}/external/keccak && make ${KECCAK_ARCH_OPTIMIZATION}/libkeccak.a
                      INSTALL_COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/deps/lib &&
                                      mkdir -p ${CMAKE_SOURCE_DIR}/deps/lib &&
                                      cd ${CMAKE_SOURCE_DIR}/external/keccak &&
                                      cp bin/${KECCAK_ARCH_OPTIMIZATION}/libkeccak.a ${CMAKE_SOURCE_DIR}/deps/lib &&
                                      cp -a bin/${KECCAK_ARCH_OPTIMIZATION}/libkeccak.a.headers ${CMAKE_SOURCE_DIR}/deps/include)

  include_directories(${CMAKE_SOURCE_DIR}/deps/include/libkeccak.a.headers)
  target_link_libraries(${CMAKE_PROJECT_NAME} keccak)
  add_dependencies(${CMAKE_PROJECT_NAME} keccak_dep)

endif()
