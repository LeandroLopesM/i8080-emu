#include <iostream>
#include <vector>

int main()
{
    std::string input;
    while (true)
    {
        std::cout << "> ";
        std::cin >> input;

    }
}

#include <cstdint>
#include <string>
#include <cstdarg>
#include <algorithm>

[[noreturn]] void panic(cpu c, std::string fmt, ...) {
    va_list va;
    va_start(va, fmt);
        vprintf(fmt.c_str(), va);
    va_end(va);

    c.dump_registers();
    c.dump_memory();

    exit(1);
}

byte encode(std::string in, std::string opA, std::string opB)
{
    if (in == "MOV") //  MOV D,S   01DDDSSS          -       Move register to register
    {

    }
    else if (in == "MVI") //  MVI D,#   00DDD110 db       -       Move immediate to register
    {

    }
    else if (in == "LXI") //  LXI RP,#  00RP0001 lb hb    -       Load register pair immediate
    {

    }
    else if (in == "LDA") //  LDA a     00111010 lb hb    -       Load A from memory
    {

    }
    else if (in == "STA") //  STA a     00110010 lb hb    -       Store A to memory
    {

    }
    else if (in == "LHLD") //  LHLD a    00101010 lb hb    -       Load H:L from memory
    {

    }
    else if (in == "SHLD") //  SHLD a    00100010 lb hb    -       Store H:L to memory
    {

    }
    else if (in == "LDAX") //  LDAX RP   00RP1010 *1       -       Load indirect through BC or DE
    {

    }
    else if (in == "STAX") //  STAX RP   00RP0010 *1       -       Store indirect through BC or DE
    {

    }
    else if (in == "XCHG") //  XCHG      11101011          -       Exchange DE and HL content
    {

    }
    else if (in == "ADD") //  ADD S     10000SSS          ZSPCA   Add register to A
    {

    }
    else if (in == "ADI") //  ADI #     11000110 db       ZSCPA   Add immediate to A
    {

    }
    else if (in == "ADC") //  ADC S     10001SSS          ZSCPA   Add register to A with carry
    {

    }
    else if (in == "ACI") //  ACI #     11001110 db       ZSCPA   Add immediate to A with carry
    {

    }
    else if (in == "SUB") //  SUB S     10010SSS          ZSCPA   Subtract register from A
    {

    }
    else if (in == "SUI") //  SUI #     11010110 db       ZSCPA   Subtract immediate from A
    {

    }
    else if (in == "SBB") //  SBB S     10011SSS          ZSCPA   Subtract register from A with borrow
    {

    }
    else if (in == "SBI") //  SBI #     11011110 db       ZSCPA   Subtract immediate from A with borrow
    {

    }
    else if (in == "INR") //  INR D     00DDD100          ZSPA    Increment register
    {

    }
    else if (in == "DCR") //  DCR D     00DDD101          ZSPA    Decrement register
    {

    }
    else if (in == "INX") //  INX RP    00RP0011          -       Increment register pair
    {

    }
    else if (in == "DCX") //  DCX RP    00RP1011          -       Decrement register pair
    {

    }
    else if (in == "DAD") //  DAD RP    00RP1001          C       Add register pair to HL (16 bit add)
    {

    }
    else if (in == "DAA") //  DAA       00100111          ZSPCA   Decimal Adjust accumulator
    {

    }
    else if (in == "ANA") //  ANA S     10100SSS          ZSCPA   AND register with A
    {

    }
    else if (in == "ANI") //  ANI #     11100110 db       ZSPCA   AND immediate with A
    {

    }
    else if (in == "ORA") //  ORA S     10110SSS          ZSPCA   OR  register with A
    {

    }
    else if (in == "ORI") //  ORI #     11110110          ZSPCA   OR  immediate with A
    {

    }
    else if (in == "XRA") //  XRA S     10101SSS          ZSPCA   ExclusiveOR register with A
    {

    }
    else if (in == "XRI") //  XRI #     11101110 db       ZSPCA   ExclusiveOR immediate with A
    {

    }
    else if (in == "CMP") //  CMP S     10111SSS          ZSPCA   Compare register with A
    {

    }
    else if (in == "CPI") //  CPI #     11111110          ZSPCA   Compare immediate with A
    {

    }
    else if (in == "RLC") //  RLC       00000111          C       Rotate A left
    {

    }
    else if (in == "RRC") //  RRC       00001111          C       Rotate A right
    {

    }
    else if (in == "RAL") //  RAL       00010111          C       Rotate A left through carry
    {

    }
    else if (in == "RAR") //  RAR       00011111          C       Rotate A right through carry
    {

    }
    else if (in == "CMA") //  CMA       00101111          -       Compliment A
    {

    }
    else if (in == "CMC") //  CMC       00111111          C       Compliment Carry flag
    {

    }
    else if (in == "STC") //  STC       00110111          C       Set Carry flag
    {

    }
    else if (in == "JMP") //  JMP a     11000011 lb hb    -       Unconditional jump
    {

    }
    else if (in == "Jccc") //  Jccc a    11CCC010 lb hb    -       Conditional jump
    {

    }
    else if (in == "CALL") //  CALL a    11001101 lb hb    -       Unconditional subroutine call
    {

    }
    else if (in == "Cccc") //  Cccc a    11CCC100 lb hb    -       Conditional subroutine call
    {

    }
    else if (in == "RET") //  RET       11001001          -       Unconditional return from subroutine
    {

    }
    else if (in == "Rccc") //  Rccc      11CCC000          -       Conditional return from subroutine
    {

    }
    else if (in == "RST") //  RST n     11NNN111          -       Restart (Call n*8)
    {

    }
    else if (in == "PCHL") //  PCHL      11101001          -       Jump to address in H:L
    {

    }
    else if (in == "PUSH") //  PUSH RP   11RP0101 *2       -       Push register pair on the stack
    {

    }
    else if (in == "POP") //  POP RP    11RP0001 *2       *2      Pop  register pair from the stack
    {

    }
    else if (in == "XTHL") //  XTHL      11100011          -       Swap H:L with top word on stack
    {

    }
    else if (in == "SPHL") //  SPHL      11111001          -       Set SP to content of H:L
    {

    }
    else if (in == "IN") //  IN p      11011011 pa       -       Read input port into A
    {

    }
    else if (in == "OUT") //  OUT p     11010011 pa       -       Write A to output port
    {

    }
    else if (in == "EI") //  EI        11111011          -       Enable interrupts
    {

    }
    else if (in == "DI") //  DI        11110011          -       Disable interrupts
    {

    }
    else if (in == "HLT") //  HLT       01110110          -       Halt processor
    {

    }
    else if (in == "NOP") //  NOP       00000000          -       No operation
    {

    }
}