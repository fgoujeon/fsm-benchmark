//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include <iostream>

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
    X(49) \
    X(50) \
    X(51) \
    X(52) \
    X(53) \
    X(54) \
    X(55) \
    X(56) \
    X(57) \
    X(58) \
    X(59) \
    X(60) \
    X(61) \
    X(62) \
    X(63) \
    X(64) \
    X(65) \
    X(66) \
    X(67) \
    X(68) \
    X(69) \
    X(70) \
    X(71) \
    X(72) \
    X(73) \
    X(74) \
    X(75) \
    X(76) \
    X(77) \
    X(78) \
    X(79) \
    X(80)

constexpr int pow(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    return a * pow(a, b - 1);
}

constexpr auto depth = 4;
constexpr auto region_size = 3;

constexpr int state_id(int parent_id, int level, int index)
{
    return parent_id - (region_size - index - 1) * pow(region_size, level);
}

constexpr int base = pow(region_size, depth) - 1;

constexpr auto test_loop_size = 1000;

constexpr int compute_expected_counter()
{
    auto counter = 0;

#define X(n) counter += n;
    COUNTER
#undef X

    return counter;
}

int test();

int main()
{
    constexpr auto main_loop_size = 500;
    constexpr auto expected_counter = main_loop_size * test_loop_size * compute_expected_counter();

    auto counter = 0;

    for(auto i = 0; i < main_loop_size; ++i)
    {
        counter += test();
    }

    std::cout << "counter = " << counter << '\n';
    std::cout << "expected_counter = " << expected_counter << '\n';

    if(counter != expected_counter)
    {
        return 1;
    }

    return 0;
}
