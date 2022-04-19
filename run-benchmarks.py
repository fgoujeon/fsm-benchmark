#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

import time
import os
import sys
import subprocess

class TestResult:
    def __init__(self, pretty_lib_name, build_time_s, execution_time_s, size_B):
        self.pretty_lib_name = pretty_lib_name
        self.build_time_s = build_time_s
        self.execution_time_s = execution_time_s
        self.size_B = size_B

def test(pretty_lib_name, lib_name):
    #Build benchmark
    start_time = time.time()
    subprocess.run([
        "cmake",
        "--build", build_dir,
        "--config", "Release",
        "--target", "large-" + lib_name])
    end_time = time.time()
    build_time_s = end_time - start_time

    unix_executable_path = os.path.join(build_dir, "bin", "large-" + lib_name)
    win_executable_path = os.path.join(build_dir, "bin", "Release", "large-" + lib_name + ".exe")
    if os.path.exists(unix_executable_path):
        executable_path = unix_executable_path
    elif os.path.exists(win_executable_path):
        executable_path = win_executable_path
    else:
        print("Can't find executable file")
        exit()

    #Run benchmark
    start_time = time.time()
    subprocess.run([executable_path])
    end_time = time.time()
    execution_time_s = end_time - start_time

    #Print size
    size_B = os.path.getsize(executable_path)

    return TestResult(pretty_lib_name, build_time_s, execution_time_s, size_B)

if len(sys.argv) != 3:
    print("Usage: run-benchmarks.py BUILD_DIR BOOST_INCLUDE_DIR")
    exit()

src_dir = os.path.dirname(__file__)
build_dir = sys.argv[1]
boost_include_dir = sys.argv[2]

#Initialize CMake
cmake_command = [
    "cmake",
    "-S", src_dir,
    "-B", build_dir,
    "-D", "CMAKE_BUILD_TYPE=Release",
    "-D", "SML_BUILD_BENCHMARKS=0",
    "-D", "SML_BUILD_EXAMPLES=0",
    "-D", "SML_BUILD_TESTS=0",
    "-D", "SML_USE_EXCEPTIONS=0",
    "-D", "BOOST_INCLUDE_DIR=" + boost_include_dir
    ]
subprocess.run(cmake_command)

#Clean
subprocess.run(["cmake", "--build", build_dir, "--target", "clean"])

#Run tests
results = [test("FGFSM", "fgfsm"), test("[Boost::ext].SML", "sml")]

#Print test results in markdown format
print("| | Build time | Execution time | Binary size")
print("|--|--|--|--")
for res in results:
    print(
        '| **%s** | %0.3f s | %0.3f s | %d B' %
        (
            res.pretty_lib_name,
            res.build_time_s,
            res.execution_time_s,
            res.size_B
        )
    )
