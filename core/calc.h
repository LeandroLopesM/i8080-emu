#ifndef CALC_H
#define CALC_H

#include "common.h"
#include "../cpu/cpu.h"

byte add_b(cpu* c, byte lhs, byte rhs);
byte add_carry_b(cpu* c, byte lhs, byte rhs);

byte sub_b(cpu* c, byte lhs, byte rhs);
byte sub_borrow_b(cpu* c, byte lhs, byte rhs);

word add_w(cpu* c, word lhs, word rhs);
word add_carry_w(cpu* c, word lhs, word rhs);

word sub_w(cpu* c, word lhs, word rhs);
word sub_borrow_w(cpu* c, word lhs, word rhs);

#endif // CALC_H