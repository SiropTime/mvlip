#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count -1)) & 1)
    {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

#endif