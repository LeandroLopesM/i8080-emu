#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../core/colors.h"
#include "../core/log/log.h"
#include "../cpu/decode/decode.h"
#include "../cpu/cpu.h"
#include "../cpu/debug/debug.h"

#include "i8080-cc/compiler/parser/util/arrays.h"
#include "i8080-cc/compiler/encoder/encoder.h"
#include "i8080-cc/compiler/parser/parser.h"

#include "i8080-cc/core/common.h"
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
        goto dump_all;
    else if (strcmp(sa->items[1].items, "cpu") == 0)
        dump_registers(&c);
    else if (strcmp(sa->items[1].items, "mem") == 0)
        dump_memory(&c);
    else if (strcmp(sa->items[1].items, "pipe") == 0)
        dump_decoder();
    else goto dump_all;

dump_all:
    {
        printf(BLUE"Dumping everything\n"RESET);
        dump_registers(&c);
        dump_memory(&c);
        dump_decoder();
    }
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

void compare(cpu before, cpu after)
{
    if (before.rgf.SP != after.rgf.SP)
        printf("SP %d -> %d\n", before.rgf.SP, after.rgf.SP);
    if (before.rgf.PC != after.rgf.PC)
        printf("PC %d -> %d\n", before.rgf.PC, after.rgf.PC);

    if (before.rgf.A != after.rgf.A)
        printf("A %d -> %d\n", before.rgf.A, after.rgf.A);
    if (before.rgf.S != after.rgf.S)
        printf("S %d -> %d\n", before.rgf.S, after.rgf.S);
    if (before.rgf.Z != after.rgf.Z)
        printf("Z %d -> %d\n", before.rgf.Z, after.rgf.Z);
    if (before.rgf.I != after.rgf.I)
        printf("I %d -> %d\n", before.rgf.I, after.rgf.I);
    if (before.rgf.P != after.rgf.P)
        printf("P %d -> %d\n", before.rgf.P, after.rgf.P);
    if (before.rgf.CY != after.rgf.CY)
        printf("CY %d -> %d\n", before.rgf.CY, after.rgf.CY);
    if (before.rgf.AC != after.rgf.AC)
        printf("AC %d -> %d\n", before.rgf.AC, after.rgf.AC);

    if (before.rgf.D  != after.rgf.D )
        printf("D %d -> %d\n", before.rgf.D, after.rgf.D);
    if (before.rgf.E  != after.rgf.E )
        printf("E %d -> %d\n", before.rgf.E, after.rgf.E);
    if (before.rgf.DE != after.rgf.DE)
        printf("DE %d -> %d\n", before.rgf.DE, after.rgf.DE);

    if (before.rgf.B  != after.rgf.B)
        printf("B %d -> %d\n", before.rgf.B, after.rgf.B);
    if (before.rgf.C  != after.rgf.C)
        printf("C %d -> %d\n", before.rgf.C, after.rgf.C);
    if (before.rgf.BC != after.rgf.BC)
        printf("BC %d -> %d\n", before.rgf.BC, after.rgf.BC);

    if (before.rgf.H  != after.rgf.H)
        printf("H %d -> %d\n", before.rgf.H, after.rgf.H);
    if (before.rgf.L  != after.rgf.L)
        printf("L %d -> %d\n", before.rgf.L, after.rgf.L);
    if (before.rgf.HL != after.rgf.HL)
        printf("HL %d -> %d\n", before.rgf.HL, after.rgf.HL);
}

const char* b2s(byte n)
{
    static char out[9];
    int i = 0;

    while (n && i != 9) {
        if (n & 1)
            out[i++] = '1';
        else
            out[i++] = '0';

        n >>= 1;
    }
    out[8] = 0;
    return out;
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

        if (in_raw.len <= 1)
            continue;

        if (in_raw.items[0] == '/')
            parse_builtin(tokenize(in_raw.items));
        else
        {
            int ff = 0;
            comp_unit cu = parse_line(in_raw.items, &ff);
            if (ff)
                continue;
            WHEN_VERBOSE(printf(
                "\n+ CompUnit:\n| Instr %d\n| A %d\n| B %d\n| C %d\n",
                cu.type,
                cu.opA? *cu.opA : 0,
                cu.opB? *cu.opB : 0,
                cu.opC? *cu.opC : 0));

            byte b = encode(&cu);

            if (b == 0)
                continue;

            c.memory[0] = b;
            if (*cu.opA != 0)
                c.memory[1] = *cu.opA;
            if (*cu.opB != 0)
                c.memory[2] = *cu.opB;

            instruction *i = decode(&c, -1, 0);

            cpu copy = c;
            exec(&c, i);
            compare(copy, c);

            printf("\n+ "GREEN"Success"RESET);
            c.rgf.PC = 0;
        }
    }
}