#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "common.hpp"
#include <variant>

enum  InstructionKind {
    MOV , MVI , LXI , LDA ,
    STA , LHLD, SHLD, LDAX,
    STAX, XCHG, ADD , ADI ,
    ADC , ACI , SUB , SUI ,
    SBB , SBI , INR , DCR ,
    INX , DCX , DAD , DAA ,
    ANA , ANI , ORA , ORI ,
    XRA , XRI , CMP , CPI ,
    RLC , RRC , RAL , RAR ,
    CMA , CMC , STC , JMP ,
    Jccc, CALL, Cccc, RET ,
    Rccc, RST , PCHL, PUSH,
    POP , XTHL, SPHL, IN  ,
    OUT , EI  , DI  , HLT ,
    NOP ,
};

struct Instruction {
    InstructionKind type;
    std::variant<byte, word>* lhs;
    std::variant<byte, word>* rhs;

    Instruction() = default;
    Instruction(Instruction& i) = default;

    Instruction(InstructionKind type,
                std::variant<byte, word>* lhs,
                std::variant<byte, word>* rhs) {
        this->type = type;
        this->lhs = lhs;
        this->rhs = rhs;
    };
};

#endif // INSTRUCTION_HPP