#include "../../core/colors.h"
#include "../../core/log/log.h"

#include "../i8080-cc/compiler/parser/util/arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern cpu c;

void set(string_arr* sa)
{
    if (sa->len == 1)
    {
        printf(RED"+"RESET" USAGE: set [register|mem addr] value\n| Sets {register} or {memory at address} to {value}");
        return;
    }

    if (strcmp(sa->items[1].items, "reg") == 0)
    {
        word val = atol(sa->items[2].items);

        if (val == 0 && sa->items[2].items[0] != '0')
        {
            error("Invalid integer %s", sa->items[2].items[0]);
            return;
        }

        if (strcmp(sa->items[1].items, "A") == 0)
            c.rgf.A = val;
        else if (strcmp(sa->items[1].items, "B") == 0)
            c.rgf.B = val;
        else if (strcmp(sa->items[1].items, "C") == 0)
            c.rgf.C = val;
        else if (strcmp(sa->items[1].items, "D") == 0)
            c.rgf.D = val;
        else if (strcmp(sa->items[1].items, "E") == 0)
            c.rgf.E = val;
        else if (strcmp(sa->items[1].items, "BC") == 0)
            c.rgf.BC = val;
        else if (strcmp(sa->items[1].items, "DE") == 0)
            c.rgf.DE = val;
        else if (strcmp(sa->items[1].items, "HL") == 0)
            c.rgf.HL = val;
        else
            error("Unknown specifier %s", sa->items[1].items);
    }
    else if (strcmp(sa->items[1].items, "mem") == 0)
    {
        word pos = atol(sa->items[2].items);
        t_word w = (t_word){.asword = atol(sa->items[3].items)};

        if (pos >= sizeof(c.memory))
        {
            error("Address %u larger than memory size", pos);
            return;
        }

        if (w.asword >= 0xFF)
        {
            warn("Assignment will overflow into next cell!");
            c.memory[pos + 1] = w.asbyte.hi;
        }

        c.memory[pos] = w.asbyte.lo;
    }
    else error("Unknown specifier %s", sa->items[0].items);
}