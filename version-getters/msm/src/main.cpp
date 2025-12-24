//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include <boost/version.hpp>
#include <iostream>

int main()
{
    std::cout
        << (BOOST_VERSION / 100'000)
        << '.'
        << (BOOST_VERSION / 100 % 100)
        << '.'
        << (BOOST_VERSION % 100)
        << '\n';
}
