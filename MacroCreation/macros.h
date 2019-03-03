#pragma once

#define ADC(Rd, Rn) {\
Rd = Rd + Rn + C_flag;\
g_cycle_count += 1;\
}
#define	ADC(Rd,Rn,Rm){\
Rd = Rn + Rm + C_flag;\
g_cycle_count += 1;\
}
#define ADCS(Rd,Rn){\
	result = Rd + Rn + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADCS(Rd,Rn, Rm){\
	result = Rn + Rm + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADD(Rd, Rn) Rd = Rd + Rn; g_cycle_count += 1;
#define ADD(Rd, Rn, Rm) Rd = Rn + Rm; g_cycle_count += 1;
#define ADDS(Rd, Rn){\
	result = Rd + Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1 << 32));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADDS(Rd, Rn, Rm){\
	result = Rn + Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1 << 32));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define AND(Rd, Rn) Rd = Rd & Rn; g_cycle_count += 1;
#define AND(Rd, Rn, Rm) Rd = Rn & Rm; g_cycle_count += 1;
#define ANDS(Rd, Rn){\
	result = Rd & Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ANDS(Rd, Rn, Rm){\
	result = Rn & Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = Rn & Rm;\
	g_cycle_count += 1;\
}
#define ASRS(Rd,Rn){\
if ((int32_t)Rd < 0 && (int32_t)Rn > 0)\
	result = (int32_t)Rd >> (int32_t)Rn | ~(~0U >> (int32_t)Rn);\
else\
	result = (int32_t)Rd >> (int32_t)Rn;\
if (Rn)\
	C_flag = (result & (1 << Rn));\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
Rd = result;\
g_cycle_count += 1;\
}
#define ASRS(Rd,Rn,Rm){\
if ((int32_t)Rn < 0 && (int32_t)Rm > 0)\
	result = (int32_t)Rn >> (int32_t)Rm | ~(~0U >> (int32_t)Rm); \
else\
	result = (int32_t)Rn >> (int32_t)Rm; \
if (Rm)\
	C_flag = (result & (1 << Rm)); \
N_flag = (result & (1 << 31)); \
Z_flag = (result == 0); \
Rd = result;\
g_cycle_count += 1;\
}
#define BIC(Rd, Rn) Rd = Rd & ~Rn; g_cycle_count += 1;
#define BIC(Rd, Rn, Rm) Rd = Rn & ~Rm; g_cycle_count += 1;
#define BICS(Rd, Rn){\
	result = Rd & ~Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}

#define BICS(Rd, Rn, Rm){\
	result = Rn & ~Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define BX_LR g_cycle_count += 3; return;
