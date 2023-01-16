#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

cmake_minimum_required(VERSION 3.10)

project(fsm-benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(FSMB_AWESM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libraries/awesm/awesm/include)
set(FSMB_SML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libraries/sml/include)

find_package(Boost 1.64.0 REQUIRED)

add_subdirectory(benchmarks)
