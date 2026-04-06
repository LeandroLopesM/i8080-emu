#ifndef PANIC_HPP
#define PANIC_HPP

#include <cstdarg>
#include <string>

template<typename T>
[[noreturn]] void panic(T c, std::string fmt, ...) {
    va_list va;
    va_start(va, fmt);
        vprintf(fmt.c_str(), va);
    va_end(va);

    c.dump_registers();
    c.dump_memory();

    exit(1);
}

#endif // PANIC_HPP