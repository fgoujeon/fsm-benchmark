#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

cmake_minimum_required(VERSION 3.10)

project(fsm-benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(FSMB_MSM_INCLUDE_DIR "" CACHE PATH "Path to MSM include dir")
set(FSMB_FORCED_CXX_STANDARD "" CACHE STRING "If set, overwrites CXX_STANDARD property of all targets")

set(FSMB_MAKI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libraries/maki/include)
set(FSMB_SML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libraries/sml/include)

add_subdirectory(version-getters)
add_subdirectory(benchmarks)
