#!/bin/bash

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

echo "Generating baseline coverage data file."
lcov --capture --initial --directory . --output-file coverage_base.info

echo "Generating coverage based on executed tests."
lcov --capture --directory . --output-file coverage_test.info

echo "Merging coverage tracefiles."
lcov --add-tracefile coverage_base.info --add-tracefile coverage_test.info --output-file coverage_merge.info

echo "Removing unwanted files from coverage."
lcov --remove coverage_merge.info "`pwd`/external/*" "`pwd`/test/*" "/usr/*" -o coverage.info

echo "Uploading coverage."
coveralls --no-gcov --lcov-file coverage.info
