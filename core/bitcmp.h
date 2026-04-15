#ifndef BITCMP_H
#define BITCMP_H

#include "common.h"

static byte bitcheck(byte num, int pos) {
    return (num >> pos) & 1;
}

static int is_eq(byte b, char* ref)
{
    char* c = ref;

    for (int i = 7; i >= 0 && *c; --i, ++c)
    {
        if (*c == '_')
            continue;
        if (bitcheck(b, i) != (*c == '1'))
            return 0;
    }

    return 1;
}

#endif // BITCMP_H