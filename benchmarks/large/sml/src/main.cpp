//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <boost/sml.hpp>

struct context
{
    int side_effect = 0;
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

//Note: Using a constexpr lambda make build slightly slower
template<int Index>
struct action
{
    void operator()(context& ctx)
    {
        ++ctx.side_effect;
    }
};

//Note: Using a constexpr lambda make build slightly slower
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
            *state<state_tpl<0>> + event<event_tpl<0>> [guard<0>{}] / action<0>{} = state<state_tpl<1>>

#define X(N, NP1) \
    , state<state_tpl<N>> + event<event_tpl<N>> [guard<N>{}] / action<N>{} = state<state_tpl<NP1>>
            COUNTER_50
#undef X
        );
    }
};

int test()
{
    auto ctx = context{};
    auto sm = boost::sml::sm<large>{ctx};

#define X(N, NP1) \
    sm.process_event(event_tpl<N>{});
    COUNTER_50
#undef X

    return ctx.side_effect;
}
