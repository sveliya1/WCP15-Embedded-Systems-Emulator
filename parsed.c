
// could not parse: assignment1.out: file format elf32-littlearm


// could not parse: Disassembly of section .text:

Label: InterruptVector:
// could not parse:  0: 00 30 00 20 21 01 00 00 c1 00 00 00 c3 00 00 00 .0. !...........
// could not parse:  10: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  20: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  30: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  40: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  50: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  60: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  70: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  80: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  90: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  a0: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................
// could not parse:  b0: c1 00 00 00 c1 00 00 00 c1 00 00 00 c1 00 00 00 ................

Label: Default_Handler:
// could not parse:  c0: e7fe b.n c0 <Default_Handler>

Label: HardFault_Handler:
// could not parse:  c2: e7fe b.n c2 <HardFault_Handler>

Label: _stop_init:
Rd = Op2// c4: 2180 movs r1, #128 ; 0x80
Rd = (address)// c6: 4a10 ldr r2, [pc, #64] ; (108 <_stop_init+0x44>)
Rd = (address)// c8: 4b10 ldr r3, [pc, #64] ; (10c <_stop_init+0x48>)
// could not parse:  ca: 0189 lsls r1, r1, #6
Rd = (address)// cc: 58d0 ldr r0, [r2, r3]
// could not parse:  ce: b530 push {r4, r5, lr}
// could not parse:  d0: 4301 orrs r1, r0
<address> = Rd// d2: 50d1 str r1, [r2, r3]
Rd = (address)// d4: 490e ldr r1, [pc, #56] ; (110 <_stop_init+0x4c>)
Rd = (address)// d6: 4c0f ldr r4, [pc, #60] ; (114 <_stop_init+0x50>)
Rd = (address)// d8: 6848 ldr r0, [r1, #4]
// could not parse:  da: 4020 ands r0, r4
<address> = Rd// dc: 6048 str r0, [r1, #4]
Rd = Op2// de: 2080 movs r0, #128 ; 0x80
Rd = (address)// e0: 684c ldr r4, [r1, #4]
// could not parse:  e2: 0040 lsls r0, r0, #1
// could not parse:  e4: 4320 orrs r0, r4
<address> = Rd// e6: 6048 str r0, [r1, #4]
Rd = Op2// e8: 2002 movs r0, #2
Rd = (address)// ea: 4c0b ldr r4, [pc, #44] ; (118 <_stop_init+0x54>)
Rd = (address)// ec: 6965 ldr r5, [r4, #20]
// could not parse:  ee: 4385 bics r5, r0
<address> = Rd// f0: 6165 str r5, [r4, #20]
Rd = (address)// f2: 684d ldr r5, [r1, #4]
// could not parse:  f4: 4305 orrs r5, r0
<address> = Rd// f6: 604d str r5, [r1, #4]
Rd = (address)// f8: 6921 ldr r1, [r4, #16]
CPSR flags = Rn AND Op2// fa: 4201 tst r1, r0
// could not parse:  fc: d0fc beq.n f8 <_stop_init+0x34>
Rd = (address)// fe: 58d1 ldr r1, [r2, r3]
Rd = (address)// 100: 4806 ldr r0, [pc, #24] ; (11c <_stop_init+0x58>)
// could not parse:  102: 4001 ands r1, r0
<address> = Rd// 104: 50d1 str r1, [r2, r3]
// could not parse:  106: bd30 pop {r4, r5, pc}
// could not parse:  108: 40047000 .word 0x40047000
// could not parse:  10c: 00001038 .word 0x00001038
// could not parse:  110: 4004d000 .word 0x4004d000
// could not parse:  114: fffff8ff .word 0xfffff8ff
// could not parse:  118: 400ff100 .word 0x400ff100
// could not parse:  11c: ffffdfff .word 0xffffdfff

