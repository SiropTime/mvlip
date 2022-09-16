#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <signal.h>

#include "memory.h"

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count -1)) & 1)
    {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

uint16_t swap16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}

int read_image(const char* image_path)
{
    FILE* file = fopen(image_path, "rb");
    if (!file)
    {
        return 0;
    }

    read_image_file(file);
    fclose(file);

    return 1;
}

void read_image_file(FILE* file)
{
    
    uint16_t origin; /* Telling where place programm in memory to */
    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    uint16_t max_read = MEMORY_MAX - origin;
    uint16_t* p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    while (read-- > 0)
    {
        *p = swap16(*p);
        ++p;
    }
}

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

void handle_interrupt(int signal)
{
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

#endif