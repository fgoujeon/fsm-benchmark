//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

template<int I0, int I1, int I2>
struct state_transition_event
{
};

// Emulated level 1 state completion event
struct state_1_completion_event
{
};

// Emulated level 0 state completion event
struct state_0_completion_event
{
};

// Level 2 state
template<int I0, int I1, int I2>
struct state_2: msm::front::state<>
{
    template<class Event, class Fsm>
    void on_exit(const Event& event, Fsm& fsm)
    {
        constexpr auto value = compute_internal_event_value(I0, I1, I2);
        *fsm.pcounter += value;
    }
};

// Level 1 emulated final state
template<int I0, int I1>
struct state_1_fin: msm::front::state<>
{
};

struct state_1_fin_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(
        const Event& /*evt*/,
        Fsm& fsm,
        SourceState&,
        TargetState&)
    {
        fsm.process_state_1_completion_event();
    }
};

// Level 1 state
template<int I0, int I1>
struct state_1_: msm::front::state_machine_def<state_1_<I0, I1>>
{
    using initial_state = state_2<I0, I1, 0>;

    struct transition_table: mpl::vector
    <
        Row<state_2<I0, I1, 0>, state_transition_event<I0, I1, 0>, state_2<I0, I1, 1>>,
        Row<state_2<I0, I1, 1>, state_transition_event<I0, I1, 1>, state_2<I0, I1, 2>>,
        Row<state_2<I0, I1, 2>, state_transition_event<I0, I1, 2>, state_1_fin<I0, I1>, state_1_fin_action>
    >{};

    template<class Event, class Fsm>
    void on_entry(const Event& event, Fsm& fsm)
    {
        pcounter = fsm.pcounter;
        process_state_1_completion_event = fsm.process_state_1_completion_event;
    }

    int* pcounter = nullptr;
    std::function<void()> process_state_1_completion_event;
};
template<int I0, int I1>
using state_1 = msm::back::state_machine<state_1_<I0, I1>>;

// Level 0 emulated final state
template<int I0>
struct state_0_fin: msm::front::state<>
{
};

struct state_0_fin_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(
        const Event& evt,
        Fsm& fsm,
        SourceState&,
        TargetState&)
    {
        fsm.process_state_0_completion_event();
    }
};

// Level 0 state
template<int I0>
struct state_0_: msm::front::state_machine_def<state_0_<I0>>
{
    using initial_state = state_1<I0, 0>;

    struct transition_table: mpl::vector
    <
        Row<state_1<I0, 0>, state_1_completion_event, state_1<I0, 1>>,
        Row<state_1<I0, 1>, state_1_completion_event, state_1<I0, 2>>,
        Row<state_1<I0, 2>, state_1_completion_event, state_0_fin<I0>, state_0_fin_action>
    >{};

    template<class Event, class Fsm>
    void on_entry(const Event& event, Fsm& fsm)
    {
        pcounter = &fsm.counter;
        process_state_1_completion_event =
            [&fsm]
            {
                fsm.process_event(state_1_completion_event{});
            };
        process_state_0_completion_event =
            [&fsm]
            {
                fsm.process_event(state_0_completion_event{});
            };
    }

    int* pcounter = nullptr;
    std::function<void()> process_state_1_completion_event;
    std::function<void()> process_state_0_completion_event;
};
template<int I0>
using state_0 = msm::back::state_machine<state_0_<I0>>;

struct fsm_: public msm::front::state_machine_def<fsm_>
{
    using initial_state = state_0<0>;

    struct transition_table: mpl::vector
    <
        Row<state_0<0>, state_0_completion_event, state_0<1>>,
        Row<state_0<1>, state_0_completion_event, state_0<2>>,
        Row<state_0<2>, state_0_completion_event, state_0<0>>
    >{};

    int counter = 0;
};

using fsm = msm::back::state_machine<fsm_>;

int test()
{
    auto sm = fsm{};

    sm.start();

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(i0, i1, i2) \
    sm.process_event(state_transition_event<i0, i1, i2>{});
        COUNTER
#undef X
    }

    return sm.counter;
}
