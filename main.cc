#include <cstddef>
#include <cstdint>
#include <string>
#include <cstdarg>
#include <algorithm>

#define GetBit(N, K) \
 ((N >> K) & 1)
#define SetBit(N, K) \
 (N = N | (1 << K))
#define ClearBit(N, K) \
 (N = N & ~(1 << K))
#define ToggleBit(N, K) \
 (N = N ^ (1 << K))
#define ModBit(N, K) \
 (N = N | (P << K))

enum opcodes {
MOV, MVI, LXI, LDA, STA, LHLD, SHLD, LDAX, STAX, XCHG, ADD, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, DAD, DAA, ANA, ANI, ORA, ORI, XRA, XRI, CMP, CPI, RLC, RRC, RAL, RAR, CMA, CMC, STC, JMP, Jccc, CALL, Cccc, RET, Rccc, RST, PCHL, PUSH, POP, XTHL, SPHL, IN, OUT, EI, DI, HLT, NOP, };

typedef uint8_t byte;
typedef uint16_t word;

struct cpu {
    struct registers {
        word SP;
        word PC;

        union {
            struct {
                byte A; // 100
                struct {
                    byte S: 1;
                    byte Z: 1;
                    byte P: 1;
                    byte AC: 1;
                }; // 101
            };
            word PSW;
        };

        union {
            struct {
                byte D; // 100
                byte E; // 101
            };
            word DE;
        };

        union {
            struct {
                byte B; // 100
                byte C; // 101
            };
            word BC;
        };

        union {
            struct {
                byte H; // 100
                byte L; // 101
            };
            word HL;
        };

    } rgf;

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
    }
    byte memory[1024];

    void parse();
    byte zspca(byte before, byte after);
    void dump_registers();
    void dump_memory();
};

byte cpu::zspca(byte before, byte after)
{
    rgf.S = GetBit(after, 7) == 1;
    rgf.Z = after == 0;
    rgf.P = GetBit(after, 0);
    rgf.AC |= GetBit(after, 3);

    return after;
}

byte bitrange(byte in, byte start, byte end)
{
    byte out = 0;
    for (auto i = start; i <= end; ++i)
    {
        if (GetBit(in, i))
            SetBit(out, i);
    }
}

union tword {
    struct {
        byte l;
        byte h;
    };
    word w;
};

word weld_lh(byte lo, byte hi)
{
    return tword{lo, hi}.w;
}

void cpu::dump_registers()
{
    printf("\n\
A(%3d) %8b\t\n\
B(%3d) %8b\nC(%3d) %8b\t==> BC(%5d) %16b\n\
D(%3d) %8b\nE(%3d) %8b\t==> DE(%5d) %16b\n\
H(%3d) %8b\nL(%3d) %8b\t==> HL(%5d) %16b\n\
PC: %5d\tPSW %5d\n\
%b %b %b %b\n\
Z S P C A\n",
rgf.A,
rgf.B, rgf.C,
rgf.D, rgf.E,
rgf.H, rgf.L,
rgf.PC, rgf.PSW,
rgf.Z, rgf.S, rgf.P, rgf.C, rgf.A);
}

