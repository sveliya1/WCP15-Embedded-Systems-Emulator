// MacroCreation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "macros.h"
#include <iostream>

int main()
{
	int result;
	int a1 = 1;
	int a2 = 5;
	int a3 = 2;
	int carry = 0;
	ANDS(a1, a2);
	ADC(a1, a2, carry)
	ADD(a1, a2) 
	ADDS(a1, a2)
	AND(a1, a2)
	ANDS(a1, a2)
	BIC(a1, a2)
	BX 
	CDP 
	CMP(a1, a2)
	EOR(a1, a2)
	LDC
	LDM 
	LDR 
	MCR
	MLA
	MOV(a1, a2)
	MOVS(a1, a2)
	MRC 
	MRS 
	MUL(a1, a2)
	MVN(a1, a2)
	ORR(a1, a2)
	ORRS(a1, a2)
	RSB(a1, a2)
	RSC(a1, a2)
	SBC(a1, a2)
	STC
	PUSH 
	STR(a1, a2) 
	SUB(a1, a2)
	SUBS(a1, a2)
	SWI(a1, a2) 
	SWP
	TEQ(a1, a2)
	TST
	LSRS(a1, a2, a3)
	LSLS(a1, a2, a3)
	BNE
	BEQ 
	B
	BL
	std::cout << a1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
