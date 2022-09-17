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
            op_add(instr);
            break;
        case op_AND:
            op_and(instr);
            break;
        case op_NOT:
            op_not(instr);

            break;
        case op_BR:
            op_not(instr);

            break;
        case op_JMP:
            op_jmp(instr);

            break;
        case op_JSR:
            op_jsr(instr);

            break;
        case op_LD:
            op_ld(instr);

            break;
        case op_LDI:
            break;
        case op_LDR:
            op_ldr(instr);

            break;
        case op_LEA:
            op_lea(instr);

            break;
        case op_ST:
            op_st(instr);

            break;
        case op_STI:
            op_sti(instr);

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