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
| **Maki** 1.0.4              | 6.768 s    | 0.389 s        | 19.5 KiB    |
| **MSM** 1.90.0              | 24.634 s   | 1.423 s        | 59.0 KiB    |
| **MSM (`backmp11`)** 1.90.0 | 6.584 s    | 1.200 s        | 60.0 KiB    |
| **SML** 1.1.10              | 7.051 s    | 0.797 s        | 48.0 KiB    |

Deep FSM (best of 3 runs):
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.4              | 13.934 s   | 0.484 s        | 25.5 KiB    |
| **MSM** 1.90.0              | 34.637 s   | 3.462 s        | 170.0 KiB   |
| **MSM (`backmp11`)** 1.90.0 | 10.296 s   | 3.703 s        | 238.5 KiB   |
| **SML** 1.1.13              | 9.639 s    | 1.758 s        | 150.0 KiB   |

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
