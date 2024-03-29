//
// zug: transducers for C++
// Copyright (C) 2019 Juan Pedro Bolivar Puente
//
// This software is distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt
//

#pragma once

#include <zug/compose.hpp>
#include <zug/transducer/count.hpp>
#include <zug/transducer/map.hpp>

namespace zug {

/*!
 * Similar to clojure.core/map-indexed$1
 */
template <typename MappingT>
constexpr auto map_indexed(MappingT&& mapping)
{
    return count() | map(std::forward<MappingT>(mapping));
}

} // namespace zug
