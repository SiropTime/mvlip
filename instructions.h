#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

enum instructions {
	CLF, CMP, CMPI, CMPF, CMPFI,
	MOV, MOVF,
	STI, STF, LDI, LDF,
	LII, LIF,
	PUSH, POP,
	PUSHF, POPF,
	ADD, SUB, MUL, DIV,
	FADD, FSUB, FMUL, FDIV,
	JLZ, JGZ, JEZ, JNZ, JMP,
	SHL, SHR,
	BAND, BOR, BNOT, BXOR,
	LAND, LOR, LNOT,
	HLT,
	NUM_INSTRUCTIONS
};

#endif // INSTRUCTIONS_H