Label: _reset_init:
// could not parse:  120: f7ff ffd0 bl c4 <_stop_init>
Rd = Op2// 124: 2288 movs r2, #136 ; 0x88
Rd = Op2// 126: 2101 movs r1, #1
Rd = (address)// 128: 4b2e ldr r3, [pc, #184] ; (1e4 <_reset_init+0xc4>)
// could not parse:  12a: 0152 lsls r2, r2, #5
<address> = Rd// 12c: 5099 str r1, [r3, r2]
Rd = (address)// 12e: 482e ldr r0, [pc, #184] ; (1e8 <_reset_init+0xc8>)
Rd = (address)// 130: 4a2e ldr r2, [pc, #184] ; (1ec <_reset_init+0xcc>)
<address> = Rd// 132: 6090 str r0, [r2, #8]
Rd = Op2// 134: 2280 movs r2, #128 ; 0x80
Rd = (address)// 136: 482e ldr r0, [pc, #184] ; (1f0 <_reset_init+0xd0>)
// could not parse:  138: 0092 lsls r2, r2, #2
Rd = (address)// 13a: 581c ldr r4, [r3, r0]
// could not parse:  13c: 4322 orrs r2, r4
<address> = Rd// 13e: 501a str r2, [r3, r0]
Rd = (address)// 140: 482c ldr r0, [pc, #176] ; (1f4 <_reset_init+0xd4>)
Rd = (address)// 142: 4a2d ldr r2, [pc, #180] ; (1f8 <_reset_init+0xd8>)
<address> = Rd// 144: 5098 str r0, [r3, r2]
Rd = (address)// 146: 681a ldr r2, [r3, #0]
Rd = (address)// 148: 482c ldr r0, [pc, #176] ; (1fc <_reset_init+0xdc>)
// could not parse:  14a: 4002 ands r2, r0
Rd = Op2// 14c: 2080 movs r0, #128 ; 0x80
<address> = Rd// 14e: 601a str r2, [r3, #0]
Rd = (address)// 150: 4a2b ldr r2, [pc, #172] ; (200 <_reset_init+0xe0>)
// could not parse:  152: 0240 lsls r0, r0, #9
Rd = (address)// 154: 589c ldr r4, [r3, r2]
// could not parse:  156: 4320 orrs r0, r4
<address> = Rd// 158: 5098 str r0, [r3, r2]
Rd = (address)// 15a: 5898 ldr r0, [r3, r2]
Rd = (address)// 15c: 4c29 ldr r4, [pc, #164] ; (204 <_reset_init+0xe4>)
// could not parse:  15e: 4004 ands r4, r0
Rd = Op2// 160: 2080 movs r0, #128 ; 0x80
// could not parse:  162: 0440 lsls r0, r0, #17
// could not parse:  164: 4320 orrs r0, r4
<address> = Rd// 166: 5098 str r0, [r3, r2]
Rd = (address)// 168: 4b27 ldr r3, [pc, #156] ; (208 <_reset_init+0xe8>)
Rd = (address)// 16a: 4c28 ldr r4, [pc, #160] ; (20c <_reset_init+0xec>)
Rd = (address)// 16c: 6c98 ldr r0, [r3, #72] ; 0x48
// could not parse:  16e: 4020 ands r0, r4
<address> = Rd// 170: 6498 str r0, [r3, #72] ; 0x48
Rd = (address)// 172: 6cda ldr r2, [r3, #76] ; 0x4c
Rd = Op2// 174: 2000 movs r0, #0
// could not parse:  176: 4022 ands r2, r4
<address> = Rd// 178: 64da str r2, [r3, #76] ; 0x4c
Rd = Op2// 17a: 2224 movs r2, #36 ; 0x24
Rd = Op2// 17c: 241f movs r4, #31
Rd = (address)// 17e: 4b24 ldr r3, [pc, #144] ; (210 <_reset_init+0xf0>)
// could not parse:  180: 7018 strb r0, [r3, #0]
Rd = (address)// 182: 4b24 ldr r3, [pc, #144] ; (214 <_reset_init+0xf4>)
// could not parse:  184: 705a strb r2, [r3, #1]
// could not parse:  186: 3274 adds r2, #116 ; 0x74
// could not parse:  188: 701a strb r2, [r3, #0]
// could not parse:  18a: 78da ldrb r2, [r3, #3]
// could not parse:  18c: 4022 ands r2, r4
// could not parse:  18e: 70da strb r2, [r3, #3]
Rd = Op2// 190: 2210 movs r2, #16
// could not parse:  192: 7119 strb r1, [r3, #4]
// could not parse:  194: 7158 strb r0, [r3, #5]
// could not parse:  196: 7999 ldrb r1, [r3, #6]
CPSR flags = Rn AND Op2// 198: 4211 tst r1, r2
// could not parse:  19a: d1fc bne.n 196 <_reset_init+0x76>
Rd = Op2// 19c: 210c movs r1, #12
// could not parse:  19e: 799a ldrb r2, [r3, #6]
// could not parse:  1a0: 400a ands r2, r1
CPSR flags = Rn - Op2// 1a2: 2a08 cmp r2, #8
// could not parse:  1a4: d1fb bne.n 19e <_reset_init+0x7e>
// could not parse:  1a6: 3238 adds r2, #56 ; 0x38
// could not parse:  1a8: 715a strb r2, [r3, #5]
// could not parse:  1aa: 7999 ldrb r1, [r3, #6]
CPSR flags = Rn AND Op2// 1ac: 4211 tst r1, r2
// could not parse:  1ae: d0fc beq.n 1aa <_reset_init+0x8a>
Rd = Op2// 1b0: 2218 movs r2, #24
Rd = Op2// 1b2: 210c movs r1, #12
// could not parse:  1b4: 701a strb r2, [r3, #0]
// could not parse:  1b6: 799a ldrb r2, [r3, #6]
// could not parse:  1b8: 400a ands r2, r1
CPSR flags = Rn - Op2// 1ba: 2a0c cmp r2, #12
// could not parse:  1bc: d1fb bne.n 1b6 <_reset_init+0x96>
Rd = Op2// 1be: 2200 movs r2, #0
Rd = (address)// 1c0: 4815 ldr r0, [pc, #84] ; (218 <_reset_init+0xf8>)
Rd = (address)// 1c2: 4916 ldr r1, [pc, #88] ; (21c <_reset_init+0xfc>)
Rd = (address)// 1c4: 4c16 ldr r4, [pc, #88] ; (220 <_reset_init+0x100>)
// could not parse:  1c6: 1813 adds r3, r2, r0
CPSR flags = Rn - Op2// 1c8: 428b cmp r3, r1
// could not parse:  1ca: d905 bls.n 1d8 <_reset_init+0xb8>
Rd = Op2// 1cc: 2100 movs r1, #0
Rd = (address)// 1ce: 4a15 ldr r2, [pc, #84] ; (224 <_reset_init+0x104>)
CPSR flags = Rn - Op2// 1d0: 4293 cmp r3, r2
// could not parse:  1d2: d905 bls.n 1e0 <_reset_init+0xc0>
// could not parse:  1d4: f000 f91c bl 410 <main>
Rd = (address)// 1d8: 58a5 ldr r5, [r4, r2]
// could not parse:  1da: 3204 adds r2, #4
<address> = Rd// 1dc: 601d str r5, [r3, #0]
// could not parse:  1de: e7f2 b.n 1c6 <_reset_init+0xa6>
// could not parse:  1e0: c302 stmia r3!, {r1}
// could not parse:  1e2: e7f5 b.n 1d0 <_reset_init+0xb0>
// could not parse:  1e4: 40047000 .word 0x40047000
// could not parse:  1e8: 00000000 .word 0x00000000
// could not parse:  1ec: e000ed00 .word 0xe000ed00
// could not parse:  1f0: 00001038 .word 0x00001038
// could not parse:  1f4: 10010000 .word 0x10010000
// could not parse:  1f8: 00001044 .word 0x00001044
// could not parse:  1fc: fff3ffff .word 0xfff3ffff
// could not parse:  200: 00001004 .word 0x00001004
// could not parse:  204: fcffffff .word 0xfcffffff
// could not parse:  208: 40049000 .word 0x40049000
// could not parse:  20c: fefff8ff .word 0xfefff8ff
// could not parse:  210: 40065000 .word 0x40065000
// could not parse:  214: 40064000 .word 0x40064000
// could not parse:  218: 1ffff000 .word 0x1ffff000
// could not parse:  21c: 1ffff000 .word 0x1ffff000
// could not parse:  220: 00000678 .word 0x00000678
// could not parse:  224: 1ffff000 .word 0x1ffff000

