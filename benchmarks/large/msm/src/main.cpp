//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE PROBLEM_SIZE_X_2
#define BOOST_MPL_LIMIT_MAP_SIZE PROBLEM_SIZE_X_2

#include "common.hpp"
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

template<int Index>
struct state_tpl: msm::front::state<>
{
};

template<int Index>
struct state_transition_event
{
    int data = 1;
};

template<int Index>
struct internal_transition_event
{
    int data = 1;
};

template<int Index>
struct state_transition_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        sm.counter += evt.data;
    }
};

template<int Index>
struct internal_transition_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        sm.counter += evt.data;
    }
};

template<int Index>
struct guard
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        return evt.data >= 0;
    }
};

struct fsm_: public msm::front::state_machine_def<fsm_>
{
    using initial_state = state_tpl<0>;

    struct transition_table: mpl::vector
    <
#define X(N) \
        COMMA_IF_NOT_0(N) Row<state_tpl<N>, state_transition_event<N>, state_tpl<(N + 1) % PROBLEM_SIZE>, state_transition_action<N>, guard<N>> \
        , Row<state_tpl<N>, internal_transition_event<N>, none, internal_transition_action<N>>
        COUNTER
#undef X
    >{};

    int counter = 0;
};

using fsm = msm::back::state_machine<fsm_>;

int test()
{
    auto sm = fsm{};

    sm.start();

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(internal_transition_event<N>{}); \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.counter;
}
