//Copyright Florian Goujeon 2021 - 2022.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fgfsm

#include <boost/sml.hpp>
#include <cassert>

struct context
{
    int side_effect = 0;
};

template<int Id>
struct event_tpl
{
    int data = 0;
};

template<int Id>
struct action
{
    void operator()(context& ctx)
    {
        ++ctx.side_effect;
    }
};

template<int Id>
struct guard
{
    bool operator()(const event_tpl<Id>& evt)
    {
        return evt.data >= 0;
    }
};

using event0 = event_tpl<0>;
using event1 = event_tpl<1>;
using event2 = event_tpl<2>;
using event3 = event_tpl<3>;
using event4 = event_tpl<4>;
using event5 = event_tpl<5>;
using event6 = event_tpl<6>;
using event7 = event_tpl<7>;
using event8 = event_tpl<8>;
using event9 = event_tpl<9>;
using event10 = event_tpl<10>;
using event11 = event_tpl<11>;
using event12 = event_tpl<12>;
using event13 = event_tpl<13>;
using event14 = event_tpl<14>;
using event15 = event_tpl<15>;
using event16 = event_tpl<16>;
using event17 = event_tpl<17>;
using event18 = event_tpl<18>;
using event19 = event_tpl<19>;
using event20 = event_tpl<20>;
using event21 = event_tpl<21>;
using event22 = event_tpl<22>;
using event23 = event_tpl<23>;
using event24 = event_tpl<24>;
using event25 = event_tpl<25>;
using event26 = event_tpl<26>;
using event27 = event_tpl<27>;
using event28 = event_tpl<28>;
using event29 = event_tpl<29>;
using event30 = event_tpl<30>;
using event31 = event_tpl<31>;
using event32 = event_tpl<32>;
using event33 = event_tpl<33>;
using event34 = event_tpl<34>;
using event35 = event_tpl<35>;
using event36 = event_tpl<36>;
using event37 = event_tpl<37>;
using event38 = event_tpl<38>;
using event39 = event_tpl<39>;
using event40 = event_tpl<40>;
using event41 = event_tpl<41>;
using event42 = event_tpl<42>;
using event43 = event_tpl<43>;
using event44 = event_tpl<44>;
using event45 = event_tpl<45>;
using event46 = event_tpl<46>;
using event47 = event_tpl<47>;
using event48 = event_tpl<48>;
using event49 = event_tpl<49>;

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

struct large
{
    auto operator()() const
    {
        using namespace boost::sml;

        return make_transition_table
        (
            *"state0"_s + event<event0>  [guard0{}]  / action0{}  = "state1"_s,
            "state1"_s  + event<event1>  [guard1{}]  / action1{}  = "state2"_s,
            "state2"_s  + event<event2>  [guard2{}]  / action2{}  = "state3"_s,
            "state3"_s  + event<event3>  [guard3{}]  / action3{}  = "state4"_s,
            "state4"_s  + event<event4>  [guard4{}]  / action4{}  = "state5"_s,
            "state5"_s  + event<event5>  [guard5{}]  / action5{}  = "state6"_s,
            "state6"_s  + event<event6>  [guard6{}]  / action6{}  = "state7"_s,
            "state7"_s  + event<event7>  [guard7{}]  / action7{}  = "state8"_s,
            "state8"_s  + event<event8>  [guard8{}]  / action8{}  = "state9"_s,
            "state9"_s  + event<event9>  [guard9{}]  / action9{}  = "state10"_s,
            "state10"_s + event<event10> [guard10{}] / action10{} = "state11"_s,
            "state11"_s + event<event11> [guard11{}] / action11{} = "state12"_s,
            "state12"_s + event<event12> [guard12{}] / action12{} = "state13"_s,
            "state13"_s + event<event13> [guard13{}] / action13{} = "state14"_s,
            "state14"_s + event<event14> [guard14{}] / action14{} = "state15"_s,
            "state15"_s + event<event15> [guard15{}] / action15{} = "state16"_s,
            "state16"_s + event<event16> [guard16{}] / action16{} = "state17"_s,
            "state17"_s + event<event17> [guard17{}] / action17{} = "state18"_s,
            "state18"_s + event<event18> [guard18{}] / action18{} = "state19"_s,
            "state19"_s + event<event19> [guard19{}] / action19{} = "state20"_s,
            "state20"_s + event<event20> [guard20{}] / action20{} = "state21"_s,
            "state21"_s + event<event21> [guard21{}] / action21{} = "state22"_s,
            "state22"_s + event<event22> [guard22{}] / action22{} = "state23"_s,
            "state23"_s + event<event23> [guard23{}] / action23{} = "state24"_s,
            "state24"_s + event<event24> [guard24{}] / action24{} = "state25"_s,
            "state25"_s + event<event25> [guard25{}] / action25{} = "state26"_s,
            "state26"_s + event<event26> [guard26{}] / action26{} = "state27"_s,
            "state27"_s + event<event27> [guard27{}] / action27{} = "state28"_s,
            "state28"_s + event<event28> [guard28{}] / action28{} = "state29"_s,
            "state29"_s + event<event29> [guard29{}] / action29{} = "state30"_s,
            "state30"_s + event<event30> [guard30{}] / action30{} = "state31"_s,
            "state31"_s + event<event31> [guard31{}] / action31{} = "state32"_s,
            "state32"_s + event<event32> [guard32{}] / action32{} = "state33"_s,
            "state33"_s + event<event33> [guard33{}] / action33{} = "state34"_s,
            "state34"_s + event<event34> [guard34{}] / action34{} = "state35"_s,
            "state35"_s + event<event35> [guard35{}] / action35{} = "state36"_s,
            "state36"_s + event<event36> [guard36{}] / action36{} = "state37"_s,
            "state37"_s + event<event37> [guard37{}] / action37{} = "state38"_s,
            "state38"_s + event<event38> [guard38{}] / action38{} = "state39"_s,
            "state39"_s + event<event39> [guard39{}] / action39{} = "state40"_s,
            "state40"_s + event<event40> [guard40{}] / action40{} = "state41"_s,
            "state41"_s + event<event41> [guard41{}] / action41{} = "state42"_s,
            "state42"_s + event<event42> [guard42{}] / action42{} = "state43"_s,
            "state43"_s + event<event43> [guard43{}] / action43{} = "state44"_s,
            "state44"_s + event<event44> [guard44{}] / action44{} = "state45"_s,
            "state45"_s + event<event45> [guard45{}] / action45{} = "state46"_s,
            "state46"_s + event<event46> [guard46{}] / action46{} = "state47"_s,
            "state47"_s + event<event47> [guard47{}] / action47{} = "state48"_s,
            "state48"_s + event<event48> [guard48{}] / action48{} = "state49"_s,
            "state49"_s + event<event49> [guard49{}] / action49{} = "state0"_s
        );
    }
};

int main()
{
    auto ctx = context{};
    auto sm = boost::sml::sm<large>{ctx};
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
}
