//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#define BOOST_MPL_LIMIT_MAP_SIZE 50

#include "common.hpp"
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

template<int Index>
struct state_transition_event
{
};

struct fsm_;

// Lowest level state template
template<int Id>
struct state_0: msm::front::state<>
{
    template<class Event, class Fsm>
    void on_exit(const Event& event, Fsm& fsm)
    {
        if constexpr (std::is_same_v<Fsm, boost::msm::back::state_machine<fsm_>>)
        {
            fsm.counter += Id;
        }
        else
        {
            *fsm.pcounter += Id;
        }
    }
};

// Intermediate level state templates
#define STATE_TEMPLATE(level, next_level) \
    template<int Id> \
    struct state_##level##_: msm::front::state_machine_def<state_##level##_<Id>> \
    { \
        using initial_state = state_##next_level<state_id(Id, next_level, 0)>; \
 \
        struct transition_table: mpl::vector \
        < \
            Row<state_##next_level<state_id(Id, next_level, 0)>, state_transition_event<state_id(Id, next_level, 0)>, state_##next_level<state_id(Id, next_level, 1)>>, \
            Row<state_##next_level<state_id(Id, next_level, 1)>, state_transition_event<state_id(Id, next_level, 1)>, state_##next_level<state_id(Id, next_level, 2)>> \
        >{}; \
 \
        template<class Event, class Fsm> \
        void on_entry(const Event& event, Fsm& fsm) \
        { \
            if constexpr (std::is_same_v<Fsm, boost::msm::back::state_machine<fsm_>>) \
            { \
                pcounter = &fsm.counter; \
            } \
            else \
            { \
                pcounter = fsm.pcounter; \
            } \
        } \
 \
        int* pcounter = nullptr; \
    }; \
    template<int Id> \
    using state_##level = msm::back::state_machine<state_##level##_<Id>>;
STATE_TEMPLATE(1, 0)
STATE_TEMPLATE(2, 1)
STATE_TEMPLATE(3, 2)
#undef STATE_TEMPLATE

// FSM
struct fsm_: public msm::front::state_machine_def<fsm_>
{
    using initial_state = state_3<state_id(base, 3, 0)>;

    struct transition_table: mpl::vector
    <
        Row<state_3<state_id(base, 3, 0)>, state_transition_event<state_id(base, 3, 0)>, state_3<state_id(base, 3, 1)>>,
        Row<state_3<state_id(base, 3, 1)>, state_transition_event<state_id(base, 3, 1)>, state_3<state_id(base, 3, 2)>>,
        Row<state_3<state_id(base, 3, 2)>, state_transition_event<state_id(base, 3, 2)>, state_3<state_id(base, 3, 0)>>
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
#define X(index) \
    sm.process_event(state_transition_event<index>{});
        COUNTER
#undef X
    }

    return sm.counter;
}
