//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <boost/sml.hpp>
#include <queue>

struct context
{
    int counter = 0;
};

template<int Index>
struct state_tpl
{
};

template<int Index>
struct event_tpl
{
    int data = 0;
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct action
{
    void operator()(context& ctx)
    {
        ++ctx.counter;
    }
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct guard
{
    bool operator()(const event_tpl<Index>& evt)
    {
        return evt.data >= 0;
    }
};

struct large
{
    auto operator()() const
    {
        using namespace boost::sml;

        return make_transition_table
        (
#define X(N) \
    COMMA_IF_NOT_0(N) state<state_tpl<N>> + event<event_tpl<N>> [guard<N>{}] / action<N>{} = state<state_tpl<(N + 1) % PROBLEM_SIZE>>
            *COUNTER
#undef X
        );
    }
};

using fsm = boost::sml::sm
<
    large,

    //We don't need run-to-completion in this use case but we enable it to be
    //fair with Boost.MSM, which can't disable it AFAIK.
    boost::sml::process_queue<std::queue>
>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(event_tpl<N>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
