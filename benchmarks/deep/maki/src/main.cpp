//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <maki.hpp>

struct context
{
    int counter = 0;
};

template<int I0, int I1, int I2>
struct state_transition_event
{
};

// Level 2 state
template<int I0, int I1, int I2>
constexpr auto state_2 = maki::state_mold{}
    .exit_action_c(
        [](auto& ctx)
        {
            constexpr auto value = compute_internal_event_value(I0, I1, I2);
            ctx.counter += value;
        });

// Level 1 state
template<int I0, int I1>
constexpr auto state_1_tt = maki::transition_table{}
    (maki::ini,          state_2<I0, I1, 0>)
    (state_2<I0, I1, 0>, state_2<I0, I1, 1>, maki::event<state_transition_event<I0, I1, 0>>)
    (state_2<I0, I1, 1>, state_2<I0, I1, 2>, maki::event<state_transition_event<I0, I1, 1>>)
    (state_2<I0, I1, 2>, maki::fin,          maki::event<state_transition_event<I0, I1, 2>>);
template<int I0, int I1>
constexpr auto state_1 = maki::state_mold{}
    .transition_tables(state_1_tt<I0, I1>);

// Level 0 state
template<int I0>
constexpr auto state_0_tt = maki::transition_table{}
    (maki::ini,      state_1<I0, 0>)
    (state_1<I0, 0>, state_1<I0, 1>)
    (state_1<I0, 1>, state_1<I0, 2>)
    (state_1<I0, 2>, maki::fin);
template<int I0>
constexpr auto state_0 = maki::state_mold{}
    .transition_tables(state_0_tt<I0>);

// FSM
constexpr auto transition_table = maki::transition_table{}
    (maki::ini,  state_0<0>)
    (state_0<0>, state_0<1>)
    (state_0<1>, state_0<2>)
    (state_0<2>, state_0<0>);
constexpr auto machine_conf = maki::machine_conf{}
    .transition_tables(transition_table)
    .context_a<context>()
    .small_event_max_size(sizeof(int))
    .process_event_now_enabled(true);
using sm_t = maki::machine<machine_conf>;

int test()
{
    auto sm = sm_t{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(i0, i1, i2) \
    sm.process_event_now(state_transition_event<i0, i1, i2>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
