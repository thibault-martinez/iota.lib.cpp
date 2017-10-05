#! /bin/bash

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

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m' # No Color
BG='\033[0;32m' # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
allert () { echo -e "${RED}$1${NC}"; }

# Building project
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j8
# Checks if last comand didn't output 0
# $? checks what last command outputed
# If output is 0 then command is succesfuly executed
# If command fails it outputs number between 0 to 255
if [ $? -ne 0 ]; then
    error "Error: there are compile errors!"
	# Terminate script and outputs 3
    exit 3
fi

showinfo "Running tests ..."
./bin/runUnitTests ../test/files $1
if [ $? -ne 0 ]; then
    error "Error: there are failed tests!"
    exit 4
fi

workingprocess "All tests compile and pass."
