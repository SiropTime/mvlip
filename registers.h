#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

enum
{
    /* General purpose registers */
    r_R0 = 0,
    r_R1,
    r_R2,
    r_R3,
    r_R4,
    r_R5,
    r_R6,
    r_R7,
    r_PC, /* Program counter */
    r_COND, /* Condition flasgs */
    r_COUNT
};

uint16_t reg[r_COUNT];

#endif