#include "decode/decode.h"
#include "../core/common.h"
#include "../core/log.h"
#include "../core/calc.h"
#include "cpu.h"

#define WORD(b) \
    (*((word*)b))

#define MKWORD(hi, lo) \
    (((t_word){{hi, lo}}).asword)

#define MKWORD_INPLACE(lo) \
    (((t_word){{*( lo + 1), *lo}}).asword)

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
            cmp_b(c, c->rgf.A, *i->opA);
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
            c->rgf.A = ~(c->rgf.A);
            break;
        case CMC:
            c->rgf.CY = ~(c->rgf.CY);
            break;
        case STC:
            c->rgf.CY = 1;
            break;
        case JMP:
            c->rgf.PC = MKWORD(*i->opB, *i->opA); // inverted because INST LO, HI ==> HI, LO
            break;
        case Jccc:
            if (try_condition(c, (condition_kind)(*i->opA)))
                c->rgf.PC = MKWORD_INPLACE(i->opB);
            break;
        case CALL:
            push_w(c, c->rgf.PC);
            c->rgf.PC = MKWORD(*i->opB, *i->opA);
            break;
        case Cccc:
            if (try_condition(c, (condition_kind)(*i->opA)))
            {
                push_w(c, c->rgf.PC);
                c->rgf.PC = MKWORD_INPLACE(i->opB);
            }
            break;
        case RET:
            c->rgf.PC = pop_w(c);
            break;
        case Rccc:
            if (try_condition(c, (condition_kind)(*i->opA)))
                c->rgf.PC = pop_w(c);
            break;
        case RST:
            c->rgf.PC = pop_w(c);
            c->rgf.PC = 8 * (*i->opA);
            error("RST: Running of guess-work on how this shit works");
            break;
        case PCHL:
            c->rgf.PC = c->rgf.HL;
            break;
        case PUSH:
            push_w(c, WORD(i->opA));
            break;
        case POP:
            *i->opA = pop_w(c);
            break;
        case XTHL:
        {
            byte save = c->rgf.HL;
            c->rgf.HL = pop_w(c);
            push_w(c, save);
        } break;
        case SPHL:
            c->rgf.SP = c->rgf.HL;
            break;
        case IN:
            panic_ext(c, "Unimplemented");
        case OUT:
            panic_ext(c, "Unimplemented");
        case EI:
            c->rgf.I = 1;
        case DI:
            c->rgf.I = 0;
        case HLT:
        {
            static int hltd = 0;

            if (!hltd)
            {
                warn("Processor halted");
                hltd=  1;
            }
        }
            c->rgf.PC--;
            break;
        case NOP:
            break;
        default:
            panic_ext(c, "Unknown instruction");
    }

}