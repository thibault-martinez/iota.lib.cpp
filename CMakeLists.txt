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

########## GLOBAL CONFIGURATION ##########

cmake_minimum_required(VERSION 3.1.0)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(iota VERSION "1.2.1")
enable_language(C CXX)

option(BUILD_TESTING "" OFF)
include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_MACOSX_RPATH 1)

########## MISC CONFIG ##########
include(misc)

########## DEFAULT FOLDERS ##########

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

########## PROJECT DIRECTORIES ##########

set(PROJECT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/source/)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(PROJECT_CMAKE_DIR   ${CMAKE_SOURCE_DIR}/cmake)

######### VERSION INCLUDE ##########

string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT_NAME)

configure_file(cmake/version.hpp.in
               ${PROJECT_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/version.hpp)

########## PROJECT FILES ##########

file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("external/json/src")

########## DEPENDENCIES ##########

include_directories(${CMAKE_SOURCE_DIR}/deps/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/lib)
include(keccak_settings.as_source)

########## LIBRARY ##########
add_library(${CMAKE_PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

########## COMPILATION SETTINGS ##########

include(compilation_settings)

########## EXTERNAL LIBRARIES SETTINGS ##########

include(curl_settings)
include(cpr_settings)
include(keccak_settings.as_dep)

########## TEST SETTINGS ##########

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
ENDIF()

if (BUILD_TESTS)
  enable_testing()

  # silence gtest compilation warnings..
  add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)

  include(gtest_settings)
  add_subdirectory(test)
ENDIF()
