#ifndef RESOLVE_H
#define RESOLVE_H

#include "../../core/common.h"
#include "../cpu.h"

byte* resolve(cpu* c, byte selector);
byte* resolve_rp(cpu* c, byte selector);
byte* resolve_rp_xx(cpu* c, byte selector);
byte* resolve_flag(cpu* c, byte selector);
byte* resolve_stack_rp(cpu* c, byte selector);

#endif // RESOLVE_H