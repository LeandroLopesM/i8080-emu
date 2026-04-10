#ifndef CPU_H
#define CPU_H
#include "../core/common.h"

struct Registers {
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
            } flags; // 101
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
    struct Registers rgf;
    byte memory[65536];
} cpu;

#endif // CPU_H