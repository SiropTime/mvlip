#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>


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

void op_add(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    /* First operand */
    uint16_t r1 = (instr >> 6) & 0x7;
    /* Whether we are in immediate mode */
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if (imm_flag)
    {
        /* If that's true we adding integer (5 bits) from the instruction */
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[r0] = reg[r1] + imm5;
    } else {
        /* Else we getting register and sum with another */
        uint16_t r2 = instr & 0x7;
        reg[r0] = reg[r1] + reg[r2];
    }

    update_flags(r0);
}

void op_and(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if (imm_flag)
    {
        uint16_t imm5 = sign_extend(instr & 0x1f, 5);
        reg[r0] = reg[r1] & imm5;
    }
    else
    {
        uint16_t r2 = instr & 0x7;
        reg[r0] = reg[r1] & reg[r2];
    }

    update_flags(r0);
}


void op_not(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;

    reg[r0] = ~reg[r1];
    
    update_flags(r0);
}

void op_br(uint16_t instr)
{
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    uint16_t cond_flag = (instr >> 9) & 0x7;
    if (cond_flag & reg[r_COND])
    {
        reg[r_PC] += pc_offset;
    }

}

void op_jmp(uint16_t instr)
{
    uint16_t r1 = (instr >> 6) & 0x7;
    reg[r_PC] = reg[r1];
}

void op_jsr(uint16_t instr)
{
    uint16_t long_flag = (instr >> 1) & 1;
    reg[r_R7] = reg[r_PC];
    if (long_flag)
    {
        uint16_t long_pc_offset = sign_extend(instr & 0x7FF, 11);
        reg[r_PC] += long_pc_offset; /* JSR */
    }
    else
    {
        uint16_t r1 = (instr >> 6) & 0x7;
        reg[r_PC] = reg[r1]; /* JSRR */
    }
}

void op_ld(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[r0] = mem_read(reg[r_PC] + pc_offset);

    update_flags(r0);
}

void op_ldr(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);
    reg[r0] = mem_read(reg[r1] + offset);
    
    update_flags(r0);

}

void op_lea(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[r0] = reg[r_PC] + pc_offset;

    update_flags(r0);

}

void op_st(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    mem_write(reg[r_PC] + pc_offset, reg[r0]);

}

void op_sti(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    mem_write(mem_read(reg[r_PC] + pc_offset), reg[r0]);

}

void op_str(uint16_t instr)
{
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);

    mem_write(reg[r1] + offset, reg[r0]);

}

#endif