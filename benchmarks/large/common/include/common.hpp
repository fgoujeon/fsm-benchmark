//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define COUNTER_50 \
    X(0) \
    X(1) \
    X(2) \
    X(3) \
    X(4) \
    X(5) \
    X(6) \
    X(7) \
    X(8) \
    X(9) \
    X(10) \
    X(11) \
    X(12) \
    X(13) \
    X(14) \
    X(15) \
    X(16) \
    X(17) \
    X(18) \
    X(19) \
    X(20) \
    X(21) \
    X(22) \
    X(23) \
    X(24) \
    X(25) \
    X(26) \
    X(27) \
    X(28) \
    X(29) \
    X(30) \
    X(31) \
    X(32) \
    X(33) \
    X(34) \
    X(35) \
    X(36) \
    X(37) \
    X(38) \
    X(39) \
    X(40) \
    X(41) \
    X(42) \
    X(43) \
    X(44) \
    X(45) \
    X(46) \
    X(47) \
    X(48) \
    X(49)

#define COMMA_0
#define COMMA_1  ,
#define COMMA_2  ,
#define COMMA_3  ,
#define COMMA_4  ,
#define COMMA_5  ,
#define COMMA_6  ,
#define COMMA_7  ,
#define COMMA_8  ,
#define COMMA_9  ,
#define COMMA_10 ,
#define COMMA_11 ,
#define COMMA_12 ,
#define COMMA_13 ,
#define COMMA_14 ,
#define COMMA_15 ,
#define COMMA_16 ,
#define COMMA_17 ,
#define COMMA_18 ,
#define COMMA_19 ,
#define COMMA_20 ,
#define COMMA_21 ,
#define COMMA_22 ,
#define COMMA_23 ,
#define COMMA_24 ,
#define COMMA_25 ,
#define COMMA_26 ,
#define COMMA_27 ,
#define COMMA_28 ,
#define COMMA_29 ,
#define COMMA_30 ,
#define COMMA_31 ,
#define COMMA_32 ,
#define COMMA_33 ,
#define COMMA_34 ,
#define COMMA_35 ,
#define COMMA_36 ,
#define COMMA_37 ,
#define COMMA_38 ,
#define COMMA_39 ,
#define COMMA_40 ,
#define COMMA_41 ,
#define COMMA_42 ,
#define COMMA_43 ,
#define COMMA_44 ,
#define COMMA_45 ,
#define COMMA_46 ,
#define COMMA_47 ,
#define COMMA_48 ,
#define COMMA_49 ,

#define COMMA_IF_NOT_0(N) COMMA_##N

int test();

int main()
{
    auto side_effect = 0;

    for(auto i = 0; i < 1000; ++i)
    {
        side_effect += test();
    }

    if(side_effect != 50'000'000)
        return 1;

    return 0;
}
