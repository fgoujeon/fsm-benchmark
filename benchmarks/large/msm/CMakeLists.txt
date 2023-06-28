#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

cmake_minimum_required(VERSION 3.10)

set(TARGET large-msm)

file(GLOB_RECURSE SOURCE_FILES *)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE_FILES})
add_executable(${TARGET} ${SOURCE_FILES})

if(FSMB_FORCED_CXX_STANDARD)
    set(TARGET_CXX_STANDARD ${FSMB_FORCED_CXX_STANDARD})
else()
    set(TARGET_CXX_STANDARD 98)
endif()

set_target_properties(
    ${TARGET} PROPERTIES
    CXX_STANDARD ${TARGET_CXX_STANDARD}
)

target_link_libraries(
    ${TARGET}
    PRIVATE
        large-common
        Boost::boost
)
