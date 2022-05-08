//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "boost/mpl/vector/vector50.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"
#include "boost/preprocessor/iterate.hpp"
#include "boost/config.hpp"

namespace boost { namespace mpl {
#define BOOST_PP_ITERATION_PARAMS_1 \
(3,(51, 100, "boost/mpl/vector/aux_/numbered.hpp"))
#include BOOST_PP_ITERATE()
}}
