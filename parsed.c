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
     ................ ;
//Could not parse:   40:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   50:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   60:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   70:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   80:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   90:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   a0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
//Could not parse:   b0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................ ;
}
void Default_Handler() 
{B.N("c0", <Default_Handler>);//  c0:	e7fe      	b.n	c0 <Default_Handler> ;
}
void HardFault_Handler() 
{B.N("c2", <HardFault_Handler>);//  c2:	e7fe      	b.n	c2 <HardFault_Handler> ;
}
void _stop_init() 
{MOVS(r1, 128);//  c4:	2180      	movs	r1, #128	 ; 0x80 ;
LDR(r2, "pc", 64);//  c6:	4a10      	ldr	r2, pc, #64	 ; (108 <_stop_init+0x44>) ;
LDR(r3, "pc", 64);//  c8:	4b10      	ldr	r3, pc, #64	 ; (10c <_stop_init+0x48>) ;
LSLS(r1, r1, 6);//  ca:	0189      	lsls	r1, r1, #6 ;
LDR(r0, r2, r3);//  cc:	58d0      	ldr	r0, r2, r3 ;
PUSH(r4, r5, lr);//  ce:	b530      	push	r4, r5, lr ;
ORRS(r1, r0);//  d0:	4301      	orrs	r1, r0 ;
STR(r1, r2, r3);//  d2:	50d1      	str	r1, r2, r3 ;
LDR(r1, "pc", 56);//  d4:	490e      	ldr	r1, pc, #56	 ; (110 <_stop_init+0x4c>) ;
LDR(r4, "pc", 60);//  d6:	4c0f      	ldr	r4, pc, #60	 ; (114 <_stop_init+0x50>) ;
LDR(r0, r1, 4);//  d8:	6848      	ldr	r0, r1, #4 ;
ANDS(r0, r4);//  da:	4020      	ands	r0, r4 ;
STR(r0, r1, 4);//  dc:	6048      	str	r0, r1, #4 ;
MOVS(r0, 128);//  de:	2080      	movs	r0, #128	 ; 0x80 ;
LDR(r4, r1, 4);//  e0:	684c      	ldr	r4, r1, #4 ;
LSLS(r0, r0, 1);//  e2:	0040      	lsls	r0, r0, #1 ;
ORRS(r0, r4);//  e4:	4320      	orrs	r0, r4 ;
STR(r0, r1, 4);//  e6:	6048      	str	r0, r1, #4 ;
MOVS(r0, 2);//  e8:	2002      	movs	r0, #2 ;
LDR(r4, "pc", 44);//  ea:	4c0b      	ldr	r4, pc, #44	 ; (118 <_stop_init+0x54>) ;
LDR(r5, r4, 20);//  ec:	6965      	ldr	r5, r4, #20 ;
//Could not parse:   ee:	4385      	bics	r5, r0 ;
STR(r5, r4, 20);//  f0:	6165      	str	r5, r4, #20 ;
LDR(r5, r1, 4);//  f2:	684d      	ldr	r5, r1, #4 ;
ORRS(r5, r0);//  f4:	4305      	orrs	r5, r0 ;
STR(r5, r1, 4);//  f6:	604d      	str	r5, r1, #4 ;
LDR(r1, r4, 16);//  f8:	6921      	ldr	r1, r4, #16 ;
TST(r1, r0);//  fa:	4201      	tst	r1, r0 ;
BEQ.N("f8", "<_stop_init+0x34>",);//  fc:	d0fc      	beq.n	f8 <_stop_init+0x34> ;
LDR(r1, r2, r3);//  fe:	58d1      	ldr	r1, r2, r3 ;
LDR(r0, "pc", 24);// 100:	4806      	ldr	r0, pc, #24	 ; (11c <_stop_init+0x58>) ;
ANDS(r1, r0);// 102:	4001      	ands	r1, r0 ;
STR(r1, r2, r3);// 104:	50d1      	str	r1, r2, r3 ;
//Could not parse:  106:	bd30      	pop	r4, r5, pc ;
//Could not parse:  108:	40047000 	.word	0x40047000 ;
//Could not parse:  10c:	00001038 	.word	0x00001038 ;
//Could not parse:  110:	4004d000 	.word	0x4004d000 ;
//Could not parse:  114:	fffff8ff 	.word	0xfffff8ff ;
//Could not parse:  118:	400ff100 	.word	0x400ff100 ;
//Could not parse:  11c:	ffffdfff 	.word	0xffffdfff ;
}
void _reset_init() 
{BL("c4", "<_stop_init>",);// 120:	f7ff ffd0 	bl	c4 <_stop_init> ;
MOVS(r2, 136);// 124:	2288      	movs	r2, #136	 ; 0x88 ;
MOVS(r1, 1);// 126:	2101      	movs	r1, #1 ;
LDR(r3, "pc", 184);// 128:	4b2e      	ldr	r3, pc, #184	 ; (1e4 <_reset_init+0xc4>) ;
LSLS(r2, r2, 5);// 12a:	0152      	lsls	r2, r2, #5 ;
STR(r1, r3, r2);// 12c:	5099      	str	r1, r3, r2 ;
LDR(r0, "pc", 184);// 12e:	482e      	ldr	r0, pc, #184	 ; (1e8 <_reset_init+0xc8>) ;
LDR(r2, "pc", 184);// 130:	4a2e      	ldr	r2, pc, #184	 ; (1ec <_reset_init+0xcc>) ;
STR(r0, r2, 8);// 132:	6090      	str	r0, r2, #8 ;
MOVS(r2, 128);// 134:	2280      	movs	r2, #128	 ; 0x80 ;
LDR(r0, "pc", 184);// 136:	482e      	ldr	r0, pc, #184	 ; (1f0 <_reset_init+0xd0>) ;
LSLS(r2, r2, 2);// 138:	0092      	lsls	r2, r2, #2 ;
LDR(r4, r3, r0);// 13a:	581c      	ldr	r4, r3, r0 ;
ORRS(r2, r4);// 13c:	4322      	orrs	r2, r4 ;
STR(r2, r3, r0);// 13e:	501a      	str	r2, r3, r0 ;
LDR(r0, "pc", 176);// 140:	482c      	ldr	r0, pc, #176	 ; (1f4 <_reset_init+0xd4>) ;
LDR(r2, "pc", 180);// 142:	4a2d      	ldr	r2, pc, #180	 ; (1f8 <_reset_init+0xd8>) ;
STR(r0, r3, r2);// 144:	5098      	str	r0, r3, r2 ;
LDR(r2, r3, 0);// 146:	681a      	ldr	r2, r3, #0 ;
LDR(r0, "pc", 176);// 148:	482c      	ldr	r0, pc, #176	 ; (1fc <_reset_init+0xdc>) ;
ANDS(r2, r0);// 14a:	4002      	ands	r2, r0 ;
MOVS(r0, 128);// 14c:	2080      	movs	r0, #128	 ; 0x80 ;
STR(r2, r3, 0);// 14e:	601a      	str	r2, r3, #0 ;
LDR(r2, "pc", 172);// 150:	4a2b      	ldr	r2, pc, #172	 ; (200 <_reset_init+0xe0>) ;
LSLS(r0, r0, 9);// 152:	0240      	lsls	r0, r0, #9 ;
LDR(r4, r3, r2);// 154:	589c      	ldr	r4, r3, r2 ;
ORRS(r0, r4);// 156:	4320      	orrs	r0, r4 ;
STR(r0, r3, r2);// 158:	5098      	str	r0, r3, r2 ;
LDR(r0, r3, r2);// 15a:	5898      	ldr	r0, r3, r2 ;
LDR(r4, "pc", 164);// 15c:	4c29      	ldr	r4, pc, #164	 ; (204 <_reset_init+0xe4>) ;
ANDS(r4, r0);// 15e:	4004      	ands	r4, r0 ;
MOVS(r0, 128);// 160:	2080      	movs	r0, #128	 ; 0x80 ;
LSLS(r0, r0, 17);// 162:	0440      	lsls	r0, r0, #17 ;
ORRS(r0, r4);// 164:	4320      	orrs	r0, r4 ;
STR(r0, r3, r2);// 166:	5098      	str	r0, r3, r2 ;
LDR(r3, "pc", 156);// 168:	4b27      	ldr	r3, pc, #156	 ; (208 <_reset_init+0xe8>) ;
LDR(r4, "pc", 160);// 16a:	4c28      	ldr	r4, pc, #160	 ; (20c <_reset_init+0xec>) ;
LDR(r0, r3, 72);// 16c:	6c98      	ldr	r0, r3, #72	 ; 0x48 ;
ANDS(r0, r4);// 16e:	4020      	ands	r0, r4 ;
STR(r0, r3, 72);// 170:	6498      	str	r0, r3, #72	 ; 0x48 ;
LDR(r2, r3, 76);// 172:	6cda      	ldr	r2, r3, #76	 ; 0x4c ;
MOVS(r0, 0);// 174:	2000      	movs	r0, #0 ;
ANDS(r2, r4);// 176:	4022      	ands	r2, r4 ;
STR(r2, r3, 76);// 178:	64da      	str	r2, r3, #76	 ; 0x4c ;
MOVS(r2, 36);// 17a:	2224      	movs	r2, #36	 ; 0x24 ;
MOVS(r4, 31);// 17c:	241f      	movs	r4, #31 ;
LDR(r3, "pc", 144);// 17e:	4b24      	ldr	r3, pc, #144	 ; (210 <_reset_init+0xf0>) ;
//Could not parse:  180:	7018      	strb	r0, r3, #0 ;
LDR(r3, "pc", 144);// 182:	4b24      	ldr	r3, pc, #144	 ; (214 <_reset_init+0xf4>) ;
//Could not parse:  184:	705a      	strb	r2, r3, #1 ;
ADDS(r2, 116);// 186:	3274      	adds	r2, #116	 ; 0x74 ;
//Could not parse:  188:	701a      	strb	r2, r3, #0 ;
//Could not parse:  18a:	78da      	ldrb	r2, r3, #3 ;
ANDS(r2, r4);// 18c:	4022      	ands	r2, r4 ;
//Could not parse:  18e:	70da      	strb	r2, r3, #3 ;
MOVS(r2, 16);// 190:	2210      	movs	r2, #16 ;
//Could not parse:  192:	7119      	strb	r1, r3, #4 ;
//Could not parse:  194:	7158      	strb	r0, r3, #5 ;
//Could not parse:  196:	7999      	ldrb	r1, r3, #6 ;
TST(r1, r2);// 198:	4211      	tst	r1, r2 ;
BNE.N("196", <_reset_init+0x76>);// 19a:	d1fc      	bne.n	196 <_reset_init+0x76> ;
MOVS(r1, 12);// 19c:	210c      	movs	r1, #12 ;
//Could not parse:  19e:	799a      	ldrb	r2, r3, #6 ;
ANDS(r2, r1);// 1a0:	400a      	ands	r2, r1 ;
CMP(r2, 8);// 1a2:	2a08      	cmp	r2, #8 ;
BNE.N("19e", <_reset_init+0x7e>);// 1a4:	d1fb      	bne.n	19e <_reset_init+0x7e> ;
ADDS(r2, 56);// 1a6:	3238      	adds	r2, #56	 ; 0x38 ;
//Could not parse:  1a8:	715a      	strb	r2, r3, #5 ;
//Could not parse:  1aa:	7999      	ldrb	r1, r3, #6 ;
TST(r1, r2);// 1ac:	4211      	tst	r1, r2 ;
BEQ.N("1aa", <_reset_init+0x8a>);// 1ae:	d0fc      	beq.n	1aa <_reset_init+0x8a> ;
MOVS(r2, 24);// 1b0:	2218      	movs	r2, #24 ;
MOVS(r1, 12);// 1b2:	210c      	movs	r1, #12 ;
//Could not parse:  1b4:	701a      	strb	r2, r3, #0 ;
//Could not parse:  1b6:	799a      	ldrb	r2, r3, #6 ;
ANDS(r2, r1);// 1b8:	400a      	ands	r2, r1 ;
CMP(r2, 12);// 1ba:	2a0c      	cmp	r2, #12 ;
BNE.N("1b6", <_reset_init+0x96>);// 1bc:	d1fb      	bne.n	1b6 <_reset_init+0x96> ;
MOVS(r2, 0);// 1be:	2200      	movs	r2, #0 ;
LDR(r0, "pc", 84);// 1c0:	4815      	ldr	r0, pc, #84	 ; (218 <_reset_init+0xf8>) ;
LDR(r1, "pc", 88);// 1c2:	4916      	ldr	r1, pc, #88	 ; (21c <_reset_init+0xfc>) ;
LDR(r4, "pc", 88);// 1c4:	4c16      	ldr	r4, pc, #88	 ; (220 <_reset_init+0x100>) ;
ADDS(r3, r2, r0);// 1c6:	1813      	adds	r3, r2, r0 ;
CMP(r3, r1);// 1c8:	428b      	cmp	r3, r1 ;
//Could not parse:  1ca:	d305      	bcc.n	1d8 <_reset_init+0xb8> ;
MOVS(r1, 0);// 1cc:	2100      	movs	r1, #0 ;
LDR(r2, "pc", 84);// 1ce:	4a15      	ldr	r2, pc, #84	 ; (224 <_reset_init+0x104>) ;
CMP(r3, r2);// 1d0:	4293      	cmp	r3, r2 ;
//Could not parse:  1d2:	d905      	bls.n	1e0 <_reset_init+0xc0> ;
BL("42c", "<main>",);// 1d4:	f000 f92a 	bl	42c <main> ;
LDR(r5, r4, r2);// 1d8:	58a5      	ldr	r5, r4, r2 ;
ADDS(r2, 4);// 1da:	3204      	adds	r2, #4 ;
STR(r5, r3, 0);// 1dc:	601d      	str	r5, r3, #0 ;
B.N("1c6", <_reset_init+0xa6>);// 1de:	e7f2      	b.n	1c6 <_reset_init+0xa6> ;
//Could not parse:  1e0:	c302      	stmia	r3!, r1 ;
B.N("1d0", <_reset_init+0xb0>);// 1e2:	e7f5      	b.n	1d0 <_reset_init+0xb0> ;
//Could not parse:  1e4:	40047000 	.word	0x40047000 ;
//Could not parse:  1e8:	00000000 	.word	0x00000000 ;
//Could not parse:  1ec:	e000ed00 	.word	0xe000ed00 ;
//Could not parse:  1f0:	00001038 	.word	0x00001038 ;
//Could not parse:  1f4:	10010000 	.word	0x10010000 ;
//Could not parse:  1f8:	00001044 	.word	0x00001044 ;
//Could not parse:  1fc:	fff3ffff 	.word	0xfff3ffff ;
//Could not parse:  200:	00001004 	.word	0x00001004 ;
//Could not parse:  204:	fcffffff 	.word	0xfcffffff ;
//Could not parse:  208:	40049000 	.word	0x40049000 ;
//Could not parse:  20c:	fefff8ff 	.word	0xfefff8ff ;
//Could not parse:  210:	40065000 	.word	0x40065000 ;
//Could not parse:  214:	40064000 	.word	0x40064000 ;
//Could not parse:  218:	1ffff000 	.word	0x1ffff000 ;
//Could not parse:  21c:	1ffff000 	.word	0x1ffff000 ;
//Could not parse:  220:	000005ce 	.word	0x000005ce ;
//Could not parse:  224:	1ffff000 	.word	0x1ffff000 ;
}
void __startup_end() 
{}
void _cfm() 
{//Could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ............~... ;
}
void delay() 
{MOVS(r2, 250);// 410:	22fa      	movs	r2, #250	 ; 0xfa ;
SUB("sp", 8);// 412:	b082      	sub	sp, #8 ;
LSLS(r2, r2, 2);// 414:	0092      	lsls	r2, r2, #2 ;
SUBS(r0, 1);// 416:	3801      	subs	r0, #1 ;
BCS.N("41e", "<delay+0xe>",);// 418:	d201      	bcs.n	41e <delay+0xe> ;
ADD("sp", 8);// 41a:	b002      	add	sp, #8 ;
BX(lr);// 41c:	4770      	bx	lr ;
STR(r2, "sp", 4);// 41e:	9201      	str	r2, sp, #4 ;
LDR(r3, "sp", 4);// 420:	9b01      	ldr	r3, sp, #4 ;
SUBS(r1, r3, 1);// 422:	1e59      	subs	r1, r3, #1 ;
STR(r1, "sp", 4);// 424:	9101      	str	r1, sp, #4 ;
CMP(r3, 0);// 426:	2b00      	cmp	r3, #0 ;
BNE.N("420", "<delay+0x10>",);// 428:	d1fa      	bne.n	420 <delay+0x10> ;
B.N("416", "<delay+0x6>",);// 42a:	e7f4      	b.n	416 <delay+0x6> ;
}
void main() 
{PUSH(r4, r5, r6, lr);// 42c:	b570      	push	r4, r5, r6, lr ;
MOVS(r5, 250);// 42e:	25fa      	movs	r5, #250	 ; 0xfa ;
BL("44c", <configure_rgbled>);// 430:	f000 f80c 	bl	44c <configure_rgbled> ;
LSLS(r5, r5, 5);// 434:	016d      	lsls	r5, r5, #5 ;
MOVS(r4, 0);// 436:	2400      	movs	r4, #0 ;
//Could not parse:  438:	b2e0      	uxtb	r0, r4 ;
BL("568", <set_rgbled_color_to>);// 43a:	f000 f895 	bl	568 <set_rgbled_color_to> ;
ADDS(r4, 1);// 43e:	3401      	adds	r4, #1 ;
MOVS(r0, r5);// 440:	0028      	movs	r0, r5 ;
BL("410", "<delay>",);// 442:	f7ff ffe5 	bl	410 <delay> ;
CMP(r4, 8);// 446:	2c08      	cmp	r4, #8 ;
BNE.N("438", "<main+0xc>",);// 448:	d1f6      	bne.n	438 <main+0xc> ;
B.N("436", "<main+0xa>",);// 44a:	e7f4      	b.n	436 <main+0xa> ;
}
void configure_rgbled() 
{MOVS(r3, 160);// 44c:	23a0      	movs	r3, #160	 ; 0xa0 ;
LDR(r1, "pc", 80);// 44e:	4914      	ldr	r1, pc, #80	 ; (4a0 <configure_rgbled+0x54>) ;
LDR(r2, "pc", 80);// 450:	4a14      	ldr	r2, pc, #80	 ; (4a4 <configure_rgbled+0x58>) ;
LSLS(r3, r3, 5);// 452:	015b      	lsls	r3, r3, #5 ;
LDR(r0, r1, r2);// 454:	5888      	ldr	r0, r1, r2 ;
ORRS(r3, r0);// 456:	4303      	orrs	r3, r0 ;
STR(r3, r1, r2);// 458:	508b      	str	r3, r1, r2 ;
LDR(r3, "pc", 76);// 45a:	4b13      	ldr	r3, pc, #76	 ; (4a8 <configure_rgbled+0x5c>) ;
LDR(r0, "pc", 76);// 45c:	4813      	ldr	r0, pc, #76	 ; (4ac <configure_rgbled+0x60>) ;
LDR(r2, r3, 72);// 45e:	6c9a      	ldr	r2, r3, #72	 ; 0x48 ;
ANDS(r2, r0);// 460:	4002      	ands	r2, r0 ;
STR(r2, r3, 72);// 462:	649a      	str	r2, r3, #72	 ; 0x48 ;
MOVS(r2, 128);// 464:	2280      	movs	r2, #128	 ; 0x80 ;
LDR(r1, r3, 72);// 466:	6c99      	ldr	r1, r3, #72	 ; 0x48 ;
LSLS(r2, r2, 1);// 468:	0052      	lsls	r2, r2, #1 ;
ORRS(r1, r2);// 46a:	4311      	orrs	r1, r2 ;
STR(r1, r3, 72);// 46c:	6499      	str	r1, r3, #72	 ; 0x48 ;
LDR(r1, r3, 76);// 46e:	6cd9      	ldr	r1, r3, #76	 ; 0x4c ;
ANDS(r1, r0);// 470:	4001      	ands	r1, r0 ;
STR(r1, r3, 76);// 472:	64d9      	str	r1, r3, #76	 ; 0x4c ;
LDR(r1, r3, 76);// 474:	6cd9      	ldr	r1, r3, #76	 ; 0x4c ;
ORRS(r1, r2);// 476:	4311      	orrs	r1, r2 ;
STR(r1, r3, 76);// 478:	64d9      	str	r1, r3, #76	 ; 0x4c ;
LDR(r3, "pc", 52);// 47a:	4b0d      	ldr	r3, pc, #52	 ; (4b0 <configure_rgbled+0x64>) ;
LDR(r1, r3, 4);// 47c:	6859      	ldr	r1, r3, #4 ;
ANDS(r1, r0);// 47e:	4001      	ands	r1, r0 ;
STR(r1, r3, 4);// 480:	6059      	str	r1, r3, #4 ;
LDR(r1, r3, 4);// 482:	6859      	ldr	r1, r3, #4 ;
ORRS(r2, r1);// 484:	430a      	orrs	r2, r1 ;
STR(r2, r3, 4);// 486:	605a      	str	r2, r3, #4 ;
MOVS(r3, 192);// 488:	23c0      	movs	r3, #192	 ; 0xc0 ;
LDR(r2, "pc", 40);// 48a:	4a0a      	ldr	r2, pc, #40	 ; (4b4 <configure_rgbled+0x68>) ;
LSLS(r3, r3, 12);// 48c:	031b      	lsls	r3, r3, #12 ;
LDR(r1, r2, 20);// 48e:	6951      	ldr	r1, r2, #20 ;
ORRS(r3, r1);// 490:	430b      	orrs	r3, r1 ;
STR(r3, r2, 20);// 492:	6153      	str	r3, r2, #20 ;
MOVS(r3, 2);// 494:	2302      	movs	r3, #2 ;
LDR(r2, "pc", 32);// 496:	4a08      	ldr	r2, pc, #32	 ; (4b8 <configure_rgbled+0x6c>) ;
LDR(r1, r2, 20);// 498:	6951      	ldr	r1, r2, #20 ;
ORRS(r3, r1);// 49a:	430b      	orrs	r3, r1 ;
STR(r3, r2, 20);// 49c:	6153      	str	r3, r2, #20 ;
BX(lr);// 49e:	4770      	bx	lr ;
//Could not parse:  4a0:	40047000 	.word	0x40047000 ;
//Could not parse:  4a4:	00001038 	.word	0x00001038 ;
//Could not parse:  4a8:	4004a000 	.word	0x4004a000 ;
//Could not parse:  4ac:	fffff8ff 	.word	0xfffff8ff ;
//Could not parse:  4b0:	4004c000 	.word	0x4004c000 ;
//Could not parse:  4b4:	400ff040 	.word	0x400ff040 ;
//Could not parse:  4b8:	400ff0c0 	.word	0x400ff0c0 ;
}
void turn_on_green_led() 
{MOVS(r3, 128);// 4bc:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 4be:	4a03      	ldr	r2, pc, #12	 ; (4cc <turn_on_green_led+0x10>) ;
LSLS(r3, r3, 12);// 4c0:	031b      	lsls	r3, r3, #12 ;
LDR(r1, r2, 8);// 4c2:	6891      	ldr	r1, r2, #8 ;
ORRS(r3, r1);// 4c4:	430b      	orrs	r3, r1 ;
STR(r3, r2, 8);// 4c6:	6093      	str	r3, r2, #8 ;
BX(lr);// 4c8:	4770      	bx	lr ;
//Could not parse:  4ca:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  4cc:	400ff040 	.word	0x400ff040 ;
}
void turn_off_green_led() 
{MOVS(r3, 128);// 4d0:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 4d2:	4a03      	ldr	r2, pc, #12	 ; (4e0 <turn_off_green_led+0x10>) ;
LSLS(r3, r3, 12);// 4d4:	031b      	lsls	r3, r3, #12 ;
LDR(r1, r2, 4);// 4d6:	6851      	ldr	r1, r2, #4 ;
ORRS(r3, r1);// 4d8:	430b      	orrs	r3, r1 ;
STR(r3, r2, 4);// 4da:	6053      	str	r3, r2, #4 ;
BX(lr);// 4dc:	4770      	bx	lr ;
//Could not parse:  4de:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  4e0:	400ff040 	.word	0x400ff040 ;
}
void toggle_green_led() 
{MOVS(r3, 128);// 4e4:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 4e6:	4a03      	ldr	r2, pc, #12	 ; (4f4 <toggle_green_led+0x10>) ;
LSLS(r3, r3, 12);// 4e8:	031b      	lsls	r3, r3, #12 ;
LDR(r1, r2, 12);// 4ea:	68d1      	ldr	r1, r2, #12 ;
ORRS(r3, r1);// 4ec:	430b      	orrs	r3, r1 ;
STR(r3, r2, 12);// 4ee:	60d3      	str	r3, r2, #12 ;
BX(lr);// 4f0:	4770      	bx	lr ;
//Could not parse:  4f2:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  4f4:	400ff040 	.word	0x400ff040 ;
}
void turn_on_red_led() 
{MOVS(r3, 128);// 4f8:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 4fa:	4a03      	ldr	r2, pc, #12	 ; (508 <turn_on_red_led+0x10>) ;
LSLS(r3, r3, 11);// 4fc:	02db      	lsls	r3, r3, #11 ;
LDR(r1, r2, 8);// 4fe:	6891      	ldr	r1, r2, #8 ;
ORRS(r3, r1);// 500:	430b      	orrs	r3, r1 ;
STR(r3, r2, 8);// 502:	6093      	str	r3, r2, #8 ;
BX(lr);// 504:	4770      	bx	lr ;
//Could not parse:  506:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  508:	400ff040 	.word	0x400ff040 ;
}
void turn_off_red_led() 
{MOVS(r3, 128);// 50c:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 50e:	4a03      	ldr	r2, pc, #12	 ; (51c <turn_off_red_led+0x10>) ;
LSLS(r3, r3, 11);// 510:	02db      	lsls	r3, r3, #11 ;
LDR(r1, r2, 4);// 512:	6851      	ldr	r1, r2, #4 ;
ORRS(r3, r1);// 514:	430b      	orrs	r3, r1 ;
STR(r3, r2, 4);// 516:	6053      	str	r3, r2, #4 ;
BX(lr);// 518:	4770      	bx	lr ;
//Could not parse:  51a:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  51c:	400ff040 	.word	0x400ff040 ;
}
void toggle_red_led() 
{MOVS(r3, 128);// 520:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 522:	4a03      	ldr	r2, pc, #12	 ; (530 <toggle_red_led+0x10>) ;
LSLS(r3, r3, 11);// 524:	02db      	lsls	r3, r3, #11 ;
LDR(r1, r2, 12);// 526:	68d1      	ldr	r1, r2, #12 ;
ORRS(r3, r1);// 528:	430b      	orrs	r3, r1 ;
STR(r3, r2, 12);// 52a:	60d3      	str	r3, r2, #12 ;
BX(lr);// 52c:	4770      	bx	lr ;
//Could not parse:  52e:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  530:	400ff040 	.word	0x400ff040 ;
}
void turn_on_blue_led() 
{MOVS(r3, 2);// 534:	2302      	movs	r3, #2 ;
LDR(r2, "pc", 8);// 536:	4a02      	ldr	r2, pc, #8	 ; (540 <turn_on_blue_led+0xc>) ;
LDR(r1, r2, 8);// 538:	6891      	ldr	r1, r2, #8 ;
ORRS(r3, r1);// 53a:	430b      	orrs	r3, r1 ;
STR(r3, r2, 8);// 53c:	6093      	str	r3, r2, #8 ;
BX(lr);// 53e:	4770      	bx	lr ;
//Could not parse:  540:	400ff0c0 	.word	0x400ff0c0 ;
}
void turn_off_blue_led() 
{MOVS(r3, 2);// 544:	2302      	movs	r3, #2 ;
LDR(r2, "pc", 8);// 546:	4a02      	ldr	r2, pc, #8	 ; (550 <turn_off_blue_led+0xc>) ;
LDR(r1, r2, 4);// 548:	6851      	ldr	r1, r2, #4 ;
ORRS(r3, r1);// 54a:	430b      	orrs	r3, r1 ;
STR(r3, r2, 4);// 54c:	6053      	str	r3, r2, #4 ;
BX(lr);// 54e:	4770      	bx	lr ;
//Could not parse:  550:	400ff0c0 	.word	0x400ff0c0 ;
}
void toggle_blue_led() 
{MOVS(r3, 128);// 554:	2380      	movs	r3, #128	 ; 0x80 ;
LDR(r2, "pc", 12);// 556:	4a03      	ldr	r2, pc, #12	 ; (564 <toggle_blue_led+0x10>) ;
LSLS(r3, r3, 11);// 558:	02db      	lsls	r3, r3, #11 ;
LDR(r1, r2, 12);// 55a:	68d1      	ldr	r1, r2, #12 ;
ORRS(r3, r1);// 55c:	430b      	orrs	r3, r1 ;
STR(r3, r2, 12);// 55e:	60d3      	str	r3, r2, #12 ;
BX(lr);// 560:	4770      	bx	lr ;
//Could not parse:  562:	46c0      	nop			 ; (mov r8, r8) ;
//Could not parse:  564:	400ff0c0 	.word	0x400ff0c0 ;
}
void set_rgbled_color_to() 
{PUSH(r4, lr);// 568:	b510      	push	r4, lr ;
CMP(r0, 0);// 56a:	2800      	cmp	r0, #0 ;
BNE.N("57c", <set_rgbled_color_to+0x14>);// 56c:	d106      	bne.n	57c <set_rgbled_color_to+0x14> ;
BL("544", <turn_off_blue_led>);// 56e:	f7ff ffe9 	bl	544 <turn_off_blue_led> ;
BL("4d0", <turn_off_green_led>);// 572:	f7ff ffad 	bl	4d0 <turn_off_green_led> ;
BL("50c", <turn_off_red_led>);// 576:	f7ff ffc9 	bl	50c <turn_off_red_led> ;
//Could not parse:  57a:	bd10      	pop	r4, pc ;
CMP(r0, 1);// 57c:	2801      	cmp	r0, #1 ;
BNE.N("586", <set_rgbled_color_to+0x1e>);// 57e:	d102      	bne.n	586 <set_rgbled_color_to+0x1e> ;
BL("534", <turn_on_blue_led>);// 580:	f7ff ffd8 	bl	534 <turn_on_blue_led> ;
B.N("572", <set_rgbled_color_to+0xa>);// 584:	e7f5      	b.n	572 <set_rgbled_color_to+0xa> ;
CMP(r0, 2);// 586:	2802      	cmp	r0, #2 ;
BNE.N("594", <set_rgbled_color_to+0x2c>);// 588:	d104      	bne.n	594 <set_rgbled_color_to+0x2c> ;
BL("544", <turn_off_blue_led>);// 58a:	f7ff ffdb 	bl	544 <turn_off_blue_led> ;
BL("4bc", <turn_on_green_led>);// 58e:	f7ff ff95 	bl	4bc <turn_on_green_led> ;
B.N("576", <set_rgbled_color_to+0xe>);// 592:	e7f0      	b.n	576 <set_rgbled_color_to+0xe> ;
CMP(r0, 3);// 594:	2803      	cmp	r0, #3 ;
BNE.N("59e", <set_rgbled_color_to+0x36>);// 596:	d102      	bne.n	59e <set_rgbled_color_to+0x36> ;
BL("534", <turn_on_blue_led>);// 598:	f7ff ffcc 	bl	534 <turn_on_blue_led> ;
B.N("58e", <set_rgbled_color_to+0x26>);// 59c:	e7f7      	b.n	58e <set_rgbled_color_to+0x26> ;
CMP(r0, 4);// 59e:	2804      	cmp	r0, #4 ;
BNE.N("5b0", <set_rgbled_color_to+0x48>);// 5a0:	d106      	bne.n	5b0 <set_rgbled_color_to+0x48> ;
BL("544", <turn_off_blue_led>);// 5a2:	f7ff ffcf 	bl	544 <turn_off_blue_led> ;
BL("4d0", <turn_off_green_led>);// 5a6:	f7ff ff93 	bl	4d0 <turn_off_green_led> ;
BL("4f8", <turn_on_red_led>);// 5aa:	f7ff ffa5 	bl	4f8 <turn_on_red_led> ;
B.N("57a", <set_rgbled_color_to+0x12>);// 5ae:	e7e4      	b.n	57a <set_rgbled_color_to+0x12> ;
CMP(r0, 5);// 5b0:	2805      	cmp	r0, #5 ;
BNE.N("5ba", <set_rgbled_color_to+0x52>);// 5b2:	d102      	bne.n	5ba <set_rgbled_color_to+0x52> ;
BL("534", <turn_on_blue_led>);// 5b4:	f7ff ffbe 	bl	534 <turn_on_blue_led> ;
B.N("5a6", <set_rgbled_color_to+0x3e>);// 5b8:	e7f5      	b.n	5a6 <set_rgbled_color_to+0x3e> ;
CMP(r0, 6);// 5ba:	2806      	cmp	r0, #6 ;
BNE.N("5c8", <set_rgbled_color_to+0x60>);// 5bc:	d104      	bne.n	5c8 <set_rgbled_color_to+0x60> ;
BL("544", <turn_off_blue_led>);// 5be:	f7ff ffc1 	bl	544 <turn_off_blue_led> ;
BL("4bc", <turn_on_green_led>);// 5c2:	f7ff ff7b 	bl	4bc <turn_on_green_led> ;
B.N("5aa", <set_rgbled_color_to+0x42>);// 5c6:	e7f0      	b.n	5aa <set_rgbled_color_to+0x42> ;
BL("534", <turn_on_blue_led>);// 5c8:	f7ff ffb4 	bl	534 <turn_on_blue_led> ;
B.N("5c2", <set_rgbled_color_to+0x5a>);// 5cc:	e7f9      	b.n	5c2 <set_rgbled_color_to+0x5a> ;
}