#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../core/colors.h"
#include "../core/log/log.h"
#include "../cpu/cpu.h"
#include "../cpu/debug/debug.h"

#include "i8080-cc/compiler/parser/util/arrays.h"
#include "i8080-cc/compiler/encoder/encoder.h"
#include "i8080-cc/compiler/parser/parser.h"

#include "../cpu/decode/decode.h"
cpu c;

#include "builtins/set.c"
#include "builtins/converters.c"

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
    printf(RED"+"RESET" USAGE: /dump [cpu, mem, pipe]\n| Dumps relevant information about requested object\n");
}

void parse_builtin(string_arr* sa)
{
    if (strcmp(sa->items[0].items, "/dump") == 0)
        dump(sa);
    else if (strcmp(sa->items[0].items, "/set") == 0)
        set(sa);
    else if(strcmp(sa->items[0].items, "/hex") == 0)
        hex(sa);
    else if(strcmp(sa->items[0].items, "/dec") == 0)
        dec(sa);
    else if(strcmp(sa->items[0].items, "/b2d") == 0)
        b2d(sa);
    else if(strcmp(sa->items[0].items, "/d2b") == 0)
        d2b(sa);
    else error("Unknown command %s", sa->items[0].items);
}

void compare(cpu a, cpu b)
{
    if (a.rgf.SP != b.rgf.SP)
        printf("SP %d -> %d", a.rgf.SP, b.rgf.SP);
    if (a.rgf.PC != b.rgf.PC)
        printf("PC %d -> %d", a.rgf.PC, b.rgf.PC);

    if (a.rgf.A != b.rgf.A)
        printf("A %d -> %d", a.rgf.A, b.rgf.A);
    if (a.rgf.S != b.rgf.S)
        printf("S %d -> %d", a.rgf.S, b.rgf.S);
    if (a.rgf.Z != b.rgf.Z)
        printf("Z %d -> %d", a.rgf.Z, b.rgf.Z);
    if (a.rgf.I != b.rgf.I)
        printf("I %d -> %d", a.rgf.I, b.rgf.I);
    if (a.rgf.P != b.rgf.P)
        printf("P %d -> %d", a.rgf.P, b.rgf.P);
    if (a.rgf.CY != b.rgf.CY)
        printf("CY %d -> %d", a.rgf.CY, b.rgf.CY);
    if (a.rgf.AC != b.rgf.AC)
        printf("AC %d -> %d", a.rgf.AC, b.rgf.AC);

    if (a.rgf.D  != b.rgf.D )
        printf("D %d -> %d", a.rgf.D, b.rgf.D);
    if (a.rgf.E  != b.rgf.E )
        printf("E %d -> %d", a.rgf.E, b.rgf.E);
    if (a.rgf.DE != b.rgf.DE)
        printf("DE %d -> %d", a.rgf.DE, b.rgf.DE);

    if (a.rgf.B  != b.rgf.B)
        printf("B %d -> %d", a.rgf.B, b.rgf.B);
    if (a.rgf.C  != b.rgf.C)
        printf("C %d -> %d", a.rgf.C, b.rgf.C);
    if (a.rgf.BC != b.rgf.BC)
        printf("BC %d -> %d", a.rgf.BC, b.rgf.BC);

    if (a.rgf.H  != b.rgf.H)
        printf("H %d -> %d", a.rgf.H, b.rgf.H);
    if (a.rgf.L  != b.rgf.L)
        printf("L %d -> %d", a.rgf.L, b.rgf.L);
    if (a.rgf.HL != b.rgf.HL)
        printf("HL %d -> %d", a.rgf.HL, b.rgf.HL);
}

int start_cli()
{
    memset(&c, 0, sizeof(cpu));
    string in_raw = {0};
    size_t i = 0;

    while (1)
    {
        printf("%llu> ", i++);

        if(!read_line(&in_raw))
        {
            printf(BG_RED"\nAborted\n"RESET);
            return 1;
        }

        if (in_raw.items[0] == '/')
            parse_builtin(tokenize(in_raw.items));
        else
        {
            int ff;
            comp_unit cu = parse_line(in_raw.items, &ff);
            if (ff)
                continue;
            printf("+ CompUnit:\n| Instr %d", cu.type);
            // byte opcode = encode(cu);

            // cpu copy = c;
            // exec(&c, (instruction *)&cu);

            // compare(copy, c);
        }
    }
}