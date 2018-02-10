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

git clone https://github.com/iotaledger/iri.git test/testnet/iri
cd test/testnet/iri
git checkout 8886df6e
cp ../iri_config/Snapshot.txt src/main/resources
cp ../iri_config/iri.ini .
cp ../iri_patch/Snapshot.java src/main/java/com/iota/iri/Snapshot.java
cp ../iri_patch/TransactionValidator.java src/main/java/com/iota/iri/TransactionValidator.java
cp ../iri_patch/TransactionValidatorTest.java src/test/java/com/iota/iri/TransactionValidatorTest.java
cp -r ../testnetdb_windows ./testnetdb
mvn clean compile
mvn package
