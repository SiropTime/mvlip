#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>


enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

void update_flags(uint16_t r)
{
    if (reg[r] == 0)
    {
        reg[r_COND] = FL_ZRO;

    }
    else if (reg[r] >> 15) /* Checking first from left byte for negative number */
    {
        reg[r_COND] = FL_NEG;
    }
    else
    {
        reg[r_COND] = FL_POS;
    }
}

#endif