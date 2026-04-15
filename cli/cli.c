#include <stdio.h>
#include <string.h>
#include "../core/colors.h"
#include "../core/log.h"
#include "../cpu/cpu.h"
#include "../cpu/decode/decode.h"
#include "../cpu/debug/debug.h"

#include "i8080-cc/compiler/parser/util/arrays.h"
#include "i8080-cc/compiler/parser/parser.h"

cpu c;

int read_line(string* s)
{
    s->len = 0;
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

void dump(string_arr* sa)
{
    if (sa->len != 2)
        goto dump_usage;
    else if (strcmp(sa->items[1].items, "cpu") == 0)
        dump_registers(&c);
    else if (strcmp(sa->items[1].items, "mem") == 0)
        dump_memory(&c);
    else if (strcmp(sa->items[1].items, "pipe") == 0)
        dump_decoder();
    else goto dump_usage;

    return;
dump_usage:
    printf(RED"+"RESET" USAGE: /dump [cpu, mem, pipe]\n| Dumps relevant information about requested object");
}

void parse_builtin(string_arr* sa)
{
    if (strcmp(sa->items[0].items, "/dump") == 0)
        dump(sa);
    else error("Unknown command %s", sa->items[0].items);
}

int start_cli()
{
    memset(&c, 0, sizeof(cpu));
    string in_raw = {0};
    size_t i = 0;

    while (1)
    {
        printf("\n%llu> ", i++);

        if(!read_line(&in_raw))
        {
            printf(BG_RED"\nAborted\n"RESET);
            return 1;
        }

        if (in_raw.items[0] == '/')
            parse_builtin(tokenize(in_raw.items));
    }
}