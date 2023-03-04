This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

Tested libraries are:

* [AweSM](https://github.com/fgoujeon/awesm);
* [Boost](https://www.boost.org/).MSM;
* [\[Boost::ext\].SML](https://boost-ext.github.io/sml/).

**Disclaimer: I'm the author of AweSM.** Obviously, I've tried my best to make the test as fair as possible for every library. However, since I'm only an expert in my own library, I might have done mistakes. Please feel free to check the implementations and contact me if something has to be fixed.

## Results

### Visual Studio

* Hardware: Intel i7 8850H, 32.0 GiB RAM
* System: Windows 11
* Compiler: Visual Studio 2017

Best results of 5 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.22            | 4.820 s    | 2.221 s        | 33.0 KiB    |
| **Boost.MSM**               | 20.593 s   | 2.135 s        | 54.5 KiB    |
| **[Boost::ext].SML** v1.1.6 | 6.008 s    | 2.161 s        | 36.0 KiB    |

### GCC

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: GCC 12.2.1

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.22            | 2.908 s    | 0.455 s        | 54.9 KiB    |
| **Boost.MSM**               | 21.759 s   | 2.344 s        | 315.8 KiB   |
| **[Boost::ext].SML** v1.1.6 | 6.870 s    | 0.575 s        | 581.7 KiB   |

### Clang

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 6.1.7-arch1-1
* Compiler: Clang 15.0.7

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **AweSM** 0.3.22            | 3.080 s    | 0.469 s        | 72.7 KiB    |
| **Boost.MSM**               | 16.070 s   | 2.795 s        | 302.7 KiB   |
| **[Boost::ext].SML** v1.1.6 | 7.931 s    | 0.561 s        | 734.9 KiB   |

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
