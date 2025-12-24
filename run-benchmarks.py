#Copyright Florian Goujeon 2021.
#Distributed under the Boost Software License, Version 1.0.
#(See accompanying file LICENSE or copy at
#https://www.boost.org/LICENSE_1_0.txt)
#Official repository: https://github.com/fgoujeon/fsm-benchmark

import time
import os
import sys
import subprocess
from dataclasses import dataclass

@dataclass
class TestResult:
    build_time_s: float
    execution_time_s: float
    size_KiB: float

@dataclass
class BenchmarkInfo:
    pretty_name: str
    name: str #e.g. for directories

@dataclass
class LibraryInfo:
    pretty_name: str
    name: str #e.g. for directories
    version: str
    test_results: dict[str, TestResult]

def make_library_info(pretty_name, name):
    return LibraryInfo(pretty_name, name, None, {})

def get_executable_path(build_dir, executable_target_name):
    unix_executable_path = os.path.join(build_dir, "bin", executable_target_name)
    win_executable_path = os.path.join(build_dir, "bin", "Release", executable_target_name + ".exe")
    if os.path.exists(unix_executable_path):
        return unix_executable_path
    elif os.path.exists(win_executable_path):
        return win_executable_path
    else:
        raise Exception("Can't find executable file")

def get_library_version(build_dir, lib_name):
    # Build corresponding version getter
    subprocess.run([
        "cmake",
        "--build", build_dir,
        "--config", "Release",
        "--target", "get-version-" + lib_name])
    version_getter_path = get_executable_path(build_dir, f"get-version-{lib_name}")

    return subprocess.check_output([version_getter_path]).decode("utf-8").strip()

def merge_to_best(res1, res2):
    if res1 == None:
        return res2

    if res2 == None:
        return res1

    return TestResult(
        min(res1.build_time_s, res2.build_time_s),
        min(res1.execution_time_s, res2.execution_time_s),
        min(res1.size_KiB, res2.size_KiB))

def test(lib_name):
    #Build benchmark
    start_time = time.time()
    subprocess.run([
        "cmake",
        "--build", build_dir,
        "--clean-first",
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
    try:
        out = subprocess.check_output([executable_path])
    except subprocess.CalledProcessError as ex:
        print("Test failed with code ", ex.returncode)
        exit()
    end_time = time.time()
    execution_time_s = end_time - start_time

    #Print size
    size_B = os.path.getsize(executable_path)
    size_KiB = size_B / 1024

    return TestResult(build_time_s, execution_time_s, size_KiB)

def print_no_ln(s):
    print(s, end='')

def print_no_ln_padding(s, length):
    print(s + " " * (length - len(s)), end='')

#In this format:
#
#| Headers[0] | Headers[1] | Headers[2] | Headers[3] |
#|------------|-----------:|-----------:|-----------:|
#| Rows[0][0] | Rows[0][1] | Rows[0][2] | Rows[0][3] |
#| Rows[1][0] | Rows[1][1] | Rows[1][2] | Rows[1][3] |
#| Rows[2][0] | Rows[2][1] | Rows[2][2] | Rows[2][3] |
def print_as_markdown(headers, rows):
    #Compute size of each column
    column_sizes = []
    for col in range(len(headers)):
        column_size = len(headers[col])
        for row in rows:
            column_size = max(column_size, len(row[col]))
        column_sizes.append(column_size)

    #Print headers
    for col in range(len(headers)):
        print_no_ln("| ")
        print_no_ln_padding(headers[col], column_sizes[col])
        print_no_ln(" ")
    print("|")

    #Print line separator
    for col in range(len(headers)):
        print_no_ln("|")
        print_no_ln("-" * (column_sizes[col] + 1))
        if col == 0:
            print_no_ln("-")
        else:
            print_no_ln(":")
    print("|")

    #Print rows
    for row in rows:
        for col in range(len(headers)):
            print_no_ln("| ")
            print_no_ln_padding(row[col], column_sizes[col])
            print_no_ln(" ")
        print("|")

def print_benchmark_test_result(libraries, benchmark):
    #Format library infos
    formatted_library_infos = []
    for library in libraries:
        formatted_library_infos.append(
            [
                "**%s** %s" % (library.pretty_name, library.version),
                "%0.3f s" % library.test_results[benchmark.name].build_time_s,
                "%0.3f s" % library.test_results[benchmark.name].execution_time_s,
                "%0.1f KiB" % library.test_results[benchmark.name].size_KiB
            ]
        )

    print(f"#### {benchmark.pretty_name}")
    print()
    print("Best results of", iteration_count, "iterations:")
    print_as_markdown(
        ["", "Build time", "Execution time", "Binary size"],
        formatted_library_infos)
    print()

def print_test_results(libraries, benchmarks):
    for benchmark in benchmarks:
        print_benchmark_test_result(libraries, benchmark)

if len(sys.argv) < 3:
    print("Usage: run-benchmarks.py BUILD_DIR ITERATION_COUNT [CMAKE_EXTRA_OPTIONS...]")
    exit()

src_dir = os.path.dirname(__file__)
build_dir = sys.argv[1]
iteration_count = max(int(sys.argv[2]), 1)
cmake_extra_options = sys.argv[3:]

# List the libraries we want to test
libraries = [
    make_library_info("Maki", "maki"),
    make_library_info("MSM", "msm"),
    make_library_info("MSM (`backmp11`)", "msm-backmp11"),
    make_library_info("SML", "sml")]

# List the benchmarks
benchmarks = [
    BenchmarkInfo("Large FSM", "large"),
    BenchmarkInfo("Deep FSM", "deep")]

# Initialize CMake
cmake_command = ["cmake", "-S", src_dir, "-B", build_dir] + cmake_extra_options
subprocess.run(cmake_command)

# Get library versions
for library in libraries:
    library.version = get_library_version(build_dir, library.name)

# Run tests
for iteration_index in range(iteration_count):
    for library in libraries:
        for benchmark in benchmarks:
            print(f"===== {library.pretty_name}, {benchmark.pretty_name}, iteration {iteration_index + 1}/{iteration_count} =====")
            result = test(library.name)
            print("Built in %0.3f s" % result.build_time_s)
            print("Executed in %0.3f s" % result.execution_time_s)
            print("Binary size is %0.1f KiB" % result.size_KiB)
            print()
            library.test_results[benchmark.name] = merge_to_best(library.test_results.get(benchmark.name), result)

# Print test results in markdown format
print("===== Final Results (markdown format) =====")
print_test_results(libraries, benchmarks)
