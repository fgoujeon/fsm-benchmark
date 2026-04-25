//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include <iostream>

#define COUNTER \
    X(0, 0, 0) \
    X(0, 0, 1) \
    X(0, 0, 2) \
    X(0, 1, 0) \
    X(0, 1, 1) \
    X(0, 1, 2) \
    X(0, 2, 0) \
    X(0, 2, 1) \
    X(0, 2, 2) \
    X(1, 0, 0) \
    X(1, 0, 1) \
    X(1, 0, 2) \
    X(1, 1, 0) \
    X(1, 1, 1) \
    X(1, 1, 2) \
    X(1, 2, 0) \
    X(1, 2, 1) \
    X(1, 2, 2) \
    X(2, 0, 0) \
    X(2, 0, 1) \
    X(2, 0, 2) \
    X(2, 1, 0) \
    X(2, 1, 1) \
    X(2, 1, 2) \
    X(2, 2, 0) \
    X(2, 2, 1) \
    X(2, 2, 2)

constexpr auto level_0_state_count = 3;
constexpr auto level_1_state_count = 3;
constexpr auto level_2_state_count = 3;

constexpr auto test_loop_size = 1000;

constexpr int compute_internal_event_value(int x, int y, int z)
{
    return (x * level_1_state_count) + (y * level_2_state_count) + z + 1;
}

constexpr int compute_expected_counter()
{
    auto counter = 0;

    for (auto x = 0; x < level_0_state_count; ++x)
    {
        for (auto y = 0; y < level_1_state_count; ++y)
        {
            for (auto z = 0; z < level_2_state_count; ++z)
            {
                counter += compute_internal_event_value(x, y, z);
            }
        }
    }

    return counter;
}

int test();

int main()
{
    constexpr auto main_loop_size = 1000;
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
