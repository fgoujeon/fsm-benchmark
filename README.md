This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

**Disclaimer: I'm the author of FGFSM.** Obviously, I've tried my best to make the test as fair as possible for every library.

## The Test

The repository defines one program per library. Each program must implement, using its own library, the test described below.

The test consists of:

* a large FSM:
  * which defines 50 states, 50 event types, 50 actions and 50 guards;
  * whose initial state is *state<sub>0</sub>*;
  * which transitions from *state<sub>n</sub>* to *state<sub>n+1</sub>* and executes *action<sub>n</sub>* whenever it receives *event<sub>n</sub>* and *guard<sub>n</sub>* returns true;
* a `test()` function that creates the FSM and makes it perform 50 state transitions from *state<sub>0</sub>* to *state<sub>49</sub>* and back to *state<sub>0</sub>*;
* a `main()` function that calls the `test()` function 10 million times.

## Results

These are the results of the benchmark executed on the following environment:

* hardware: Intel i5 750 (2.67 GHz, quad core), 9.7 GiB RAM;
* system: Arch Linux 5.17.1-arch1-1;
* compiler: G++ 11.2.0.

| | Build time | Execution time | Binary size
|--|--|--|--
| **FGFSM** 0.3.0 | 3.065 s | 0.048 s | 16488 B
| **[Boost::ext].SML** 1.1.5 | 1.787 s | 0.130 s | 165856 B
