/*

    Main file
    Copy of LC-3 architecture virtual machine

    No copyright, just fun :)

*/

/* Includes */
#include <stdio.h>
#include <signal.h>

  // _kbhit

#include "registers.h"
#include "flags.h"
#include "instructions.h"
#include "utility.h"
#include "traps.h"



int main(int argc, const char* argv[])
{
    /* Load arguments */
    if (argc < 2)
    {
        printf("mvlip [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j)
    {
        if (!read_image(argv[j]))
        {
            printf("Failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    /* Setup */
    reg[r_COND] = FL_ZRO;
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    /* Setting program counter to default starting position */
    enum
    {
        PC_START = 0x3000
    };
    reg[r_PC] = PC_START;

    int running = 1;

    while (running)
    {
        /* Fetch */
        uint16_t instr = mem_read(reg[r_PC]++);
        uint16_t op = instr >> 12;

        /* Checking and doing instruction */
        switch (op)
        {
        case op_ADD:
            /* Destination */
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
            break;
        case op_AND:
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
            break;
        case op_NOT:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;

            reg[r0] = ~reg[r1];
            
            update_flags(r0);
            break;
        case op_BR:
            uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
            uint16_t cond_flag = (instr >> 9) & 0x7;
            if (cond_flag & reg[r_COND])
            {
                reg[r_PC] += pc_offset;
            }

            break;
        case op_JMP:
            uint16_t r1 = (instr >> 6) & 0x7;
            reg[r_PC] = reg[r1];

            break;
        case op_JSR:
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

            break;
        case op_LD:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
            reg[r0] = mem_read(reg[r_PC] + pc_offset);

            update_flags(r0);

            break;
        case op_LDI:
            break;
        case op_LDR:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            uint16_t offset = sign_extend(instr & 0x3F, 6);
            reg[r0] = mem_read(reg[r1] + offset);
            
            update_flags(r0);

            break;
        case op_LEA:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
            reg[r0] = reg[r_PC] + pc_offset;

            update_flags(r0);

            break;
        case op_ST:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
            mem_write(reg[r_PC] + pc_offset, reg[r0]);

            break;
        case op_STI:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
            mem_write(mem_read(reg[r_PC] + pc_offset), reg[r0]);

            break;
        case op_STR:
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            uint16_t offset = sign_extend(instr & 0x3F, 6);

            mem_write(reg[r1] + offset, reg[r0]);

            break;
        case op_TRAP:

            process_traps(instr, &running);
            break;
        case op_RES:
            abort();
        case op_RTI:
            abort();
        default:
            abort();
            break;
        }
        
    }

    /* Shutdown */
    restore_input_buffering();
}