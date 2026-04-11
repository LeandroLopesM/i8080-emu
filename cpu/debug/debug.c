#include "debug.h"
#include <stdint.h>
#include <stdio.h>

void dump_registers(cpu* c)
{
    printf("* Core dump:\n");
    printf("| SP: %-4X PC: %-4X\n", c->rgf.SP, c->rgf.PC);
    printf("| %d%d%d%d%d%d\n", c->rgf.S, c->rgf.Z, c->rgf.I, c->rgf.P, c->rgf.CY, c->rgf.AC);
    printf("| SZIPCYA\n");
    printf("+ General registers:\n");
    printf("| PSW: %-4X A: %2X:\n", c->rgf.A, c->rgf.PSW);
    printf("| D: %2X E: %2X => DE: %-4X\n", c->rgf.D, c->rgf.E, c->rgf.DE);
    printf("| B: %2X C: %2X => BC: %-4X\n", c->rgf.B, c->rgf.C, c->rgf.BC);
    printf("| H: %2X L: %2X => HL: %-4X\n", c->rgf.H, c->rgf.L, c->rgf.HL);

    fflush(stdout);
}

int clamp(int a, int b, int c)
{
    return a < b? b : a > c? c : a;
}

void dump_memory(cpu* c)
{
    printf("+ Memory dump (%X:%X): { ", clamp(c->rgf.PC, 0, UINT16_MAX), clamp(c->rgf.PC + 5, 0, UINT16_MAX));
    for (int i = clamp(c->rgf.PC, 0, UINT16_MAX); i < clamp(c->rgf.PC + 5, 0, UINT16_MAX); ++i)
    {
        if (i == c->rgf.PC)
            printf("[%2X] ", c->memory[i]);
        else
            printf("%2X ", c->memory[i]);
    }
    printf("};\n");
    fflush(stdout);
}