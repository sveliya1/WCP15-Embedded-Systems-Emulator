#pragma once

#define ADC(a1, a2, carry) a1 = a1 + a2 + carry;
#define ADD(a1, a2) a1 = a1 + a2;
#define ADDS(a1, a2) a1 = a1 + a2; result = a1;
#define AND(a1, a2) a1 = a1 & a2;
#define ANDS(a1, a2) a1 = a1 & a2; result = a1;
#define BIC(a1, a2) a1 = a1 & ~a2;
#define BX //TODO
#define CDP //co-processor specific
#define CMP(a1, a2) result = a1 - a2;
#define EOR(a1, a2) a1 = a1 ^ a2;
#define LDC //coprocessor load
#define LDM //stack manipulation (pop)
#define LDR //load from memory
#define MCR //TODO
#define MLA //todo
#define MOV(a1, a2) a1 = a2;
#define MOVS(a1, a2) a1 = a2; result = a2;
#define MRC //todo
#define MRS //TODO
#define MUL(a1, a2) a1 = a1 * a2;
#define MVN(a1, a2) a1 = ~a2;
#define ORR(a1, a2) a1 = a1 | a2;
#define ORRS(a1, a2) a1 = a1 | a2; result = a1;
#define RSB(a1, a2) a1 = a2 - a1;
#define RSC(a1, a2) a1 = a2 - a1 - carry;
#define SBC(a1, a2) a1 = a1 - a2 - 1 + carry;
#define STC //todo
#define PUSH //todo
#define STR(a1, a2) //TODO
#define SUB(a1, a2) a1 = a1 - a2;
#define SUBS(a1, a2) a1 = a1 - a2; result = a1;
#define SWI(a1, a2) //TODO os call
#define SWP //todo
#define TEQ(a1, a2) //TODO
#define TST //TODO
#define LSRS(a1, a2, a3) a1 = (a2 >> a3);
#define LSLS(a1, a2, a3) a1 = (a2 << a3);
#define BNE //TODO
#define BEQ //TODO
#define B //TODO
#define BL //TODO