Label: __startup_end:
// could not parse:  ...


Label: _cfm:
// could not parse:  400: ffffffff ffffffff ffffffff fffff77e ............~...

Label: main:
// could not parse:  410: b510 push {r4, lr}
// could not parse:  412: f000 f903 bl 61c <configure_sw1>
// could not parse:  416: f000 f8ab bl 570 <initialize_rgbled>
// could not parse:  41a: f000 f8f5 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 41e: 2001 movs r0, #1
// could not parse:  420: f000 f878 bl 514 <set_rgbled_color_to>
// could not parse:  424: f000 f8f0 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 428: 2002 movs r0, #2
// could not parse:  42a: f000 f873 bl 514 <set_rgbled_color_to>
// could not parse:  42e: f000 f8eb bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 432: 2000 movs r0, #0
// could not parse:  434: f000 f86e bl 514 <set_rgbled_color_to>
// could not parse:  438: f000 f8e6 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 43c: 2003 movs r0, #3
// could not parse:  43e: f000 f869 bl 514 <set_rgbled_color_to>
// could not parse:  442: f000 f8e1 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 446: 2004 movs r0, #4
// could not parse:  448: f000 f864 bl 514 <set_rgbled_color_to>
// could not parse:  44c: f000 f8dc bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 450: 2005 movs r0, #5
// could not parse:  452: f000 f85f bl 514 <set_rgbled_color_to>
// could not parse:  456: f000 f8d7 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 45a: 2006 movs r0, #6
// could not parse:  45c: f000 f85a bl 514 <set_rgbled_color_to>
// could not parse:  460: f000 f8d2 bl 608 <wait_for_sw1_pressed_and_released>
Rd = Op2// 464: 2007 movs r0, #7
// could not parse:  466: f000 f855 bl 514 <set_rgbled_color_to>
// could not parse:  46a: e7d6 b.n 41a <main+0xa>

