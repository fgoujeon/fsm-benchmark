//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <fgfsm.hpp>

struct context
{
    int counter = 0;
};

template<int Index>
struct state{};

template<int Index>
struct event
{
    int data = 0;
};

template<int Index>
struct action
{
    void execute()
    {
        ++ctx.counter;
    }

    context& ctx;
};

template<int Index>
struct guard
{
    bool check(const event<Index>& evt)
    {
        return evt.data >= 0;
    }
};

struct fsm_configuration: fgfsm::fsm_configuration
{
    using transition_table = fgfsm::transition_table
    <
#define X(N) \
        COMMA_IF_NOT_0(N) fgfsm::row<state<N>, event<N>, state<(N + 1) % PROBLEM_SIZE>, action<N>, guard<N>>
        COUNTER
#undef X
    >;

    //We don't need run-to-completion in this use case but we enable it to be
    //fair with Boost.MSM, which can't disable it AFAIK.
    static constexpr auto enable_run_to_completion = true;

    static constexpr auto enable_in_state_internal_transitions = false;
};

using fsm = fgfsm::fsm<fsm_configuration>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(event<N>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
