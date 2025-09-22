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

* Hardware: AMD Ryzen 5 1600, 8.0 GiB RAM
* System: Windows 10
* Compiler: Visual Studio 2022

```batch
py run-benchmarks.py %BUILD_DIR% 3 -G "Visual Studio 17 2022" -A "x64" -D Boost_INCLUDE_DIR=%BOOST_INCLUDE_DIR% -D FSMB_FORCED_CXX_STANDARD=20
```

Best results of 3 iterations:
|                              | Build time | Execution time | Binary size |
|------------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.1               | 7.226 s    | 0.637 s        | 20.0 KiB    |
| **Boost.MSM**                | 23.857 s   | 4.291 s        | 60.5 KiB    |
| **[Boost::ext].SML** v1.1.10 | 6.714 s    | 0.809 s        | 48.0 KiB    |

### GCC

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.16.5-arch1-1
* Compiler: GCC 15.2.1

```bash
CXX=g++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_FORCED_CXX_STANDARD=20
```

Best results of 3 iterations:
|                              | Build time | Execution time | Binary size |
|------------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.1               | 1.244 s    | 0.256 s        | 24.8 KiB    |
| **Boost.MSM**                | 5.566 s    | 1.054 s        | 332.2 KiB   |
| **[Boost::ext].SML** v1.1.10 | 2.408 s    | 0.219 s        | 606.5 KiB   |

### Clang

* Hardware: AMD Ryzen 7 7800X3D, 32 GiB RAM
* System: Linux 6.16.5-arch1-1
* Compiler: Clang 20.1.8

```bash
CXX=clang++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_FORCED_CXX_STANDARD=20
```

Best results of 3 iterations:
|                              | Build time | Execution time | Binary size |
|------------------------------|-----------:|---------------:|------------:|
| **Maki** 1.0.1               | 2.501 s    | 0.134 s        | 24.6 KiB    |
| **Boost.MSM**                | 5.250 s    | 1.110 s        | 399.8 KiB   |
| **[Boost::ext].SML** v1.1.10 | 2.551 s    | 0.204 s        | 751.6 KiB   |

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
