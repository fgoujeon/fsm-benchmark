//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <boost/sml.hpp>
#include <queue>

namespace sml = boost::sml;

struct context
{
    int counter = 0;
};

template<int I0, int I1, int I2>
struct state_transition_event
{
};

// Level 2 state
template<int I0, int I1, int I2>
struct state_2
{
};
template<int I0, int I1, int I2>
constexpr auto state_2_exit_action =
    [](context& ctx)
    {
        constexpr auto value = compute_internal_event_value(I0, I1, I2);
        ctx.counter += value;
    };

// Level 1 state
template<int I0, int I1>
struct state_1
{
    auto operator()() const noexcept
    {
        using namespace sml;

        return make_transition_table(
            // State transitions
            *state<state_2<I0, I1, 0>> + event<state_transition_event<I0, I1, 0>> = state<state_2<I0, I1, 1>>
            ,state<state_2<I0, I1, 1>> + event<state_transition_event<I0, I1, 1>> = state<state_2<I0, I1, 2>>
            ,state<state_2<I0, I1, 2>> + event<state_transition_event<I0, I1, 2>> = X

            // Exit actions
            ,state<state_2<I0, I1, 0>> + sml::on_exit<_> / state_2_exit_action<I0, I1, 0>
            ,state<state_2<I0, I1, 1>> + sml::on_exit<_> / state_2_exit_action<I0, I1, 1>
            ,state<state_2<I0, I1, 2>> + sml::on_exit<_> / state_2_exit_action<I0, I1, 2>
            );
    }
};

// Level 0 state
template<int I0>
struct state_0
{
    auto operator()() const
    {
        using namespace boost::sml;

        return make_transition_table(
            *state<state_1<I0, 0>> = state<state_1<I0, 1>>
            ,state<state_1<I0, 1>> = state<state_1<I0, 2>>
            ,state<state_1<I0, 2>> = X
            );
    }
};

// Level 0 transition table
struct transition_table
{
    auto operator()() const
    {
        using namespace boost::sml;

        return make_transition_table(
            *state<state_0<0>> = state<state_0<1>>
            ,state<state_0<1>> = state<state_0<2>>
            ,state<state_0<2>> = state<state_0<0>>
            );
    }
};

using fsm = boost::sml::sm
<
    transition_table,
    boost::sml::process_queue<std::queue> //Enable run-to-completion
>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(i0, i1, i2) \
    sm.process_event(state_transition_event<i0, i1, i2>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
