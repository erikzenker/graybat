/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/equal.hpp>
#include <boost/hana/prepend.hpp>
#include <boost/hana/tuple.hpp>
namespace hana = boost::hana;


static_assert(hana::prepend(hana::make_tuple(), 1) == hana::make_tuple(1), "");
static_assert(hana::prepend(hana::make_tuple('2', 3.3), 1) == hana::make_tuple(1, '2', 3.3), "");

int main() { }
