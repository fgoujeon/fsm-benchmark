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
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 0.4.2              | 7.445 s    | 0.624 s        | 21.5 KiB    |
| **Boost.MSM**               | 20.236 s   | 4.430 s        | 67.5 KiB    |
| **[Boost::ext].SML** v1.1.8 | 5.675 s    | 0.496 s        | 48.5 KiB    |

### GCC

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Linux 6.7.0-arch3-1
* Compiler: GCC 13.2.1

```bash
CXX=g++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_FORCED_CXX_STANDARD=20
```

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 0.4.2              | 4.010 s    | 0.378 s        | 25.9 KiB    |
| **Boost.MSM**               | 20.670 s   | 2.440 s        | 319.8 KiB   |
| **[Boost::ext].SML** v1.1.8 | 7.346 s    | 0.735 s        | 585.7 KiB   |

### Clang

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Linux 6.7.0-arch3-1
* Compiler: Clang 16.0.6

```bash
CXX=clang++ python run-benchmarks.py ${BUILD_DIR} 3 -D CMAKE_BUILD_TYPE=Release -D FSMB_FORCED_CXX_STANDARD=20
```

Best results of 3 iterations:
|                             | Build time | Execution time | Binary size |
|-----------------------------|-----------:|---------------:|------------:|
| **Maki** 0.4.2              | 7.916 s    | 0.435 s        | 25.7 KiB    |
| **Boost.MSM**               | 19.398 s   | 2.939 s        | 302.7 KiB   |
| **[Boost::ext].SML** v1.1.8 | 9.169 s    | 0.629 s        | 742.8 KiB   |

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
