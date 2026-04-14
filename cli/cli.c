#include <stdio.h>
#include <string.h>
#include "../core/colors.h"
#include "../cpu/cpu.h"

#include "external/i8080-cc/compiler/parser/util/arrays.h"
#include "external/i8080-cc/compiler/parser/parser.h"

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

void parse_builtin(string_arr* sa)
{

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

        printf("\nGot: %s", in_raw.items); 
    }
}