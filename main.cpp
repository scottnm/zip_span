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

    /*
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    std::tuple<int&, int&> fwd{a, b};
    std::tuple<int&, int&> bwd{c, d};
    printf("fwd: %i, %i\tbwd: %i, %i\n",
        std::get<0>(fwd), std::get<1>(fwd),
        std::get<0>(bwd), std::get<1>(bwd));
    std::swap(fwd, bwd);
    printf("fwd: %i, %i\tbwd: %i, %i\n",
        std::get<0>(fwd), std::get<1>(fwd),
        std::get<0>(bwd), std::get<1>(bwd));

    int& ar = a;
    int& br = b;
    printf("a: %i b: %i\n", ar, br);
    std::swap(ar, br);
    printf("a: %i b: %i\n", ar, br);
    */
}
