This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

Tested libraries are:

* [Maki](https://github.com/fgoujeon/maki);
* [Boost](https://www.boost.org/).MSM (with its `back` and `backmp11` back ends);
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
| **Maki** 1.1.1              | 7.038 s    | 0.382 s        | 19.5 KiB    |
| **MSM** 1.90.0              | 25.760 s   | 1.449 s        | 59.0 KiB    |
| **MSM (`backmp11`)** 1.90.0 | 6.868 s    | 1.248 s        | 60.0 KiB    |
| **SML** 1.1.10              | 7.350 s    | 0.821 s        | 48.0 KiB    |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.1.1              | 14.801 s   | 0.482 s        | 25.5 KiB    |
| **MSM** 1.90.0              | 36.635 s   | 3.648 s        | 170.0 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 10.881 s   | 3.789 s        | 238.5 KiB   |
| **SML** 1.1.13              | 10.413 s   | 1.827 s        | 150.0 KiB   |

Note: SML 1.1.13 Large FSM build fails with error C1202 (recursive type or function dependency context too complex).


### GCC

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.19.13-arch1-1
* Compiler: GCC 15.2.1 20260209

```bash
CXX=g++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_MSM_INCLUDE_DIR=${MSM_INCLUDE_DIR} -D FSMB_FORCED_CXX_STANDARD=20
```

Large FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.1.1              | 1.234 s    | 0.261 s        | 25.4 KiB    |
| **MSM** 1.90.0              | 5.625 s    | 1.051 s        | 332.8 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 2.017 s    | 0.444 s        | 168.6 KiB   |
| **SML** 1.1.13              | 2.343 s    | 0.257 s        | 99.4 KiB    |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.1.1              | 1.381 s    | 0.011 s        | 22.0 KiB    |
| **MSM** 1.90.0              | 9.547 s    | 0.932 s        | 672.2 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 4.488 s    | 0.968 s        | 661.4 KiB   |
| **SML** 1.1.13              | 3.736 s    | 0.252 s        | 538.9 KiB   |


### Clang

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.19.13-arch1-1
* Compiler: Clang 22.1.3

```bash
CXX=clang++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_MSM_INCLUDE_DIR=${MSM_INCLUDE_DIR} -D FSMB_FORCED_CXX_STANDARD=20
```

Large FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.1.1              | 1.913 s    | 0.138 s        | 25.1 KiB    |
| **MSM** 1.90.0              | 5.128 s    | 1.118 s        | 400.3 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 1.661 s    | 0.564 s        | 140.0 KiB   |
| **SML** 1.1.13              | 3.356 s    | 0.820 s        | 668.8 KiB   |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.1.1              | 2.847 s    | 0.017 s        | 20.8 KiB    |
| **MSM** 1.90.0              | 8.239 s    | 1.317 s        | 720.9 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 3.632 s    | 1.044 s        | 588.5 KiB   |
| **SML** 1.1.13              | 4.066 s    | 0.500 s        | 1020.8 KiB  |


## Benchmarks Specifications

### Large FSM

This benchmark tries to mimic a real-life large FSM. It consists of:

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


### Deep FSM

This benchmark shall define an FSM with three levels of composite states:

* the FSM shall contain three level-0 composite states;
* each level-0 composite state shall contain three level-1 composite states and a final state;
* each level-1 composite state shall contain three level-2 simple states and a final state;
* each level-2 simple state shall define an exit action that adds `x * 3 + y * 3 + z + 1` to a counter, where:
  * `x` is the ID of the parent level-0 state;
  * `y` is the ID of the parent level-1 state;
  * `z` is the ID of the level-2 state.

The transition table of the FSM shall be the following:

```
[*]          -> lvl0_state_0
lvl0_state_0 -> lvl0_state_1
lvl0_state_1 -> lvl0_state_2
lvl0_state_2 -> lvl0_state_0
```

The transition table of every level-0 composite state shall be the following:

```
[*]           -> lvl1_state_x0
lvl1_state_x0 -> lvl1_state_x1
lvl1_state_x1 -> lvl1_state_x2
lvl1_state_x2 -> [*]
```

The transition table of every level-1 composite state shall be the following:

```
[*]            -> lvl2_state_xy0
lvl2_state_xy0 -> lvl2_state_xy1 : transition_event_xy0
lvl2_state_xy1 -> lvl2_state_xy2 : transition_event_xy1
lvl2_state_xy2 -> [*]            : transition_event_xy2
```

The benchmark shall define a `test()` function that:

* creates the counter;
* creates the FSM;
* executes a process loop 1,000 times.

The process loop shall make the FSM process the following events (in this order), which allows a full loop in the root transition table:

* `transition_event_000`;
* `transition_event_001`;
* `transition_event_002`;
* `transition_event_010`;
* `transition_event_011`;
* `transition_event_012`;
* `transition_event_020`;
* `transition_event_021`;
* `transition_event_022`;
* `transition_event_100`;
* `transition_event_101`;
* `transition_event_102`;
* `transition_event_110`;
* `transition_event_111`;
* `transition_event_112`;
* `transition_event_120`;
* `transition_event_121`;
* `transition_event_122`;
* `transition_event_200`;
* `transition_event_201`;
* `transition_event_202`;
* `transition_event_210`;
* `transition_event_211`;
* `transition_event_212`;
* `transition_event_220`;
* `transition_event_221`;
* `transition_event_222`.

The benchmark shall invoke the `test()` function 1,000 times and check that the counter has the expected value.


## Note

Each program is required to enable run-to-completion. This implies that FSM libraries that don't support run-to-completion can't take part in this benchmark.
