//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <fgfsm.hpp>

struct context
{
    int side_effect = 0;
};

template<int Index>
struct state
{
    void on_entry()
    {
    }

    void on_exit()
    {
    }

    context& ctx;
};

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
        ++ctx.side_effect;
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

    context& ctx;
};

using transition_table = fgfsm::transition_table
<
#define X(N, NP1) \
    COMMA_IF_NOT_0(N) fgfsm::row<state<N>, event<N>, state<NP1>, action<N>, guard<N>>
    COUNTER_50
#undef X
>;

struct fsm_configuration: fgfsm::default_fsm_configuration
{
    //Disable features to be on-par with sml
    static constexpr auto enable_run_to_completion = false;
    static constexpr auto enable_in_state_internal_transitions = false;
};

using fsm = fgfsm::fsm<transition_table, fsm_configuration>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

#define X(N, NP1) \
    sm.process_event(event<N>{});
    COUNTER_50
#undef X

    return ctx.side_effect;
}
