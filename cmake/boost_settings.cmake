#
# MIT License
#
# Copyright (c) 2017 Thibault Martinez
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

find_package(Boost 1.64.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  ExternalProject_Add("boost_dep"
                      URL https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
                      DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external
                      SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/boost
                      BUILD_IN_SOURCE 1
                      UPDATE_COMMAND ""
                      CONFIGURE_COMMAND ""
                      BUILD_COMMAND ""
                      INSTALL_COMMAND "")

  add_dependencies(${CMAKE_PROJECT_NAME} boost_dep)
  include_directories(${CMAKE_SOURCE_DIR}/external/boost)
endif()
