#include "decode/decode.h"
void exec(cpu* c, instruction* i)
{
    switch (i->kind)
    {
        case MOV:
        case MVI:
            *i->opA = *i->opB;
            break;
        case LXI:
            *((word*)i->opA) = *((word*)i->opB);
            break;
        case LDA:
            c->rgf.A = *i->opA;
            break;
        case STA:
            *i->opA = c->rgf.A;
        case LHLD:
            c->rgf.HL = *((word*)i->opA);
            break;
        case SHLD:
            *((word*)i->opA) = c->rgf.HL;
            break;
        case LDAX:
        case STAX:
        case XCHG:
        case ADD:
        case ADI:
        case ADC:
        case ACI:
        case SUB:
        case SUI:
        case SBB:
        case SBI:
        case INR:
        case DCR:
        case INX:
        case DCX:
        case DAD:
        case DAA:
        case ANA:
        case ANI:
        case ORA:
        case ORI:
        case XRA:
        case XRI:
        case CMP:
        case CPI:
        case RLC:
        case RRC:
        case RAL:
        case RAR:
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