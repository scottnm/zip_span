#pragma once

#include <gsl/span>

// FIXME: mocked out what the return value is actually supposed to be
#include <vector>
std::vector<std::tuple<cstr, int, char>>
zip_span(
    // FIXME: mocked out what the input params are
    // should be made more generic
    gsl::span<const char*> keys,
    gsl::span<int> values,
    gsl::span<char> aux
    )
{
    (void)keys;(void)values;(void)aux;
    return {};
}
