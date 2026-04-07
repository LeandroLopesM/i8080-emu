#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "common.hpp"
#include <utility>

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

template<typename A,typename B>
struct Instruction {
    InstructionKind type;
    std::pair<A, B> ops;

    Instruction(Instruction& i) = default;
    Instruction(InstructionKind type,
        std::pair<A, B> ops) : type(type), ops(ops) {}

};

#endif // INSTRUCTION_HPP