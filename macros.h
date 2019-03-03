#pragma once


#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...) N
#define __RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

// general definition for any function name
#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)

#define ADC(...)VFUNC(ADC,__VA_ARGS__)
#define ADC2(Rd, Rn) {\
Rd = Rd + Rn + C_flag;\
g_cycle_count += 1;\
}
#define	ADC3(Rd,Rn,Rm){\
Rd = Rn + Rm + C_flag;\
g_cycle_count += 1;\
}
#define ADCS(...)VFUNC(ADCS,__VA_ARGS__)
#define ADCS2(Rd,Rn){\
	result = Rd + Rn + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADCS3(Rd,Rn, Rm){\
	result = Rn + Rm + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADD(...)VFUNC(ADD,__VA_ARGS__)
#define ADD2(Rd, Rn) Rd = Rd + Rn; g_cycle_count += 1;
#define ADD3(Rd, Rn, Rm) Rd = Rn + Rm; g_cycle_count += 1;
#define ADDS(...)VFUNC(ADDS,__VA_ARGS__)
#define ADDS2(Rd, Rn){\
	result = Rd + Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1 << 32));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADDS3(Rd, Rn, Rm){\
	result = Rn + Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1 << 32));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define AND(...)VFUNC(AND,__VA_ARGS__)
#define AND2(Rd, Rn) Rd = Rd & Rn; g_cycle_count += 1;
#define AND3(Rd, Rn, Rm) Rd = Rn & Rm; g_cycle_count += 1;
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
#define LDR(...)VFUNC(LDR,__VA_ARGS__)
#define LDR2(reg,address){\
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
#define PUSH //todo
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
