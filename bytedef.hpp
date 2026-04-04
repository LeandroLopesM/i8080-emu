#ifndef BYTEDEF_HPP
#define BYTEDEF_HPP

#include <bit>
#include <cstdint>

#if std::endian::native == std::endian::little
    typedef se_byte byte;
#else
    typedef uint8_t byte;
#endif

#endif // BYTEDEF_HPP