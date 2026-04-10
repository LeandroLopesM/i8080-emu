#ifndef DECODE_H
#define DECODE_H

#include "../common.h"
#include "cpu.h"

typedef struct {
    size_t idx;
    byte opcode;
    byte* opA;
    byte* opB;
} Instruction;

byte *resolve(cpu* c, byte mask);
byte *resolve_rp(cpu* c, byte mask);
Instruction *decode(cpu* c, int mempos, size_t tick);

#endif // DECODE_H