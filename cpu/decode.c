#include "decode.h"
#include "masks.h"
#include <stdlib.h>

#define BITMASK(orig, mask) \
    (((orig) & (mask)) == (mask))

Instruction *decode(cpu* c, int mempos, size_t tick)
{
    static Instruction* out = NULL;
    static byte opcode = 0;

    word* truepos = mempos == -1? &c->rgf.PC : (word*)(&mempos);
    opcode = c->memory[(*truepos)++];

    if (out->opcode == opcode)
        return out;

    out->opcode = opcode;

    if (out == NULL)
    {
        if (tick != 0)
            error("Someone deleted the decode buffer (null despite tick %lu)", tick);

        calloc(sizeof (Instruction), 1);
    }

    if (BITMASK(opcode, m_MOV)) {
        out->idx = 0;
        out->opA = resolve(c, (opcode & m_MOV_DST) << 2);
        out->opB = resolve(c, (opcode & m_MOV_SRC) << 5);
    }
    if (BITMASK(opcode, m_MVI)) {
        out->idx = 1;
        out->opA = resolve(c, (opcode & m_MVI_DST) << 2);
        out->opB = &c->memory[(*truepos)++];
    }
    if (BITMASK(opcode, m_LXI)) {
        out->idx = 2;
        out->opA = resolve(c, (opcode & m_LXI_DST) << 2);
        out->opB = &c->memory[(*truepos)++];
    }
    if (BITMASK(opcode, m_LDA)) {
        out->idx = 3;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_STA)) {
        out->idx = 4;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_LHLD)) {
        out->idx = 5;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_SHLD)) {
        out->idx = 6;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_LDAX)) {
        out->idx = 7;
        out->opA = resolve_rp(c, (opcode & m_LDAX_SRC) << 2);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_STAX)) {
        out->idx = 8;
        out->opA = resolve_rp(c, (opcode & m_LDAX_SRC) << 2);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_XCHG)) {
        out->idx = 9;
        out->opA = NULL;
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_ADD)) {
        out->idx = 10;
        out->opA = resolve(c, (opcode & m_ADD_SRC) << 5);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_ADI)) {
        out->idx = 11;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_ADC)) {
        out->idx = 12;
        out->opA = resolve(c, (opcode & m_ADC_SRC) << 5);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_ACI)) {
        out->idx = 13;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_SUB)) {
        out->idx = 14;
        out->opA = resolve(c, (opcode & m_SUB_SRC) << 5);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_SUI)) {
        out->idx = 15;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_SBB)) {
        out->idx = 9;
        out->opA = resolve(c, (opcode & m_SBB_SRC) << 5);
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_SBI)) {
        out->idx = 9;
        out->opA = &c->memory[(*truepos)++];
        out->opB = NULL;
    }
    if (BITMASK(opcode, m_INR)) {}
    if (BITMASK(opcode, m_DCR)) {}
    if (BITMASK(opcode, m_INX)) {}
    if (BITMASK(opcode, m_DCX)) {}
    if (BITMASK(opcode, m_DAD)) {}
    if (BITMASK(opcode, m_DAA)) {}
    if (BITMASK(opcode, m_ANA)) {}
    if (BITMASK(opcode, m_ANI)) {}
    if (BITMASK(opcode, m_ORA)) {}
    if (BITMASK(opcode, m_ORI)) {}
    if (BITMASK(opcode, m_XRA)) {}
    if (BITMASK(opcode, m_XRI)) {}
    if (BITMASK(opcode, m_CMP)) {}
    if (BITMASK(opcode, m_CPI)) {}
    if (BITMASK(opcode, m_RLC)) {}
    if (BITMASK(opcode, m_RRC)) {}
    if (BITMASK(opcode, m_RAL)) {}
    if (BITMASK(opcode, m_RAR)) {}
    if (BITMASK(opcode, m_CMA)) {}
    if (BITMASK(opcode, m_CMC)) {}
    if (BITMASK(opcode, m_STC)) {}
    if (BITMASK(opcode, m_JMP)) {}
    if (BITMASK(opcode, m_Jccc)) {}
    if (BITMASK(opcode, m_CALL)) {}
    if (BITMASK(opcode, m_Cccc)) {}
    if (BITMASK(opcode, m_RET)) {}
    if (BITMASK(opcode, m_Rccc)) {}
    if (BITMASK(opcode, m_RST)) {}
    if (BITMASK(opcode, m_PCHL)) {}
    if (BITMASK(opcode, m_PUSH)) {}
    if (BITMASK(opcode, m_POP)) {}
    if (BITMASK(opcode, m_XTHL)) {}
    if (BITMASK(opcode, m_SPHL)) {}
    if (BITMASK(opcode, m_IN)) {}
    if (BITMASK(opcode, m_OUT)) {}
    if (BITMASK(opcode, m_EI)) {}
    if (BITMASK(opcode, m_DI)) {}
    if (BITMASK(opcode, m_HLT)) {}
    if (BITMASK(opcode, m_NOP)) {}
}