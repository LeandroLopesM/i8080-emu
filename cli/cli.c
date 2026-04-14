#include <stdio.h>
#include <string.h>
#include "util/dastring.h"
#include "../core/colors.h"
#include "../cpu/cpu.h"

cpu c;

int read_line(string* s)
{
    char buf;
    while ((buf = getc(stdin)) != '\n')
    {
        if (buf == EOF) return 0;

        push_char(s, buf);
    }

    push_char(s, 0);
    s->len--;
    return 1;
}

int start_cli()
{
    memset(&c, 0, sizeof(cpu));
    string* in = NULL;
    size_t i = 0;

    while (1)
    {
        printf("\n%llu> ", i++);

        if(!read_line(in))
        {
            printf(BG_RED"\nAborted\n"RESET);
            return 1;
        }

        printf("\nGot: %s", in->items);
    }   
}