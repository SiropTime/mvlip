#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "instructions.h"
#include "flags.h"

#include <stdio.h>
#include <stdlib.h>

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

void runCPU(CPU *cpu) {
    while(cpu->i_instruction != HLT) {
        fetch(cpu);
        execute(cpu);
    }
}

void fetch(CPU *cpu) {
    cpu->r_programCounter++;
    cpu->i_instruction = cpu->memory[cpu->r_programCounter] & FIRST_BYTE;
    cpu->i_destination = cpu->memory[cpu->r_programCounter+1];
    cpu->i_source = cpu->memory[cpu->r_programCounter+2];
}

void execute(CPU *cpu) {
    switch (cpu->i_instruction) {
        case CLF:
            clearFlags(cpu);
            break;
        case CMP:
            setFlags(cpu, cpu->r_registers[cpu->i_destination], cpu->r_registers[cpu->i_source]);
            cpu->r_programCounter += 2;
            break;
        case CMPI:
            setFlags(cpu, cpu->r_registers[cpu->i_destination], cpu->i_source);
            cpu->r_programCounter += 2;
            break;
        case CMPFI:
            fSetFlags(cpu, cpu->r_floatRegisters[cpu->i_destination - 8], (float64) cpu->r_floatRegisters[cpu->i_source - 8]);
            cpu->r_programCounter += 2;
            break;
    }
}


#endif // CPU_H