Label: toggle_green_led:
Rd = Op2// 46c: 2380 movs r3, #128 ; 0x80
Rd = (address)// 46e: 4a03 ldr r2, [pc, #12] ; (47c <toggle_green_led+0x10>)
// could not parse:  470: 031b lsls r3, r3, #12
Rd = (address)// 472: 68d1 ldr r1, [r2, #12]
// could not parse:  474: 430b orrs r3, r1
<address> = Rd// 476: 60d3 str r3, [r2, #12]
R15 = Rn 
 T bit = Rn[0]// 478: 4770 bx lr
// could not parse:  47a: 46c0 nop ; (mov r8, r8)
// could not parse:  47c: 400ff040 .word 0x400ff040

Label: turn_on_green_led:
Rd = Op2// 480: 2380 movs r3, #128 ; 0x80
Rd = (address)// 482: 4a03 ldr r2, [pc, #12] ; (490 <turn_on_green_led+0x10>)
// could not parse:  484: 031b lsls r3, r3, #12
Rd = (address)// 486: 6891 ldr r1, [r2, #8]
// could not parse:  488: 430b orrs r3, r1
<address> = Rd// 48a: 6093 str r3, [r2, #8]
R15 = Rn 
 T bit = Rn[0]// 48c: 4770 bx lr
// could not parse:  48e: 46c0 nop ; (mov r8, r8)
// could not parse:  490: 400ff040 .word 0x400ff040

