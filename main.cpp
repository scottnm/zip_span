#include "span_zip.h"

typedef const char* cstr;

void main()
{
    cstr keys[] = { "key1", "key2", "key3" };
    int values[] = { 1, 2, 3, 4 };
    char aux_data[] = { '1', '2', '3', '4', '5' };

    /* FIXME:
    for (auto nextTuple : zip_span(keys, values, aux_data))
    {
        printf("%s=%i\t|%c", nextTuple<0>.get(), nextTuple<1>.get(), nextTuple<2>.get());
    }
    */
    (void)keys;
    (void)values;
    (void)aux_data;
}