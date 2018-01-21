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

###
# project
###
set(PROJECT iota_lib_cpp_tests)
project(${PROJECT} CXX)


###
# compilation options
###
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT WIN32)


###
# includes
###
include_directories("include")


###
# executables
###
set(MAIN "source/main.cpp" "source/configuration.cpp")
set(DIRS "source")

foreach(DIR ${DIRS})
  file(GLOB_RECURSE s_${DIR} "${DIR}/*.cpp")

  foreach(SOURCE ${s_${DIR}})
    get_filename_component(TEST_NAME ${SOURCE} NAME_WE)
    get_filename_component(TEST_PATH ${SOURCE} PATH)
    get_filename_component(TEST_DIR ${TEST_PATH} NAME)
    set(TEST_FULL_NAME "${TEST_DIR}_${TEST_NAME}")
    add_executable(${TEST_FULL_NAME} ${MAIN} ${SOURCE})
    target_compile_features(${TEST_FULL_NAME}  PRIVATE cxx_range_for)
    target_link_libraries(${TEST_FULL_NAME} googletest pthread ${CMAKE_PROJECT_NAME})
    add_test(NAME ${TEST_FULL_NAME} COMMAND ${TEST_FULL_NAME} ${CMAKE_SOURCE_DIR}/test/files)
  endforeach()

endforeach()
