/*

Main file
Copy of LC-3 architecture virtual machine

*/

/* Includes */
#include <stdio.h>
#include <signal.h>
#include <Windows.h>
#include <conio.h>  // _kbhit

#include "registers.h"
#include "flags.h"
#include "instructions.h"
#include "utility.h"

HANDLE hStdin = INVALID_HANDLE_VALUE;
DWORD fdwMode, fdwOldMode;

void disable_input_buffering()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &fdwOldMode); /* save old mode */
    fdwMode = fdwOldMode
            ^ ENABLE_ECHO_INPUT  /* no input echo */
            ^ ENABLE_LINE_INPUT; /* return when one or
                                    more characters are available */
    SetConsoleMode(hStdin, fdwMode); /* set new mode */
    FlushConsoleInputBuffer(hStdin); /* clear buffer */
}

void restore_input_buffering()
{
    SetConsoleMode(hStdin, fdwOldMode);
}

uint16_t check_key()
{
    return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}

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
            break;
        case op_NOT:
            break;
        case op_BR:
            break;
        case op_JMP:
            break;
        case op_JSR:
            break;
        case op_LD:
            break;
        case op_LDI:
            break;
        case op_LDR:
            break;
        case op_LEA:
            break;
        case op_ST:
            break;
        case op_STI:
            break;
        case op_STR:
            break;
        case op_TRAP:
            break;
        case op_RES:
            break;
        case op_RTI:
            break;
        default:
            /* Bad opcode */
            break;
        }
        
    }

    /* Shutdown */
    
}