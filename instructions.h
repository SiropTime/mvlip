#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

enum
{
    op_BR = 0, /* branch */
    /*
    ADD A B C. Sum B and C then stores in A. Or
    ADD A B int. Adds int to B and store in A.
    */
    op_ADD,    
    op_LD,     /* load */
    op_ST,     /* store */
    op_JSR,    /* jump register */
    op_AND,    /* bitwise and */
    op_LDR,    /* load register */
    op_STR,    /* store register */
    op_RTI,    /* unused */
    op_NOT,    /* bitwise not */
    op_LDI,    /* load indirect */
    op_STI,    /* store indirect */
    op_JMP,    /* jump */
    op_RES,    /* reserved (unused) */
    op_LEA,    /* load effective address */
    op_TRAP    /* execute trap */
};

#endif