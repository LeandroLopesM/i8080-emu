#ifndef MASKS_HPP
#define MASKS_HPP

#define DF_REG_MASK 0b00111000
#define DF_RP_MASK 0b00110000

#define m_MOV   "01______"  // MOV D,S   01______          -       Move register to register
#define m_MVI   "00___110"  // MVI D,#   00___110 db       -       Move immediate to register
#define m_LXI   "00__0001"  // LXI __,#  00__0001 lb hb    -       Load register pair immediate
#define m_LDA   "00111010"  // LDA a     00111010 lb hb    -       Load A from memory
#define m_STA   "00110010"  // STA a     00110010 lb hb    -       Store A to memory
#define m_LHLD  "00101010"  // LHLD a    00101010 lb hb    -       Load H:L from memory
#define m_SHLD  "00100010"  // SHLD a    00100010 lb hb    -       Store H:L to memory
#define m_LDAX  "00__1010"  // LDAX __   00__1010 *1       -       Load indirect through BC or DE
#define m_STAX  "00__0010"  // STAX __   00__0010 *1       -       Store indirect through BC or DE
#define m_XCHG  "11101011"  // XCHG      11101011          -       Exchange DE and HL content
#define m_ADD   "10000___"  // ADD S     10000___          ZSPCA   Add register to A
#define m_ADI   "11000110"  // ADI #     11000110 db       ZSCPA   Add immediate to A
#define m_ADC   "10001___"  // ADC S     10001___          ZSCPA   Add register to A with carry
#define m_ACI   "11001110"  // ACI #     11001110 db       ZSCPA   Add immediate to A with carry
#define m_SUB   "10010___"  // SUB S     10010___          ZSCPA   Subtract register from A
#define m_SUI   "11010110"  // SUI #     11010110 db       ZSCPA   Subtract immediate from A
#define m_SBB   "10011___"  // SBB S     10011___          ZSCPA   Subtract register from A with borrow
#define m_SBI   "11011110"  // SBI #     11011110 db       ZSCPA   Subtract immediate from A with borrow
#define m_INR   "00___100"  // INR D     00___100          ZSPA    Increment register
#define m_DCR   "00___101"  // DCR D     00___101          ZSPA    Decrement register
#define m_INX   "00__0011"  // INX __    00__0011          -       Increment register pair
#define m_DCX   "00__1011"  // DCX __    00__1011          -       Decrement register pair
#define m_DAD   "00__1001"  // DAD __    00__1001          C       Add register pair to HL (16 bit add)
#define m_DAA   "00100111"  // DAA       00100111          ZSPCA   Decimal Adjust accumulator
#define m_ANA   "10100___"  // ANA S     10100___          ZSCPA   AND register with A
#define m_ANI   "11100110"  // ANI #     11100110 db       ZSPCA   AND immediate with A
#define m_ORA   "10110___"  // ORA S     10110___          ZSPCA   OR  register with A
#define m_ORI   "11110110"  // ORI #     11110110          ZSPCA   OR  immediate with A
#define m_XRA   "10101___"  // XRA S     10101___          ZSPCA   ExclusiveOR register with A
#define m_XRI   "11101110"  // XRI #     11101110 db       ZSPCA   ExclusiveOR immediate with A
#define m_CMP   "10111___"  // CMP S     10111___          ZSPCA   Compare register with A
#define m_CPI   "11111110"  // CPI #     11111110          ZSPCA   Compare immediate with A
#define m_RLC   "00000111"  // RLC       00000111          C       Rotate A left
#define m_RRC   "00001111"  // RRC       00001111          C       Rotate A right
#define m_RAL   "00010111"  // RAL       00010111          C       Rotate A left through carry
#define m_RAR   "00011111"  // RAR       00011111          C       Rotate A right through carry
#define m_CMA   "00101111"  // CMA       00101111          -       Compliment A
#define m_CMC   "00111111"  // CMC       00111111          C       Compliment Carry flag
#define m_STC   "00110111"  // STC       00110111          C       Set Carry flag
#define m_JMP   "11000011"  // JMP a     11000011 lb hb    -       Unconditional jump
#define m_Jccc  "11___010"  // Jccc a    11___010 lb hb    -       Conditional jump
#define m_CALL  "11001101"  // CALL a    11001101 lb hb    -       Unconditional subroutine call
#define m_Cccc  "11___100"  // Cccc a    11___100 lb hb    -       Conditional subroutine call
#define m_RET   "11001001"  // RET       11001001          -       Unconditional return from subroutine
#define m_Rccc  "11___000"  // Rccc      11___000          -       Conditional return from subroutine
#define m_RST   "11___111"  // RST n     11___111          -       Restart (Call n*8)
#define m_PCHL  "11101001"  // PCHL      11101001          -       Jump to address in H:L
#define m_PUSH  "11__0101"  // PUSH __   11__0101 *2       -       Push register pair on the stack
#define m_POP   "11__0001"  // POP __    11__0001 *2       *2      Pop  register pair from the stack
#define m_XTHL  "11100011"  // XTHL      11100011          -       Swap H:L with top word on stack
#define m_SPHL  "11111001"  // SPHL      11111001          -       Set SP to content of H:L
#define m_IN    "11011011"  // IN p      11011011 pa       -       Read input port into A
#define m_OUT   "11010011"  // OUT p     11010011 pa       -       Write A to output port
#define m_EI    "11111011"  // EI        11111011          -       Enable interrupts
#define m_DI    "11110011"  // DI        11110011          -       Disable interrupts
#define m_HLT   "01110110"  // HLT       01110110          -       Halt processor
#define m_NOP   "00000000"  // NOP       00000000          -       No operation

#endif // MASKS_HPP