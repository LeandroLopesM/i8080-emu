#include "../cpu/decode/decode.h"
#include "../cpu/debug/debug.h"
#include "../cpu/cpu.h"
#include "colors.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void __log(char* prefix, const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    printf("[%5s]: ", prefix);
    vprintf( fmt, va);
    printf("\n");
    va_end(va);
}

void error(const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    __log(RED"ERROR"RESET, fmt, va);
    va_end(va);
}

void warn(const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    __log(YELLOW"WARN"RESET, fmt, va);
    va_end(va);
}

void debug(const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    __log(BLUE"DEBUG"RESET, fmt, va);
    va_end(va);
}


static void __panic(int die, const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    printf("["BG_RED"PANIC"RESET"] : ");
    vprintf(fmt, va);
    printf("\n");
    va_end(va);

    if (die) exit(1);
}

void panic(const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    __panic(1, fmt, va);
    va_end(va);
}

void panic_ext(cpu *c, const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    __panic(0, fmt, va);
    va_end(va);
    dump_registers(c);
    dump_memory(c);
    dump_decoder();
    exit(1);
}