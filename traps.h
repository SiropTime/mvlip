#ifndef TRAPS_H
#define TRAPS_H

#include <stdint.h>
#include <stdio.h>

enum
{
    TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
    TRAP_OUT = 0x21,   /* output a character */
    TRAP_PUTS = 0x22,  /* output a word string */
    TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
    TRAP_PUTSP = 0x24, /* output a byte string */
    TRAP_HALT = 0x25   /* halt the program */
};

void trap_getc()
{
    reg[r_R0] = (uint16_t) getchar();
    update_flags(r_R0);
}

void trap_out()
{
    putc((char) reg[r_R0], stdout);
    fflush(stdout);
}

void trap_puts()
{
    uint16_t* c = memory + reg[r_R0];
    while (*c)
    {
        putc((char) *c, stdout);
        ++c;
    }

    fflush(stdout);
}

void trap_in()
{
    printf("Enter a character: ");
    char ch = getchar();
    putc(ch, stdout);
    fflush(stdout);

    reg[r_R0] = (uint16_t) ch;

    update_flags(r_R0);

}

void trap_putsp()
{
    uint16_t* c = memory + reg[r_R0];
    
    while (*c)
    {
        char ch1 = (*c) & 0xFF;
        putc(ch1, stdout);
        char ch2 = (*c) >> 8;
        if (ch2) putc(ch2, stdout);
        ++c;
    }
    
    fflush(stdout);

}

void process_traps(uint16_t instr, int *p_running)
{
    reg[r_R7] = reg[r_PC];

    switch (instr & 0xFF)
    {
    case TRAP_GETC:
        trap_getc();
        
        break;
    case TRAP_OUT:
        trap_out();
        
        break;
    case TRAP_PUTS:
        trap_puts();

        break;
    case TRAP_IN:
        trap_in();

        break;
    case TRAP_PUTSP:
        trap_putsp();

        break;
    case TRAP_HALT:
        puts("HALT");
        fflush(stdout);

        (*p_running) = 0;
        break;
    
    }
}

#endif