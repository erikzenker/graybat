/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>
namespace hana = boost::hana;


static_assert(hana::filter(hana::make_tuple(1, 2.0, 3, 4.0), hana::trait<std::is_integral>) == hana::make_tuple(1, 3), "");
static_assert(hana::filter(hana::just(3), hana::trait<std::is_integral>) == hana::just(3), "");
BOOST_HANA_CONSTANT_CHECK(hana::filter(hana::just(3.0), hana::trait<std::is_integral>) == hana::nothing);

int main() { }
