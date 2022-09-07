#ifndef FLAGS_H
#define FLAGS_H

void clearFlags(CPU *cpu) {
    cpu->f_zero = 0;
    cpu->f_gtz = 0;
    cpu->f_ltz = 0;
    cpu->f_int = 0;

}

void setFlags(CPU *cpu, uint64 destination, uint64 source) {
    cpu->f_zero = (destination - source == 0);
    cpu->f_gtz = (destination - source > 0);
    cpu->f_ltz = (destination - source < 0);
}

void fSetFlags(CPU *cpu, float64 destination, float64 source) {
    cpu->f_zero = (destination - source == 0);
    cpu->f_gtz = (destination - source > 0);
    cpu->f_ltz = (destination - source < 0);
}
#endif // FLAGS_H
