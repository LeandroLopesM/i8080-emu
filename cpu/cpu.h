#ifndef CPU_H
#define CPU_H
#include "../core/common.h"

typedef enum {
    NZ, // ('Z'ero flag not set)
    Z,  // ('Z'ero flag set)
    NC, // ('C'arry flag not set)
    C,  // ('C'arry flag set)
    PO, // ('P'arity flag not set - ODD)
    PE, // ('P'arity flag set - EVEN)
    P,  // ('S'ign flag not set - POSITIVE)
    M,  // ('S'ign flag set - MINUS)
} condition_kind;

struct registers {
    word SP;
    word PC;

    union {
        struct {
            byte A; // 100
            struct {
                byte S: 1; // signed
                byte Z: 1; // Zero
                byte I: 1; // interrupt enable
                byte P: 1; // parity
                byte CY: 1; // Carry
                byte AC: 1; // AuxCy
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
};

typedef struct {
    struct registers rgf;
    byte memory[65536];
} cpu;

#endif // CPU_H