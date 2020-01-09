#include "span_zip.h"

typedef const char* cstr;

void main()
{
    cstr keys[] = { "key1", "key2", "key3" };
    int values[] = { 1, 2, 3, 4 };
    char aux_data[] = { '1', '2', '3', '4', '5' };

    for (auto nextTuple : zip_span(keys, values, aux_data))
    {
        printf("%s=%i\t|%c", std::get<0>(nextTuple), std::get<1>(nextTuple), std::get<2>(nextTuple));
    }
}