Label: turn_off_green_led:
Rd = Op2// 494: 2380 movs r3, #128 ; 0x80
Rd = (address)// 496: 4a03 ldr r2, [pc, #12] ; (4a4 <turn_off_green_led+0x10>)
// could not parse:  498: 031b lsls r3, r3, #12
Rd = (address)// 49a: 6851 ldr r1, [r2, #4]
// could not parse:  49c: 430b orrs r3, r1
<address> = Rd// 49e: 6053 str r3, [r2, #4]
R15 = Rn 
 T bit = Rn[0]// 4a0: 4770 bx lr
// could not parse:  4a2: 46c0 nop ; (mov r8, r8)
// could not parse:  4a4: 400ff040 .word 0x400ff040

Label: toggle_red_led:
Rd = Op2// 4a8: 2380 movs r3, #128 ; 0x80
Rd = (address)// 4aa: 4a03 ldr r2, [pc, #12] ; (4b8 <toggle_red_led+0x10>)
// could not parse:  4ac: 02db lsls r3, r3, #11
Rd = (address)// 4ae: 68d1 ldr r1, [r2, #12]
// could not parse:  4b0: 430b orrs r3, r1
<address> = Rd// 4b2: 60d3 str r3, [r2, #12]
R15 = Rn 
 T bit = Rn[0]// 4b4: 4770 bx lr
// could not parse:  4b6: 46c0 nop ; (mov r8, r8)
// could not parse:  4b8: 400ff040 .word 0x400ff040

Label: turn_on_red_led:
Rd = Op2// 4bc: 2380 movs r3, #128 ; 0x80
Rd = (address)// 4be: 4a03 ldr r2, [pc, #12] ; (4cc <turn_on_red_led+0x10>)
// could not parse:  4c0: 02db lsls r3, r3, #11
Rd = (address)// 4c2: 6891 ldr r1, [r2, #8]
// could not parse:  4c4: 430b orrs r3, r1
<address> = Rd// 4c6: 6093 str r3, [r2, #8]
R15 = Rn 
 T bit = Rn[0]// 4c8: 4770 bx lr
// could not parse:  4ca: 46c0 nop ; (mov r8, r8)
// could not parse:  4cc: 400ff040 .word 0x400ff040

Label: turn_off_red_led:
Rd = Op2// 4d0: 2380 movs r3, #128 ; 0x80
Rd = (address)// 4d2: 4a03 ldr r2, [pc, #12] ; (4e0 <turn_off_red_led+0x10>)
// could not parse:  4d4: 02db lsls r3, r3, #11
Rd = (address)// 4d6: 6851 ldr r1, [r2, #4]
// could not parse:  4d8: 430b orrs r3, r1
<address> = Rd// 4da: 6053 str r3, [r2, #4]
R15 = Rn 
 T bit = Rn[0]// 4dc: 4770 bx lr
// could not parse:  4de: 46c0 nop ; (mov r8, r8)
// could not parse:  4e0: 400ff040 .word 0x400ff040

Label: toggle_blue_led:
Rd = Op2// 4e4: 2302 movs r3, #2
Rd = (address)// 4e6: 4a02 ldr r2, [pc, #8] ; (4f0 <toggle_blue_led+0xc>)
Rd = (address)// 4e8: 68d1 ldr r1, [r2, #12]
// could not parse:  4ea: 430b orrs r3, r1
<address> = Rd// 4ec: 60d3 str r3, [r2, #12]
R15 = Rn 
 T bit = Rn[0]// 4ee: 4770 bx lr
// could not parse:  4f0: 400ff0c0 .word 0x400ff0c0

Label: turn_on_blue_led:
Rd = Op2// 4f4: 2302 movs r3, #2
Rd = (address)// 4f6: 4a02 ldr r2, [pc, #8] ; (500 <turn_on_blue_led+0xc>)
Rd = (address)// 4f8: 6891 ldr r1, [r2, #8]
// could not parse:  4fa: 430b orrs r3, r1
<address> = Rd// 4fc: 6093 str r3, [r2, #8]
R15 = Rn 
 T bit = Rn[0]// 4fe: 4770 bx lr
// could not parse:  500: 400ff0c0 .word 0x400ff0c0

