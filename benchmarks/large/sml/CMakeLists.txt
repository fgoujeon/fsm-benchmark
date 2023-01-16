#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

cmake_minimum_required(VERSION 3.10)

set(TARGET large-sml)

file(GLOB_RECURSE SOURCE_FILES *)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE_FILES})
add_executable(${TARGET} ${SOURCE_FILES})

set_target_properties(
    ${TARGET} PROPERTIES
    CXX_STANDARD 17
)

target_include_directories(
    ${TARGET}
    PRIVATE
        ${FSMB_SML_INCLUDE_DIR}
)

target_link_libraries(
    ${TARGET}
    PRIVATE
        large-common
)
