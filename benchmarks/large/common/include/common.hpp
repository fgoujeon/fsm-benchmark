//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define PROBLEM_SIZE 25
#define PROBLEM_SIZE_X_2 50

#define COUNTER \
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
    X(24)

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

#define COMMA_IF_NOT_0(N) COMMA_##N

constexpr auto test_loop_size = 1000;

int test();

int main()
{
    constexpr auto main_loop_size = 1000;

    auto counter = 0;

    for(auto i = 0; i < main_loop_size; ++i)
    {
        counter += test();
    }

    const auto expected_counter =
        PROBLEM_SIZE *
        test_loop_size *
        main_loop_size *
        2 //internal transition + state transition
    ;

    if(counter != expected_counter)
        return 1;

    return 0;
}
