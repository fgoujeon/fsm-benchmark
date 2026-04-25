#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

cmake_minimum_required(VERSION 3.10)

set(TARGET deep-common)

add_library(${TARGET} INTERFACE)

target_include_directories(
    ${TARGET}
    INTERFACE
        include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(
        ${TARGET}
        INTERFACE
            -Wall -pedantic
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(
        ${TARGET}
        INTERFACE
            -Wall -pedantic
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ${TARGET}
        INTERFACE
            /W4 /permissive-
    )
endif()
