#!/bin/bash

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

BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NORMAL='\033[0m'

info() { echo -e "${BLUE}$1${NORMAL}"; }
success() { echo -e "${GREEN}$1${NORMAL}"; }
fail() { >&2 echo -e "${RED}$1${NORMAL}"; }

############################
info "Building project..." #
############################
mkdir -p build
cd build
cmake -DBUILD_TESTS=1 -DTRAVIS_KEEP_ALIVE=1 ..
make -j4
if [ $? -ne 0 ]; then
    fail "Error : compilation failed !"
    exit 1
fi

#########################
info "Running tests..." #
#########################
./bin/runUnitTests ../test/files $1
if [ $? -ne 0 ]; then
    fail "Error : tests failed !"
    exit 1
fi

success "Everything is ok !"
