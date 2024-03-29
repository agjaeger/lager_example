
//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

#include <zug/detail/is_non_empty.hpp>
#include <zug/detail/reduce_nested_non_empty.hpp>
#include <zug/skip.hpp>

namespace zug {

/*!
 * Similar to @a reduce, but does not unwrap `reduced` values.  This is useful
 * when calling reduce recursively inside a transducer.
 *
 * @see take
 */
template <typename ReducingFnT, typename StateT, typename... InputRangeTs>
decltype(auto)
reduce_nested(ReducingFnT&& step, StateT&& state, InputRangeTs&&... ranges)
{
    return detail::is_non_empty(ranges...)
               ? call(
                     [&](auto&& state) {
                         return detail::reduce_nested_non_empty(
                             std::forward<ReducingFnT>(step),
                             ZUG_FWD(state),
                             std::forward<InputRangeTs>(ranges)...);
                     },
                     std::forward<StateT>(state))
               : skip(std::forward<StateT>(state));
}

} // namespace zug
