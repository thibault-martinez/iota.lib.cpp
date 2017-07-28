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

########## PROJECT TEST FILES ##########

file(GLOB PROJECT_TEST_FILES *.cpp)

########## EXECUTABLE ##########

add_executable(runUnitTests ${PROJECT_TEST_FILES})
target_link_libraries(runUnitTests googletest pthread ${CMAKE_PROJECT_NAME})

# target_compile_features(runUnitTests PRIVATE cxx_range_for)
# add_sanitizers(runUnitTests)

add_test(AllTests runUnitTests)

# if(CMAKE_COMPILER_IS_GNUCXX)
#   include(CodeCoverage)
#   target_link_libraries(runUnitTests gcov)
#   target_compile_options(runUnitTests PRIVATE "-fprofile-arcs" "-ftest-coverage")
#   target_compile_options(${LIBRARY_NAME}static PRIVATE "-fprofile-arcs" "-ftest-coverage")
#   setup_target_for_coverage(coverage runUnitTests coverage)
# endif(CMAKE_COMPILER_IS_GNUCXX)
