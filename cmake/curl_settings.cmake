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

ExternalProject_Add("curl_dep"
                    GIT_SUBMODULES ""
                    CMAKE_ARGS "-DBUILD_CURL_EXE=OFF"
                    CMAKE_ARGS "-DHTTP_ONLY=ON"
                    CMAKE_ARGS "-DCMAKE_USE_OPENSSL=OFF"
                    CMAKE_ARGS "-DCMAKE_USE_LIBSSH2=OFF"
                    CMAKE_ARGS "-DCURL_CA_PATH_SET=OFF"
                    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
                    CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
                    CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
                    CMAKE_ARGS "-Wno-dev"
                    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                    CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
                    CMAKE_ARGS "-DCMAKE_CXX_FLAGS=${FORWARD_FLAGS}"
                    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/curl")

include_directories(${CMAKE_SOURCE_DIR}/external/cpr/include)

if (WIN32)
  target_link_libraries(${CMAKE_PROJECT_NAME} cpr libcurl_imp)
else ()
  target_link_libraries(${CMAKE_PROJECT_NAME} cpr curl)
ENDIF (WIN32)

add_dependencies(${CMAKE_PROJECT_NAME} cpr_dep)
