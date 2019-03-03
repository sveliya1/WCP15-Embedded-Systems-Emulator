#include <stdint.h>
#include "macros.h"
#include <stdio.h>
#include <iostream>
//#include "memorymap.h"
#ifdef _WIN32
#include <windows.h>
#endif
#define DEBUG 1
using namespace std;
uint8_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, pc, lr, sp;
bool n_flag, z_flag, c_flag, v_flag =  false;
int result = 0;
void InterruptVector();
void Default_Handler();
void HardFault_Handler();
void _stop_init();
void _reset_init();
void __startup_end();
void _cfm();
void delay();
void main();
void configure_rgbled();
void turn_on_green_led();
void turn_off_green_led();
void toggle_green_led();
void turn_on_red_led();
void turn_off_red_led();
void toggle_red_led();
void turn_on_blue_led();
void turn_off_blue_led();
void toggle_blue_led();
void set_rgbled_color_to();
int Memory[2048];
void filler()
{
label_timing_demoout:  ;
//Could not parse: timing_demoout:     file format elf32-littlearm ;
//Could not parse: Disassembly of section text: ;
}
void InterruptVector() 
{label_0:  ;
//Could not parse:    0:	00 30 00 20 21 01 00 00 c1 00 00 00 c3 00 00 00     0 ! ;
label_10:  ;
//Could not parse:   10:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_20:  ;
//Could not parse:   20:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_30:  ;
//Could not parse:   30:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_40:  ;
//Could not parse:   40:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_50:  ;
//Could not parse:   50:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_60:  ;
//Could not parse:   60:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_70:  ;
//Could not parse:   70:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_80:  ;
//Could not parse:   80:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_90:  ;
//Could not parse:   90:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_a0:  ;
//Could not parse:   a0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
label_b0:  ;
//Could not parse:   b0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00      ;
}
void Default_Handler() 
{label_c0:  ;
 goto(label_c0);//  c0:	e7fe      	bn	c0 <Default_Handler> ;
}
void HardFault_Handler() 
{label_c2:  ;
 goto(label_c2);//  c2:	e7fe      	bn	c2 <HardFault_Handler> ;
}
void _stop_init() 
{label_c4:  ;
MOVS(r1, 128);//  c4:	2180      	movs	r1, #128	 ; 0x80 ;
label_c6:  ;
LDR(r2, pc, 64);//  c6:	4a10      	ldr	r2, pc, #64	 ; (108 <_stop_init+0x44>) ;
label_c8:  ;
LDR(r3, pc, 64);//  c8:	4b10      	ldr	r3, pc, #64	 ; (10c <_stop_init+0x48>) ;
label_ca:  ;
LSLS(r1, r1, 6);//  ca:	0189      	lsls	r1, r1, #6 ;
label_cc:  ;
LDR(r0, r2, r3);//  cc:	58d0      	ldr	r0, r2, r3 ;
label_ce:  ;
PUSH(r4, r5, lr);//  ce:	b530      	push	r4, r5, lr ;
label_d0:  ;
ORRS(r1, r0);//  d0:	4301      	orrs	r1, r0 ;
label_d2:  ;
STR(r1, r2, r3);//  d2:	50d1      	str	r1, r2, r3 ;
label_d4:  ;
LDR(r1, pc, 56);//  d4:	490e      	ldr	r1, pc, #56	 ; (110 <_stop_init+0x4c>) ;
label_d6:  ;
LDR(r4, pc, 60);//  d6:	4c0f      	ldr	r4, pc, #60	 ; (114 <_stop_init+0x50>) ;
label_d8:  ;
LDR(r0, r1, 4);//  d8:	6848      	ldr	r0, r1, #4 ;
label_da:  ;
ANDS(r0, r4);//  da:	4020      	ands	r0, r4 ;
label_dc:  ;
STR(r0, r1, 4);//  dc:	6048      	str	r0, r1, #4 ;
label_de:  ;
MOVS(r0, 128);//  de:	2080      	movs	r0, #128	 ; 0x80 ;
label_e0:  ;
LDR(r4, r1, 4);//  e0:	684c      	ldr	r4, r1, #4 ;
label_e2:  ;
LSLS(r0, r0, 1);//  e2:	0040      	lsls	r0, r0, #1 ;
label_e4:  ;
ORRS(r0, r4);//  e4:	4320      	orrs	r0, r4 ;
label_e6:  ;
STR(r0, r1, 4);//  e6:	6048      	str	r0, r1, #4 ;
label_e8:  ;
MOVS(r0, 2);//  e8:	2002      	movs	r0, #2 ;
label_ea:  ;
LDR(r4, pc, 44);//  ea:	4c0b      	ldr	r4, pc, #44	 ; (118 <_stop_init+0x54>) ;
label_ec:  ;
LDR(r5, r4, 20);//  ec:	6965      	ldr	r5, r4, #20 ;
label_ee:  ;
//Could not parse:   ee:	4385      	bics	r5, r0 ;
label_f0:  ;
STR(r5, r4, 20);//  f0:	6165      	str	r5, r4, #20 ;
label_f2:  ;
LDR(r5, r1, 4);//  f2:	684d      	ldr	r5, r1, #4 ;
label_f4:  ;
ORRS(r5, r0);//  f4:	4305      	orrs	r5, r0 ;
label_f6:  ;
STR(r5, r1, 4);//  f6:	604d      	str	r5, r1, #4 ;
label_f8:  ;
LDR(r1, r4, 16);//  f8:	6921      	ldr	r1, r4, #16 ;
label_fa:  ;
TST(r1, r0);//  fa:	4201      	tst	r1, r0 ;
label_fc:  ;
//Could not parse:   fc:	d0fc      	beqn	f8 <_stop_init+0x34> ;
label_fe:  ;
LDR(r1, r2, r3);//  fe:	58d1      	ldr	r1, r2, r3 ;
label_100:  ;
LDR(r0, pc, 24);// 100:	4806      	ldr	r0, pc, #24	 ; (11c <_stop_init+0x58>) ;
label_102:  ;
ANDS(r1, r0);// 102:	4001      	ands	r1, r0 ;
label_104:  ;
STR(r1, r2, r3);// 104:	50d1      	str	r1, r2, r3 ;
label_106:  ;
//Could not parse:  106:	bd30      	pop	r4, r5, pc ;
label_108:  ;
//Could not parse:  108:	40047000 	word	0x40047000 ;
label_10c:  ;
//Could not parse:  10c:	00001038 	word	0x00001038 ;
label_110:  ;
//Could not parse:  110:	4004d000 	word	0x4004d000 ;
label_114:  ;
//Could not parse:  114:	fffff8ff 	word	0xfffff8ff ;
label_118:  ;
//Could not parse:  118:	400ff100 	word	0x400ff100 ;
label_11c:  ;
//Could not parse:  11c:	ffffdfff 	word	0xffffdfff ;
}
void _reset_init() 
{label_120:  ;
_stop_init();// 120:	f7ff ffd0 	bl	c4 <_stop_init> ;
label_124:  ;
MOVS(r2, 136);// 124:	2288      	movs	r2, #136	 ; 0x88 ;
label_126:  ;
MOVS(r1, 1);// 126:	2101      	movs	r1, #1 ;
label_128:  ;
LDR(r3, pc, 184);// 128:	4b2e      	ldr	r3, pc, #184	 ; (1e4 <_reset_init+0xc4>) ;
label_12a:  ;
LSLS(r2, r2, 5);// 12a:	0152      	lsls	r2, r2, #5 ;
label_12c:  ;
STR(r1, r3, r2);// 12c:	5099      	str	r1, r3, r2 ;
label_12e:  ;
LDR(r0, pc, 184);// 12e:	482e      	ldr	r0, pc, #184	 ; (1e8 <_reset_init+0xc8>) ;
label_130:  ;
LDR(r2, pc, 184);// 130:	4a2e      	ldr	r2, pc, #184	 ; (1ec <_reset_init+0xcc>) ;
label_132:  ;
STR(r0, r2, 8);// 132:	6090      	str	r0, r2, #8 ;
label_134:  ;
MOVS(r2, 128);// 134:	2280      	movs	r2, #128	 ; 0x80 ;
label_136:  ;
LDR(r0, pc, 184);// 136:	482e      	ldr	r0, pc, #184	 ; (1f0 <_reset_init+0xd0>) ;
label_138:  ;
LSLS(r2, r2, 2);// 138:	0092      	lsls	r2, r2, #2 ;
label_13a:  ;
LDR(r4, r3, r0);// 13a:	581c      	ldr	r4, r3, r0 ;
label_13c:  ;
ORRS(r2, r4);// 13c:	4322      	orrs	r2, r4 ;
label_13e:  ;
STR(r2, r3, r0);// 13e:	501a      	str	r2, r3, r0 ;
label_140:  ;
LDR(r0, pc, 176);// 140:	482c      	ldr	r0, pc, #176	 ; (1f4 <_reset_init+0xd4>) ;
label_142:  ;
LDR(r2, pc, 180);// 142:	4a2d      	ldr	r2, pc, #180	 ; (1f8 <_reset_init+0xd8>) ;
label_144:  ;
STR(r0, r3, r2);// 144:	5098      	str	r0, r3, r2 ;
label_146:  ;
LDR(r2, r3, 0);// 146:	681a      	ldr	r2, r3, #0 ;
label_148:  ;
LDR(r0, pc, 176);// 148:	482c      	ldr	r0, pc, #176	 ; (1fc <_reset_init+0xdc>) ;
label_14a:  ;
ANDS(r2, r0);// 14a:	4002      	ands	r2, r0 ;
label_14c:  ;
MOVS(r0, 128);// 14c:	2080      	movs	r0, #128	 ; 0x80 ;
label_14e:  ;
STR(r2, r3, 0);// 14e:	601a      	str	r2, r3, #0 ;
label_150:  ;
LDR(r2, pc, 172);// 150:	4a2b      	ldr	r2, pc, #172	 ; (200 <_reset_init+0xe0>) ;
label_152:  ;
LSLS(r0, r0, 9);// 152:	0240      	lsls	r0, r0, #9 ;
label_154:  ;
LDR(r4, r3, r2);// 154:	589c      	ldr	r4, r3, r2 ;
label_156:  ;
ORRS(r0, r4);// 156:	4320      	orrs	r0, r4 ;
label_158:  ;
STR(r0, r3, r2);// 158:	5098      	str	r0, r3, r2 ;
label_15a:  ;
LDR(r0, r3, r2);// 15a:	5898      	ldr	r0, r3, r2 ;
label_15c:  ;
LDR(r4, pc, 164);// 15c:	4c29      	ldr	r4, pc, #164	 ; (204 <_reset_init+0xe4>) ;
label_15e:  ;
ANDS(r4, r0);// 15e:	4004      	ands	r4, r0 ;
label_160:  ;
MOVS(r0, 128);// 160:	2080      	movs	r0, #128	 ; 0x80 ;
label_162:  ;
LSLS(r0, r0, 17);// 162:	0440      	lsls	r0, r0, #17 ;
label_164:  ;
ORRS(r0, r4);// 164:	4320      	orrs	r0, r4 ;
label_166:  ;
STR(r0, r3, r2);// 166:	5098      	str	r0, r3, r2 ;
label_168:  ;
LDR(r3, pc, 156);// 168:	4b27      	ldr	r3, pc, #156	 ; (208 <_reset_init+0xe8>) ;
label_16a:  ;
LDR(r4, pc, 160);// 16a:	4c28      	ldr	r4, pc, #160	 ; (20c <_reset_init+0xec>) ;
label_16c:  ;
LDR(r0, r3, 72);// 16c:	6c98      	ldr	r0, r3, #72	 ; 0x48 ;
label_16e:  ;
ANDS(r0, r4);// 16e:	4020      	ands	r0, r4 ;
label_170:  ;
STR(r0, r3, 72);// 170:	6498      	str	r0, r3, #72	 ; 0x48 ;
label_172:  ;
LDR(r2, r3, 76);// 172:	6cda      	ldr	r2, r3, #76	 ; 0x4c ;
label_174:  ;
MOVS(r0, 0);// 174:	2000      	movs	r0, #0 ;
label_176:  ;
ANDS(r2, r4);// 176:	4022      	ands	r2, r4 ;
label_178:  ;
STR(r2, r3, 76);// 178:	64da      	str	r2, r3, #76	 ; 0x4c ;
label_17a:  ;
MOVS(r2, 36);// 17a:	2224      	movs	r2, #36	 ; 0x24 ;
label_17c:  ;
MOVS(r4, 31);// 17c:	241f      	movs	r4, #31 ;
label_17e:  ;
LDR(r3, pc, 144);// 17e:	4b24      	ldr	r3, pc, #144	 ; (210 <_reset_init+0xf0>) ;
label_180:  ;
//Could not parse:  180:	7018      	strb	r0, r3, #0 ;
label_182:  ;
LDR(r3, pc, 144);// 182:	4b24      	ldr	r3, pc, #144	 ; (214 <_reset_init+0xf4>) ;
label_184:  ;
//Could not parse:  184:	705a      	strb	r2, r3, #1 ;
label_186:  ;
ADDS(r2, 116);// 186:	3274      	adds	r2, #116	 ; 0x74 ;
label_188:  ;
//Could not parse:  188:	701a      	strb	r2, r3, #0 ;
label_18a:  ;
//Could not parse:  18a:	78da      	ldrb	r2, r3, #3 ;
label_18c:  ;
ANDS(r2, r4);// 18c:	4022      	ands	r2, r4 ;
label_18e:  ;
//Could not parse:  18e:	70da      	strb	r2, r3, #3 ;
label_190:  ;
MOVS(r2, 16);// 190:	2210      	movs	r2, #16 ;
label_192:  ;
//Could not parse:  192:	7119      	strb	r1, r3, #4 ;
label_194:  ;
//Could not parse:  194:	7158      	strb	r0, r3, #5 ;
label_196:  ;
//Could not parse:  196:	7999      	ldrb	r1, r3, #6 ;
label_198:  ;
TST(r1, r2);// 198:	4211      	tst	r1, r2 ;
label_19a:  ;
//Could not parse:  19a:	d1fc      	bnen	196 <_reset_init+0x76> ;
label_19c:  ;
MOVS(r1, 12);// 19c:	210c      	movs	r1, #12 ;
label_19e:  ;
//Could not parse:  19e:	799a      	ldrb	r2, r3, #6 ;
label_1a0:  ;
ANDS(r2, r1);// 1a0:	400a      	ands	r2, r1 ;
label_1a2:  ;
CMP(r2, 8);// 1a2:	2a08      	cmp	r2, #8 ;
label_1a4:  ;
//Could not parse:  1a4:	d1fb      	bnen	19e <_reset_init+0x7e> ;
label_1a6:  ;
ADDS(r2, 56);// 1a6:	3238      	adds	r2, #56	 ; 0x38 ;
label_1a8:  ;
//Could not parse:  1a8:	715a      	strb	r2, r3, #5 ;
label_1aa:  ;
//Could not parse:  1aa:	7999      	ldrb	r1, r3, #6 ;
label_1ac:  ;
TST(r1, r2);// 1ac:	4211      	tst	r1, r2 ;
label_1ae:  ;
//Could not parse:  1ae:	d0fc      	beqn	1aa <_reset_init+0x8a> ;
label_1b0:  ;
MOVS(r2, 24);// 1b0:	2218      	movs	r2, #24 ;
label_1b2:  ;
MOVS(r1, 12);// 1b2:	210c      	movs	r1, #12 ;
label_1b4:  ;
//Could not parse:  1b4:	701a      	strb	r2, r3, #0 ;
label_1b6:  ;
//Could not parse:  1b6:	799a      	ldrb	r2, r3, #6 ;
label_1b8:  ;
ANDS(r2, r1);// 1b8:	400a      	ands	r2, r1 ;
label_1ba:  ;
CMP(r2, 12);// 1ba:	2a0c      	cmp	r2, #12 ;
label_1bc:  ;
//Could not parse:  1bc:	d1fb      	bnen	1b6 <_reset_init+0x96> ;
label_1be:  ;
MOVS(r2, 0);// 1be:	2200      	movs	r2, #0 ;
label_1c0:  ;
LDR(r0, pc, 84);// 1c0:	4815      	ldr	r0, pc, #84	 ; (218 <_reset_init+0xf8>) ;
label_1c2:  ;
LDR(r1, pc, 88);// 1c2:	4916      	ldr	r1, pc, #88	 ; (21c <_reset_init+0xfc>) ;
label_1c4:  ;
LDR(r4, pc, 88);// 1c4:	4c16      	ldr	r4, pc, #88	 ; (220 <_reset_init+0x100>) ;
label_1c6:  ;
ADDS(r3, r2, r0);// 1c6:	1813      	adds	r3, r2, r0 ;
label_1c8:  ;
CMP(r3, r1);// 1c8:	428b      	cmp	r3, r1 ;
label_1ca:  ;
//Could not parse:  1ca:	d305      	bccn	1d8 <_reset_init+0xb8> ;
label_1cc:  ;
MOVS(r1, 0);// 1cc:	2100      	movs	r1, #0 ;
label_1ce:  ;
LDR(r2, pc, 84);// 1ce:	4a15      	ldr	r2, pc, #84	 ; (224 <_reset_init+0x104>) ;
label_1d0:  ;
CMP(r3, r2);// 1d0:	4293      	cmp	r3, r2 ;
label_1d2:  ;
//Could not parse:  1d2:	d905      	blsn	1e0 <_reset_init+0xc0> ;
label_1d4:  ;
main();// 1d4:	f000 f92a 	bl	42c <main> ;
label_1d8:  ;
LDR(r5, r4, r2);// 1d8:	58a5      	ldr	r5, r4, r2 ;
label_1da:  ;
ADDS(r2, 4);// 1da:	3204      	adds	r2, #4 ;
label_1dc:  ;
STR(r5, r3, 0);// 1dc:	601d      	str	r5, r3, #0 ;
label_1de:  ;
 goto(label_1c6);// 1de:	e7f2      	bn	1c6 <_reset_init+0xa6> ;
label_1e0:  ;
//Could not parse:  1e0:	c302      	stmia	r3!, r1 ;
label_1e2:  ;
 goto(label_1d0);// 1e2:	e7f5      	bn	1d0 <_reset_init+0xb0> ;
label_1e4:  ;
//Could not parse:  1e4:	40047000 	word	0x40047000 ;
label_1e8:  ;
//Could not parse:  1e8:	00000000 	word	0x00000000 ;
label_1ec:  ;
//Could not parse:  1ec:	e000ed00 	word	0xe000ed00 ;
label_1f0:  ;
//Could not parse:  1f0:	00001038 	word	0x00001038 ;
label_1f4:  ;
//Could not parse:  1f4:	10010000 	word	0x10010000 ;
label_1f8:  ;
//Could not parse:  1f8:	00001044 	word	0x00001044 ;
label_1fc:  ;
//Could not parse:  1fc:	fff3ffff 	word	0xfff3ffff ;
label_200:  ;
//Could not parse:  200:	00001004 	word	0x00001004 ;
label_204:  ;
//Could not parse:  204:	fcffffff 	word	0xfcffffff ;
label_208:  ;
//Could not parse:  208:	40049000 	word	0x40049000 ;
label_20c:  ;
//Could not parse:  20c:	fefff8ff 	word	0xfefff8ff ;
label_210:  ;
//Could not parse:  210:	40065000 	word	0x40065000 ;
label_214:  ;
//Could not parse:  214:	40064000 	word	0x40064000 ;
label_218:  ;
//Could not parse:  218:	1ffff000 	word	0x1ffff000 ;
label_21c:  ;
//Could not parse:  21c:	1ffff000 	word	0x1ffff000 ;
label_220:  ;
//Could not parse:  220:	000005ce 	word	0x000005ce ;
label_224:  ;
//Could not parse:  224:	1ffff000 	word	0x1ffff000 ;
}
void __startup_end() 
{}
void _cfm() 
{label_400:  ;
//Could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ~ ;
}
void delay() 
{label_410:  ;
MOVS(r2, 250);// 410:	22fa      	movs	r2, #250	 ; 0xfa ;
label_412:  ;
SUB(sp, 8);// 412:	b082      	sub	sp, #8 ;
label_414:  ;
LSLS(r2, r2, 2);// 414:	0092      	lsls	r2, r2, #2 ;
label_416:  ;
SUBS(r0, 1);// 416:	3801      	subs	r0, #1 ;
label_418:  ;
//Could not parse:  418:	d201      	bcsn	41e <delay+0xe> ;
label_41a:  ;
ADD(sp, 8);// 41a:	b002      	add	sp, #8 ;
label_41c:  ;
BX(lr);// 41c:	4770      	bx	lr ;
label_41e:  ;
STR(r2, sp, 4);// 41e:	9201      	str	r2, sp, #4 ;
label_420:  ;
LDR(r3, sp, 4);// 420:	9b01      	ldr	r3, sp, #4 ;
label_422:  ;
SUBS(r1, r3, 1);// 422:	1e59      	subs	r1, r3, #1 ;
label_424:  ;
STR(r1, sp, 4);// 424:	9101      	str	r1, sp, #4 ;
label_426:  ;
CMP(r3, 0);// 426:	2b00      	cmp	r3, #0 ;
label_428:  ;
//Could not parse:  428:	d1fa      	bnen	420 <delay+0x10> ;
label_42a:  ;
 goto(label_416);// 42a:	e7f4      	bn	416 <delay+0x6> ;
}
void main() 
{label_42c:  ;
PUSH(r4, r5, r6, lr);// 42c:	b570      	push	r4, r5, r6, lr ;
label_42e:  ;
MOVS(r5, 250);// 42e:	25fa      	movs	r5, #250	 ; 0xfa ;
label_430:  ;
configure_rgbled();// 430:	f000 f80c 	bl	44c <configure_rgbled> ;
label_434:  ;
LSLS(r5, r5, 5);// 434:	016d      	lsls	r5, r5, #5 ;
label_436:  ;
MOVS(r4, 0);// 436:	2400      	movs	r4, #0 ;
label_438:  ;
//Could not parse:  438:	b2e0      	uxtb	r0, r4 ;
label_43a:  ;
set_rgbled_color_to();// 43a:	f000 f895 	bl	568 <set_rgbled_color_to> ;
label_43e:  ;
ADDS(r4, 1);// 43e:	3401      	adds	r4, #1 ;
label_440:  ;
MOVS(r0, r5);// 440:	0028      	movs	r0, r5 ;
label_442:  ;
delay();// 442:	f7ff ffe5 	bl	410 <delay> ;
label_446:  ;
CMP(r4, 8);// 446:	2c08      	cmp	r4, #8 ;
label_448:  ;
//Could not parse:  448:	d1f6      	bnen	438 <main+0xc> ;
label_44a:  ;
 goto(label_436);// 44a:	e7f4      	bn	436 <main+0xa> ;
}
void configure_rgbled() 
{label_44c:  ;
MOVS(r3, 160);// 44c:	23a0      	movs	r3, #160	 ; 0xa0 ;
label_44e:  ;
LDR(r1, pc, 80);// 44e:	4914      	ldr	r1, pc, #80	 ; (4a0 <configure_rgbled+0x54>) ;
label_450:  ;
LDR(r2, pc, 80);// 450:	4a14      	ldr	r2, pc, #80	 ; (4a4 <configure_rgbled+0x58>) ;
label_452:  ;
LSLS(r3, r3, 5);// 452:	015b      	lsls	r3, r3, #5 ;
label_454:  ;
LDR(r0, r1, r2);// 454:	5888      	ldr	r0, r1, r2 ;
label_456:  ;
ORRS(r3, r0);// 456:	4303      	orrs	r3, r0 ;
label_458:  ;
STR(r3, r1, r2);// 458:	508b      	str	r3, r1, r2 ;
label_45a:  ;
LDR(r3, pc, 76);// 45a:	4b13      	ldr	r3, pc, #76	 ; (4a8 <configure_rgbled+0x5c>) ;
label_45c:  ;
LDR(r0, pc, 76);// 45c:	4813      	ldr	r0, pc, #76	 ; (4ac <configure_rgbled+0x60>) ;
label_45e:  ;
LDR(r2, r3, 72);// 45e:	6c9a      	ldr	r2, r3, #72	 ; 0x48 ;
label_460:  ;
ANDS(r2, r0);// 460:	4002      	ands	r2, r0 ;
label_462:  ;
STR(r2, r3, 72);// 462:	649a      	str	r2, r3, #72	 ; 0x48 ;
label_464:  ;
MOVS(r2, 128);// 464:	2280      	movs	r2, #128	 ; 0x80 ;
label_466:  ;
LDR(r1, r3, 72);// 466:	6c99      	ldr	r1, r3, #72	 ; 0x48 ;
label_468:  ;
LSLS(r2, r2, 1);// 468:	0052      	lsls	r2, r2, #1 ;
label_46a:  ;
ORRS(r1, r2);// 46a:	4311      	orrs	r1, r2 ;
label_46c:  ;
STR(r1, r3, 72);// 46c:	6499      	str	r1, r3, #72	 ; 0x48 ;
label_46e:  ;
LDR(r1, r3, 76);// 46e:	6cd9      	ldr	r1, r3, #76	 ; 0x4c ;
label_470:  ;
ANDS(r1, r0);// 470:	4001      	ands	r1, r0 ;
label_472:  ;
STR(r1, r3, 76);// 472:	64d9      	str	r1, r3, #76	 ; 0x4c ;
label_474:  ;
LDR(r1, r3, 76);// 474:	6cd9      	ldr	r1, r3, #76	 ; 0x4c ;
label_476:  ;
ORRS(r1, r2);// 476:	4311      	orrs	r1, r2 ;
label_478:  ;
STR(r1, r3, 76);// 478:	64d9      	str	r1, r3, #76	 ; 0x4c ;
label_47a:  ;
LDR(r3, pc, 52);// 47a:	4b0d      	ldr	r3, pc, #52	 ; (4b0 <configure_rgbled+0x64>) ;
label_47c:  ;
LDR(r1, r3, 4);// 47c:	6859      	ldr	r1, r3, #4 ;
label_47e:  ;
ANDS(r1, r0);// 47e:	4001      	ands	r1, r0 ;
label_480:  ;
STR(r1, r3, 4);// 480:	6059      	str	r1, r3, #4 ;
label_482:  ;
LDR(r1, r3, 4);// 482:	6859      	ldr	r1, r3, #4 ;
label_484:  ;
ORRS(r2, r1);// 484:	430a      	orrs	r2, r1 ;
label_486:  ;
STR(r2, r3, 4);// 486:	605a      	str	r2, r3, #4 ;
label_488:  ;
MOVS(r3, 192);// 488:	23c0      	movs	r3, #192	 ; 0xc0 ;
label_48a:  ;
LDR(r2, pc, 40);// 48a:	4a0a      	ldr	r2, pc, #40	 ; (4b4 <configure_rgbled+0x68>) ;
label_48c:  ;
LSLS(r3, r3, 12);// 48c:	031b      	lsls	r3, r3, #12 ;
label_48e:  ;
LDR(r1, r2, 20);// 48e:	6951      	ldr	r1, r2, #20 ;
label_490:  ;
ORRS(r3, r1);// 490:	430b      	orrs	r3, r1 ;
label_492:  ;
STR(r3, r2, 20);// 492:	6153      	str	r3, r2, #20 ;
label_494:  ;
MOVS(r3, 2);// 494:	2302      	movs	r3, #2 ;
label_496:  ;
LDR(r2, pc, 32);// 496:	4a08      	ldr	r2, pc, #32	 ; (4b8 <configure_rgbled+0x6c>) ;
label_498:  ;
LDR(r1, r2, 20);// 498:	6951      	ldr	r1, r2, #20 ;
label_49a:  ;
ORRS(r3, r1);// 49a:	430b      	orrs	r3, r1 ;
label_49c:  ;
STR(r3, r2, 20);// 49c:	6153      	str	r3, r2, #20 ;
label_49e:  ;
BX(lr);// 49e:	4770      	bx	lr ;
label_4a0:  ;
//Could not parse:  4a0:	40047000 	word	0x40047000 ;
label_4a4:  ;
//Could not parse:  4a4:	00001038 	word	0x00001038 ;
label_4a8:  ;
//Could not parse:  4a8:	4004a000 	word	0x4004a000 ;
label_4ac:  ;
//Could not parse:  4ac:	fffff8ff 	word	0xfffff8ff ;
label_4b0:  ;
//Could not parse:  4b0:	4004c000 	word	0x4004c000 ;
label_4b4:  ;
//Could not parse:  4b4:	400ff040 	word	0x400ff040 ;
label_4b8:  ;
//Could not parse:  4b8:	400ff0c0 	word	0x400ff0c0 ;
}
void turn_on_green_led() 
{label_4bc:  ;
MOVS(r3, 128);// 4bc:	2380      	movs	r3, #128	 ; 0x80 ;
label_4be:  ;
LDR(r2, pc, 12);// 4be:	4a03      	ldr	r2, pc, #12	 ; (4cc <turn_on_green_led+0x10>) ;
label_4c0:  ;
LSLS(r3, r3, 12);// 4c0:	031b      	lsls	r3, r3, #12 ;
label_4c2:  ;
LDR(r1, r2, 8);// 4c2:	6891      	ldr	r1, r2, #8 ;
label_4c4:  ;
ORRS(r3, r1);// 4c4:	430b      	orrs	r3, r1 ;
label_4c6:  ;
STR(r3, r2, 8);// 4c6:	6093      	str	r3, r2, #8 ;
label_4c8:  ;
BX(lr);// 4c8:	4770      	bx	lr ;
label_4ca:  ;
//Could not parse:  4ca:	46c0      	nop			 ; (mov r8, r8) ;
label_4cc:  ;
//Could not parse:  4cc:	400ff040 	word	0x400ff040 ;
}
void turn_off_green_led() 
{label_4d0:  ;
MOVS(r3, 128);// 4d0:	2380      	movs	r3, #128	 ; 0x80 ;
label_4d2:  ;
LDR(r2, pc, 12);// 4d2:	4a03      	ldr	r2, pc, #12	 ; (4e0 <turn_off_green_led+0x10>) ;
label_4d4:  ;
LSLS(r3, r3, 12);// 4d4:	031b      	lsls	r3, r3, #12 ;
label_4d6:  ;
LDR(r1, r2, 4);// 4d6:	6851      	ldr	r1, r2, #4 ;
label_4d8:  ;
ORRS(r3, r1);// 4d8:	430b      	orrs	r3, r1 ;
label_4da:  ;
STR(r3, r2, 4);// 4da:	6053      	str	r3, r2, #4 ;
label_4dc:  ;
BX(lr);// 4dc:	4770      	bx	lr ;
label_4de:  ;
//Could not parse:  4de:	46c0      	nop			 ; (mov r8, r8) ;
label_4e0:  ;
//Could not parse:  4e0:	400ff040 	word	0x400ff040 ;
}
void toggle_green_led() 
{label_4e4:  ;
MOVS(r3, 128);// 4e4:	2380      	movs	r3, #128	 ; 0x80 ;
label_4e6:  ;
LDR(r2, pc, 12);// 4e6:	4a03      	ldr	r2, pc, #12	 ; (4f4 <toggle_green_led+0x10>) ;
label_4e8:  ;
LSLS(r3, r3, 12);// 4e8:	031b      	lsls	r3, r3, #12 ;
label_4ea:  ;
LDR(r1, r2, 12);// 4ea:	68d1      	ldr	r1, r2, #12 ;
label_4ec:  ;
ORRS(r3, r1);// 4ec:	430b      	orrs	r3, r1 ;
label_4ee:  ;
STR(r3, r2, 12);// 4ee:	60d3      	str	r3, r2, #12 ;
label_4f0:  ;
BX(lr);// 4f0:	4770      	bx	lr ;
label_4f2:  ;
//Could not parse:  4f2:	46c0      	nop			 ; (mov r8, r8) ;
label_4f4:  ;
//Could not parse:  4f4:	400ff040 	word	0x400ff040 ;
}
void turn_on_red_led() 
{label_4f8:  ;
MOVS(r3, 128);// 4f8:	2380      	movs	r3, #128	 ; 0x80 ;
label_4fa:  ;
LDR(r2, pc, 12);// 4fa:	4a03      	ldr	r2, pc, #12	 ; (508 <turn_on_red_led+0x10>) ;
label_4fc:  ;
LSLS(r3, r3, 11);// 4fc:	02db      	lsls	r3, r3, #11 ;
label_4fe:  ;
LDR(r1, r2, 8);// 4fe:	6891      	ldr	r1, r2, #8 ;
label_500:  ;
ORRS(r3, r1);// 500:	430b      	orrs	r3, r1 ;
label_502:  ;
STR(r3, r2, 8);// 502:	6093      	str	r3, r2, #8 ;
label_504:  ;
BX(lr);// 504:	4770      	bx	lr ;
label_506:  ;
//Could not parse:  506:	46c0      	nop			 ; (mov r8, r8) ;
label_508:  ;
//Could not parse:  508:	400ff040 	word	0x400ff040 ;
}
void turn_off_red_led() 
{label_50c:  ;
MOVS(r3, 128);// 50c:	2380      	movs	r3, #128	 ; 0x80 ;
label_50e:  ;
LDR(r2, pc, 12);// 50e:	4a03      	ldr	r2, pc, #12	 ; (51c <turn_off_red_led+0x10>) ;
label_510:  ;
LSLS(r3, r3, 11);// 510:	02db      	lsls	r3, r3, #11 ;
label_512:  ;
LDR(r1, r2, 4);// 512:	6851      	ldr	r1, r2, #4 ;
label_514:  ;
ORRS(r3, r1);// 514:	430b      	orrs	r3, r1 ;
label_516:  ;
STR(r3, r2, 4);// 516:	6053      	str	r3, r2, #4 ;
label_518:  ;
BX(lr);// 518:	4770      	bx	lr ;
label_51a:  ;
//Could not parse:  51a:	46c0      	nop			 ; (mov r8, r8) ;
label_51c:  ;
//Could not parse:  51c:	400ff040 	word	0x400ff040 ;
}
void toggle_red_led() 
{label_520:  ;
MOVS(r3, 128);// 520:	2380      	movs	r3, #128	 ; 0x80 ;
label_522:  ;
LDR(r2, pc, 12);// 522:	4a03      	ldr	r2, pc, #12	 ; (530 <toggle_red_led+0x10>) ;
label_524:  ;
LSLS(r3, r3, 11);// 524:	02db      	lsls	r3, r3, #11 ;
label_526:  ;
LDR(r1, r2, 12);// 526:	68d1      	ldr	r1, r2, #12 ;
label_528:  ;
ORRS(r3, r1);// 528:	430b      	orrs	r3, r1 ;
label_52a:  ;
STR(r3, r2, 12);// 52a:	60d3      	str	r3, r2, #12 ;
label_52c:  ;
BX(lr);// 52c:	4770      	bx	lr ;
label_52e:  ;
//Could not parse:  52e:	46c0      	nop			 ; (mov r8, r8) ;
label_530:  ;
//Could not parse:  530:	400ff040 	word	0x400ff040 ;
}
void turn_on_blue_led() 
{label_534:  ;
MOVS(r3, 2);// 534:	2302      	movs	r3, #2 ;
label_536:  ;
LDR(r2, pc, 8);// 536:	4a02      	ldr	r2, pc, #8	 ; (540 <turn_on_blue_led+0xc>) ;
label_538:  ;
LDR(r1, r2, 8);// 538:	6891      	ldr	r1, r2, #8 ;
label_53a:  ;
ORRS(r3, r1);// 53a:	430b      	orrs	r3, r1 ;
label_53c:  ;
STR(r3, r2, 8);// 53c:	6093      	str	r3, r2, #8 ;
label_53e:  ;
BX(lr);// 53e:	4770      	bx	lr ;
label_540:  ;
//Could not parse:  540:	400ff0c0 	word	0x400ff0c0 ;
}
void turn_off_blue_led() 
{label_544:  ;
MOVS(r3, 2);// 544:	2302      	movs	r3, #2 ;
label_546:  ;
LDR(r2, pc, 8);// 546:	4a02      	ldr	r2, pc, #8	 ; (550 <turn_off_blue_led+0xc>) ;
label_548:  ;
LDR(r1, r2, 4);// 548:	6851      	ldr	r1, r2, #4 ;
label_54a:  ;
ORRS(r3, r1);// 54a:	430b      	orrs	r3, r1 ;
label_54c:  ;
STR(r3, r2, 4);// 54c:	6053      	str	r3, r2, #4 ;
label_54e:  ;
BX(lr);// 54e:	4770      	bx	lr ;
label_550:  ;
//Could not parse:  550:	400ff0c0 	word	0x400ff0c0 ;
}
void toggle_blue_led() 
{label_554:  ;
MOVS(r3, 128);// 554:	2380      	movs	r3, #128	 ; 0x80 ;
label_556:  ;
LDR(r2, pc, 12);// 556:	4a03      	ldr	r2, pc, #12	 ; (564 <toggle_blue_led+0x10>) ;
label_558:  ;
LSLS(r3, r3, 11);// 558:	02db      	lsls	r3, r3, #11 ;
label_55a:  ;
LDR(r1, r2, 12);// 55a:	68d1      	ldr	r1, r2, #12 ;
label_55c:  ;
ORRS(r3, r1);// 55c:	430b      	orrs	r3, r1 ;
label_55e:  ;
STR(r3, r2, 12);// 55e:	60d3      	str	r3, r2, #12 ;
label_560:  ;
BX(lr);// 560:	4770      	bx	lr ;
label_562:  ;
//Could not parse:  562:	46c0      	nop			 ; (mov r8, r8) ;
label_564:  ;
//Could not parse:  564:	400ff0c0 	word	0x400ff0c0 ;
}
void set_rgbled_color_to() 
{label_568:  ;
PUSH(r4, lr);// 568:	b510      	push	r4, lr ;
label_56a:  ;
CMP(r0, 0);// 56a:	2800      	cmp	r0, #0 ;
label_56c:  ;
//Could not parse:  56c:	d106      	bnen	57c <set_rgbled_color_to+0x14> ;
label_56e:  ;
turn_off_blue_led();// 56e:	f7ff ffe9 	bl	544 <turn_off_blue_led> ;
label_572:  ;
turn_off_green_led();// 572:	f7ff ffad 	bl	4d0 <turn_off_green_led> ;
label_576:  ;
turn_off_red_led();// 576:	f7ff ffc9 	bl	50c <turn_off_red_led> ;
label_57a:  ;
//Could not parse:  57a:	bd10      	pop	r4, pc ;
label_57c:  ;
CMP(r0, 1);// 57c:	2801      	cmp	r0, #1 ;
label_57e:  ;
//Could not parse:  57e:	d102      	bnen	586 <set_rgbled_color_to+0x1e> ;
label_580:  ;
turn_on_blue_led();// 580:	f7ff ffd8 	bl	534 <turn_on_blue_led> ;
label_584:  ;
 goto(label_572);// 584:	e7f5      	bn	572 <set_rgbled_color_to+0xa> ;
label_586:  ;
CMP(r0, 2);// 586:	2802      	cmp	r0, #2 ;
label_588:  ;
//Could not parse:  588:	d104      	bnen	594 <set_rgbled_color_to+0x2c> ;
label_58a:  ;
turn_off_blue_led();// 58a:	f7ff ffdb 	bl	544 <turn_off_blue_led> ;
label_58e:  ;
turn_on_green_led();// 58e:	f7ff ff95 	bl	4bc <turn_on_green_led> ;
label_592:  ;
 goto(label_576);// 592:	e7f0      	bn	576 <set_rgbled_color_to+0xe> ;
label_594:  ;
CMP(r0, 3);// 594:	2803      	cmp	r0, #3 ;
label_596:  ;
//Could not parse:  596:	d102      	bnen	59e <set_rgbled_color_to+0x36> ;
label_598:  ;
turn_on_blue_led();// 598:	f7ff ffcc 	bl	534 <turn_on_blue_led> ;
label_59c:  ;
 goto(label_58e);// 59c:	e7f7      	bn	58e <set_rgbled_color_to+0x26> ;
label_59e:  ;
CMP(r0, 4);// 59e:	2804      	cmp	r0, #4 ;
label_5a0:  ;
//Could not parse:  5a0:	d106      	bnen	5b0 <set_rgbled_color_to+0x48> ;
label_5a2:  ;
turn_off_blue_led();// 5a2:	f7ff ffcf 	bl	544 <turn_off_blue_led> ;
label_5a6:  ;
turn_off_green_led();// 5a6:	f7ff ff93 	bl	4d0 <turn_off_green_led> ;
label_5aa:  ;
turn_on_red_led();// 5aa:	f7ff ffa5 	bl	4f8 <turn_on_red_led> ;
label_5ae:  ;
 goto(label_57a);// 5ae:	e7e4      	bn	57a <set_rgbled_color_to+0x12> ;
label_5b0:  ;
CMP(r0, 5);// 5b0:	2805      	cmp	r0, #5 ;
label_5b2:  ;
//Could not parse:  5b2:	d102      	bnen	5ba <set_rgbled_color_to+0x52> ;
label_5b4:  ;
turn_on_blue_led();// 5b4:	f7ff ffbe 	bl	534 <turn_on_blue_led> ;
label_5b8:  ;
 goto(label_5a6);// 5b8:	e7f5      	bn	5a6 <set_rgbled_color_to+0x3e> ;
label_5ba:  ;
CMP(r0, 6);// 5ba:	2806      	cmp	r0, #6 ;
label_5bc:  ;
//Could not parse:  5bc:	d104      	bnen	5c8 <set_rgbled_color_to+0x60> ;
label_5be:  ;
turn_off_blue_led();// 5be:	f7ff ffc1 	bl	544 <turn_off_blue_led> ;
label_5c2:  ;
turn_on_green_led();// 5c2:	f7ff ff7b 	bl	4bc <turn_on_green_led> ;
label_5c6:  ;
 goto(label_5aa);// 5c6:	e7f0      	bn	5aa <set_rgbled_color_to+0x42> ;
label_5c8:  ;
turn_on_blue_led();// 5c8:	f7ff ffb4 	bl	534 <turn_on_blue_led> ;
label_5cc:  ;
 goto(label_5c2);// 5cc:	e7f9      	bn	5c2 <set_rgbled_color_to+0x5a> ;
}