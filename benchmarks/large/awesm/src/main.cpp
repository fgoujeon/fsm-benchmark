//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <awesm.hpp>

struct context
{
    int counter = 0;
};

template<int Index>
struct state_transition_event
{
    int data = 1;
};

struct internal_transition_event
{
    int data = 1;
};

template<int Index>
struct state
{
    void on_entry()
    {
        sm.process_event(internal_transition_event{});
    }

    void on_event(const internal_transition_event& evt)
    {
        ctx.counter += evt.data;
    }

    void on_exit()
    {
    }

    context& ctx;
    awesm::sm_ref<internal_transition_event> sm;
};

template<int Index>
struct state_transition_action
{
    void execute(const state_transition_event<Index>& evt)
    {
        ctx.counter += evt.data;
    }

    context& ctx;
};

template<int Index>
struct guard
{
    bool check(const state_transition_event<Index>& evt)
    {
        return evt.data >= 0;
    }
};

struct sm_configuration: awesm::sm_configuration
{
    using transition_table = awesm::transition_table
    <
#define X(N) \
        COMMA_IF_NOT_0(N) awesm::row<state<N>, state_transition_event<N>, state<(N + 1) % PROBLEM_SIZE>, state_transition_action<N>, guard<N>>
        COUNTER
#undef X
    >;
};

using sm_t = awesm::sm<sm_configuration>;

int test()
{
    auto ctx = context{};
    auto sm = sm_t{ctx};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
