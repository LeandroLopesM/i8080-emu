#include "core/log.h"
#include "cpu/cpu.h"
#include "cpu/decode/decode.h"
int main()
{
    cpu c = {0};
    c.memory[0] = 0b11000110;
    c.memory[1] = 12;
    instruction* i = decode(&c, 0, 0);
    exec(&c, i);
    panic_ext(&c, "Something");
}