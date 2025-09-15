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

template<int Index>
struct state_transition_event
{
    int two = 2;
};

struct internal_transition_event
{
    int two = 2;
};

template<int Index>
constexpr auto state = maki::state_mold{}
    .internal_action_ce<internal_transition_event>
    (
        [](context& ctx, const internal_transition_event& evt)
        {
            ctx.counter /= evt.two;
        }
    )
    .exit_action_m
    (
        [](auto& mach)
        {
            mach.push_event(internal_transition_event{});
        }
    )
;

template<int Index>
constexpr auto state_transition_action = maki::action_ce([](context& ctx, const state_transition_event<Index>& evt)
{
    ctx.counter = (ctx.counter + 1) * evt.two;
});

template<int Index>
constexpr auto guard = maki::guard_e([](const state_transition_event<Index>& evt)
{
    return evt.two >= 0;
});

constexpr auto transition_table = maki::transition_table{}
    (maki::ini, state<0>)
#define X(N) \
    (state<N>, state<(N + 1) % PROBLEM_SIZE>, maki::event<state_transition_event<N>>, state_transition_action<N>, guard<N>)
    COUNTER
#undef X
;

constexpr auto machine_conf = maki::machine_conf{}
    .transition_tables(transition_table)
    .context_a<context>()
    .small_event_max_size(sizeof(int))
    .process_event_now_enabled(true)
;

using sm_t = maki::machine<machine_conf>;

int test()
{
    auto sm = sm_t{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event_now(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
