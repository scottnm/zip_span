typedef const char* cstr;

template<typename T>
struct NonCopy
{
    T v;

    // Delete copy assn and copy ctor
    NonCopy(T v) : v(v) {}
    NonCopy(const NonCopy&)=delete;
    NonCopy& operator=(const NonCopy&)=delete;
    NonCopy(NonCopy&&)=default;
    NonCopy& operator=(NonCopy&&)=default;
};

#include "span_zip.h"

void main()
{
    NonCopy<cstr> keys[] = { "key1", "key2", "key3" };
    NonCopy<int> values[] = { 1, 2, 3, 4 };
    NonCopy<char> aux_data[] = { '1', '2', '3', '4', '5' };

    for (auto nextTuple : zip_span(keys, values, aux_data))
    {
        printf("%s, %i, %i\n", std::get<0>(nextTuple)->v, std::get<1>(nextTuple)->v, std::get<2>(nextTuple)->v);
    }
}
