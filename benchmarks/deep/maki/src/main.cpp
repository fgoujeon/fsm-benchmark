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
struct state_transition_event_t
{
};
template<int Index>
constexpr auto state_transition_event = maki::event<state_transition_event_t<Index>>;

// Lowest level state template
template<int Id>
constexpr auto state_0 = maki::state_mold{}
    .exit_action_c(
        [](context& ctx)
        {
            ctx.counter += Id;
        });

// Intermediate level state templates
#define STATE_TEMPLATE(level, next_level) \
    template<int Id> \
    constexpr auto state_##level##_tt = maki::transition_table{} \
        (maki::ini,                                       state_##next_level<state_id(Id, next_level, 0)>) \
        (state_##next_level<state_id(Id, next_level, 0)>, state_##next_level<state_id(Id, next_level, 1)>, state_transition_event<state_id(Id, next_level, 0)>) \
        (state_##next_level<state_id(Id, next_level, 1)>, state_##next_level<state_id(Id, next_level, 2)>, state_transition_event<state_id(Id, next_level, 1)>); \
    template<int Id> \
    constexpr auto state_##level = maki::state_mold{} \
        .transition_tables(state_##level##_tt<Id>);
STATE_TEMPLATE(1, 0)
STATE_TEMPLATE(2, 1)
STATE_TEMPLATE(3, 2)
#undef STATE_TEMPLATE

// FSM
constexpr auto transition_table = maki::transition_table{}
    (maki::ini,                     state_3<state_id(base, 3, 0)>)
    (state_3<state_id(base, 3, 0)>, state_3<state_id(base, 3, 1)>, state_transition_event<state_id(base, 3, 0)>)
    (state_3<state_id(base, 3, 1)>, state_3<state_id(base, 3, 2)>, state_transition_event<state_id(base, 3, 1)>)
    (state_3<state_id(base, 3, 2)>, state_3<state_id(base, 3, 0)>, state_transition_event<state_id(base, 3, 2)>);
struct machine_conf
{
    static constexpr auto value = maki::machine_conf{}
        .transition_tables(transition_table)
        .context_a<context>()
        .small_event_max_size(sizeof(int))
        .process_event_now_enabled(true);
};
using sm_t = maki::machine<machine_conf>;

int test()
{
    auto sm = sm_t{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(index) \
    sm.process_event_now(state_transition_event_t<index>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
