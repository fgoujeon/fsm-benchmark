#!/bin/bash

#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

#Check argument count
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 BUILD_DIR" >&2
  exit 1
fi

SRC_DIR=`dirname $0`
BUILD_DIR=$1

cmake \
    -S $SRC_DIR \
    -B $BUILD_DIR \
    -D CMAKE_BUILD_TYPE=Release \
    -D SML_BUILD_BENCHMARKS=0 \
    -D SML_BUILD_EXAMPLES=0 \
    -D SML_BUILD_TESTS=0 \
    -D SML_USE_EXCEPTIONS=0

cmake --build $BUILD_DIR --target clean

echo "========== fgfsm =========="
echo
echo "build time:"
time cmake --build $BUILD_DIR --target large-fgfsm
echo
echo "execution time:"
time $BUILD_DIR/bin/large-fgfsm
echo
echo "size:"
echo
du -sh $BUILD_DIR/bin/large-fgfsm
echo

echo "========== sml =========="
echo
echo "build time:"
time cmake --build $BUILD_DIR --target large-sml
echo
echo "execution time:"
time $BUILD_DIR/bin/large-sml
echo
echo "size:"
echo
du -sh $BUILD_DIR/bin/large-sml
echo
