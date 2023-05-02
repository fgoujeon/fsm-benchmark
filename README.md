This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

Tested libraries are:

* [AweSM](https://github.com/fgoujeon/awesm);
* [Boost](https://www.boost.org/).MSM;
* [\[Boost::ext\].SML](https://boost-ext.github.io/sml/).

**Disclaimer**:

* I'm the author of AweSM.
* I've tried my best to make the test as fair as possible for every library. However, since I'm only an expert in my own library, I might have done mistakes. Please feel free to check the implementations and contact me if something has to be fixed.
* Keep in mind that this is only a single test. Different benchmarks may (or may not) give different results.

## Results

### Visual Studio

* Hardware: Intel i7 8850H, 32.0 GiB RAM
* System: Windows 11
* Compiler: Visual Studio 2017

```batch
python run-benchmarks.py %BUILD_DIR% 5 -G "Visual Studio 15 2017 Win64" -D Boost_INCLUDE_DIR=%BOOST_INCLUDE_DIR%
```

Best results of 5 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.25            | 5.629 s    | 1.251 s        | 31.5 KiB    |
| **Boost.MSM**               | 25.613 s   | 4.982 s        | 69.5 KiB    |
| **[Boost::ext].SML** v1.1.6 | 7.773 s    | 1.385 s        | 52.5 KiB    |

### GCC

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: GCC 12.2.1

```bash
CXX=g++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release
```

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.25            | 2.619 s    | 0.464 s        | 49.3 KiB    |
| **Boost.MSM**               | 21.843 s   | 2.391 s        | 315.8 KiB   |
| **[Boost::ext].SML** v1.1.6 | 6.912 s    | 0.573 s        | 581.7 KiB   |

### Clang

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: Clang 15.0.7

```bash
CXX=clang++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release
```

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.25            | 3.206 s    | 0.556 s        | 74.3 KiB    |
| **Boost.MSM**               | 16.075 s   | 2.809 s        | 302.7 KiB   |
| **[Boost::ext].SML** v1.1.6 | 7.982 s    | 0.587 s        | 734.9 KiB   |

## The Test

The repository defines one program per library. Each program must implement, using its assigned library, the test described below.

The test tries to mimic a real-life large FSM. It consists of:

* an `int counter`;
* a large FSM:
  * which defines:
    * 25 states (*state<sub>0</sub>* to *state<sub>24</sub>*);
    * 25 event types for state transitions (*sevent<sub>0</sub>* to *sevent<sub>24</sub>*) that contain an `int two = 2`;
    * 1 event type for internal transitions (*ievent*) that contains an `int two = 2`;
    * 25 state transition actions (*saction<sub>0</sub>* to *saction<sub>24</sub>*) doing `counter = (counter + 1) * event.two`;
    * 25 internal transition actions (*iaction<sub>0</sub>* to *iaction<sub>24</sub>*) doing `counter /= event.two`;
    * 25 state exit actions (*eaction<sub>0</sub>* to *eaction<sub>24</sub>*) making the FSM process *ievent* (in order to test run-to-completion);
    * 25 guards;
  * whose initial state is *state<sub>0</sub>*;
  * which transitions from *state<sub>n</sub>* to *state<sub>(n+1)%25</sub>* and executes *saction<sub>n</sub>* whenever it receives *sevent<sub>n</sub>* and *guard<sub>n</sub>* returns true;
  * which executes *iaction<sub>n</sub>* whenever it receives *ievent* in *state<sub>n</sub>*;
  * whose all guards check that the event data is positive (effectively returning `true` every time);
* a `test()` function that:
  * creates the counter;
  * creates the FSM;
  * makes the FSM perform 25 state transitions from *state<sub>0</sub>* to *state<sub>24</sub>* and back to *state<sub>0</sub>*, 1000 times;
  * returns the value of the counter;
* a `main()` function that calls the `test()` function 1,000 times and checks that the counter has the expected value.

Note: Each program is required to enable run-to-completion. This implies that FSM libraries that don't support run-to-completion can't take part in this benchmark.
