//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define CATCH_CONFIG_MAIN
#include <tinyfsm.hpp>
#include <catch2/catch.hpp>
#include <iostream>

#define EVENT(NAME) \
    struct NAME: tinyfsm::Event{};

EVENT(event0);
EVENT(event1);
EVENT(event2);
EVENT(event3);
EVENT(event4);
EVENT(event5);
EVENT(event6);
EVENT(event7);
EVENT(event8);
EVENT(event9);

#undef EVENT

class fsm: public tinyfsm::Fsm<fsm>
{
    public:
        void react(const tinyfsm::Event&)
        {
        }

        virtual void react(const event0&){}
        virtual void react(const event1&){}
        virtual void react(const event2&){}
        virtual void react(const event3&){}
        virtual void react(const event4&){}
        virtual void react(const event5&){}
        virtual void react(const event6&){}
        virtual void react(const event7&){}
        virtual void react(const event8&){}
        virtual void react(const event9&){}

        //I could have make it nonvirtual because entry() functions don't
        //make anything. This would make transitions faster. But a real-life
        //project would probably need to implement entry actions.
        virtual void entry(){}

        void exit(){}
};

class state0;
class state1;
class state2;
class state3;
class state4;
class state5;
class state6;
class state7;
class state8;
class state9;

#define TRANSITION(START_STATE, EVENT, TARGET_STATE) \
    class START_STATE: public fsm \
    { \
        void entry() override \
        { \
        } \
 \
        void react(const EVENT&) override \
        { \
            transit<TARGET_STATE>(); \
        } \
    };

TRANSITION(state0, event0, state1)
TRANSITION(state1, event1, state2)
TRANSITION(state2, event2, state3)
TRANSITION(state3, event3, state4)
TRANSITION(state4, event4, state5)
TRANSITION(state5, event5, state6)
TRANSITION(state6, event6, state7)
TRANSITION(state7, event7, state8)
TRANSITION(state8, event8, state9)
TRANSITION(state9, event9, state0)

#undef TRANSITION

FSM_INITIAL_STATE(fsm, state0)

TEST_CASE("tinyfsm")
{
    auto sm = fsm{};
    sm.start();

    BENCHMARK("state transitions")
    {
        sm.dispatch(event0{});
        sm.dispatch(event1{});
        sm.dispatch(event2{});
        sm.dispatch(event3{});
        sm.dispatch(event4{});
        sm.dispatch(event5{});
        sm.dispatch(event6{});
        sm.dispatch(event7{});
        sm.dispatch(event8{});
        sm.dispatch(event9{});
    };
}
