#pragma once
#include "memorymap.h"
//Libary Macro Code
#define ADC_2(Rd, Rn) {\
Rd = Rd + Rn + C_flag;\
g_cycle_count += 1;\
}
#define	ADC_3(Rd,Rn,Rm){\
Rd = Rn + Rm + C_flag;\
g_cycle_count += 1;\
}
#define ADCS_2(Rd,Rn){\
	result = Rd + Rn + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADCS_3(Rd,Rn, Rm){\
	uint64_t result = Rn + Rm + C_flag;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADD_2(Rd, Rn) Rd = Rd + Rn; g_cycle_count += 1;
#define ADD_3(Rd, Rn, Rm) Rd = Rn + Rm; g_cycle_count += 1;
#define ADDS_2(Rd, Rn){\
	result = Rd + Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ADDS_3(Rd, Rn, Rm){\
	result = Rn + Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	C_flag = (result  & (1ULL << 32ULL));\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define AND_2(Rd, Rn) Rd = Rd & Rn; g_cycle_count += 1;
#define AND_3(Rd, Rn, Rm) Rd = Rn & Rm; g_cycle_count += 1;
#define ANDS_2(Rd, Rn){\
	result = Rd & Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ANDS_3(Rd, Rn, Rm){\
	result = Rn & Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = Rn & Rm;\
	g_cycle_count += 1;\
}
#define ASRS_2(Rd,Rn){\
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
#define ASRS_3(Rd,Rn,Rm){\
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
#define BIC_2(Rd, Rn) Rd = Rd & ~Rn; g_cycle_count += 1;
#define BIC_3(Rd, Rn, Rm) Rd = Rn & ~Rm; g_cycle_count += 1;
#define BICS_2(Rd, Rn){\
	result = Rd & ~Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}

#define BICS_3(Rd, Rn, Rm){\
	result = Rn & ~Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define BX_LR g_cycle_count += 3; return;
#define CMP_2(Rd, Rn){\
	result = Rd - Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(Rn > Rd);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	g_cycle_count += 1;\
}
#define CMN_2(Rd,Rn){\
	result = Rd - ~Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(Rn > Rd);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	g_cycle_count += 1;\
}
#define EOR_2(Rd, Rn) Rd = Rd ^ Rn; g_cycle_count += 1;
#define EOR_3(Rd,Rn,Rm) Rd = Rn ^ Rm; g_cycle_count += 1;
#define EORS_2(Rd, Rn){\
	result = Rd ^ Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result; \
	g_cycle_count += 1;\
}
#define EORS_3(Rd, Rn, Rm){\
	result = Rn ^ Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
}
#define io_write(address,value){\
switch (address)\
{\
case 0x400FF044:\
set_register(0x400FF040, value);\
break;\
case 0x400FF048:\
clear_register(0x400FF040, value);\
break;\
case 0x400FF04C:\
toggle_register(0x400FF040, value);\
break;\
case 0x400FF0C4:\
set_register(0x400FF0C0, value);\
break;\
case 0x400FF0C8:\
clear_register(0x400FF0C0, value);\
break;\
case 0x400FF0CC:\
toggle_register(0x400FF0C0, value);\
break;\
default:\
map->write_word(address, (uint32_t)value);\
break;\
}\
}
#define LDMIA(base_reg, reg_vector){\
if (reg_vector & (1 << 7)) {\
		LDR_2(R0, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 6)) {\
		LDR_2(R1, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 5)) {\
		LDR_2(R2, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 4)) {\
		LDR_2(R3, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 3)) {\
		LDR_2(R4, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 2)) {\
		LDR_2(R5, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 1)) {\
		LDR_2(R6, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 0)) {\
		LDR_2(R7, base_reg);\
		base_reg += 4;\
}\
}
#define LDR_2(reg,address){\
reg = map -> read(address, Size::WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LDRB_2(reg,address){\
reg = map -> read(address, Size::BYTE);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LDRH_2(reg,address){\
reg = map -> read(address, Size::HALF_WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LDR_3(reg,rg_addr, offset){\
reg = map -> read((uint32_t)(rg_addr+offset), Size::WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LDRB_3(reg,rg_addr,offset){\
reg = map -> read((unsigned)(rg_addr+offset), Size::BYTE);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LDRH_3(reg,address){\
reg = map -> read((rg_addr+offset), Size::HALF_WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define LSRS_2(Rd,Rn){\
	result = Rd >> Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSRS_3(Rd, Rn, Rm){\
	result = Rn >> Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSLS_2(Rd,Rn){\
	result = Rd << Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define LSLS_3(Rd, Rn, Rm){\
	result = Rn << Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = (result & (1 << 32));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define MOV_2(Rd, Rn) Rd = Rn; g_cycle_count += 1;
#define MOVS_2(Rd, Rn){\
	Rd = Rn;\
	N_flag = (Rd & (1 << 31));\
	Z_flag = (Rd == 0);\
	g_cycle_count += 1;\
}
#define MVNS_2(Rd, Rn){\
	Rd = ~Rn;\
	N_flag = (Rd & (1 << 31));\
	Z_flag = (Rd == 0);\
	g_cycle_count += 1;\
}
#define MULS_2(Rd, Rn){\
result = Rd * Rn;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
Rd = result;\
g_cycle_count += 1;\
}
#define MULS_3(Rd,Rn,Rm){\
result = Rn * Rm;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
Rd = result;\
g_cycle_count += 1;\
}
#define MVN_2(Rd, Rn) Rd = ~Rn; g_cycle_count += 1;
#define ORR_2(Rd, Rn) Rd = Rd |Rn; g_cycle_count += 1;
#define ORR_3(Rd,Rn,Rm) Rd = Rn | Rm; g_cycle_count += 1;
#define ORRS_2(Rd, Rn){\
	result = Rd | Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
}
#define ORRS_3(Rd,Rn,Rm){\
	result = Rn | Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define ORNS_2(Rd,Rn){\
	result = Rd | ~Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define ORNS_3(Rd,Rn,Rm){\
	result = Rn | ~Rm;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	Rd = result;\
	g_cycle_count += 1;\
}
#define PUSH(SP, reg_vector) {\
if (reg_vector & (1 << 8)) {\
		STR_2(R0, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 7)) {\
		STR_2(R1, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 6)) {\
		STR_2(R2, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 5)) {\
		STR_2(R3, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 4)) {\
		STR_2(R4, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 3)) {\
		STR_2(R5, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 2)) {\
		STR_2(R6, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 1)) {\
		STR_2(R7, SP); \
		SP -= 4; \
}\
if (reg_vector & (1 << 0)) {\
		STR_2(LR, SP); \
		SP -= 4; \
}\
}
#define POP(SP, reg_vector){\
if (reg_vector & (1 << 8)) {\
		LDR_2(R0, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 7)) {\
		LDR_2(R1, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 6)) {\
		LDR_2(R2, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 5)) {\
		LDR_2(R3, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 4)) {\
		LDR_2(R4, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 3)) {\
		LDR_2(R5, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 2)) {\
		LDR_2(R6, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 1)) {\
		LDR_2(R7, SP); \
		SP += 4; \
}\
if (reg_vector & (1 << 0)) {\
		LDR_2(PC, SP); \
		SP += 4; \
}\
}
#define RORS_2(Rd,Rn){\
	result = ((uint32_t)Rd >> (uint32_t)Rn) | ((uint32_t)Rd) << (32 - (uint32_t)Rn);\
	if (Rn)\
		C_flag = (result & (1 << Rn));\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define RORS_3(Rd,Rn,Rm){\
	result = ((uint32_t)Rn >> (uint32_t)Rm) | ((uint32_t)Rn) << (32 - (uint32_t)Rm);\
	if (Rm)\
		C_flag = (result & (1 << Rm));\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0); \
	Rd = result;\
	g_cycle_count += 1;\
};
#define RSB_2(Rd, Rn) Rd = Rn - Rd; g_cycle_count += 1;
#define RSB_3(Rd, Rn, Rm) Rd = Rm - Rn; g_cycle_count += 1;
#define RSBS_2(Rd,Rn) {\
result = Rn - Rd;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(Rd > Rn);\
V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define RSBS_3(Rd,Rn,Rm){\
result = Rm - Rn;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(Rn > Rm);\
V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
//#define RSC(Rd, Rn) Rd = Rn - Rd - carry; Not defined in Thumb mode
//#define RSC(Rd, Rn, Rm) Rd = Rm - Rn - carry;
#define SBC_2(Rd, Rn) Rd = Rd - Rn - 1 + carry; g_cycle_count += 1;
#define SBC_3(Rd, Rn,Rm) Rd = Rn - Rm - 1 + carry; g_cycle_count += 1;
#define SBCS_2(Rd,Rn){\
result = Rd - Rn - C_flag;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(Rn > Rd);\
V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define SBCS_3(Rd,Rn, Rm){\
result = Rn - Rm - C_flag;\
N_flag = (result & (1 << 31));\
Z_flag = (result == 0);\
C_flag = !(Rm > Rn);\
V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
Rd = result;\
g_cycle_count += 1;\
}
#define SXTB_2(Rd,Rm){\
	lsb_byte = (0xFF & Rm);\
	if (lsb_byte & (1 << 7))\
		Rd = (0xFFFFFF00 | lsb_byte;\
	else\
		Rd = lsb_byte;\
	g_cycle_count += 1;\
}
#define SXTH_2(Rd,Rm){\
	lsb_word = (0xFFFF & Rm);\
	if (lsb_word & (1 << 15))\
		Rd = (0xFFFF0000 | lsb_word;\
	else\
		Rd = lsb_word;\
	g_cycle_count += 1;\
}
#define STR_2(value, address){\
 io_write(address,value);\
if (g_cycle_count > supervisor_threshold)\
 supervisor();\
g_cycle_count += 2;\
}
#define STRB_2(value, address){\
 map -> write(address, (unsigned) value, Size::BYTE);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define STRH_2(value, address){\
 map -> write(address, (unsigned) value, Size::HALF_WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define STR_3(value, reg, offset){\
 io_write((reg+offset),value);\
if (g_cycle_count > supervisor_threshold)\
 supervisor();\
g_cycle_count += 2;\
}
#define STRB_3(value, reg, offset){\
 map -> write((unsigned)(reg+offset), value, Size::BYTE);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define STRH_3(value, reg, offset){\
 map -> write((unsigned)(reg+offset), value, Size::HALF_WORD);\
if (g_cycle_count > supervisor_threshold)\
supervisor();\
g_cycle_count += 2;\
}
#define STMIA(base_reg, reg_vector) {\
if (reg_vector & (1 << 7)) {\
		STR_2(R0, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 6)) {\
		STR_2(R1, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 5)) {\
		STR_2(R2, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 4)) {\
		STR_2(R3, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 3)) {\
		STR_2(R4, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 2)) {\
		STR_2(R5, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 1)) {\
		STR_2(R6, base_reg);\
		base_reg += 4;\
}\
if (reg_vector & (1 << 0)) {\
		STR_2(R7, base_reg);\
		base_reg += 4;\
}\
}
#define SUB_2(Rd,Rn) Rd = Rd - Rn; g_cycle_count += 1;
#define SUB_3(Rd,Rn,Rm) Rd = Rn - Rm; g_cycle_count += 1;
#define SUBS_2(Rd, Rn){\
	result = Rd - Rn;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(Rn > Rd);\
	V_flag = ((result & (1 << 31)) != ((Rd & (1 << 31)) ^ (Rn & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define SUBS_3(Rd, Rn, Rm){\
	result = Rn - Rm;\
	N_flag = (result & (1 & 31));\
	Z_flag = (result == 0);\
	C_flag = !(Rm > Rn);\
	V_flag = ((result & (1 << 31)) != ((Rn & (1 << 31)) ^ (Rm & (1 << 31))));\
	Rd = result;\
	g_cycle_count += 1;\
}
#define TST_2(Rd,Rn){\
	result = Rd & Rn;\
	N_flag = (result & (1 << 31));\
	Z_flag = (result == 0);\
	g_cycle_count += 1;\
}
#define UXTB_2(Rd,Rm){\
	Rd = (0xFF & Rm);\
	g_cycle_count += 1;\
}
#define UXTH_2(Rd,Rm){\
	Rd = (0xFFFF & Rm);\
	g_cycle_count += 1;\
}
#define MRS( Rn, Co){\
	Rn=Co;\
	g_cycle_count+=1;\
}
#define MSR(Co, Rn){\
	Co=Rn;\
	g_cycle_count+=1;\
}
