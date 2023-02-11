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
    <
        awesm::state_options::on_event_any_of<internal_transition_event>,
        awesm::state_options::on_exit_any
    >;

    void on_event(const internal_transition_event& evt)
    {
        ctx.counter /= evt.two;
    }

    void on_exit()
    {
        sm.process_event(internal_transition_event{});
    }

    awesm::sm_ref<internal_transition_event> sm;
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
    <
#define X(N) \
        COMMA_IF_NOT_0(N) awesm::row<state<N>, state_transition_event<N>, state<(N + 1) % PROBLEM_SIZE>, state_transition_action<N>, guard<N>>
        COUNTER
#undef X
    >;
}

struct sm_def
{
    using conf = awesm::sm_conf
    <
        sm_transition_table,
        context,
        awesm::sm_options::small_event_max_size<sizeof(int)>
    >;
};

using sm_t = awesm::sm<sm_def>;

int test()
{
    auto ctx = context{};
    auto sm = sm_t{ctx};

    sm.start();

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