void cpu::dump_memory()
{
    auto lowbound = std::clamp(rgf.PC - 5, 0, 1024);
    auto upbound = std::clamp(rgf.PC - 5, 0, 1024);

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

[[noreturn]] void panic(cpu c, std::string fmt, ...) {
    va_list va;
    va_start(va, fmt);
        vprintf(fmt.c_str(), va);
    va_end(va);

    c.dump_registers();
    c.dump_memory();
}

void cpu::parse()
{
    byte opcode = memory[rgf.PC++];
    switch (opcode)
    {
        //  MOV D,S   01DDDSSS          -       Move register to register
        case MOV:
            resolve(bitrange(opcode, 2, 4)) = resolve(bitrange(opcode, 5, 7));
        //  MVI D,#   00DDD110 db       -       Move immediate to register
        case MVI:
            resolve(bitrange(opcode, 2, 4)) = memory[rgf.PC++];
        //  LXI RP,#  00RP0001 lb hb    -       Load register pair immediate
        case LXI:
            resolve_rp(bitrange(opcode, 2, 3)) = weld_lh(memory[rgf.PC++], memory[rgf.PC++]);
        //  LDA a     00111010 lb hb    -       Load A from memory
        case LDA:
            rgf.A = memory[weld_lh(memory[rgf.PC++], memory[rgf.PC++])];
        //  STA a     00110010 lb hb    -       Store A to memory
        case STA:
            memory[weld_lh(memory[rgf.PC++], memory[rgf.PC++])] = rgf.A;
        //  LHLD a    00101010 lb hb    -       Load H:L from memory
        case LHLD:
            rgf.HL = weld_lh(memory[rgf.PC++], memory[rgf.PC++]);
        //  SHLD a    00100010 lb hb    -       Store H:L to memory
        case SHLD:
            memory[memory[rgf.PC++]] = rgf.H;
            memory[memory[rgf.PC++]] = rgf.L;
        //  LDAX RP   00RP1010 *1       -       Load indirect through BC or DE
        case LDAX:
            rgf.A = memory[resolve_rp(bitrange(opcode, 2, 3))];
        //  STAX RP   00RP0010 *1       -       Store indirect through BC or DE
        case STAX:
            memory[resolve_rp(bitrange(opcode, 2, 3))] = rgf.A;
        //  XCHG      11101011          -       Exchange DE and HL content
        case XCHG:
            byte HL = rgf.HL;
            rgf.HL = rgf.DE;
            rgf.DE = HL;
        //  ADD S     10000SSS          ZSPCA   Add register to A
        case ADD:
            rgf.A = zspca(rgf.A, rgf.A + resolve(bitrange(opcode, 5, 7)));
        //  ADI #     11000110 db       ZSCPA   Add immediate to A
        case ADI:
            rgf.A = zspca(rgf.A, rgf.A + memory[rgf.PC++]);
        //  ADC S     10001SSS          ZSCPA   Add register to A with carry
        case ADC:
            rgf.A = zspca(rgf.A, rgf.A + resolve(bitrange(opcode, 5, 7)) + rgf.C);
        //  ACI #     11001110 db       ZSCPA   Add immediate to A with carry
        case ACI:
            rgf.A = zspca(rgf.A, rgf.A + memory[rgf.PC++] + rgf.C);

        //  SUB S     10010SSS          ZSCPA   Subtract register from A
        case SUB:
        //  SUI #     11010110 db       ZSCPA   Subtract immediate from A
        case SUI:
        //  SBB S     10011SSS          ZSCPA   Subtract register from A with borrow
        case SBB:
        //  SBI #     11011110 db       ZSCPA   Subtract immediate from A with borrow
        case SBI:
            panic(*this, "[SUB] Unimplemented");
        //  INR D     00DDD100          ZSPA    Increment register
        case INR:
        //  DCR D     00DDD101          ZSPA    Decrement register
        case DCR:
        //  INX RP    00RP0011          -       Increment register pair
        case INX:
        //  DCX RP    00RP1011          -       Decrement register pair
        case DCX:
        //  DAD RP    00RP1001          C       Add register pair to HL (16 bit add)
        case DAD:
        //  DAA       00100111          ZSPCA   Decimal Adjust accumulator
        case DAA:
        //  ANA S     10100SSS          ZSCPA   AND register with A
        case ANA:
        //  ANI #     11100110 db       ZSPCA   AND immediate with A
        case ANI:
        //  ORA S     10110SSS          ZSPCA   OR  register with A
        case ORA:
        //  ORI #     11110110          ZSPCA   OR  immediate with A
        case ORI:
        //  XRA S     10101SSS          ZSPCA   ExclusiveOR register with A
        case XRA:
        //  XRI #     11101110 db       ZSPCA   ExclusiveOR immediate with A
        case XRI:
        //  CMP S     10111SSS          ZSPCA   Compare register with A
        case CMP:
        //  CPI #     11111110          ZSPCA   Compare immediate with A
        case CPI:
        //  RLC       00000111          C       Rotate A left
        case RLC:
        //  RRC       00001111          C       Rotate A right
        case RRC:
        //  RAL       00010111          C       Rotate A left through carry
        case RAL:
        //  RAR       00011111          C       Rotate A right through carry
        case RAR:
        //  CMA       00101111          -       Compliment A
        case CMA:
        //  CMC       00111111          C       Compliment Carry flag
        case CMC:
        //  STC       00110111          C       Set Carry flag
        case STC:
        //  JMP a     11000011 lb hb    -       Unconditional jump
        case JMP:
        //  Jccc a    11CCC010 lb hb    -       Conditional jump
        case Jccc:
        //  CALL a    11001101 lb hb    -       Unconditional subroutine call
        case CALL:
        //  Cccc a    11CCC100 lb hb    -       Conditional subroutine call
        case Cccc:
        //  RET       11001001          -       Unconditional return from subroutine
        case RET:
        //  Rccc      11CCC000          -       Conditional return from subroutine
        case Rccc:
        //  RST n     11NNN111          -       Restart (Call n*8)
        case RST:
        //  PCHL      11101001          -       Jump to address in H:L
        case PCHL:
        //  PUSH RP   11RP0101 *2       -       Push register pair on the stack
        case PUSH:
        //  POP RP    11RP0001 *2       *2      Pop  register pair from the stack
        case POP:
        //  XTHL      11100011          -       Swap H:L with top word on stack
        case XTHL:
        //  SPHL      11111001          -       Set SP to content of H:L
        case SPHL:
        //  IN p      11011011 pa       -       Read input port into A
        case IN:
        //  OUT p     11010011 pa       -       Write A to output port
        case OUT:
        //  EI        11111011          -       Enable interrupts
        case EI:
        //  DI        11110011          -       Disable interrupts
        case DI:
        //  HLT       01110110          -       Halt processor
        case HLT:
        //  NOP       00000000          -       No operation
        case NOP:
    }
}