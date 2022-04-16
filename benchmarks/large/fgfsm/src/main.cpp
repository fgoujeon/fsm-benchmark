//Copyright Florian Goujeon 2021 - 2022.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fgfsm

#include <fgfsm.hpp>

struct context
{
    int side_effect = 0;
};

template<int Id>
struct state
{
    void on_entry()
    {
    }

    void on_exit()
    {
    }

    context& ctx;
};

template<int Id>
struct event
{
    int data = 0;
};

template<int Id>
struct action
{
    void execute()
    {
        ++ctx.side_effect;
    }

    context& ctx;
};

template<int Id>
struct guard
{
    bool check()
    {
        return ctx.side_effect >= 0;
    }

    context& ctx;
};

using state0 = state<0>;
using state1 = state<1>;
using state2 = state<2>;
using state3 = state<3>;
using state4 = state<4>;
using state5 = state<5>;
using state6 = state<6>;
using state7 = state<7>;
using state8 = state<8>;
using state9 = state<9>;
using state10 = state<10>;
using state11 = state<11>;
using state12 = state<12>;
using state13 = state<13>;
using state14 = state<14>;
using state15 = state<15>;
using state16 = state<16>;
using state17 = state<17>;
using state18 = state<18>;
using state19 = state<19>;
using state20 = state<20>;
using state21 = state<21>;
using state22 = state<22>;
using state23 = state<23>;
using state24 = state<24>;
using state25 = state<25>;
using state26 = state<26>;
using state27 = state<27>;
using state28 = state<28>;
using state29 = state<29>;
using state30 = state<30>;
using state31 = state<31>;
using state32 = state<32>;
using state33 = state<33>;
using state34 = state<34>;
using state35 = state<35>;
using state36 = state<36>;
using state37 = state<37>;
using state38 = state<38>;
using state39 = state<39>;
using state40 = state<40>;
using state41 = state<41>;
using state42 = state<42>;
using state43 = state<43>;
using state44 = state<44>;
using state45 = state<45>;
using state46 = state<46>;
using state47 = state<47>;
using state48 = state<48>;
using state49 = state<49>;

using event0 = event<0>;
using event1 = event<1>;
using event2 = event<2>;
using event3 = event<3>;
using event4 = event<4>;
using event5 = event<5>;
using event6 = event<6>;
using event7 = event<7>;
using event8 = event<8>;
using event9 = event<9>;
using event10 = event<10>;
using event11 = event<11>;
using event12 = event<12>;
using event13 = event<13>;
using event14 = event<14>;
using event15 = event<15>;
using event16 = event<16>;
using event17 = event<17>;
using event18 = event<18>;
using event19 = event<19>;
using event20 = event<20>;
using event21 = event<21>;
using event22 = event<22>;
using event23 = event<23>;
using event24 = event<24>;
using event25 = event<25>;
using event26 = event<26>;
using event27 = event<27>;
using event28 = event<28>;
using event29 = event<29>;
using event30 = event<30>;
using event31 = event<31>;
using event32 = event<32>;
using event33 = event<33>;
using event34 = event<34>;
using event35 = event<35>;
using event36 = event<36>;
using event37 = event<37>;
using event38 = event<38>;
using event39 = event<39>;
using event40 = event<40>;
using event41 = event<41>;
using event42 = event<42>;
using event43 = event<43>;
using event44 = event<44>;
using event45 = event<45>;
using event46 = event<46>;
using event47 = event<47>;
using event48 = event<48>;
using event49 = event<49>;

