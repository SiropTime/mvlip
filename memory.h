#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_MAX (1 << 16)

#include <stdint.h>


uint16_t memory[MEMORY_MAX];

/* Memory mapped registers */
enum
{
    mr_KBSR = 0xFE00, /* Has key been pressed */
    mr_KBDR = 0xFE02  /* Which key was pressed */  
};

void mem_write(uint16_t address, uint16_t val)
{
    memory[address]  = val;
}

uint16_t mem_read(uint16_t address)
{
    if (address == mr_KBSR)
    {
        if (check_key())
        {
            memory[mr_KBSR] = (1 << 15);
            memory[mr_KBDR] = getchar();
        }
        else
        {
            memory[mr_KBSR] = 0;
        }
    }

    return memory[address];
}

#endif