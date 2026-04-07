#include "instruction_masks.hpp"
#include "instructions.hpp"
#include "cpu.hpp"

Instruction CPU::decode(word& pos)
{
    byte* reference_buffer = &memory[0];
    static Instruction* instruction_buffer;

    if ((memory[pos++] & m_MOV) == m_MOV)
    {
        instruction_buffer = Instruction<byte&, byte&> {
            MOV,
            {
                resolve(memory[pos++] | m_MOV_DST << 2),
                resolve(memory[pos++] | m_MOV_SRC << 5)
            }
        };
    } else if ((memory[pos++] & m_MVI) == m_MVI)
    {
        instruction_buffer = Instruction<byte&, byte&> {
            MVI,
            { resolve(memory[pos++] | m_MVI_DST << 2), memory[0] }
        };
    } else if ((memory[pos++] & m_LXI) == m_LXI)
    {
        instruction_buffer = Instruction<word&, byte&> {
            LXI,
            { resolve_rp(memory[pos++] | m_LXI_DST << 2), memory[0]}
        };
    } else if ((memory[pos++] & m_LDA) == m_LDA)
    {
        instruction_buffer = Instruction<byte, byte> {
            LDA,
            {
                memory[pos++],
                memory[pos++],
            }
        };
    } else if ((memory[pos++] & m_STA) == m_STA)
    {
        instruction_buffer = Instruction<byte, byte> {
            STA,
            {
                memory[pos++],
                memory[pos++],
            }
        };
    } else if ((memory[pos++] & m_LHLD) == m_LHLD)
    {
        instruction_buffer = Instruction<byte, byte> {
            LHLD,
            {
                memory[pos++],
                memory[pos++],
            }
        };
    } else if ((memory[pos++] & m_SHLD) == m_SHLD)
    {
        instruction_buffer = Instruction<byte, byte>
        {
            SHLD,
            {
                memory[pos++],
                memory[pos++],
            }
        }
    } else if ((memory[pos++] & m_LDAX) == m_LDAX)
    {
        instruction_buffer = Instruction<byte&, byte*> {
            LDAX,
            {
                memory[resolve_rp((memory[pos - 1] | m_LDAX_SRC) << 2)],
                nullptr
            }
        };
    } else if ((memory[pos++] & m_STAX) == m_STAX)
    {
        instruction_buffer = Instruction<byte&, byte*> {
            STAX,
            {
                memory[resolve_rp((memory[pos - 1] | m_LDAX_SRC) << 2)],
                nullptr
            }
        };
    } else if ((memory[pos++] & m_XCHG) == m_XCHG)
    {
        instruction_buffer = Instruction<byte*, byte*> {
            XCHG,
            {nullptr, nullptr}
        };
    } else if ((memory[pos++] & m_ADD) == m_ADD)
    {

    } else if ((memory[pos++] & m_ADI) == m_ADI)
    {

    } else if ((memory[pos++] & m_ADC) == m_ADC)
    {

    } else if ((memory[pos++] & m_ACI) == m_ACI)
    {

    } else if ((memory[pos++] & m_SUB) == m_SUB)
    {

    } else if ((memory[pos++] & m_SUI) == m_SUI)
    {

    } else if ((memory[pos++] & m_SBB) == m_SBB)
    {

    } else if ((memory[pos++] & m_SBI) == m_SBI)
    {

    } else if ((memory[pos++] & m_INR) == m_INR)
    {

    } else if ((memory[pos++] & m_DCR) == m_DCR)
    {

    } else if ((memory[pos++] & m_INX) == m_INX)
    {

    } else if ((memory[pos++] & m_DCX) == m_DCX)
    {

    } else if ((memory[pos++] & m_DAD) == m_DAD)
    {

    } else if ((memory[pos++] & m_DAA) == m_DAA)
    {

    } else if ((memory[pos++] & m_ANA) == m_ANA)
    {

    } else if ((memory[pos++] & m_ANI) == m_ANI)
    {

    } else if ((memory[pos++] & m_ORA) == m_ORA)
    {

    } else if ((memory[pos++] & m_ORI) == m_ORI)
    {

    } else if ((memory[pos++] & m_XRA) == m_XRA)
    {

    } else if ((memory[pos++] & m_XRI) == m_XRI)
    {

    } else if ((memory[pos++] & m_CMP) == m_CMP)
    {

    } else if ((memory[pos++] & m_CPI) == m_CPI)
    {

    } else if ((memory[pos++] & m_RLC) == m_RLC)
    {

    } else if ((memory[pos++] & m_RRC) == m_RRC)
    {

    } else if ((memory[pos++] & m_RAL) == m_RAL)
    {

    } else if ((memory[pos++] & m_RAR) == m_RAR)
    {

    } else if ((memory[pos++] & m_CMA) == m_CMA)
    {

    } else if ((memory[pos++] & m_CMC) == m_CMC)
    {

    } else if ((memory[pos++] & m_STC) == m_STC)
    {

    } else if ((memory[pos++] & m_JMP) == m_JMP)
    {

    } else if ((memory[pos++] & m_Jccc) == m_Jccc)
    {

    } else if ((memory[pos++] & m_CALL) == m_CALL)
    {

    } else if ((memory[pos++] & m_Cccc) == m_Cccc)
    {

    } else if ((memory[pos++] & m_RET) == m_RET)
    {

    } else if ((memory[pos++] & m_Rccc) == m_Rccc)
    {

    } else if ((memory[pos++] & m_RST) == m_RST)
    {

    } else if ((memory[pos++] & m_PCHL) == m_PCHL)
    {

    } else if ((memory[pos++] & m_PUSH) == m_PUSH)
    {

    } else if ((memory[pos++] & m_POP) == m_POP)
    {

    } else if ((memory[pos++] & m_XTHL) == m_XTHL)
    {

    } else if ((memory[pos++] & m_SPHL) == m_SPHL)
    {

    } else if ((memory[pos++] & m_IN) == m_IN)
    {

    } else if ((memory[pos++] & m_OUT) == m_OUT)
    {

    } else if ((memory[pos++] & m_EI) == m_EI)
    {

    } else if ((memory[pos++] & m_DI) == m_DI)
    {

    } else if ((memory[pos++] & m_HLT) == m_HLT)
    {

    } else if ((memory[pos++] & m_NOP) == m_NOP)
    {

    }

    opcode = (opcode) == 0 ? memory[rgf.PC++] : opcode;
}