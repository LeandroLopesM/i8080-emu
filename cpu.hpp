#ifndef CPU_HPP
#define CPU_HPP

#include "common.hpp"
#include "instructions.hpp"
#include "registers.hpp"
#include "panic.hpp"
#include <cmath>
#include <vector>

class CPU {
public:
    Registers rgf;
    std::vector<byte> memory;

    CPU() { memory = std::vector<byte>(static_cast<size_t>(trunc(pow(2, sizeof(Registers::HL) * 8)))); }

    byte &resolve(byte in)
    {
        switch (in)
        {
        case 0b111:
            return rgf.A;
        case 0b000:
            return rgf.B;
        case 0b001:
            return rgf.C;
        case 0b010:
            return rgf.D;
        case 0b011:
            return rgf.E;
        case 0b100:
            return rgf.H;
        case 0b101:
            return rgf.L;
        case 0b110:
            return memory[rgf.HL];
        }

        panic(*this, "Tried to resolve unknown register %4b", in); return rgf.L;
    }

    word &resolve_rp(byte in, bool is_PP = false)
    {
        switch (in)
        {
        case 0b00:
            return rgf.BC; // (B:C as 16 bit register)
        case 0b01:
            return rgf.DE; // (D:E as 16 bit register)
        case 0b10:
            return rgf.HL; // (H:L as 16 bit register)
        case 0b11:
            return is_PP? rgf.PSW : rgf.SP; // (Stack pointer, refers to PSW (FLAGS:A) for PUSH/POP)
        }

        panic(*this, "Tried to resolve unknown word register %4b", in); return rgf.HL;
    }

    void tick();
    byte zspca(byte before, byte after);
    Instruction decode(word& pos);
    void dump_registers()
    {
        printf("\n\
Register dump:\n\
A: %2X\n\
.  [ B: %2X  C: %2X ]  >  BC: %-4X \n\
.  [ D: %2X  E: %2X ]  >  DE: %-4X \n\
.  [ H: %2X  L: %2X ]  >  HL: %-4X \n\
PC:  %-4X\n\
SP:  %-4X\n\
PSW: %-4X\n\
%d %d %d %d %d\n\
Z S P C A\n",
        rgf.A,
        rgf.B, rgf.C, rgf.BC,
        rgf.D, rgf.E, rgf.DE,
        rgf.H, rgf.L, rgf.HL,
        rgf.PC, rgf.SP, rgf.PSW,
        rgf.Z, rgf.S, rgf.P, rgf.C, rgf.A);
    }

    void dump_memory()
    {
        auto lowbound = clamp(rgf.PC - 5, 0, 1024);
        auto upbound = clamp(rgf.PC - 5, 0, 1024);

        for (int i = lowbound; i < upbound; ++i)
        {
            printf("%*c%*c%#x%*c%*c",
                (i == lowbound)? 0 : 1, ' ',
                (i == rgf.PC)? 1 : 0, '[',
                memory[i],
                (i == rgf.PC)? 1 : 0, ']',
                (i == upbound - 1)? 0 : 1, ' ' );
        }
    }
};

#endif // CPU_HPP