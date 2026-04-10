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
        } _;
        word PSW;
    } _;

    union {
        struct {
            byte D; // 100
            byte E; // 101
        }_;
        word DE;
    }_0;

    union {
        struct {
            byte B; // 100
            byte C; // 101
        }_;
        word BC;
    }_1;

    union {
        struct {
            byte H; // 100
            byte L; // 101
        }_;
        word HL;
    }_2;
};

typedef struct {
    struct Registers rgf;
    byte memory[65536];
} cpu;

#endif // CPU_H