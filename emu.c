#include "cli/cli.h"
#include "core/log.h"
#include "cpu/cpu.h"
#include "cpu/decode/decode.h"

int main(int argc)
{
    if (argc == 1)
        return start_cli();    
}