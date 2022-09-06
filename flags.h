#ifndef FLAGS_H
#define FLAGS_H

void clearFlags(CPU *cpu) {
    cpu->f_zero = 0;
    cpu->f_gtz = 0;
    cpu->f_ltz = 0;
    cpu->f_int = 0;

}

void setFlags(CPU *cpu, uint64 destination) {
    cpu->f_zero = (dest == 0);
    cpu->f_gtz = (dest > 0);
    cpu->f_ltz = (dest < 0);
}

void fSetFlags(CPU *cpu, float64 destination) {
    cpu->f_zero = (dest == 0);
    cpu->f_gtz = (dest > 0);
    cpu->f_ltz = (dest < 0);
}
#endif // FLAGS_H