#define CMP(Rd, Rn){\
	result = Rd - Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(operand2 > operand1);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	g_cycle_count += 1;\
}
#define CMN(Rd,Rn){\
	result = Rd - ~Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(operand2 > operand1);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	g_cycle_count += 1;\
}
#define EOR(Rd, Rn) Rd = Rd ^ Rn; g_cycle_count += 1;
#define EOR(Rd,Rn,Rm) Rd = Rn ^ Rm; g_cycle_count += 1;
#define EORS(Rd, Rn){\
	result = Rd ^ Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result; \
	g_cycle_count += 1;\
}
#define EORS(Rd, Rn, Rm){\
	result = Rn ^ Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
}
#define LDR(reg,address){\
reg = map -> read(address, WORD);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define LDRB(reg,address){\
reg = map -> read(address, BYTE);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define LDRH(reg,address){\
reg = map -> read(address, HALF_WORD);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define LSRS(Rd,Rn){\
	result = Rd >> Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSRS(Rd, Rn, Rm){\
	result = Rn >> Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSLS(Rd,Rn){\
	result = Rd << Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSLS(Rd, Rn, Rm){\
	result = Rn << Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define MOV(Rd, Rn) Rd = Rn; g_cycle_count += 1;
#define MOVS(Rd, Rn){\
	Rd = Rn;\
	N_flag = (Rd & (1 << 31));\
	Z_flag = (Rd == 0);\
	g_cycle_count += 1;\
}
#define MVNS(Rd, Rn){\
	Rd = ~Rn;\
	N_flag = (Rd & (1 << 31));\
	Z_flag = (Rd == 0);\
	g_cycle_count += 1;\
}
#define MULS(Rd, Rn){\
result = Rd * Rn;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
Rd = result;\
g_cycle_count += 1;\
}
#define MULS(Rd,Rn,Rm){\
result = Rn * Rm;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
Rd = result;\
g_cycle_count += 1;\
}
#define MVN(Rd, Rn) Rd = ~Rn; g_cycle_count += 1;
#define ORR(Rd, Rn) Rd = Rd | Rn; g_cycle_count += 1;
#define ORR(Rd,Rn,Rm) Rd = Rn | Rm; g_cycle_count += 1;
#define ORRS(Rd, Rn){\
	result = Rd | Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
}
#define ORRS(Rd,Rn,Rm){\
	result = Rn | Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define ORNS(Rd,Rn){\
	result = Rd | ~Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ORNS(Rd,Rn,Rm){\
	result = Rn | ~Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define PUSH //TODO
#define RORS(Rd,Rn){\
	result = ((uint32_t)Rd >> (uint32_t)Rn) | ((uint32_t)Rd) << (32 - (uint32_t)Rn);\
	if (Rn)\
		C_flag = (result & (1 << Rn));\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define RORS(Rd,Rn,Rm){\
	result = ((uint32_t)Rn >> (uint32_t)Rm) | ((uint32_t)Rn) << (32 - (uint32_t)Rm);\
	if (Rm)\
		C_flag = (result & (1 << Rm));\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define RSB(Rd, Rn) Rd = Rn - Rd; g_cycle_count += 1;
#define RSB(Rd, Rn, Rm) Rd = Rm - Rn; g_cycle_count += 1;
#define RSBS(Rd,Rn) {\
result = Rn - Rd;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(operand2 > operand1);\
V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define RSBS(Rd,Rn,Rm){\
result = Rm - Rn;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(operand2 > operand1);\
V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
//#define RSC(Rd, Rn) Rd = Rn - Rd - carry; Not defined in Thumb mode
//#define RSC(Rd, Rn, Rm) Rd = Rm - Rn - carry;
#define SBC(Rd, Rn) Rd = Rd - Rn - 1 + carry; g_cycle_count += 1;
#define SBC(Rd, Rn,Rm) Rd = Rn - Rm - 1 + carry; g_cycle_count += 1;
#define SBCS(Rd,Rn){\
result = Rd - Rn - C_flag;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(operand2 > operand1);\
V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define SBCS(Rd,Rn, Rm){\
result = Rn - Rm - C_flag;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(operand2 > operand1);\
V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define SXTB(Rd,Rm){\
	lsb_byte = (0xFF & Rm);\
	if (lsb_byte & (1 << 7))\
		Rd = (0xFFFFFF00 | lsb_byte;\
	else\
		Rd = lsb_byte;\
	g_cycle_count += 1;\
}
#define SXTH(Rd,Rm){\
	lsb_word = (0xFFFF & Rm);\
	if (lsb_word & (1 << 15))\
		Rd = (0xFFFF0000 | lsb_word;\
	else\
		Rd = lsb_word;\
	g_cycle_count += 1;\
}
#define STR(value, address){\
 map -> write(value, (unsigned) address, WORD);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define STRB(value, address){\
 map -> write(value, (unsigned) address, BYTE);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define STRH(value, address){\
 map -> write(value, (unsigned) address, HALF_WORD);\
supervisor();\
get_io_mutex();\
g_cycle_count += 2;\
}
#define SUB(Rd,Rn) Rd = Rd - Rn; g_cycle_count += 1;
#define SUB(Rd,Rn,Rm) Rd = Rn - Rm; g_cycle_count += 1;
#define SUBS(Rd, Rn){\
	result = Rd - Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(operand2 > operand1);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define SUBS(Rd, Rn, Rm){\
	result = Rn - Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(operand2 > operand1);\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define TST(Rd,Rn){\
	result = operand1 & operand2;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	g_cycle_count += 1;\
}
#define UXTB(Rd,Rm){\
	Rd = (0xFF & Rm);\
	g_cycle_count += 1;\
}
#define UXTH(Rd,Rm){\
	Rd = (0xFFFF & Rm);\
	g_cycle_count += 1;\
}
