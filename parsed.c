#include <stdint.h>
uint8_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16;
int result = 0;
int Memory[2048];
void main(){
goto main;
// could not parse: timing_demo.out:     file format elf32-littlearm


// could not parse: Disassembly of section .text:

Label: InterruptVector:
// could not parse:    0:	00 30 00 20 21 01 00 00 c1 00 00 00 c3 00 00 00     .0. !...........
// could not parse:   10:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   20:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   30:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   40:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   50:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   60:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   70:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   80:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   90:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   a0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................
// could not parse:   b0:	c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00     ................

Label: Default_Handler:
	goto c0 ; //  c0:	e7fe      	b.n	c0 <Default_Handler>

Label: HardFault_Handler:
	goto c2 ; //  c2:	e7fe      	b.n	c2 <HardFault_Handler>

Label: _stop_init:
	r1 = 128 ; result = r1 ; //  c4:	2180      	movs	r1, #128	; 0x80
	r2 = Memory[ (r2+198+0) /8 ] ; //  c6:	4a10      	ldr	r2, [pc, #64]	; (108 <_stop_init+0x44>)
	r3 = Memory[ (r3+200+0) /8 ] ; //  c8:	4b10      	ldr	r3, [pc, #64]	; (10c <_stop_init+0x48>)
	r1 = r1 << 6 ; //  ca:	0189      	lsls	r1, r1, #6
	r0 = Memory[ (r0+r2+0) /8 ] ; //  cc:	58d0      	ldr	r0, [r2, r3]
	//stack manipulation (Push) ; //  ce:	b530      	push	{r4, r5, lr}
	r1 = r1 | r0 ; result = r1 ; //  d0:	4301      	orrs	r1, r0
	Memory[ d2 ] = r1 ; //  d2:	50d1      	str	r1, [r2, r3]
	r1 = Memory[ (r1+212+0) /8 ] ; //  d4:	490e      	ldr	r1, [pc, #56]	; (110 <_stop_init+0x4c>)
	r4 = Memory[ (r4+214+0) /8 ] ; //  d6:	4c0f      	ldr	r4, [pc, #60]	; (114 <_stop_init+0x50>)
	r0 = Memory[ (r0+r1+0) /8 ] ; //  d8:	6848      	ldr	r0, [r1, #4]
	r0 = r0 & r4 ; result = r0 ; //  da:	4020      	ands	r0, r4
	Memory[ dc ] = r0 ; //  dc:	6048      	str	r0, [r1, #4]
	r0 = 128 ; result = r0 ; //  de:	2080      	movs	r0, #128	; 0x80
	r4 = Memory[ (r4+r1+0) /8 ] ; //  e0:	684c      	ldr	r4, [r1, #4]
	r0 = r0 << 1 ; //  e2:	0040      	lsls	r0, r0, #1
	r0 = r0 | r4 ; result = r0 ; //  e4:	4320      	orrs	r0, r4
	Memory[ e6 ] = r0 ; //  e6:	6048      	str	r0, [r1, #4]
	r0 = 2 ; result = r0 ; //  e8:	2002      	movs	r0, #2
	r4 = Memory[ (r4+234+0) /8 ] ; //  ea:	4c0b      	ldr	r4, [pc, #44]	; (118 <_stop_init+0x54>)
	r5 = Memory[ (r5+r4+0) /8 ] ; //  ec:	6965      	ldr	r5, [r4, #20]
// could not parse:   ee:	4385      	bics	r5, r0
	Memory[ f0 ] = r5 ; //  f0:	6165      	str	r5, [r4, #20]
	r5 = Memory[ (r5+r1+0) /8 ] ; //  f2:	684d      	ldr	r5, [r1, #4]
	r5 = r5 | r0 ; result = r5 ; //  f4:	4305      	orrs	r5, r0
	Memory[ f6 ] = r5 ; //  f6:	604d      	str	r5, [r1, #4]
	r1 = Memory[ (r1+r4+0) /8 ] ; //  f8:	6921      	ldr	r1, [r4, #16]
	result = r1 & r0 ; //  fa:	4201      	tst	r1, r0
	if(result == 0){ goto f8 ; } //  fc:	d0fc      	beq.n	f8 <_stop_init+0x34>
	r1 = Memory[ (r1+r2+0) /8 ] ; //  fe:	58d1      	ldr	r1, [r2, r3]
	r0 = Memory[ (r0+256+0) /8 ] ; // 100:	4806      	ldr	r0, [pc, #24]	; (11c <_stop_init+0x58>)
	r1 = r1 & r0 ; result = r1 ; // 102:	4001      	ands	r1, r0
	Memory[ 104 ] = r1 ; // 104:	50d1      	str	r1, [r2, r3]
// could not parse:  106:	bd30      	pop	{r4, r5, pc}
// could not parse:  108:	40047000 	.word	0x40047000
// could not parse:  10c:	00001038 	.word	0x00001038
// could not parse:  110:	4004d000 	.word	0x4004d000
// could not parse:  114:	fffff8ff 	.word	0xfffff8ff
// could not parse:  118:	400ff100 	.word	0x400ff100
// could not parse:  11c:	ffffdfff 	.word	0xffffdfff

Label: _reset_init:
	goto c4 ; //TODO linking // 120:	f7ff ffd0 	bl	c4 <_stop_init>
	r2 = 136 ; result = r2 ; // 124:	2288      	movs	r2, #136	; 0x88
	r1 = 1 ; result = r1 ; // 126:	2101      	movs	r1, #1
	r3 = Memory[ (r3+296+0) /8 ] ; // 128:	4b2e      	ldr	r3, [pc, #184]	; (1e4 <_reset_init+0xc4>)
	r2 = r2 << 5 ; // 12a:	0152      	lsls	r2, r2, #5
	Memory[ 12c ] = r1 ; // 12c:	5099      	str	r1, [r3, r2]
	r0 = Memory[ (r0+302+0) /8 ] ; // 12e:	482e      	ldr	r0, [pc, #184]	; (1e8 <_reset_init+0xc8>)
	r2 = Memory[ (r2+304+0) /8 ] ; // 130:	4a2e      	ldr	r2, [pc, #184]	; (1ec <_reset_init+0xcc>)
	Memory[ 132 ] = r0 ; // 132:	6090      	str	r0, [r2, #8]
	r2 = 128 ; result = r2 ; // 134:	2280      	movs	r2, #128	; 0x80
	r0 = Memory[ (r0+310+0) /8 ] ; // 136:	482e      	ldr	r0, [pc, #184]	; (1f0 <_reset_init+0xd0>)
	r2 = r2 << 2 ; // 138:	0092      	lsls	r2, r2, #2
	r4 = Memory[ (r4+r3+0) /8 ] ; // 13a:	581c      	ldr	r4, [r3, r0]
	r2 = r2 | r4 ; result = r2 ; // 13c:	4322      	orrs	r2, r4
	Memory[ 13e ] = r2 ; // 13e:	501a      	str	r2, [r3, r0]
	r0 = Memory[ (r0+320+0) /8 ] ; // 140:	482c      	ldr	r0, [pc, #176]	; (1f4 <_reset_init+0xd4>)
	r2 = Memory[ (r2+322+0) /8 ] ; // 142:	4a2d      	ldr	r2, [pc, #180]	; (1f8 <_reset_init+0xd8>)
	Memory[ 144 ] = r0 ; // 144:	5098      	str	r0, [r3, r2]
	r2 = Memory[ (r2+r3+0) /8 ] ; // 146:	681a      	ldr	r2, [r3, #0]
	r0 = Memory[ (r0+328+0) /8 ] ; // 148:	482c      	ldr	r0, [pc, #176]	; (1fc <_reset_init+0xdc>)
	r2 = r2 & r0 ; result = r2 ; // 14a:	4002      	ands	r2, r0
	r0 = 128 ; result = r0 ; // 14c:	2080      	movs	r0, #128	; 0x80
	Memory[ 14e ] = r2 ; // 14e:	601a      	str	r2, [r3, #0]
	r2 = Memory[ (r2+336+0) /8 ] ; // 150:	4a2b      	ldr	r2, [pc, #172]	; (200 <_reset_init+0xe0>)
	r0 = r0 << 9 ; // 152:	0240      	lsls	r0, r0, #9
	r4 = Memory[ (r4+r3+0) /8 ] ; // 154:	589c      	ldr	r4, [r3, r2]
	r0 = r0 | r4 ; result = r0 ; // 156:	4320      	orrs	r0, r4
	Memory[ 158 ] = r0 ; // 158:	5098      	str	r0, [r3, r2]
	r0 = Memory[ (r0+r3+0) /8 ] ; // 15a:	5898      	ldr	r0, [r3, r2]
	r4 = Memory[ (r4+348+0) /8 ] ; // 15c:	4c29      	ldr	r4, [pc, #164]	; (204 <_reset_init+0xe4>)
	r4 = r4 & r0 ; result = r4 ; // 15e:	4004      	ands	r4, r0
	r0 = 128 ; result = r0 ; // 160:	2080      	movs	r0, #128	; 0x80
	r0 = r0 << 17 ; // 162:	0440      	lsls	r0, r0, #17
	r0 = r0 | r4 ; result = r0 ; // 164:	4320      	orrs	r0, r4
	Memory[ 166 ] = r0 ; // 166:	5098      	str	r0, [r3, r2]
	r3 = Memory[ (r3+360+0) /8 ] ; // 168:	4b27      	ldr	r3, [pc, #156]	; (208 <_reset_init+0xe8>)
	r4 = Memory[ (r4+362+0) /8 ] ; // 16a:	4c28      	ldr	r4, [pc, #160]	; (20c <_reset_init+0xec>)
	r0 = Memory[ (r0+r3+0) /8 ] ; // 16c:	6c98      	ldr	r0, [r3, #72]	; 0x48
	r0 = r0 & r4 ; result = r0 ; // 16e:	4020      	ands	r0, r4
	Memory[ 170 ] = r0 ; // 170:	6498      	str	r0, [r3, #72]	; 0x48
	r2 = Memory[ (r2+r3+0) /8 ] ; // 172:	6cda      	ldr	r2, [r3, #76]	; 0x4c
	r0 = 0 ; result = r0 ; // 174:	2000      	movs	r0, #0
	r2 = r2 & r4 ; result = r2 ; // 176:	4022      	ands	r2, r4
	Memory[ 178 ] = r2 ; // 178:	64da      	str	r2, [r3, #76]	; 0x4c
	r2 = 36 ; result = r2 ; // 17a:	2224      	movs	r2, #36	; 0x24
	r4 = 31 ; result = r4 ; // 17c:	241f      	movs	r4, #31
	r3 = Memory[ (r3+382+0) /8 ] ; // 17e:	4b24      	ldr	r3, [pc, #144]	; (210 <_reset_init+0xf0>)
// could not parse:  180:	7018      	strb	r0, [r3, #0]
	r3 = Memory[ (r3+386+0) /8 ] ; // 182:	4b24      	ldr	r3, [pc, #144]	; (214 <_reset_init+0xf4>)
// could not parse:  184:	705a      	strb	r2, [r3, #1]
	r2 = r2 + 116 ; result = r2 ; // 186:	3274      	adds	r2, #116	; 0x74
// could not parse:  188:	701a      	strb	r2, [r3, #0]
// could not parse:  18a:	78da      	ldrb	r2, [r3, #3]
	r2 = r2 & r4 ; result = r2 ; // 18c:	4022      	ands	r2, r4
// could not parse:  18e:	70da      	strb	r2, [r3, #3]
	r2 = 16 ; result = r2 ; // 190:	2210      	movs	r2, #16
// could not parse:  192:	7119      	strb	r1, [r3, #4]
// could not parse:  194:	7158      	strb	r0, [r3, #5]
// could not parse:  196:	7999      	ldrb	r1, [r3, #6]
	result = r1 & r2 ; // 198:	4211      	tst	r1, r2
	if(result != 0){ goto 196 ;} // 19a:	d1fc      	bne.n	196 <_reset_init+0x76>
	r1 = 12 ; result = r1 ; // 19c:	210c      	movs	r1, #12
// could not parse:  19e:	799a      	ldrb	r2, [r3, #6]
	r2 = r2 & r1 ; result = r2 ; // 1a0:	400a      	ands	r2, r1
	result = r2 - 8 // 1a2:	2a08      	cmp	r2, #8
	if(result != 0){ goto 19e ;} // 1a4:	d1fb      	bne.n	19e <_reset_init+0x7e>
	r2 = r2 + 56 ; result = r2 ; // 1a6:	3238      	adds	r2, #56	; 0x38
// could not parse:  1a8:	715a      	strb	r2, [r3, #5]
// could not parse:  1aa:	7999      	ldrb	r1, [r3, #6]
	result = r1 & r2 ; // 1ac:	4211      	tst	r1, r2
	if(result == 0){ goto 1aa ; } // 1ae:	d0fc      	beq.n	1aa <_reset_init+0x8a>
	r2 = 24 ; result = r2 ; // 1b0:	2218      	movs	r2, #24
	r1 = 12 ; result = r1 ; // 1b2:	210c      	movs	r1, #12
// could not parse:  1b4:	701a      	strb	r2, [r3, #0]
// could not parse:  1b6:	799a      	ldrb	r2, [r3, #6]
	r2 = r2 & r1 ; result = r2 ; // 1b8:	400a      	ands	r2, r1
	result = r2 - 12 // 1ba:	2a0c      	cmp	r2, #12
	if(result != 0){ goto 1b6 ;} // 1bc:	d1fb      	bne.n	1b6 <_reset_init+0x96>
	r2 = 0 ; result = r2 ; // 1be:	2200      	movs	r2, #0
	r0 = Memory[ (r0+448+0) /8 ] ; // 1c0:	4815      	ldr	r0, [pc, #84]	; (218 <_reset_init+0xf8>)
	r1 = Memory[ (r1+450+0) /8 ] ; // 1c2:	4916      	ldr	r1, [pc, #88]	; (21c <_reset_init+0xfc>)
	r4 = Memory[ (r4+452+0) /8 ] ; // 1c4:	4c16      	ldr	r4, [pc, #88]	; (220 <_reset_init+0x100>)
	r3 = r3 + r2 ; result = r3 ; // 1c6:	1813      	adds	r3, r2, r0
	result = r3 - r1 // 1c8:	428b      	cmp	r3, r1
// could not parse:  1ca:	d305      	bcc.n	1d8 <_reset_init+0xb8>
	r1 = 0 ; result = r1 ; // 1cc:	2100      	movs	r1, #0
	r2 = Memory[ (r2+462+0) /8 ] ; // 1ce:	4a15      	ldr	r2, [pc, #84]	; (224 <_reset_init+0x104>)
	result = r3 - r2 // 1d0:	4293      	cmp	r3, r2
// could not parse:  1d2:	d905      	bls.n	1e0 <_reset_init+0xc0>
	goto 42c ; //TODO linking // 1d4:	f000 f92a 	bl	42c <main>
	r5 = Memory[ (r5+r4+0) /8 ] ; // 1d8:	58a5      	ldr	r5, [r4, r2]
	r2 = r2 + 4 ; result = r2 ; // 1da:	3204      	adds	r2, #4
	Memory[ 1dc ] = r5 ; // 1dc:	601d      	str	r5, [r3, #0]
	goto 1c6 ; // 1de:	e7f2      	b.n	1c6 <_reset_init+0xa6>
// could not parse:  1e0:	c302      	stmia	r3!, {r1}
	goto 1d0 ; // 1e2:	e7f5      	b.n	1d0 <_reset_init+0xb0>
// could not parse:  1e4:	40047000 	.word	0x40047000
// could not parse:  1e8:	00000000 	.word	0x00000000
// could not parse:  1ec:	e000ed00 	.word	0xe000ed00
// could not parse:  1f0:	00001038 	.word	0x00001038
// could not parse:  1f4:	10010000 	.word	0x10010000
// could not parse:  1f8:	00001044 	.word	0x00001044
// could not parse:  1fc:	fff3ffff 	.word	0xfff3ffff
// could not parse:  200:	00001004 	.word	0x00001004
// could not parse:  204:	fcffffff 	.word	0xfcffffff
// could not parse:  208:	40049000 	.word	0x40049000
// could not parse:  20c:	fefff8ff 	.word	0xfefff8ff
// could not parse:  210:	40065000 	.word	0x40065000
// could not parse:  214:	40064000 	.word	0x40064000
// could not parse:  218:	1ffff000 	.word	0x1ffff000
// could not parse:  21c:	1ffff000 	.word	0x1ffff000
// could not parse:  220:	000005ce 	.word	0x000005ce
// could not parse:  224:	1ffff000 	.word	0x1ffff000

Label: __startup_end:


Label: _cfm:
// could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ............~...

Label: delay:
	r2 = 250 ; result = r2 ; // 410:	22fa      	movs	r2, #250	; 0xfa
	sp = sp - 8 ; // 412:	b082      	sub	sp, #8
	r2 = r2 << 2 ; // 414:	0092      	lsls	r2, r2, #2
	r0 = r0 - 1 ; result = r0 ; // 416:	3801      	subs	r0, #1
	if(!(result & (1 << 31))){ goto 41e ; } // 418:	d201      	bcs.n	41e <delay+0xe>
	sp = sp + 8 ; // 41a:	b002      	add	sp, #8
	//R15 = lr ; T bit = Rn[0] ; // 41c:	4770      	bx	lr
	Memory[ 41e ] = r2 ; // 41e:	9201      	str	r2, [sp, #4]
	r3 = Memory[ (r3++0) /8 ] ; // 420:	9b01      	ldr	r3, [sp, #4]
	r1 = r1 - r3 ; result = r1 ; // 422:	1e59      	subs	r1, r3, #1
	Memory[ 424 ] = r1 ; // 424:	9101      	str	r1, [sp, #4]
	result = r3 - 0 // 426:	2b00      	cmp	r3, #0
	if(result != 0){ goto 420 ;} // 428:	d1fa      	bne.n	420 <delay+0x10>
	goto 416 ; // 42a:	e7f4      	b.n	416 <delay+0x6>

Label: main:
	//stack manipulation (Push) ; // 42c:	b570      	push	{r4, r5, r6, lr}
	r5 = 250 ; result = r5 ; // 42e:	25fa      	movs	r5, #250	; 0xfa
	goto 44c ; //TODO linking // 430:	f000 f80c 	bl	44c <configure_rgbled>
	r5 = r5 << 5 ; // 434:	016d      	lsls	r5, r5, #5
	r4 = 0 ; result = r4 ; // 436:	2400      	movs	r4, #0
// could not parse:  438:	b2e0      	uxtb	r0, r4
	goto 568 ; //TODO linking // 43a:	f000 f895 	bl	568 <set_rgbled_color_to>
	r4 = r4 + 1 ; result = r4 ; // 43e:	3401      	adds	r4, #1
	r0 = r5 ; result = r0 ; // 440:	0028      	movs	r0, r5
	goto 410 ; //TODO linking // 442:	f7ff ffe5 	bl	410 <delay>
	result = r4 - 8 // 446:	2c08      	cmp	r4, #8
	if(result != 0){ goto 438 ;} // 448:	d1f6      	bne.n	438 <main+0xc>
	goto 436 ; // 44a:	e7f4      	b.n	436 <main+0xa>

Label: configure_rgbled:
	r3 = 160 ; result = r3 ; // 44c:	23a0      	movs	r3, #160	; 0xa0
	r1 = Memory[ (r1+1102+0) /8 ] ; // 44e:	4914      	ldr	r1, [pc, #80]	; (4a0 <configure_rgbled+0x54>)
	r2 = Memory[ (r2+1104+0) /8 ] ; // 450:	4a14      	ldr	r2, [pc, #80]	; (4a4 <configure_rgbled+0x58>)
	r3 = r3 << 5 ; // 452:	015b      	lsls	r3, r3, #5
	r0 = Memory[ (r0+r1+0) /8 ] ; // 454:	5888      	ldr	r0, [r1, r2]
	r3 = r3 | r0 ; result = r3 ; // 456:	4303      	orrs	r3, r0
	Memory[ 458 ] = r3 ; // 458:	508b      	str	r3, [r1, r2]
	r3 = Memory[ (r3+1114+0) /8 ] ; // 45a:	4b13      	ldr	r3, [pc, #76]	; (4a8 <configure_rgbled+0x5c>)
	r0 = Memory[ (r0+1116+0) /8 ] ; // 45c:	4813      	ldr	r0, [pc, #76]	; (4ac <configure_rgbled+0x60>)
	r2 = Memory[ (r2+r3+0) /8 ] ; // 45e:	6c9a      	ldr	r2, [r3, #72]	; 0x48
	r2 = r2 & r0 ; result = r2 ; // 460:	4002      	ands	r2, r0
	Memory[ 462 ] = r2 ; // 462:	649a      	str	r2, [r3, #72]	; 0x48
	r2 = 128 ; result = r2 ; // 464:	2280      	movs	r2, #128	; 0x80
	r1 = Memory[ (r1+r3+0) /8 ] ; // 466:	6c99      	ldr	r1, [r3, #72]	; 0x48
	r2 = r2 << 1 ; // 468:	0052      	lsls	r2, r2, #1
	r1 = r1 | r2 ; result = r1 ; // 46a:	4311      	orrs	r1, r2
	Memory[ 46c ] = r1 ; // 46c:	6499      	str	r1, [r3, #72]	; 0x48
	r1 = Memory[ (r1+r3+0) /8 ] ; // 46e:	6cd9      	ldr	r1, [r3, #76]	; 0x4c
	r1 = r1 & r0 ; result = r1 ; // 470:	4001      	ands	r1, r0
	Memory[ 472 ] = r1 ; // 472:	64d9      	str	r1, [r3, #76]	; 0x4c
	r1 = Memory[ (r1+r3+0) /8 ] ; // 474:	6cd9      	ldr	r1, [r3, #76]	; 0x4c
	r1 = r1 | r2 ; result = r1 ; // 476:	4311      	orrs	r1, r2
	Memory[ 478 ] = r1 ; // 478:	64d9      	str	r1, [r3, #76]	; 0x4c
	r3 = Memory[ (r3+1146+0) /8 ] ; // 47a:	4b0d      	ldr	r3, [pc, #52]	; (4b0 <configure_rgbled+0x64>)
	r1 = Memory[ (r1+r3+0) /8 ] ; // 47c:	6859      	ldr	r1, [r3, #4]
	r1 = r1 & r0 ; result = r1 ; // 47e:	4001      	ands	r1, r0
	Memory[ 480 ] = r1 ; // 480:	6059      	str	r1, [r3, #4]
	r1 = Memory[ (r1+r3+0) /8 ] ; // 482:	6859      	ldr	r1, [r3, #4]
	r2 = r2 | r1 ; result = r2 ; // 484:	430a      	orrs	r2, r1
	Memory[ 486 ] = r2 ; // 486:	605a      	str	r2, [r3, #4]
	r3 = 192 ; result = r3 ; // 488:	23c0      	movs	r3, #192	; 0xc0
	r2 = Memory[ (r2+1162+0) /8 ] ; // 48a:	4a0a      	ldr	r2, [pc, #40]	; (4b4 <configure_rgbled+0x68>)
	r3 = r3 << 12 ; // 48c:	031b      	lsls	r3, r3, #12
	r1 = Memory[ (r1+r2+0) /8 ] ; // 48e:	6951      	ldr	r1, [r2, #20]
	r3 = r3 | r1 ; result = r3 ; // 490:	430b      	orrs	r3, r1
	Memory[ 492 ] = r3 ; // 492:	6153      	str	r3, [r2, #20]
	r3 = 2 ; result = r3 ; // 494:	2302      	movs	r3, #2
	r2 = Memory[ (r2+1174+0) /8 ] ; // 496:	4a08      	ldr	r2, [pc, #32]	; (4b8 <configure_rgbled+0x6c>)
	r1 = Memory[ (r1+r2+0) /8 ] ; // 498:	6951      	ldr	r1, [r2, #20]
	r3 = r3 | r1 ; result = r3 ; // 49a:	430b      	orrs	r3, r1
	Memory[ 49c ] = r3 ; // 49c:	6153      	str	r3, [r2, #20]
	//R15 = lr ; T bit = Rn[0] ; // 49e:	4770      	bx	lr
// could not parse:  4a0:	40047000 	.word	0x40047000
// could not parse:  4a4:	00001038 	.word	0x00001038
// could not parse:  4a8:	4004a000 	.word	0x4004a000
// could not parse:  4ac:	fffff8ff 	.word	0xfffff8ff
// could not parse:  4b0:	4004c000 	.word	0x4004c000
// could not parse:  4b4:	400ff040 	.word	0x400ff040
// could not parse:  4b8:	400ff0c0 	.word	0x400ff0c0

Label: turn_on_green_led:
	r3 = 128 ; result = r3 ; // 4bc:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1214+0) /8 ] ; // 4be:	4a03      	ldr	r2, [pc, #12]	; (4cc <turn_on_green_led+0x10>)
	r3 = r3 << 12 ; // 4c0:	031b      	lsls	r3, r3, #12
	r1 = Memory[ (r1+r2+0) /8 ] ; // 4c2:	6891      	ldr	r1, [r2, #8]
	r3 = r3 | r1 ; result = r3 ; // 4c4:	430b      	orrs	r3, r1
	Memory[ 4c6 ] = r3 ; // 4c6:	6093      	str	r3, [r2, #8]
	//R15 = lr ; T bit = Rn[0] ; // 4c8:	4770      	bx	lr
// could not parse:  4ca:	46c0      	nop			; (mov r8, r8)
// could not parse:  4cc:	400ff040 	.word	0x400ff040

Label: turn_off_green_led:
	r3 = 128 ; result = r3 ; // 4d0:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1234+0) /8 ] ; // 4d2:	4a03      	ldr	r2, [pc, #12]	; (4e0 <turn_off_green_led+0x10>)
	r3 = r3 << 12 ; // 4d4:	031b      	lsls	r3, r3, #12
	r1 = Memory[ (r1+r2+0) /8 ] ; // 4d6:	6851      	ldr	r1, [r2, #4]
	r3 = r3 | r1 ; result = r3 ; // 4d8:	430b      	orrs	r3, r1
	Memory[ 4da ] = r3 ; // 4da:	6053      	str	r3, [r2, #4]
	//R15 = lr ; T bit = Rn[0] ; // 4dc:	4770      	bx	lr
// could not parse:  4de:	46c0      	nop			; (mov r8, r8)
// could not parse:  4e0:	400ff040 	.word	0x400ff040

Label: toggle_green_led:
	r3 = 128 ; result = r3 ; // 4e4:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1254+0) /8 ] ; // 4e6:	4a03      	ldr	r2, [pc, #12]	; (4f4 <toggle_green_led+0x10>)
	r3 = r3 << 12 ; // 4e8:	031b      	lsls	r3, r3, #12
	r1 = Memory[ (r1+r2+0) /8 ] ; // 4ea:	68d1      	ldr	r1, [r2, #12]
	r3 = r3 | r1 ; result = r3 ; // 4ec:	430b      	orrs	r3, r1
	Memory[ 4ee ] = r3 ; // 4ee:	60d3      	str	r3, [r2, #12]
	//R15 = lr ; T bit = Rn[0] ; // 4f0:	4770      	bx	lr
// could not parse:  4f2:	46c0      	nop			; (mov r8, r8)
// could not parse:  4f4:	400ff040 	.word	0x400ff040

Label: turn_on_red_led:
	r3 = 128 ; result = r3 ; // 4f8:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1274+0) /8 ] ; // 4fa:	4a03      	ldr	r2, [pc, #12]	; (508 <turn_on_red_led+0x10>)
	r3 = r3 << 11 ; // 4fc:	02db      	lsls	r3, r3, #11
	r1 = Memory[ (r1+r2+0) /8 ] ; // 4fe:	6891      	ldr	r1, [r2, #8]
	r3 = r3 | r1 ; result = r3 ; // 500:	430b      	orrs	r3, r1
	Memory[ 502 ] = r3 ; // 502:	6093      	str	r3, [r2, #8]
	//R15 = lr ; T bit = Rn[0] ; // 504:	4770      	bx	lr
// could not parse:  506:	46c0      	nop			; (mov r8, r8)
// could not parse:  508:	400ff040 	.word	0x400ff040

Label: turn_off_red_led:
	r3 = 128 ; result = r3 ; // 50c:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1294+0) /8 ] ; // 50e:	4a03      	ldr	r2, [pc, #12]	; (51c <turn_off_red_led+0x10>)
	r3 = r3 << 11 ; // 510:	02db      	lsls	r3, r3, #11
	r1 = Memory[ (r1+r2+0) /8 ] ; // 512:	6851      	ldr	r1, [r2, #4]
	r3 = r3 | r1 ; result = r3 ; // 514:	430b      	orrs	r3, r1
	Memory[ 516 ] = r3 ; // 516:	6053      	str	r3, [r2, #4]
	//R15 = lr ; T bit = Rn[0] ; // 518:	4770      	bx	lr
// could not parse:  51a:	46c0      	nop			; (mov r8, r8)
// could not parse:  51c:	400ff040 	.word	0x400ff040

Label: toggle_red_led:
	r3 = 128 ; result = r3 ; // 520:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1314+0) /8 ] ; // 522:	4a03      	ldr	r2, [pc, #12]	; (530 <toggle_red_led+0x10>)
	r3 = r3 << 11 ; // 524:	02db      	lsls	r3, r3, #11
	r1 = Memory[ (r1+r2+0) /8 ] ; // 526:	68d1      	ldr	r1, [r2, #12]
	r3 = r3 | r1 ; result = r3 ; // 528:	430b      	orrs	r3, r1
	Memory[ 52a ] = r3 ; // 52a:	60d3      	str	r3, [r2, #12]
	//R15 = lr ; T bit = Rn[0] ; // 52c:	4770      	bx	lr
// could not parse:  52e:	46c0      	nop			; (mov r8, r8)
// could not parse:  530:	400ff040 	.word	0x400ff040

Label: turn_on_blue_led:
	r3 = 2 ; result = r3 ; // 534:	2302      	movs	r3, #2
	r2 = Memory[ (r2+1334+0) /8 ] ; // 536:	4a02      	ldr	r2, [pc, #8]	; (540 <turn_on_blue_led+0xc>)
	r1 = Memory[ (r1+r2+0) /8 ] ; // 538:	6891      	ldr	r1, [r2, #8]
	r3 = r3 | r1 ; result = r3 ; // 53a:	430b      	orrs	r3, r1
	Memory[ 53c ] = r3 ; // 53c:	6093      	str	r3, [r2, #8]
	//R15 = lr ; T bit = Rn[0] ; // 53e:	4770      	bx	lr
// could not parse:  540:	400ff0c0 	.word	0x400ff0c0

Label: turn_off_blue_led:
	r3 = 2 ; result = r3 ; // 544:	2302      	movs	r3, #2
	r2 = Memory[ (r2+1350+0) /8 ] ; // 546:	4a02      	ldr	r2, [pc, #8]	; (550 <turn_off_blue_led+0xc>)
	r1 = Memory[ (r1+r2+0) /8 ] ; // 548:	6851      	ldr	r1, [r2, #4]
	r3 = r3 | r1 ; result = r3 ; // 54a:	430b      	orrs	r3, r1
	Memory[ 54c ] = r3 ; // 54c:	6053      	str	r3, [r2, #4]
	//R15 = lr ; T bit = Rn[0] ; // 54e:	4770      	bx	lr
// could not parse:  550:	400ff0c0 	.word	0x400ff0c0

Label: toggle_blue_led:
	r3 = 128 ; result = r3 ; // 554:	2380      	movs	r3, #128	; 0x80
	r2 = Memory[ (r2+1366+0) /8 ] ; // 556:	4a03      	ldr	r2, [pc, #12]	; (564 <toggle_blue_led+0x10>)
	r3 = r3 << 11 ; // 558:	02db      	lsls	r3, r3, #11
	r1 = Memory[ (r1+r2+0) /8 ] ; // 55a:	68d1      	ldr	r1, [r2, #12]
	r3 = r3 | r1 ; result = r3 ; // 55c:	430b      	orrs	r3, r1
	Memory[ 55e ] = r3 ; // 55e:	60d3      	str	r3, [r2, #12]
	//R15 = lr ; T bit = Rn[0] ; // 560:	4770      	bx	lr
// could not parse:  562:	46c0      	nop			; (mov r8, r8)
// could not parse:  564:	400ff0c0 	.word	0x400ff0c0

Label: set_rgbled_color_to:
	//stack manipulation (Push) ; // 568:	b510      	push	{r4, lr}
	result = r0 - 0 // 56a:	2800      	cmp	r0, #0
	if(result != 0){ goto 57c ;} // 56c:	d106      	bne.n	57c <set_rgbled_color_to+0x14>
	goto 544 ; //TODO linking // 56e:	f7ff ffe9 	bl	544 <turn_off_blue_led>
	goto 4d0 ; //TODO linking // 572:	f7ff ffad 	bl	4d0 <turn_off_green_led>
	goto 50c ; //TODO linking // 576:	f7ff ffc9 	bl	50c <turn_off_red_led>
// could not parse:  57a:	bd10      	pop	{r4, pc}
	result = r0 - 1 // 57c:	2801      	cmp	r0, #1
	if(result != 0){ goto 586 ;} // 57e:	d102      	bne.n	586 <set_rgbled_color_to+0x1e>
	goto 534 ; //TODO linking // 580:	f7ff ffd8 	bl	534 <turn_on_blue_led>
	goto 572 ; // 584:	e7f5      	b.n	572 <set_rgbled_color_to+0xa>
	result = r0 - 2 // 586:	2802      	cmp	r0, #2
	if(result != 0){ goto 594 ;} // 588:	d104      	bne.n	594 <set_rgbled_color_to+0x2c>
	goto 544 ; //TODO linking // 58a:	f7ff ffdb 	bl	544 <turn_off_blue_led>
	goto 4bc ; //TODO linking // 58e:	f7ff ff95 	bl	4bc <turn_on_green_led>
	goto 576 ; // 592:	e7f0      	b.n	576 <set_rgbled_color_to+0xe>
	result = r0 - 3 // 594:	2803      	cmp	r0, #3
	if(result != 0){ goto 59e ;} // 596:	d102      	bne.n	59e <set_rgbled_color_to+0x36>
	goto 534 ; //TODO linking // 598:	f7ff ffcc 	bl	534 <turn_on_blue_led>
	goto 58e ; // 59c:	e7f7      	b.n	58e <set_rgbled_color_to+0x26>
	result = r0 - 4 // 59e:	2804      	cmp	r0, #4
	if(result != 0){ goto 5b0 ;} // 5a0:	d106      	bne.n	5b0 <set_rgbled_color_to+0x48>
	goto 544 ; //TODO linking // 5a2:	f7ff ffcf 	bl	544 <turn_off_blue_led>
	goto 4d0 ; //TODO linking // 5a6:	f7ff ff93 	bl	4d0 <turn_off_green_led>
	goto 4f8 ; //TODO linking // 5aa:	f7ff ffa5 	bl	4f8 <turn_on_red_led>
	goto 57a ; // 5ae:	e7e4      	b.n	57a <set_rgbled_color_to+0x12>
	result = r0 - 5 // 5b0:	2805      	cmp	r0, #5
	if(result != 0){ goto 5ba ;} // 5b2:	d102      	bne.n	5ba <set_rgbled_color_to+0x52>
	goto 534 ; //TODO linking // 5b4:	f7ff ffbe 	bl	534 <turn_on_blue_led>
	goto 5a6 ; // 5b8:	e7f5      	b.n	5a6 <set_rgbled_color_to+0x3e>
	result = r0 - 6 // 5ba:	2806      	cmp	r0, #6
	if(result != 0){ goto 5c8 ;} // 5bc:	d104      	bne.n	5c8 <set_rgbled_color_to+0x60>
	goto 544 ; //TODO linking // 5be:	f7ff ffc1 	bl	544 <turn_off_blue_led>
	goto 4bc ; //TODO linking // 5c2:	f7ff ff7b 	bl	4bc <turn_on_green_led>
	goto 5aa ; // 5c6:	e7f0      	b.n	5aa <set_rgbled_color_to+0x42>
	goto 534 ; //TODO linking // 5c8:	f7ff ffb4 	bl	534 <turn_on_blue_led>
	goto 5c2 ; // 5cc:	e7f9      	b.n	5c2 <set_rgbled_color_to+0x5a>
}