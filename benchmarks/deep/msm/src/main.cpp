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

// Level 1 state
template<int I0, int I1>
struct pseudo_exit_1: msm::front::exit_pseudo_state<state_transition_event<I0, I1, 2>>
{
};
template<int I0, int I1>
struct state_1_: msm::front::state_machine_def<state_1_<I0, I1>>
{
    using initial_state = state_2<I0, I1, 0>;

    struct transition_table: mpl::vector
    <
        Row<state_2<I0, I1, 0>, state_transition_event<I0, I1, 0>, state_2<I0, I1, 1>>,
        Row<state_2<I0, I1, 1>, state_transition_event<I0, I1, 1>, state_2<I0, I1, 2>>,
        Row<state_2<I0, I1, 2>, state_transition_event<I0, I1, 2>, pseudo_exit_1<I0, I1>>
    >{};

    template<class Event, class Fsm>
    void on_entry(const Event& event, Fsm& fsm)
    {
        pcounter = fsm.pcounter;
    }

    int* pcounter = nullptr;
};
template<int I0, int I1>
using state_1 = msm::back::state_machine<state_1_<I0, I1>>;
template<int I0, int I1>
using exit_point_1 = state_1<I0, I1>::template exit_pt<pseudo_exit_1<I0, I1>>;

// Level 0 state
template<int I0>
struct pseudo_exit_0: msm::front::exit_pseudo_state<state_transition_event<I0, 2, 2>>
{
};
template<int I0>
struct state_0_: msm::front::state_machine_def<state_0_<I0>>
{
    using initial_state = state_1<I0, 0>;

    struct transition_table: mpl::vector
    <
        Row<exit_point_1<I0, 0>, state_transition_event<I0, 0, 2>, state_1<I0, 1>>,
        Row<exit_point_1<I0, 1>, state_transition_event<I0, 1, 2>, state_1<I0, 2>>,
        Row<exit_point_1<I0, 2>, state_transition_event<I0, 2, 2>, pseudo_exit_0<I0>>
    >{};

    template<class Event, class Fsm>
    void on_entry(const Event& event, Fsm& fsm)
    {
        pcounter = &fsm.counter;
    }

    int* pcounter = nullptr;
};
template<int I0>
using state_0 = msm::back::state_machine<state_0_<I0>>;
template<int I0>
using exit_point_0 = state_0<I0>::template exit_pt<pseudo_exit_0<I0>>;

struct fsm_: public msm::front::state_machine_def<fsm_>
{
    using initial_state = state_0<0>;

    struct transition_table: mpl::vector
    <
        Row<exit_point_0<0>, state_transition_event<0, 2, 2>, state_0<1>>,
        Row<exit_point_0<1>, state_transition_event<1, 2, 2>, state_0<2>>,
        Row<exit_point_0<2>, state_transition_event<2, 2, 2>, state_0<0>>
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
