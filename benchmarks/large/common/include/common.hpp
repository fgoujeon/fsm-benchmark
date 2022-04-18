//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#define COUNTER_50 \
    X(0,  1) \
    X(1,  2) \
    X(2,  3) \
    X(3,  4) \
    X(4,  5) \
    X(5,  6) \
    X(6,  7) \
    X(7,  8) \
    X(8,  9) \
    X(9,  10) \
    X(10, 11) \
    X(11, 12) \
    X(12, 13) \
    X(13, 14) \
    X(14, 15) \
    X(15, 16) \
    X(16, 17) \
    X(17, 18) \
    X(18, 19) \
    X(19, 20) \
    X(20, 21) \
    X(21, 22) \
    X(22, 23) \
    X(23, 24) \
    X(24, 25) \
    X(25, 26) \
    X(26, 27) \
    X(27, 28) \
    X(28, 29) \
    X(29, 30) \
    X(30, 31) \
    X(31, 32) \
    X(32, 33) \
    X(33, 34) \
    X(34, 35) \
    X(35, 36) \
    X(36, 37) \
    X(37, 38) \
    X(38, 39) \
    X(39, 40) \
    X(40, 41) \
    X(41, 42) \
    X(42, 43) \
    X(43, 44) \
    X(44, 45) \
    X(45, 46) \
    X(46, 47) \
    X(47, 48) \
    X(48, 49) \
    X(49, 0)

int test();

int main()
{
    auto side_effect = 0;

    for(auto i = 0; i < 1'000'000; ++i)
    {
        side_effect += test();
    }

    if(side_effect != 50'000'000)
        return 1;

    return 0;
}