Label: turn_off_blue_led:
Rd = Op2// 504: 2302 movs r3, #2
Rd = (address)// 506: 4a02 ldr r2, [pc, #8] ; (510 <turn_off_blue_led+0xc>)
Rd = (address)// 508: 6851 ldr r1, [r2, #4]
// could not parse:  50a: 430b orrs r3, r1
<address> = Rd// 50c: 6053 str r3, [r2, #4]
R15 = Rn 
 T bit = Rn[0]// 50e: 4770 bx lr
// could not parse:  510: 400ff0c0 .word 0x400ff0c0

Label: set_rgbled_color_to:
// could not parse:  514: b510 push {r4, lr}
CPSR flags = Rn - Op2// 516: 2807 cmp r0, #7
// could not parse:  518: d80b bhi.n 532 <set_rgbled_color_to+0x1e>
// could not parse:  51a: f000 f8a3 bl 664 <__gnu_thumb1_case_uqi>
// could not parse:  51e: 0b04 .short 0x0b04
// could not parse:  520: 1d16130e .word 0x1d16130e
// could not parse:  524: 2520 .short 0x2520
// could not parse:  526: f7ff ffed bl 504 <turn_off_blue_led>
// could not parse:  52a: f7ff ffb3 bl 494 <turn_off_green_led>
// could not parse:  52e: f7ff ffcf bl 4d0 <turn_off_red_led>
// could not parse:  532: bd10 pop {r4, pc}
// could not parse:  534: f7ff ffde bl 4f4 <turn_on_blue_led>
// could not parse:  538: e7f7 b.n 52a <set_rgbled_color_to+0x16>
// could not parse:  53a: f7ff ffe3 bl 504 <turn_off_blue_led>
// could not parse:  53e: f7ff ff9f bl 480 <turn_on_green_led>
// could not parse:  542: e7f4 b.n 52e <set_rgbled_color_to+0x1a>
// could not parse:  544: f7ff ffd6 bl 4f4 <turn_on_blue_led>
// could not parse:  548: e7f9 b.n 53e <set_rgbled_color_to+0x2a>
// could not parse:  54a: f7ff ffdb bl 504 <turn_off_blue_led>
// could not parse:  54e: f7ff ffa1 bl 494 <turn_off_green_led>
// could not parse:  552: f7ff ffb3 bl 4bc <turn_on_red_led>
// could not parse:  556: e7ec b.n 532 <set_rgbled_color_to+0x1e>
// could not parse:  558: f7ff ffcc bl 4f4 <turn_on_blue_led>
// could not parse:  55c: e7f7 b.n 54e <set_rgbled_color_to+0x3a>
// could not parse:  55e: f7ff ffd1 bl 504 <turn_off_blue_led>
// could not parse:  562: f7ff ff8d bl 480 <turn_on_green_led>
// could not parse:  566: e7f4 b.n 552 <set_rgbled_color_to+0x3e>
// could not parse:  568: f7ff ffc4 bl 4f4 <turn_on_blue_led>
// could not parse:  56c: e7f9 b.n 562 <set_rgbled_color_to+0x4e>
// could not parse:  ...


