#include <string>

namespace types {

    struct registers {
        unsigned char AX; // Accumulator
        unsigned char BX; // Base
        unsigned char CX; // Counter
        unsigned char DX; // Data
        unsigned char EX; // Random generator (Encounter)
    };

    unsigned char flags = $0000000; // ZF OF RF IF DF

    unsigned char randomAccessMemory[4096];

    struct commands {
        const unsigned char JMP = 1;
        const unsigned char MOV = 2;
        const unsigned char INC = 3;
        const unsigned char DEC = 4;
        const unsigned char CMP = 5;
        const unsigned char UPE = 6; // Update encounter
        const unsigned char INT = 7; // Interruption
    };
    
}
