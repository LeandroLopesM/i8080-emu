#ifndef DASTRING_H
#define DASTRING_H

#include <stdlib.h>

typedef struct {
    size_t len;
    size_t cap;
    char* items;
} string;

static void push_char(string* s, char c)
{
    if (s == NULL)
        s = (string*)calloc(1, sizeof (string));

    if (s->len + 1 >= s->cap)
    {
        if (s->cap == 0) s->cap = 128;
        else s->cap *= 2;

        s->items = (char*)realloc(s->items, s->cap);
    }

    s->items[s->len++] = c;
}

#endif // DASTRING_H