Label: initialize_rgbled:
Rd = Op2// 570: 23a0 movs r3, #160 ; 0xa0
Rd = (address)// 572: 4916 ldr r1, [pc, #88] ; (5cc <initialize_rgbled+0x5c>)
Rd = (address)// 574: 4a16 ldr r2, [pc, #88] ; (5d0 <initialize_rgbled+0x60>)
// could not parse:  576: 015b lsls r3, r3, #5
Rd = (address)// 578: 5888 ldr r0, [r1, r2]
// could not parse:  57a: b510 push {r4, lr}
// could not parse:  57c: 4303 orrs r3, r0
<address> = Rd// 57e: 508b str r3, [r1, r2]
Rd = (address)// 580: 4b14 ldr r3, [pc, #80] ; (5d4 <initialize_rgbled+0x64>)
Rd = (address)// 582: 4815 ldr r0, [pc, #84] ; (5d8 <initialize_rgbled+0x68>)
Rd = (address)// 584: 6c9a ldr r2, [r3, #72] ; 0x48
// could not parse:  586: 4002 ands r2, r0
<address> = Rd// 588: 649a str r2, [r3, #72] ; 0x48
Rd = Op2// 58a: 2280 movs r2, #128 ; 0x80
Rd = (address)// 58c: 6c99 ldr r1, [r3, #72] ; 0x48
// could not parse:  58e: 0052 lsls r2, r2, #1
// could not parse:  590: 4311 orrs r1, r2
<address> = Rd// 592: 6499 str r1, [r3, #72] ; 0x48
Rd = (address)// 594: 6cd9 ldr r1, [r3, #76] ; 0x4c
// could not parse:  596: 4001 ands r1, r0
<address> = Rd// 598: 64d9 str r1, [r3, #76] ; 0x4c
Rd = (address)// 59a: 6cd9 ldr r1, [r3, #76] ; 0x4c
// could not parse:  59c: 4311 orrs r1, r2
<address> = Rd// 59e: 64d9 str r1, [r3, #76] ; 0x4c
Rd = (address)// 5a0: 4b0e ldr r3, [pc, #56] ; (5dc <initialize_rgbled+0x6c>)
Rd = (address)// 5a2: 6859 ldr r1, [r3, #4]
// could not parse:  5a4: 4001 ands r1, r0
<address> = Rd// 5a6: 6059 str r1, [r3, #4]
Rd = (address)// 5a8: 6859 ldr r1, [r3, #4]
Rd = Op2// 5aa: 2000 movs r0, #0
// could not parse:  5ac: 430a orrs r2, r1
<address> = Rd// 5ae: 605a str r2, [r3, #4]
Rd = Op2// 5b0: 23c0 movs r3, #192 ; 0xc0
Rd = (address)// 5b2: 4a0b ldr r2, [pc, #44] ; (5e0 <initialize_rgbled+0x70>)
// could not parse:  5b4: 031b lsls r3, r3, #12
Rd = (address)// 5b6: 6951 ldr r1, [r2, #20]
// could not parse:  5b8: 430b orrs r3, r1
<address> = Rd// 5ba: 6153 str r3, [r2, #20]
Rd = Op2// 5bc: 2302 movs r3, #2
Rd = (address)// 5be: 4a09 ldr r2, [pc, #36] ; (5e4 <initialize_rgbled+0x74>)
Rd = (address)// 5c0: 6951 ldr r1, [r2, #20]
// could not parse:  5c2: 430b orrs r3, r1
<address> = Rd// 5c4: 6153 str r3, [r2, #20]
// could not parse:  5c6: f7ff ffa5 bl 514 <set_rgbled_color_to>
// could not parse:  5ca: bd10 pop {r4, pc}
// could not parse:  5cc: 40047000 .word 0x40047000
// could not parse:  5d0: 00001038 .word 0x00001038
// could not parse:  5d4: 4004a000 .word 0x4004a000
// could not parse:  5d8: fffff8ff .word 0xfffff8ff
// could not parse:  5dc: 4004c000 .word 0x4004c000
// could not parse:  5e0: 400ff040 .word 0x400ff040
// could not parse:  5e4: 400ff0c0 .word 0x400ff0c0

Label: sw1_is_pressed:
Rd = Op2// 5e8: 2001 movs r0, #1
Rd = (address)// 5ea: 4b02 ldr r3, [pc, #8] ; (5f4 <sw1_is_pressed+0xc>)
Rd = (address)// 5ec: 691b ldr r3, [r3, #16]
// could not parse:  5ee: 0d1b lsrs r3, r3, #20
// could not parse:  5f0: 4398 bics r0, r3
R15 = Rn 
 T bit = Rn[0]// 5f2: 4770 bx lr
// could not parse:  5f4: 400ff000 .word 0x400ff000

Label: sw1_is_not_pressed:
// could not parse:  5f8: b510 push {r4, lr}
// could not parse:  5fa: f7ff fff5 bl 5e8 <sw1_is_pressed>
Rd = Op2// 5fe: 0003 movs r3, r0
Rd = Op2// 600: 2001 movs r0, #1
// could not parse:  602: 4058 eors r0, r3
// could not parse:  604: b2c0 uxtb r0, r0
// could not parse:  606: bd10 pop {r4, pc}

