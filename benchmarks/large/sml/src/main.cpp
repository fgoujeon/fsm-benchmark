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
struct state_transition_event
{
    int two = 2;
};

struct internal_transition_event
{
    int two = 2;
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct state_transition_action
{
    void operator()(const state_transition_event<Index>& evt, context& ctx)
    {
        ctx.counter = (ctx.counter + 1) * evt.two;
    }
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct internal_transition_action
{
    void operator()(const internal_transition_event& evt, context& ctx)
    {
        ctx.counter /= evt.two;
    }
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct exit_action
{
    void operator()
    (
        boost::sml::back::process<internal_transition_event> process
    )
    {
        process(internal_transition_event{});
    }
};

//Note: Using a constexpr lambda makes the build slightly slower (at least on GCC)
template<int Index>
struct guard
{
    bool operator()(const state_transition_event<Index>& evt)
    {
        return evt.two >= 0;
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
    COMMA_IF_NOT_0(N) state<state_tpl<N>> + event<state_transition_event<N>> [guard<N>{}] / state_transition_action<N>{} = state<state_tpl<(N + 1) % PROBLEM_SIZE>> \
    , state<state_tpl<N>> + event<internal_transition_event> / internal_transition_action<N>{}
            *COUNTER
#undef X

#define X(N) \
    , state<state_tpl<N>> + on_exit<_> / exit_action<N>{}
            COUNTER
#undef X
        );
    }
};

using fsm = boost::sml::sm
<
    large,
    boost::sml::process_queue<std::queue> //Enable run-to-completion
>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
