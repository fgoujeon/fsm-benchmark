//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <boost/msm/backmp11/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mp11 = boost::mp11;
using namespace msm::front;

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
struct state_tpl: msm::front::state<>
{
    template<class Event, class Fsm>
    void on_exit(const Event& event, Fsm& fsm)
    {
        fsm.enqueue_event(internal_transition_event{});
    }
};

template<int Index>
struct state_transition_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        sm.counter = (sm.counter + 1) * evt.two;
    }
};

template<int Index>
struct internal_transition_action
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        sm.counter /= evt.two;
    }
};

template<int Index>
struct guard
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event& evt, Fsm& sm, SourceState&, TargetState&)
    {
        return evt.two >= 0;
    }
};

struct fsm_: public msm::front::state_machine_def<fsm_>
{
    using initial_state = state_tpl<0>;

    using transition_table = mp11::mp_list
    <
#define X(N) \
        COMMA_IF_NOT_0(N) Row<state_tpl<N>, state_transition_event<N>, state_tpl<(N + 1) % PROBLEM_SIZE>, state_transition_action<N>, guard<N>> \
        , Row<state_tpl<N>, internal_transition_event, none, internal_transition_action<N>>
        COUNTER
#undef X
    >;

    int counter = 0;
};

using fsm = msm::backmp11::state_machine<fsm_>;

int test()
{
    auto sm = fsm{};

    sm.start();

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.counter;
}
