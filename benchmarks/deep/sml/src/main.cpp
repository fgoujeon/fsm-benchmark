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

template<int Index>
struct state_transition_event
{
};

// Level 2 state
template<int Id>
struct state_0
{
};
template<int Id>
constexpr auto state_0_exit_action =
    [](context& ctx)
    {
        ctx.counter += Id;
    };

// Level 1 state
template<int Id>
struct state_1
{
    auto operator()() const noexcept
    {
        using namespace sml;

        return make_transition_table(
            // State transitions
            *state<state_0<state_id(Id, 0, 0)>> + event<state_transition_event<state_id(Id, 0, 0)>> = state<state_0<state_id(Id, 0, 1)>>
            ,state<state_0<state_id(Id, 0, 1)>> + event<state_transition_event<state_id(Id, 0, 1)>> = state<state_0<state_id(Id, 0, 2)>>

            // Exit actions
            ,state<state_0<state_id(Id, 0, 0)>> + sml::on_exit<_> / state_0_exit_action<state_id(Id, 0, 0)>
            ,state<state_0<state_id(Id, 0, 1)>> + sml::on_exit<_> / state_0_exit_action<state_id(Id, 0, 1)>
            ,state<state_0<state_id(Id, 0, 2)>> + sml::on_exit<_> / state_0_exit_action<state_id(Id, 0, 2)>
            );
    }
};

// Level 2 state
template<int Id>
struct state_2
{
    auto operator()() const noexcept
    {
        using namespace sml;

        return make_transition_table(
            // State transitions
            *state<state_1<state_id(Id, 1, 0)>> + event<state_transition_event<state_id(Id, 1, 0)>> = state<state_1<state_id(Id, 1, 1)>>
            ,state<state_1<state_id(Id, 1, 1)>> + event<state_transition_event<state_id(Id, 1, 1)>> = state<state_1<state_id(Id, 1, 2)>>
            );
    }
};

// Level 3 state
template<int Id>
struct state_3
{
    auto operator()() const noexcept
    {
        using namespace sml;

        return make_transition_table(
            // State transitions
            *state<state_2<state_id(Id, 2, 0)>> + event<state_transition_event<state_id(Id, 2, 0)>> = state<state_2<state_id(Id, 2, 1)>>
            ,state<state_2<state_id(Id, 2, 1)>> + event<state_transition_event<state_id(Id, 2, 1)>> = state<state_2<state_id(Id, 2, 2)>>
            );
    }
};

// FSM
struct transition_table
{
    auto operator()() const
    {
        using namespace boost::sml;

        return make_transition_table(
            *state<state_3<state_id(base, 3, 0)>> + event<state_transition_event<state_id(base, 3, 0)>> = state<state_3<state_id(base, 3, 1)>>
            ,state<state_3<state_id(base, 3, 1)>> + event<state_transition_event<state_id(base, 3, 1)>> = state<state_3<state_id(base, 3, 2)>>
            ,state<state_3<state_id(base, 3, 2)>> + event<state_transition_event<state_id(base, 3, 2)>> = state<state_3<state_id(base, 3, 0)>>
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
#define X(index) \
    sm.process_event(state_transition_event<index>{});
        COUNTER
#undef X
    }

    return ctx.counter;
}
