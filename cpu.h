#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "instructions.h"
#include "flags.h"

void execute(CPU *cpu);
void fetch(CPU *cpu);

void *getLocation(CPU *cpu, uint64 num) {
    if (num < 8) return &cpu->r_registers[num];
    if (num >= 8) return &cpu->r_floatRegisters[num - 8];
}

CPU *newCPU(uint64 *memory, uint64 memorySize) {

    CPU *cpu = malloc(sizeof(CPU));
    cpu->memory = memory;
    cpu->r_stackPointer = memorySize - 1;
    cpu->maxMemory = memorySize;
    cpu->r_programCounter = -1;
    cpu->i_instruction = 0;

    return cpu;
}

void freeCPU(CPU *cpu) {
    free(cpu);
}

#endif // CPU_H
