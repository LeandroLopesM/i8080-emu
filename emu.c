#include "cli/cli.h"
#include "core/log.h"
#include "cpu/cpu.h"
#include "cpu/decode/decode.h"

int main(int argc, char** argv)
{
    (void)(argv);
    if (argc == 1)
        return start_cli();
}