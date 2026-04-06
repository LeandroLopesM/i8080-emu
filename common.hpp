#ifndef BYTEDEF_HPP
#define BYTEDEF_HPP

#include <cstdint>

// #if std::endian::native == std::endian::little
    // typedef se_byte byte;
// #else
typedef uint8_t byte;
typedef uint16_t word;

#define GetBit(N, K) \
 ((N >> K) & 1)
#define SetBit(N, K) \
 (N = N | (1 << K))
#define ClearBit(N, K) \
 (N = N & ~(1 << K))
#define ToggleBit(N, K) \
 (N = N ^ (1 << K))
#define ModBit(N, K) \
 (N = N | (P << K))
// #endif

template <typename T>
inline T clamp(T a, T lo, T hi)
{
    return a <= lo? lo : a >= hi? hi : a;
}

#endif // BYTEDEF_HPP