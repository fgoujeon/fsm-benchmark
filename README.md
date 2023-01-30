This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

**Disclaimer: I'm the author of AweSM.** Obviously, I've tried my best to make the test as fair as possible for every library. However, since I'm only an expert in my own library, I might have done mistakes. Please feel free to check the implementations and contact me if something has to be fixed.

## Results

### Visual Studio

* Hardware: Intel i7 8850H, 32.0 GiB RAM
* System: Windows 11
* Compiler: Visual Studio 2017

Best results of 5 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.17            | 4.465 s    | 2.200 s        | 33.5 KiB    |
| **Boost.MSM**               | 20.620 s   | 2.116 s        | 54.5 KiB    |
| **[Boost::ext].SML** v1.1.6 | 5.955 s    | 2.235 s        | 36.0 KiB    |

### GCC

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: GCC 12.2.1

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.17            | 3.354 s    | 0.454 s        | 55.8 KiB    |
| **Boost.MSM**               | 21.609 s   | 2.436 s        | 316.1 KiB   |
| **[Boost::ext].SML** v1.1.6 | 6.942 s    | 0.494 s        | 595.0 KiB   |

### Clang

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: Clang 15.0.7

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.17            | 3.972 s    | 0.611 s        | 81.2 KiB    |
| **Boost.MSM**               | 16.300 s   | 2.936 s        | 302.7 KiB   |
| **[Boost::ext].SML** v1.1.6 | 8.141 s    | 0.515 s        | 732.4 KiB   |

## The Test

The repository defines one program per library. Each program must implement, using its assigned library, the test described below.

The test tries to mimic a real-life large FSM. It consists of:

* a counter (under the form of an `int` variable);
* a large FSM:
  * which defines:
    * 25 states (*state<sub>0</sub>* to *state<sub>24</sub>*);
    * 25 event types for state transitions (*sevent<sub>0</sub>* to *sevent<sub>24</sub>*);
    * 1 event type for internal transitions (*ievent*);
    * 25 state transition actions (*saction<sub>0</sub>* to *saction<sub>24</sub>*);
    * 25 internal transition actions (*iaction<sub>0</sub>* to *iaction<sub>24</sub>*);
    * 25 state entry actions (*eaction<sub>0</sub>* to *eaction<sub>24</sub>*);
    * 25 guards;
  * whose initial state is *state<sub>0</sub>*;
  * which transitions from *state<sub>n</sub>* to *state<sub>(n+1)%25</sub>* and executes *saction<sub>n</sub>* whenever it receives *sevent<sub>n</sub>* and *guard<sub>n</sub>* returns true;
  * whose *state<sub>n</sub>* executes *iaction<sub>n</sub>* whenever it receives *ievent*;
  * whose all events contain an `int` data whose value is `1`;
  * whose state transition actions and internal transition actions add the event data to the counter (effectively incrementing the counter);
  * whose state entry actions make the FSM process *ievent* (in order to test run-to-completion);
  * whose all guards check that the event data is positive (effectively returning `true` every time);
* a `test()` function that:
  * creates the counter;
  * creates the FSM;
  * makes the FSM perform 25 state transitions from *state<sub>0</sub>* to *state<sub>24</sub>* and back to *state<sub>0</sub>*, 1000 times;
  * returns the value of the counter;
* a `main()` function that calls the `test()` function 1,000 times and checks that the counter has the expected value.

Also, each program is required to enable run-to-completion (as most real-life applications do), even if it doesn't affect the result of this test. This implies that FSM libraries that don't support run-to-completion can't take part in this benchmark.
