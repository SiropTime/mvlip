#ifndef TYPES_H
#define TYPES_H

#define FIRST_BYTE 0x00000000000000FF
#define byte unsigned char
#define uint64 unsigned long long
#define int64 long long
#define float64 double

enum registers {
    R0, R1, R2, R3, R4, R5, R6, R7,
    F0, F1, F2, F3, F4, F5, F6, F7,
    NUM_REGISTERS
};

typedef struct {
    // Memory block
    uint64 *memory;
    uint64 maxMemory;

    // Registers block
    uint64 r_programCounter;
    uint64 r_stackPointer;
    int64 r_registers[8];
    float64 r_floatRegisters[8];

    // Instructions block
    uint64 i_instruction;
    uint64 i_destination;
    uint64 i_source;

    // Buses block
    uint64 busA;
    uint64 busB;

    // Flags block
    uint64 f_zero;
    uint64 f_ltz;
    uint64 f_gtz;
    uint64 f_int;

} CPU;

#endif // TYPES_H
