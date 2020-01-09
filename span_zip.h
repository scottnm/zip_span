#pragma once

#include <gsl/span>

// FIXME: mocked out what the return value is actually supposed to be
#include <vector>
std::vector<std::tuple<NonCopy<cstr>&, NonCopy<int>&, NonCopy<char>&>>
zip_span(
    // FIXME: mocked out what the input params are
    // should be made more generic
    gsl::span<NonCopy<cstr>> keys,
    gsl::span<NonCopy<int>> values,
    gsl::span<NonCopy<char>> aux
    )
{
    (void)keys;(void)values;(void)aux;
    return {};
}

std::vector<std::tuple<NonCopy<cstr>, NonCopy<int>, NonCopy<char>>>
test_no_copy(
    )
{
    return {};
}