Label: wait_for_sw1_pressed_and_released:
// could not parse:  608: b510 push {r4, lr}
// could not parse:  60a: f7ff ffed bl 5e8 <sw1_is_pressed>
CPSR flags = Rn - Op2// 60e: 2800 cmp r0, #0
// could not parse:  610: d1fb bne.n 60a <wait_for_sw1_pressed_and_released+0x2>
// could not parse:  612: f7ff fff1 bl 5f8 <sw1_is_not_pressed>
CPSR flags = Rn - Op2// 616: 2800 cmp r0, #0
// could not parse:  618: d1fb bne.n 612 <wait_for_sw1_pressed_and_released+0xa>
// could not parse:  61a: bd10 pop {r4, pc}

Label: configure_sw1:
Rd = Op2// 61c: 2380 movs r3, #128 ; 0x80
Rd = (address)// 61e: 490b ldr r1, [pc, #44] ; (64c <configure_sw1+0x30>)
Rd = (address)// 620: 4a0b ldr r2, [pc, #44] ; (650 <configure_sw1+0x34>)
// could not parse:  622: 009b lsls r3, r3, #2
Rd = (address)// 624: 5888 ldr r0, [r1, r2]
// could not parse:  626: 4303 orrs r3, r0
<address> = Rd// 628: 508b str r3, [r1, r2]
Rd = (address)// 62a: 4b0a ldr r3, [pc, #40] ; (654 <configure_sw1+0x38>)
Rd = (address)// 62c: 490a ldr r1, [pc, #40] ; (658 <configure_sw1+0x3c>)
Rd = (address)// 62e: 6d1a ldr r2, [r3, #80] ; 0x50
// could not parse:  630: 400a ands r2, r1
<address> = Rd// 632: 651a str r2, [r3, #80] ; 0x50
Rd = Op2// 634: 2280 movs r2, #128 ; 0x80
Rd = (address)// 636: 6d19 ldr r1, [r3, #80] ; 0x50
// could not parse:  638: 0052 lsls r2, r2, #1
// could not parse:  63a: 430a orrs r2, r1
<address> = Rd// 63c: 651a str r2, [r3, #80] ; 0x50
Rd = (address)// 63e: 4a07 ldr r2, [pc, #28] ; (65c <configure_sw1+0x40>)
Rd = (address)// 640: 4907 ldr r1, [pc, #28] ; (660 <configure_sw1+0x44>)
Rd = (address)// 642: 6953 ldr r3, [r2, #20]
// could not parse:  644: 400b ands r3, r1
<address> = Rd// 646: 6153 str r3, [r2, #20]
R15 = Rn 
 T bit = Rn[0]// 648: 4770 bx lr
// could not parse:  64a: 46c0 nop ; (mov r8, r8)
// could not parse:  64c: 40047000 .word 0x40047000
// could not parse:  650: 00001038 .word 0x00001038
// could not parse:  654: 40049000 .word 0x40049000
// could not parse:  658: fffff8ff .word 0xfffff8ff
// could not parse:  65c: 400ff000 .word 0x400ff000
// could not parse:  660: ffefffff .word 0xffefffff

Label: __gnu_thumb1_case_uqi:
// could not parse:  664: b402 push {r1}
// could not parse:  666: 4671 mov r1, lr
// could not parse:  668: 0849 lsrs r1, r1, #1
// could not parse:  66a: 0049 lsls r1, r1, #1
// could not parse:  66c: 5c09 ldrb r1, [r1, r0]
// could not parse:  66e: 0049 lsls r1, r1, #1
Rd = Rn + Op2// 670: 448e add lr, r1
// could not parse:  672: bc02 pop {r1}
R15 = Rn 
 T bit = Rn[0]// 674: 4770 bx lr
// could not parse:  676: 46c0 nop ; (mov r8, r8)
