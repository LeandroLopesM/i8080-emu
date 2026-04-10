#include "decode/decode.h"
#include "../core/log.h"
#include "../core/calc.h"

#define WORD(b) \
    (*((word*)b))

void exec(cpu* c, instruction* i)
{
    switch (i->kind)
    {
        case MOV:
        case MVI:
            *i->opA = *i->opB;
            break;
        case LXI:
            WORD(i->opA) = WORD(i->opB);
            break;
        case LDA:
            c->rgf.A = *i->opA;
            break;
        case STA:
            *i->opA = c->rgf.A;
        case LHLD:
            c->rgf.HL = WORD(i->opA);
            break;
        case SHLD:
            WORD(i->opA) = c->rgf.HL;
            break;
        case LDAX:
        case STAX:
            panic_ext(c, "STAX: Not sure how this one works");
        case XCHG:
        {
            byte b = c->rgf.HL;
            c->rgf.HL = c->rgf.DE;
            c->rgf.DE = b;
        } break;
        case ADD:
        case ADI:
            c->rgf.A = add_b(c, c->rgf.A, *i->opA);
            break;
        case ADC:
        case ACI:
            c->rgf.A = add_carry_b(c, c->rgf.A, *i->opA);
            break;
        case SUB:
        case SUI:
            c->rgf.A = sub_b(c, *i->opA, c->rgf.A);
            break;
        case SBB:
        case SBI:
            c->rgf.A = sub_borrow_b(c, *i->opA, c->rgf.A);
            break;
        case INR:
            *i->opA = add_b(c, *i->opA, 1);
            break;
        case DCR:
            *i->opA = sub_b(c, *i->opA, 1);
            break;
        case INX:
            WORD(i->opA) = add_w(c, WORD(i->opA), 1);
            break;
        case DCX:
            WORD(i->opA) = add_w(c, WORD(i->opA), 1);
            break;
        case DAD:
            c->rgf.HL = add_w(c, c->rgf.HL, WORD(i->opA));
            break;
        case DAA:
            panic_ext(c, "DAA: Undefined");
        case ANA:
        case ANI:
            c->rgf.A &= *i->opA;
            break;
        case ORA:
        case ORI:
            c->rgf.A |= *i->opA;
            break;
        case XRA:
        case XRI:
            c->rgf.A ^= *i->opA;
            break;
        case CMP:
        case CPI:
            cmp_b(c, c->rgf.A, i->opA);
            break;
        case RLC:
            c->rgf.A = rot_l(c, c->rgf.A);
            break;
        case RRC:
            c->rgf.A = rot_r(c, c->rgf.A);
            break;
        case RAL:
            c->rgf.A = rot_carry_l(c, c->rgf.A);
            break;
        case RAR:
            c->rgf.A = rot_carry_r(c, c->rgf.A);
            break;
        case CMA:

        case CMC:
        case STC:
        case JMP:
        case Jccc:
        case CALL:
        case Cccc:
        case RET:
        case Rccc:
        case RST:
        case PCHL:
        case PUSH:
        case POP:
        case XTHL:
        case SPHL:
        case IN:
        case OUT:
        case EI:
        case DI:
        case HLT:
        case NOP:
          break;
        }
}