using action0 = action<0>;
using action1 = action<1>;
using action2 = action<2>;
using action3 = action<3>;
using action4 = action<4>;
using action5 = action<5>;
using action6 = action<6>;
using action7 = action<7>;
using action8 = action<8>;
using action9 = action<9>;
using action10 = action<10>;
using action11 = action<11>;
using action12 = action<12>;
using action13 = action<13>;
using action14 = action<14>;
using action15 = action<15>;
using action16 = action<16>;
using action17 = action<17>;
using action18 = action<18>;
using action19 = action<19>;
using action20 = action<20>;
using action21 = action<21>;
using action22 = action<22>;
using action23 = action<23>;
using action24 = action<24>;
using action25 = action<25>;
using action26 = action<26>;
using action27 = action<27>;
using action28 = action<28>;
using action29 = action<29>;
using action30 = action<30>;
using action31 = action<31>;
using action32 = action<32>;
using action33 = action<33>;
using action34 = action<34>;
using action35 = action<35>;
using action36 = action<36>;
using action37 = action<37>;
using action38 = action<38>;
using action39 = action<39>;
using action40 = action<40>;
using action41 = action<41>;
using action42 = action<42>;
using action43 = action<43>;
using action44 = action<44>;
using action45 = action<45>;
using action46 = action<46>;
using action47 = action<47>;
using action48 = action<48>;
using action49 = action<49>;

using guard0 = guard<0>;
using guard1 = guard<1>;
using guard2 = guard<2>;
using guard3 = guard<3>;
using guard4 = guard<4>;
using guard5 = guard<5>;
using guard6 = guard<6>;
using guard7 = guard<7>;
using guard8 = guard<8>;
using guard9 = guard<9>;
using guard10 = guard<10>;
using guard11 = guard<11>;
using guard12 = guard<12>;
using guard13 = guard<13>;
using guard14 = guard<14>;
using guard15 = guard<15>;
using guard16 = guard<16>;
using guard17 = guard<17>;
using guard18 = guard<18>;
using guard19 = guard<19>;
using guard20 = guard<20>;
using guard21 = guard<21>;
using guard22 = guard<22>;
using guard23 = guard<23>;
using guard24 = guard<24>;
using guard25 = guard<25>;
using guard26 = guard<26>;
using guard27 = guard<27>;
using guard28 = guard<28>;
using guard29 = guard<29>;
using guard30 = guard<30>;
using guard31 = guard<31>;
using guard32 = guard<32>;
using guard33 = guard<33>;
using guard34 = guard<34>;
using guard35 = guard<35>;
using guard36 = guard<36>;
using guard37 = guard<37>;
using guard38 = guard<38>;
using guard39 = guard<39>;
using guard40 = guard<40>;
using guard41 = guard<41>;
using guard42 = guard<42>;
using guard43 = guard<43>;
using guard44 = guard<44>;
using guard45 = guard<45>;
using guard46 = guard<46>;
using guard47 = guard<47>;
using guard48 = guard<48>;
using guard49 = guard<49>;

