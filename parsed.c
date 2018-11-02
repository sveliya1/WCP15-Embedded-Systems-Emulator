
// could not parse: assignment1.out:     file format elf32-littlearm



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
// could not parse:   c0:	e7fe      	b.n	c0 <Default_Handler>


Label: HardFault_Handler:
// could not parse:   c2:	e7fe      	b.n	c2 <HardFault_Handler>


Label: _stop_init:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:   ca:	0189      	lsls	r1, r1, #6

Rd = (address)//Rd = (address)
// could not parse:   ce:	b530      	push	{r4, r5, lr}

// could not parse:   d0:	4301      	orrs	r1, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:   da:	4020      	ands	r0, r4

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:   e2:	0040      	lsls	r0, r0, #1

// could not parse:   e4:	4320      	orrs	r0, r4

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:   ee:	4385      	bics	r5, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
// could not parse:   f4:	4305      	orrs	r5, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
CPSR flags = Rn AND Op2//CPSR flags = Rn AND Op2
// could not parse:   fc:	d0fc      	beq.n	f8 <_stop_init+0x34>

Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  102:	4001      	ands	r1, r0

<address> = Rd//<address> = Rd
// could not parse:  106:	bd30      	pop	{r4, r5, pc}

// could not parse:  108:	40047000 	.word	0x40047000

// could not parse:  10c:	00001038 	.word	0x00001038

// could not parse:  110:	4004d000 	.word	0x4004d000

// could not parse:  114:	fffff8ff 	.word	0xfffff8ff

// could not parse:  118:	400ff100 	.word	0x400ff100

// could not parse:  11c:	ffffdfff 	.word	0xffffdfff


Label: _reset_init:
// could not parse:  120:	f7ff ffd0 	bl	c4 <_stop_init>

Rd = Op2//Rd = Op2
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  12a:	0152      	lsls	r2, r2, #5

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  138:	0092      	lsls	r2, r2, #2

Rd = (address)//Rd = (address)
// could not parse:  13c:	4322      	orrs	r2, r4

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  14a:	4002      	ands	r2, r0

Rd = Op2//Rd = Op2
<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
// could not parse:  152:	0240      	lsls	r0, r0, #9

Rd = (address)//Rd = (address)
// could not parse:  156:	4320      	orrs	r0, r4

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  15e:	4004      	ands	r4, r0

Rd = Op2//Rd = Op2
// could not parse:  162:	0440      	lsls	r0, r0, #17

