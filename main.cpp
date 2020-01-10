typedef const char* cstr;

template<typename T>
struct NonCopy
{
    T v;

    NonCopy(T v) : v(v) {}

    // Delete copy assn and ctor
    NonCopy(const NonCopy&)=delete;
    NonCopy& operator=(const NonCopy&)=delete;

    // Allow move assn and ctor
    NonCopy(NonCopy&&)=default;
    NonCopy& operator=(NonCopy&&)=default;
};

#include "span_zip.h"

void main()
{
    NonCopy<cstr> cstrs[] = { "key1", "key2", "key3", "key4", "key5", "key6" };
    NonCopy<int> ints[] = { 1, 2, 3, 4, 5};
    NonCopy<char> chars[] = { '1', '2', '3', '4' };
    NonCopy<float> floats[] = { 1.f, 2.f, 3.f };
    NonCopy<cstr> cstrs2[] = { "key1", "key2" };

    for (auto nextTuple : zip_span(cstrs, ints))
    {
        printf("%s, %i\n",
            std::get<0>(nextTuple)->v,
            std::get<1>(nextTuple)->v
            );
    }
    printf("\n");

    for (auto nextTuple : zip_span(cstrs, ints, chars))
    {
        printf("%s, %i, '%c'\n",
            std::get<0>(nextTuple)->v,
            std::get<1>(nextTuple)->v,
            std::get<2>(nextTuple)->v
            );
    }
    printf("\n");

    for (auto nextTuple : zip_span(cstrs, ints, chars, floats))
    {
        printf("%s, %i, '%c', %.1f\n",
            std::get<0>(nextTuple)->v,
            std::get<1>(nextTuple)->v,
            std::get<2>(nextTuple)->v,
            std::get<3>(nextTuple)->v
            );
    }
    printf("\n");

    for (auto nextTuple : zip_span(cstrs, ints, chars, floats, cstrs2))
    {
        printf("%s, %i, '%c', %.1f, %s\n",
            std::get<0>(nextTuple)->v,
            std::get<1>(nextTuple)->v,
            std::get<2>(nextTuple)->v,
            std::get<3>(nextTuple)->v,
            std::get<4>(nextTuple)->v
            );
    }
    printf("\n");
}
