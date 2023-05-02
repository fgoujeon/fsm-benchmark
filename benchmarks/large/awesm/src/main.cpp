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
    int two = 2;
};

struct internal_transition_event
{
    int two = 2;
};

template<int Index>
struct state
{
    using conf = awesm::state_conf
        ::on_event<internal_transition_event>
        ::on_exit
    ;

    void on_event(const internal_transition_event& evt)
    {
        ctx.counter /= evt.two;
    }

    template<class Sm, class Event>
    void on_exit(Sm& sm, const Event& /*event*/)
    {
        sm.queue_event(internal_transition_event{});
    }

    context& ctx;
};

template<int Index>
void state_transition_action(context& ctx, const state_transition_event<Index>& evt)
{
    ctx.counter = (ctx.counter + 1) * evt.two;
}

template<int Index>
bool guard(context& /*ctx*/, const state_transition_event<Index>& evt)
{
    return evt.two >= 0;
}

auto sm_transition_table()
{
    return awesm::transition_table
#define X(N) \
    ::add<state<N>, state_transition_event<N>, state<(N + 1) % PROBLEM_SIZE>, state_transition_action<N>, guard<N>>
        COUNTER
#undef X
    {};
}

struct sm_def
{
    using conf = awesm::sm_conf
        ::transition_tables<decltype(sm_transition_table())>
        ::context<context>
        ::small_event_max_size<sizeof(int)>
    ;
};

using sm_t = awesm::sm<sm_def>;

int test()
{
    auto sm = sm_t{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
