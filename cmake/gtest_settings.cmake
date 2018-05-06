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

set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

ExternalProject_Add("googletest_dep"
                    SOURCE_DIR "${CMAKE_SOURCE_DIR}/${GOOGLETEST_ROOT}"
                    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
                    CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
                    CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
                    CMAKE_ARGS "-Dgtest_force_shared_crt=ON" # Prevent overriding the parent project's compiler/linker settings on Windows
                    CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS} -D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
                    CMAKE_ARGS "-DCMAKE_CXX_FLAGS=${FORWARD_FLAGS} -D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
                    UPDATE_COMMAND git checkout tags/release-1.8.0
                    INSTALL_COMMAND "")

########## GOOGLE TEST INCLUDES DIRECTORIES ##########

include_directories(
  ${CMAKE_SOURCE_DIR}/${GOOGLETEST_ROOT}
  ${CMAKE_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

add_dependencies(${CMAKE_PROJECT_NAME} googletest_dep)
