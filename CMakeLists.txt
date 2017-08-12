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

########## GLOBAL CONFIGURATION ##########

cmake_minimum_required(VERSION 3.1.0)

project(iota)
enable_language(C CXX)

include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE OFF)

########## DEFAULT FOLDERS ##########

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
########## PROJECT DIRECTORIES ##########

set(PROJECT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/source/)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(PROJECT_CMAKE_DIR   ${CMAKE_SOURCE_DIR}/cmake)

######### VERSION ##########

string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT_NAME)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

configure_file(cmake/version.hpp.in
               ${PROJECT_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/version.hpp)

########## PROJECT FILES ##########

file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}"
                    "${PROJECT_INCLUDE_DIR}/API"
                    "${PROJECT_INCLUDE_DIR}/API/Responses"
                    "${PROJECT_INCLUDE_DIR}/API/Requests"
                    "${PROJECT_INCLUDE_DIR}/Model"
                    "${PROJECT_INCLUDE_DIR}/Type"
                    "${PROJECT_INCLUDE_DIR}/Utils"
                    )

########## LIBRARY ##########

add_library(${CMAKE_PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

########## COMPILATION SETTINGS ##########

include(compilation_settings)

########## TEST SETTINGS ##########

#TODO WARNING BUILD
if(BUILD_TESTING)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  include(gtest_settings)
  enable_testing()
  add_subdirectory(test)
endif(BUILD_TESTING)