using transition_table = fgfsm::transition_table
<
    fgfsm::row<state0,  event0,  state1,  action0,  guard0>,
    fgfsm::row<state1,  event1,  state2,  action1,  guard1>,
    fgfsm::row<state2,  event2,  state3,  action2,  guard2>,
    fgfsm::row<state3,  event3,  state4,  action3,  guard3>,
    fgfsm::row<state4,  event4,  state5,  action4,  guard4>,
    fgfsm::row<state5,  event5,  state6,  action5,  guard5>,
    fgfsm::row<state6,  event6,  state7,  action6,  guard6>,
    fgfsm::row<state7,  event7,  state8,  action7,  guard7>,
    fgfsm::row<state8,  event8,  state9,  action8,  guard8>,
    fgfsm::row<state9,  event9,  state10, action9,  guard9>,
    fgfsm::row<state10, event10, state11, action10, guard10>,
    fgfsm::row<state11, event11, state12, action11, guard11>,
    fgfsm::row<state12, event12, state13, action12, guard12>,
    fgfsm::row<state13, event13, state14, action13, guard13>,
    fgfsm::row<state14, event14, state15, action14, guard14>,
    fgfsm::row<state15, event15, state16, action15, guard15>,
    fgfsm::row<state16, event16, state17, action16, guard16>,
    fgfsm::row<state17, event17, state18, action17, guard17>,
    fgfsm::row<state18, event18, state19, action18, guard18>,
    fgfsm::row<state19, event19, state20, action19, guard19>,
    fgfsm::row<state20, event20, state21, action20, guard20>,
    fgfsm::row<state21, event21, state22, action21, guard21>,
    fgfsm::row<state22, event22, state23, action22, guard22>,
    fgfsm::row<state23, event23, state24, action23, guard23>,
    fgfsm::row<state24, event24, state25, action24, guard24>,
    fgfsm::row<state25, event25, state26, action25, guard25>,
    fgfsm::row<state26, event26, state27, action26, guard26>,
    fgfsm::row<state27, event27, state28, action27, guard27>,
    fgfsm::row<state28, event28, state29, action28, guard28>,
    fgfsm::row<state29, event29, state30, action29, guard29>,
    fgfsm::row<state30, event30, state31, action30, guard30>,
    fgfsm::row<state31, event31, state32, action31, guard31>,
    fgfsm::row<state32, event32, state33, action32, guard32>,
    fgfsm::row<state33, event33, state34, action33, guard33>,
    fgfsm::row<state34, event34, state35, action34, guard34>,
    fgfsm::row<state35, event35, state36, action35, guard35>,
    fgfsm::row<state36, event36, state37, action36, guard36>,
    fgfsm::row<state37, event37, state38, action37, guard37>,
    fgfsm::row<state38, event38, state39, action38, guard38>,
    fgfsm::row<state39, event39, state40, action39, guard39>,
    fgfsm::row<state40, event40, state41, action40, guard40>,
    fgfsm::row<state41, event41, state42, action41, guard41>,
    fgfsm::row<state42, event42, state43, action42, guard42>,
    fgfsm::row<state43, event43, state44, action43, guard43>,
    fgfsm::row<state44, event44, state45, action44, guard44>,
    fgfsm::row<state45, event45, state46, action45, guard45>,
    fgfsm::row<state46, event46, state47, action46, guard46>,
    fgfsm::row<state47, event47, state48, action47, guard47>,
    fgfsm::row<state48, event48, state49, action48, guard48>,
    fgfsm::row<state49, event49, state0,  action49, guard49>
>;

struct fsm_configuration: fgfsm::default_fsm_configuration
{
    //Disable features to be on-par with sml
    static constexpr auto enable_run_to_completion = false;
    static constexpr auto enable_in_state_internal_transitions = false;
};

using fsm = fgfsm::fsm<transition_table, fsm_configuration>;

int test()
{
    auto ctx = context{};
    auto sm = fsm{ctx};

    sm.process_event(event0{});
    sm.process_event(event1{});
    sm.process_event(event2{});
    sm.process_event(event3{});
    sm.process_event(event4{});
    sm.process_event(event5{});
    sm.process_event(event6{});
    sm.process_event(event7{});
    sm.process_event(event8{});
    sm.process_event(event9{});
    sm.process_event(event10{});
    sm.process_event(event11{});
    sm.process_event(event12{});
    sm.process_event(event13{});
    sm.process_event(event14{});
    sm.process_event(event15{});
    sm.process_event(event16{});
    sm.process_event(event17{});
    sm.process_event(event18{});
    sm.process_event(event19{});
    sm.process_event(event20{});
    sm.process_event(event21{});
    sm.process_event(event22{});
    sm.process_event(event23{});
    sm.process_event(event24{});
    sm.process_event(event25{});
    sm.process_event(event26{});
    sm.process_event(event27{});
    sm.process_event(event28{});
    sm.process_event(event29{});
    sm.process_event(event30{});
    sm.process_event(event31{});
    sm.process_event(event32{});
    sm.process_event(event33{});
    sm.process_event(event34{});
    sm.process_event(event35{});
    sm.process_event(event36{});
    sm.process_event(event37{});
    sm.process_event(event38{});
    sm.process_event(event39{});
    sm.process_event(event40{});
    sm.process_event(event41{});
    sm.process_event(event42{});
    sm.process_event(event43{});
    sm.process_event(event44{});
    sm.process_event(event45{});
    sm.process_event(event46{});
    sm.process_event(event47{});
    sm.process_event(event48{});
    sm.process_event(event49{});

    return ctx.side_effect;
}

int main()
{
    auto side_effect = 0;

    for(auto i = 0; i < 1'000'000; ++i)
    {
        side_effect += test();
    }

    if(side_effect != 50'000'000)
        throw 0;
}
