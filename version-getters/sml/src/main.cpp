//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include <boost/sml.hpp>
#include <iostream>

int main()
{
    std::cout
        << (BOOST_SML_VERSION / 1'000)
        << '.'
        << (BOOST_SML_VERSION / 100 % 10)
        << '.'
        << (BOOST_SML_VERSION % 100)
        << '\n';
}
