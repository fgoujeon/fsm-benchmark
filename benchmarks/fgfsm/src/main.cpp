//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define CATCH_CONFIG_MAIN
#include <fgfsm.hpp>
#include <catch2/catch.hpp>

struct context
{
    int i = 0;
};

struct event0{};
struct event1{};
struct event2{};
struct event3{};
struct event4{};
struct event5{};
struct event6{};
struct event7{};
struct event8{};
struct event9{};
struct event_internal{};

#define STATE(NAME) \
    struct NAME \
    { \
        void on_entry(const fgfsm::any_cref&) \
        { \
            ctx.i = 1; \
        } \
 \
        void on_event(const fgfsm::any_cref&) \
        { \
            ctx.i = 2; \
        } \
 \
        void on_exit(const fgfsm::any_cref&) \
        { \
            ctx.i = 3; \
        } \
 \
        context& ctx; \
    };

STATE(state0);
STATE(state1);
STATE(state2);
STATE(state3);
STATE(state4);
STATE(state5);
STATE(state6);
STATE(state7);
STATE(state8);
STATE(state9);

#undef STATE

using transition_table = fgfsm::transition_table
<
    fgfsm::row<state0, event0, state1>,
    fgfsm::row<state1, event1, state2>,
    fgfsm::row<state2, event2, state3>,
    fgfsm::row<state3, event3, state4>,
    fgfsm::row<state4, event4, state5>,
    fgfsm::row<state5, event5, state6>,
    fgfsm::row<state6, event6, state7>,
    fgfsm::row<state7, event7, state8>,
    fgfsm::row<state8, event8, state9>,
    fgfsm::row<state9, event9, state0>
>;

using fsm = fgfsm::fsm<transition_table>;

TEST_CASE("fgfsm")
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    BENCHMARK("state transitions")
    {
        sm.process_event(event0{});
        sm.process_event(event_internal{});
        sm.process_event(event1{});
        sm.process_event(event_internal{});
        sm.process_event(event2{});
        sm.process_event(event_internal{});
        sm.process_event(event3{});
        sm.process_event(event_internal{});
        sm.process_event(event4{});
        sm.process_event(event_internal{});
        sm.process_event(event5{});
        sm.process_event(event_internal{});
        sm.process_event(event6{});
        sm.process_event(event_internal{});
        sm.process_event(event7{});
        sm.process_event(event_internal{});
        sm.process_event(event8{});
        sm.process_event(event_internal{});
        sm.process_event(event9{});
        sm.process_event(event_internal{});
        return ctx.i;
    };
}
