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

void compare(cpu before, cpu after)
{
    if (before.rgf.SP != after.rgf.SP)
        printf("SP %d -> %d", before.rgf.SP, after.rgf.SP);
    if (before.rgf.PC != after.rgf.PC)
        printf("PC %d -> %d", before.rgf.PC, after.rgf.PC);

    if (before.rgf.A != after.rgf.A)
        printf("A %d -> %d", before.rgf.A, after.rgf.A);
    if (before.rgf.S != after.rgf.S)
        printf("S %d -> %d", before.rgf.S, after.rgf.S);
    if (before.rgf.Z != after.rgf.Z)
        printf("Z %d -> %d", before.rgf.Z, after.rgf.Z);
    if (before.rgf.I != after.rgf.I)
        printf("I %d -> %d", before.rgf.I, after.rgf.I);
    if (before.rgf.P != after.rgf.P)
        printf("P %d -> %d", before.rgf.P, after.rgf.P);
    if (before.rgf.CY != after.rgf.CY)
        printf("CY %d -> %d", before.rgf.CY, after.rgf.CY);
    if (before.rgf.AC != after.rgf.AC)
        printf("AC %d -> %d", before.rgf.AC, after.rgf.AC);

    if (before.rgf.D  != after.rgf.D )
        printf("D %d -> %d", before.rgf.D, after.rgf.D);
    if (before.rgf.E  != after.rgf.E )
        printf("E %d -> %d", before.rgf.E, after.rgf.E);
    if (before.rgf.DE != after.rgf.DE)
        printf("DE %d -> %d", before.rgf.DE, after.rgf.DE);

    if (before.rgf.B  != after.rgf.B)
        printf("B %d -> %d", before.rgf.B, after.rgf.B);
    if (before.rgf.C  != after.rgf.C)
        printf("C %d -> %d", before.rgf.C, after.rgf.C);
    if (before.rgf.BC != after.rgf.BC)
        printf("BC %d -> %d", before.rgf.BC, after.rgf.BC);

    if (before.rgf.H  != after.rgf.H)
        printf("H %d -> %d", before.rgf.H, after.rgf.H);
    if (before.rgf.L  != after.rgf.L)
        printf("L %d -> %d", before.rgf.L, after.rgf.L);
    if (before.rgf.HL != after.rgf.HL)
        printf("HL %d -> %d", before.rgf.HL, after.rgf.HL);
}

const char* b2s(byte n)
{
    static char out[9];
    int i = 0;

    while (n && i != 8) {
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

            instruction i = {
                .kind = cu.type,
                .opcode = encode(&cu),
                .opA = cu.opA,
                .opB = cu.opB
            };

            // cpu copy = c;
            // exec(&c, &i);

            debug("OC: %s\n", b2s(i.opcode));

            // compare(copy, c);
        }
    }
}