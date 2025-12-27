This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

Tested libraries are:

* [Maki](https://github.com/fgoujeon/maki);
* [Boost](https://www.boost.org/).MSM;
* [\[Boost::ext\].SML](https://boost-ext.github.io/sml/).

**Disclaimer**:

* I'm the author of Maki.
* I've tried my best to make the test as fair as possible for every library. However, since I'm only an expert in my own library, I might have done mistakes. Please feel free to check the implementations and contact me if something has to be fixed.
* Keep in mind that this is only a single test. Different benchmarks may (or may not) give different results.

## Results

### Visual Studio

* Hardware: AMD Ryzen 5 1600, 8 GiB RAM
* System: Windows 10
* Compiler: Visual Studio 2022

```batch
python run-benchmarks.py %BUILD_DIR% 3 -G "Visual Studio 17 2022" -A "x64" -D FSMB_MSM_INCLUDE_DIR=%BOOST_INCLUDE_DIR% -D FSMB_FORCED_CXX_STANDARD=20
```

Large FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 9.459 s    | 0.399 s        | 19.5 KiB    |
| **MSM** 1.90.0              | 27.384 s   | 1.418 s        | 59.0 KiB    |
| **MSM (`backmp11`)** 1.90.0 | 9.341 s    | 1.209 s        | 60.0 KiB    |
| **SML** 1.1.10              | 7.407 s    | 0.832 s        | 48.0 KiB    |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 14.371 s   | 0.481 s        | 25.5 KiB    |
| **MSM** 1.90.0              | 37.484 s   | 3.471 s        | 170.0 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 13.062 s   | 3.863 s        | 238.5 KiB   |
| **SML** 1.1.13              | 12.908 s   | 1.817 s        | 150.0 KiB   |

Note: SML 1.1.13 Large FSM build fails with error C1202 (recursive type or function dependency context too complex).

### GCC

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.18.2-arch2-1
* Compiler: GCC 15.2.1

```bash
CXX=g++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_MSM_INCLUDE_DIR=${MSM_INCLUDE_DIR} -D FSMB_FORCED_CXX_STANDARD=20
```

Large FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 1.211 s    | 0.255 s        | 24.8 KiB    |
| **MSM** 1.90.0              | 5.624 s    | 1.045 s        | 332.2 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 2.023 s    | 0.437 s        | 168.0 KiB   |
| **SML** 1.1.13              | 2.343 s    | 0.249 s        | 98.8 KiB    |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 1.354 s    | 0.011 s        | 21.3 KiB    |
| **MSM** 1.90.0              | 9.534 s    | 0.933 s        | 671.7 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 4.497 s    | 0.922 s        | 660.8 KiB   |
| **SML** 1.1.13              | 3.707 s    | 0.247 s        | 534.4 KiB   |

### Clang

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.18.2-arch2-1
* Compiler: Clang 21.1.6

```bash
CXX=clang++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_MSM_INCLUDE_DIR=${MSM_INCLUDE_DIR} -D FSMB_FORCED_CXX_STANDARD=20
```

Large FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 1.928 s    | 0.134 s        | 24.6 KiB    |
| **MSM** 1.90.0              | 5.420 s    | 1.102 s        | 399.8 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 1.712 s    | 0.583 s        | 139.5 KiB   |
| **SML** 1.1.13              | 3.379 s    | 0.810 s        | 668.2 KiB   |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 2.818 s    | 0.023 s        | 24.2 KiB    |
| **MSM** 1.90.0              | 8.823 s    | 1.328 s        | 720.4 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 3.763 s    | 1.017 s        | 588.0 KiB   |
| **SML** 1.1.13              | 4.326 s    | 0.599 s        | 1036.3 KiB  |

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