// could not parse:  164:	4320      	orrs	r0, r4

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  16e:	4020      	ands	r0, r4

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = Op2//Rd = Op2
// could not parse:  176:	4022      	ands	r2, r4

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  180:	7018      	strb	r0, [r3, #0]

Rd = (address)//Rd = (address)
// could not parse:  184:	705a      	strb	r2, [r3, #1]

// could not parse:  186:	3274      	adds	r2, #116	; 0x74

// could not parse:  188:	701a      	strb	r2, [r3, #0]

// could not parse:  18a:	78da      	ldrb	r2, [r3, #3]

// could not parse:  18c:	4022      	ands	r2, r4

// could not parse:  18e:	70da      	strb	r2, [r3, #3]

Rd = Op2//Rd = Op2
// could not parse:  192:	7119      	strb	r1, [r3, #4]

// could not parse:  194:	7158      	strb	r0, [r3, #5]

// could not parse:  196:	7999      	ldrb	r1, [r3, #6]

CPSR flags = Rn AND Op2//CPSR flags = Rn AND Op2
// could not parse:  19a:	d1fc      	bne.n	196 <_reset_init+0x76>

Rd = Op2//Rd = Op2
// could not parse:  19e:	799a      	ldrb	r2, [r3, #6]

// could not parse:  1a0:	400a      	ands	r2, r1

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  1a4:	d1fb      	bne.n	19e <_reset_init+0x7e>

// could not parse:  1a6:	3238      	adds	r2, #56	; 0x38

// could not parse:  1a8:	715a      	strb	r2, [r3, #5]

// could not parse:  1aa:	7999      	ldrb	r1, [r3, #6]

CPSR flags = Rn AND Op2//CPSR flags = Rn AND Op2
// could not parse:  1ae:	d0fc      	beq.n	1aa <_reset_init+0x8a>

Rd = Op2//Rd = Op2
Rd = Op2//Rd = Op2
// could not parse:  1b4:	701a      	strb	r2, [r3, #0]

// could not parse:  1b6:	799a      	ldrb	r2, [r3, #6]

// could not parse:  1b8:	400a      	ands	r2, r1

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  1bc:	d1fb      	bne.n	1b6 <_reset_init+0x96>

Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  1c6:	1813      	adds	r3, r2, r0

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  1ca:	d905      	bls.n	1d8 <_reset_init+0xb8>

Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  1d2:	d905      	bls.n	1e0 <_reset_init+0xc0>

// could not parse:  1d4:	f000 f91c 	bl	410 <main>

Rd = (address)//Rd = (address)
// could not parse:  1da:	3204      	adds	r2, #4

<address> = Rd//<address> = Rd
// could not parse:  1de:	e7f2      	b.n	1c6 <_reset_init+0xa6>

// could not parse:  1e0:	c302      	stmia	r3!, {r1}

// could not parse:  1e2:	e7f5      	b.n	1d0 <_reset_init+0xb0>

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

// could not parse:  220:	00000678 	.word	0x00000678

// could not parse:  224:	1ffff000 	.word	0x1ffff000


Label: __startup_end:

Label: _cfm:
// could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ............~...


Label: main:
// could not parse:  410:	b510      	push	{r4, lr}

// could not parse:  412:	f000 f903 	bl	61c <configure_sw1>

// could not parse:  416:	f000 f8ab 	bl	570 <initialize_rgbled>

// could not parse:  41a:	f000 f8f5 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  420:	f000 f878 	bl	514 <set_rgbled_color_to>

// could not parse:  424:	f000 f8f0 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  42a:	f000 f873 	bl	514 <set_rgbled_color_to>

// could not parse:  42e:	f000 f8eb 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  434:	f000 f86e 	bl	514 <set_rgbled_color_to>

// could not parse:  438:	f000 f8e6 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  43e:	f000 f869 	bl	514 <set_rgbled_color_to>

// could not parse:  442:	f000 f8e1 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  448:	f000 f864 	bl	514 <set_rgbled_color_to>

// could not parse:  44c:	f000 f8dc 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  452:	f000 f85f 	bl	514 <set_rgbled_color_to>

// could not parse:  456:	f000 f8d7 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  45c:	f000 f85a 	bl	514 <set_rgbled_color_to>

// could not parse:  460:	f000 f8d2 	bl	608 <wait_for_sw1_pressed_and_released>

Rd = Op2//Rd = Op2
// could not parse:  466:	f000 f855 	bl	514 <set_rgbled_color_to>

// could not parse:  46a:	e7d6      	b.n	41a <main+0xa>


Label: toggle_green_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  470:	031b      	lsls	r3, r3, #12

Rd = (address)//Rd = (address)
// could not parse:  474:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  47a:	46c0      	nop			; (mov r8, r8)

// could not parse:  47c:	400ff040 	.word	0x400ff040


Label: turn_on_green_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  484:	031b      	lsls	r3, r3, #12

Rd = (address)//Rd = (address)
// could not parse:  488:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  48e:	46c0      	nop			; (mov r8, r8)

// could not parse:  490:	400ff040 	.word	0x400ff040


Label: turn_off_green_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  498:	031b      	lsls	r3, r3, #12

Rd = (address)//Rd = (address)
// could not parse:  49c:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  4a2:	46c0      	nop			; (mov r8, r8)

// could not parse:  4a4:	400ff040 	.word	0x400ff040


Label: toggle_red_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  4ac:	02db      	lsls	r3, r3, #11

Rd = (address)//Rd = (address)
// could not parse:  4b0:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  4b6:	46c0      	nop			; (mov r8, r8)

// could not parse:  4b8:	400ff040 	.word	0x400ff040


Label: turn_on_red_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  4c0:	02db      	lsls	r3, r3, #11

Rd = (address)//Rd = (address)
// could not parse:  4c4:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  4ca:	46c0      	nop			; (mov r8, r8)

// could not parse:  4cc:	400ff040 	.word	0x400ff040


Label: turn_off_red_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  4d4:	02db      	lsls	r3, r3, #11

Rd = (address)//Rd = (address)
// could not parse:  4d8:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  4de:	46c0      	nop			; (mov r8, r8)

// could not parse:  4e0:	400ff040 	.word	0x400ff040


Label: toggle_blue_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  4ea:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  4f0:	400ff0c0 	.word	0x400ff0c0


Label: turn_on_blue_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  4fa:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  500:	400ff0c0 	.word	0x400ff0c0


Label: turn_off_blue_led:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  50a:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  510:	400ff0c0 	.word	0x400ff0c0


Label: set_rgbled_color_to:
// could not parse:  514:	b510      	push	{r4, lr}

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  518:	d80b      	bhi.n	532 <set_rgbled_color_to+0x1e>

// could not parse:  51a:	f000 f8a3 	bl	664 <__gnu_thumb1_case_uqi>

// could not parse:  51e:	0b04      	.short	0x0b04

// could not parse:  520:	1d16130e 	.word	0x1d16130e

// could not parse:  524:	2520      	.short	0x2520

// could not parse:  526:	f7ff ffed 	bl	504 <turn_off_blue_led>

// could not parse:  52a:	f7ff ffb3 	bl	494 <turn_off_green_led>

// could not parse:  52e:	f7ff ffcf 	bl	4d0 <turn_off_red_led>

// could not parse:  532:	bd10      	pop	{r4, pc}

// could not parse:  534:	f7ff ffde 	bl	4f4 <turn_on_blue_led>

// could not parse:  538:	e7f7      	b.n	52a <set_rgbled_color_to+0x16>

// could not parse:  53a:	f7ff ffe3 	bl	504 <turn_off_blue_led>

// could not parse:  53e:	f7ff ff9f 	bl	480 <turn_on_green_led>

// could not parse:  542:	e7f4      	b.n	52e <set_rgbled_color_to+0x1a>

// could not parse:  544:	f7ff ffd6 	bl	4f4 <turn_on_blue_led>

// could not parse:  548:	e7f9      	b.n	53e <set_rgbled_color_to+0x2a>

// could not parse:  54a:	f7ff ffdb 	bl	504 <turn_off_blue_led>

// could not parse:  54e:	f7ff ffa1 	bl	494 <turn_off_green_led>

// could not parse:  552:	f7ff ffb3 	bl	4bc <turn_on_red_led>

// could not parse:  556:	e7ec      	b.n	532 <set_rgbled_color_to+0x1e>

// could not parse:  558:	f7ff ffcc 	bl	4f4 <turn_on_blue_led>

// could not parse:  55c:	e7f7      	b.n	54e <set_rgbled_color_to+0x3a>

// could not parse:  55e:	f7ff ffd1 	bl	504 <turn_off_blue_led>

// could not parse:  562:	f7ff ff8d 	bl	480 <turn_on_green_led>

// could not parse:  566:	e7f4      	b.n	552 <set_rgbled_color_to+0x3e>

// could not parse:  568:	f7ff ffc4 	bl	4f4 <turn_on_blue_led>

// could not parse:  56c:	e7f9      	b.n	562 <set_rgbled_color_to+0x4e>


Label: initialize_rgbled:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  576:	015b      	lsls	r3, r3, #5

Rd = (address)//Rd = (address)
// could not parse:  57a:	b510      	push	{r4, lr}

// could not parse:  57c:	4303      	orrs	r3, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  586:	4002      	ands	r2, r0

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  58e:	0052      	lsls	r2, r2, #1

// could not parse:  590:	4311      	orrs	r1, r2

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
// could not parse:  596:	4001      	ands	r1, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
// could not parse:  59c:	4311      	orrs	r1, r2

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  5a4:	4001      	ands	r1, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = Op2//Rd = Op2
// could not parse:  5ac:	430a      	orrs	r2, r1

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  5b4:	031b      	lsls	r3, r3, #12

Rd = (address)//Rd = (address)
// could not parse:  5b8:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  5c2:	430b      	orrs	r3, r1

<address> = Rd//<address> = Rd
// could not parse:  5c6:	f7ff ffa5 	bl	514 <set_rgbled_color_to>

// could not parse:  5ca:	bd10      	pop	{r4, pc}

// could not parse:  5cc:	40047000 	.word	0x40047000

// could not parse:  5d0:	00001038 	.word	0x00001038

// could not parse:  5d4:	4004a000 	.word	0x4004a000

// could not parse:  5d8:	fffff8ff 	.word	0xfffff8ff

// could not parse:  5dc:	4004c000 	.word	0x4004c000

// could not parse:  5e0:	400ff040 	.word	0x400ff040

// could not parse:  5e4:	400ff0c0 	.word	0x400ff0c0


Label: sw1_is_pressed:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  5ee:	0d1b      	lsrs	r3, r3, #20

// could not parse:  5f0:	4398      	bics	r0, r3

R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  5f4:	400ff000 	.word	0x400ff000


Label: sw1_is_not_pressed:
// could not parse:  5f8:	b510      	push	{r4, lr}

// could not parse:  5fa:	f7ff fff5 	bl	5e8 <sw1_is_pressed>

Rd = Op2//Rd = Op2
Rd = Op2//Rd = Op2
// could not parse:  602:	4058      	eors	r0, r3

// could not parse:  604:	b2c0      	uxtb	r0, r0

// could not parse:  606:	bd10      	pop	{r4, pc}


Label: wait_for_sw1_pressed_and_released:
// could not parse:  608:	b510      	push	{r4, lr}

// could not parse:  60a:	f7ff ffed 	bl	5e8 <sw1_is_pressed>

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  610:	d1fb      	bne.n	60a <wait_for_sw1_pressed_and_released+0x2>

// could not parse:  612:	f7ff fff1 	bl	5f8 <sw1_is_not_pressed>

CPSR flags = Rn - Op2//CPSR flags = Rn - Op2
// could not parse:  618:	d1fb      	bne.n	612 <wait_for_sw1_pressed_and_released+0xa>

// could not parse:  61a:	bd10      	pop	{r4, pc}


Label: configure_sw1:
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  622:	009b      	lsls	r3, r3, #2

Rd = (address)//Rd = (address)
// could not parse:  626:	4303      	orrs	r3, r0

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  630:	400a      	ands	r2, r1

<address> = Rd//<address> = Rd
Rd = Op2//Rd = Op2
Rd = (address)//Rd = (address)
// could not parse:  638:	0052      	lsls	r2, r2, #1

// could not parse:  63a:	430a      	orrs	r2, r1

<address> = Rd//<address> = Rd
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
Rd = (address)//Rd = (address)
// could not parse:  644:	400b      	ands	r3, r1

<address> = Rd//<address> = Rd
R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  64a:	46c0      	nop			; (mov r8, r8)

// could not parse:  64c:	40047000 	.word	0x40047000

// could not parse:  650:	00001038 	.word	0x00001038

// could not parse:  654:	40049000 	.word	0x40049000

// could not parse:  658:	fffff8ff 	.word	0xfffff8ff

// could not parse:  65c:	400ff000 	.word	0x400ff000

// could not parse:  660:	ffefffff 	.word	0xffefffff


Label: __gnu_thumb1_case_uqi:
// could not parse:  664:	b402      	push	{r1}

// could not parse:  666:	4671      	mov	r1, lr

// could not parse:  668:	0849      	lsrs	r1, r1, #1

// could not parse:  66a:	0049      	lsls	r1, r1, #1

// could not parse:  66c:	5c09      	ldrb	r1, [r1, r0]

// could not parse:  66e:	0049      	lsls	r1, r1, #1

Rd = Rn + Op2//Rd = Rn + Op2
// could not parse:  672:	bc02      	pop	{r1}

R15 = Rn 
 T bit = Rn[0]//R15 = Rn 
 T bit = Rn[0]
// could not parse:  676:	46c0      	nop			; (mov r8, r8)

