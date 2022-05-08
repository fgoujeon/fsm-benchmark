This repository aims to benchmark various C++ FSM (Finite State Machine) libraries.

**Disclaimer: I'm the author of FGFSM.** Obviously, I've tried my best to make the test as fair as possible for every library. However, since I'm only an expert in my own library, I might have done mistakes. Please feel free to check the implementations and contact me if something has to be fixed.

## Results

<!---
### Visual Studio

* Hardware: Intel i7 8850H, 32.0 GiB RAM
* System: Windows 11
* Compiler: Visual Studio 2017

| | Build time | Execution time | Binary size
|--|--|--|--
| **FGFSM** 0.3.0 | 0.756 s | 1.157 s | 13824 B
| **[Boost::ext].SML** 1.1.5 | 4.204 s | 1.405 s | 30720 B
--->

### GCC

* Hardware: Intel i5 750, 9.7 GiB RAM
* System: Arch Linux 5.17.1-arch1-1
* Compiler: GCC 11.2.0

| | Build time | Execution time | Binary size
|--|--:|--:|--:|
| **Boost.MSM**  | 126.965 s | 1.828 s | 2334.3 kB
| **FGFSM** 0.3.4 | 8.133 s | 0.625 s | 168.2 kB
| **[Boost::ext].SML** v1.1.5 | 5.592 s | 0.457 s | 928.4 kB

## The Test

The repository defines one program per library. Each program must implement, using its assigned library, the test described below.

The test tries to mimic a real-life large FSM. It consists of:

* a counter (under the form of an `int` variable);
* a large FSM:
  * which defines:
    * 50 states (*state<sub>0</sub>* to *state<sub>49</sub>*);
    * 50 event types for state transitions (*sevent<sub>0</sub>* to *sevent<sub>49</sub>*);
    * 50 event types for internal transitions (*ievent<sub>0</sub>* to *ievent<sub>49</sub>*);
    * 50 actions for state transitions (*saction<sub>0</sub>* to *saction<sub>49</sub>*);
    * 50 actions for internal transitions (*iaction<sub>0</sub>* to *iaction<sub>49</sub>*);
    * 50 guards;
  * whose initial state is *state<sub>0</sub>*;
  * which transitions from *state<sub>n</sub>* to *state<sub>(n+1)%50</sub>* and executes *saction<sub>n</sub>* whenever it receives *sevent<sub>n</sub>* and *guard<sub>n</sub>* returns true;
  * whose *state<sub>n</sub>* executes *iaction<sub>n</sub>* whenever it receives *ievent<sub>n</sub>*;
  * whose all events contain a `int` data whose value is `1`;
  * whose all actions add the event data to the counter (effectively incrementing the counter);
  * whose all guards check that the event data is positive (effectively returning `true` every time);
* a `test()` function that:
  * creates the counter;
  * creates the FSM;
  * makes the FSM perform 50 state transitions from *state<sub>0</sub>* to *state<sub>49</sub>* and back to *state<sub>0</sub>*, 1000 times;
  * makes the FSM perform 50 internal transitions (one per state), 1000 times;
  * returns the value of the counter;
* a `main()` function that calls the `test()` function 1000 times and checks that the counter has the expected value.

Also, each program is required to enable run-to-completion (as most real-life applications do), even if this use case doesn't actually require it. This implies that FSM libraries that don't support run-to-completion can't take part in this benchmark.
