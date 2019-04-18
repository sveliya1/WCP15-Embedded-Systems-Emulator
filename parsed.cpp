#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "memorymap.h"
#include "flash.h"
#include "macros.h"
#include "IO_Register.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <chrono>
#include "rgbled.h"
void InterruptVector();
void Default_Handler();
void HardFault_Handler();
void _reset_init();
void __startup_end();
void _cfm();
void delay();
void main_thread();
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
void ISR();
void ISR()
{
}


//All addresses are 0 addressable, add 1 to all of their sizes
#define FLASH_START 0x00000000
#define FLASH_SIZE 0x07FFFFFF+1
#define RAM_START 0x1FFFF000
#define RAM_SIZE 0x20002FFF+1-RAM_START
#define AIPS_START 0x40000000
#define AIPS_SIZE 0x4007FFFF+1-AIPS_START

#define GPIO_START 0x400FF000 
#define GPIO_SIZE 0x400FFFFF+1-GPIO_START

#define PRIVATE_PERI_START 0xE0000000
#define PRIVATE_SIZE 0xE00FFFFF+1 - PRIVATE_PERI_START

uint64_t R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, SP, LR, PC, result = 0;

uint64_t g_embedded_sys_freq = 48000000;
uint64_t supervisor_threshold =  0.5*g_embedded_sys_freq;
uint64_t supervisor_increment = supervisor_threshold;

uint8_t lsb_byte;
uint64_t g_cycle_count;
uint32_t lsb_word;
bool N_flag, C_flag, Z_flag, V_flag;
MemoryMap* map = new MemoryMap();
RAMDevice* gpio = new RAMDevice(GPIO_START, GPIO_SIZE, ENDIAN_LITTLE);
RAMDevice* aips = new RAMDevice(AIPS_START, AIPS_SIZE, ENDIAN_LITTLE);
RAMDevice* ram = new RAMDevice(RAM_START, RAM_SIZE, ENDIAN_LITTLE);
RAMDevice* private_peri = new RAMDevice(PRIVATE_PERI_START, PRIVATE_SIZE, ENDIAN_LITTLE);
ROMDevice* flash = new ROMDevice(FLASH_START, FLASH_SIZE, ENDIAN_LITTLE);

void supervisor();
uint32_t read_register(uint32_t address, uint32_t bit_value);
void clear_register(uint32_t address, uint32_t value);
void set_register(uint32_t address, uint32_t value);
void toggle_register(uint32_t address, uint32_t value);

auto start = std::chrono::high_resolution_clock::now();
auto finish= std::chrono::high_resolution_clock::now();

void clear_register(uint32_t address, uint32_t value)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg &= ~value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}
void set_register(uint32_t address, uint32_t value)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg |= value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}

void toggle_register(uint32_t address, uint32_t value)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg ^= value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}


uint32_t read_register(uint32_t address, uint32_t bit_value)
{
	uint32_t register_value = map->read(address, Size::WORD);
	register_value &= ((1uL << bit_value));
	register_value = (register_value >> bit_value);
	return register_value;
}

void supervisor() {

	static uint64_t previous_g_cycle_count = 0;
	double embedded_sys_CPU_time = (double) (g_cycle_count - previous_g_cycle_count) / (double) g_embedded_sys_freq;
	finish = std::chrono::high_resolution_clock::now();
	double wall_clock_time = (double) (std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * pow(10, -9));
	double sleep_time = embedded_sys_CPU_time - wall_clock_time;
	if (sleep_time > 0) {
		auto sleep_start = std::chrono::high_resolution_clock::now();
		auto sleep_finish = std::chrono::high_resolution_clock::now();
		double time_slept = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_finish - sleep_start).count() * pow(10, -9));
		while (time_slept < sleep_time) {
			 sleep_finish = std::chrono::high_resolution_clock::now();
			 time_slept = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_finish - sleep_start).count() * pow(10, -9));
		}
	}
	start = std::chrono::high_resolution_clock::now();
	previous_g_cycle_count = g_cycle_count;
	supervisor_threshold += supervisor_increment;
	std::cout << "Sleep Time: " << sleep_time << std::endl;

}

void main()
{
std::cout << "Hello" << std::endl;
map->addDevice(flash);
map->addDevice(ram);
map->addDevice(aips);
map->addDevice(gpio);
map->addDevice(private_peri);
burn_flash_to_mem(flash);
std::cout << "Memory Allocate is good" << std::endl;
SP = init_sp();
start = std::chrono::high_resolution_clock::now();
std::thread led(led_read_state,map);
_reset_init();
label_timing_demoout:  ;
//Could not parse: timing_demoout:     file format elf32-littlearm ;
//Could not parse: Disassembly of section text: ;
}
void InterruptVector() 
{label_0:  ;
//Could not parse:    0:	00 30 00 20 c9 00 00 00 c1 00 00 00 c3 00 00 00     0  ;
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
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_c0 ; } ;//  c0:	e7fe      	bn	c0 <Default_Handler> ;
}
void HardFault_Handler() 
{label_c2:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_c2 ; } ;//  c2:	e7fe      	bn	c2 <HardFault_Handler> ;
label_c4:  ;
//Could not parse:   c4:	46c0      	nop			 ; (mov r8, r8) ;
label_c6:  ;
//Could not parse:   c6:	46c0      	nop			 ; (mov r8, r8) ;
}
void _reset_init() 
{label_c8:  ;
R2 = 0x00000000 ;//  c8:	4a0a      	ldr	r2, [pc, #40]	 ; (f4 <_reset_init+0x2c>) ;
label_ca:  ;
R3 = 0xe000ed00 ;//  ca:	4b0b      	ldr	r3, [pc, #44]	 ; (f8 <_reset_init+0x30>) ;
label_cc:  ;
R0 = 0x1ffff000 ;//  cc:	480b      	ldr	r0, [pc, #44]	 ; (fc <_reset_init+0x34>) ;
label_ce:  ;
STR_3(R2, R3, 8);//  ce:	609a      	str	r2, [r3, #8] ;
label_d0:  ;
MOVS_2(R2, 0);//  d0:	2200      	movs	r2, #0 ;
label_d2:  ;
R1 = 0x1ffff000 ;//  d2:	490b      	ldr	r1, [pc, #44]	 ; (100 <_reset_init+0x38>) ;
label_d4:  ;
R4 = 0x000005ce ;//  d4:	4c0b      	ldr	r4, [pc, #44]	 ; (104 <_reset_init+0x3c>) ;
label_d6:  ;
ADDS_3(R3, R2, R0 );//  d6:	1813      	adds	r3, r2, r0 ;
label_d8:  ;
CMP_2(R3, R1 );//  d8:	428b      	cmp	r3, r1 ;
label_da:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_e8 ; } ;//  da:	d305      	bccn	e8 <_reset_init+0x20> ;
label_dc:  ;
MOVS_2(R1, 0);//  dc:	2100      	movs	r1, #0 ;
label_de:  ;
R2 = 0x1ffff000 ;//  de:	4a0a      	ldr	r2, [pc, #40]	 ; (108 <_reset_init+0x40>) ;
label_e0:  ;
CMP_2(R3, R2 );//  e0:	4293      	cmp	r3, r2 ;
label_e2:  ;
g_cycle_count++;
 if (C_flag == 0 && Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_f0 ; } ;//  e2:	d905      	blsn	f0 <_reset_init+0x28> ;
label_e4:  ;
g_cycle_count += 3;
main_thread( );//  e4:	f000 f9a2 	bl	42c <main_thread> ;
label_e8:  ;
LDR_3(R5, R4, R2 );//  e8:	58a5      	ldr	r5, [r4, r2] ;
label_ea:  ;
ADDS_2(R2, 4);//  ea:	3204      	adds	r2, #4 ;
label_ec:  ;
STR_3(R5, R3, 0);//  ec:	601d      	str	r5, [r3, #0] ;
label_ee:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_d6 ; } ;//  ee:	e7f2      	bn	d6 <_reset_init+0xe> ;
label_f0:  ;
STMIA(R3,0b000111111);//  f0:	c302      	stmia	r3!, r1 ;
label_f2:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_e0 ; } ;//  f2:	e7f5      	bn	e0 <_reset_init+0x18> ;
label_f4:  ;
//Could not parse:   f4:	00000000 	word	0x00000000 ;
label_f8:  ;
//Could not parse:   f8:	e000ed00 	word	0xe000ed00 ;
label_fc:  ;
//Could not parse:   fc:	1ffff000 	word	0x1ffff000 ;
label_100:  ;
//Could not parse:  100:	1ffff000 	word	0x1ffff000 ;
label_104:  ;
//Could not parse:  104:	000005ce 	word	0x000005ce ;
label_108:  ;
//Could not parse:  108:	1ffff000 	word	0x1ffff000 ;
}
void __startup_end() 
{}
void _cfm() 
{label_400:  ;
//Could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ~ ;
}
void delay() 
{label_410:  ;
MOVS_2(R2, 250);// 410:	22fa      	movs	r2, #250	 ; 0xfa ;
label_412:  ;
SUB_2(SP, 8);// 412:	b082      	sub	sp, #8 ;
label_414:  ;
LSLS_3(R2, R2, 2);// 414:	0092      	lsls	r2, r2, #2 ;
label_416:  ;
SUBS_2(R0, 1);// 416:	3801      	subs	r0, #1 ;
label_418:  ;
g_cycle_count++;
 if (C_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_41e ; } ;// 418:	d201      	bcsn	41e <delay+0xe> ;
label_41a:  ;
ADD_2(SP, 8);// 41a:	b002      	add	sp, #8 ;
label_41c:  ;
return ;// 41c:	4770      	bx	lr ;
label_41e:  ;
STR_3(R2, SP, 4);// 41e:	9201      	str	r2, [sp, #4] ;
label_420:  ;
LDR_3(R3, SP, 4);// 420:	9b01      	ldr	r3, [sp, #4] ;
label_422:  ;
SUBS_3(R1, R3, 1);// 422:	1e59      	subs	r1, r3, #1 ;
label_424:  ;
STR_3(R1, SP, 4);// 424:	9101      	str	r1, [sp, #4] ;
label_426:  ;
CMP_2(R3, 0);// 426:	2b00      	cmp	r3, #0 ;
label_428:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_420 ; } ;// 428:	d1fa      	bnen	420 <delay+0x10> ;
label_42a:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_416 ; } ;// 42a:	e7f4      	bn	416 <delay+0x6> ;
}
void main_thread() 
{label_42c:  ;
PUSH(SP,0b0000111001);// 42c:	b570      	push	r4, r5, r6, lr ;
label_42e:  ;
MOVS_2(R5, 250);// 42e:	25fa      	movs	r5, #250	 ; 0xfa ;
label_430:  ;
g_cycle_count += 3;
configure_rgbled( );// 430:	f000 f80c 	bl	44c <configure_rgbled> ;
label_434:  ;
LSLS_3(R5, R5, 5);// 434:	016d      	lsls	r5, r5, #5 ;
label_436:  ;
MOVS_2(R4, 0);// 436:	2400      	movs	r4, #0 ;
label_438:  ;
UXTB_2(R0, R4 );// 438:	b2e0      	uxtb	r0, r4 ;
label_43a:  ;
g_cycle_count += 3;
set_rgbled_color_to( );// 43a:	f000 f895 	bl	568 <set_rgbled_color_to> ;
label_43e:  ;
ADDS_2(R4, 1);// 43e:	3401      	adds	r4, #1 ;
label_440:  ;
MOVS_2(R0, R5 );// 440:	0028      	movs	r0, r5 ;
label_442:  ;
g_cycle_count += 3;
delay( );// 442:	f7ff ffe5 	bl	410 <delay> ;
label_446:  ;
CMP_2(R4, 8);// 446:	2c08      	cmp	r4, #8 ;
label_448:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_438 ; } ;// 448:	d1f6      	bnen	438 <main+0xc> ;
label_44a:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_436 ; } ;// 44a:	e7f4      	bn	436 <main+0xa> ;
}
void configure_rgbled() 
{label_44c:  ;
MOVS_2(R3, 160);// 44c:	23a0      	movs	r3, #160	 ; 0xa0 ;
label_44e:  ;
R1 = 0x40047000 ;// 44e:	4914      	ldr	r1, [pc, #80]	 ; (4a0 <configure_rgbled+0x54>) ;
label_450:  ;
R2 = 0x00001038 ;// 450:	4a14      	ldr	r2, [pc, #80]	 ; (4a4 <configure_rgbled+0x58>) ;
label_452:  ;
LSLS_3(R3, R3, 5);// 452:	015b      	lsls	r3, r3, #5 ;
label_454:  ;
LDR_3(R0, R1, R2 );// 454:	5888      	ldr	r0, [r1, r2] ;
label_456:  ;
ORRS_2(R3, R0 );// 456:	4303      	orrs	r3, r0 ;
label_458:  ;
STR_3(R3, R1, R2 );// 458:	508b      	str	r3, [r1, r2] ;
label_45a:  ;
R3 = 0x4004a000 ;// 45a:	4b13      	ldr	r3, [pc, #76]	 ; (4a8 <configure_rgbled+0x5c>) ;
label_45c:  ;
R0 = 0xfffff8ff ;// 45c:	4813      	ldr	r0, [pc, #76]	 ; (4ac <configure_rgbled+0x60>) ;
label_45e:  ;
LDR_3(R2, R3, 72);// 45e:	6c9a      	ldr	r2, [r3, #72]	 ; 0x48 ;
label_460:  ;
ANDS_2(R2, R0 );// 460:	4002      	ands	r2, r0 ;
label_462:  ;
STR_3(R2, R3, 72);// 462:	649a      	str	r2, [r3, #72]	 ; 0x48 ;
label_464:  ;
MOVS_2(R2, 128);// 464:	2280      	movs	r2, #128	 ; 0x80 ;
label_466:  ;
LDR_3(R1, R3, 72);// 466:	6c99      	ldr	r1, [r3, #72]	 ; 0x48 ;
label_468:  ;
LSLS_3(R2, R2, 1);// 468:	0052      	lsls	r2, r2, #1 ;
label_46a:  ;
ORRS_2(R1, R2 );// 46a:	4311      	orrs	r1, r2 ;
label_46c:  ;
STR_3(R1, R3, 72);// 46c:	6499      	str	r1, [r3, #72]	 ; 0x48 ;
label_46e:  ;
LDR_3(R1, R3, 76);// 46e:	6cd9      	ldr	r1, [r3, #76]	 ; 0x4c ;
label_470:  ;
ANDS_2(R1, R0 );// 470:	4001      	ands	r1, r0 ;
label_472:  ;
STR_3(R1, R3, 76);// 472:	64d9      	str	r1, [r3, #76]	 ; 0x4c ;
label_474:  ;
LDR_3(R1, R3, 76);// 474:	6cd9      	ldr	r1, [r3, #76]	 ; 0x4c ;
label_476:  ;
ORRS_2(R1, R2 );// 476:	4311      	orrs	r1, r2 ;
label_478:  ;
STR_3(R1, R3, 76);// 478:	64d9      	str	r1, [r3, #76]	 ; 0x4c ;
label_47a:  ;
R3 = 0x4004c000 ;// 47a:	4b0d      	ldr	r3, [pc, #52]	 ; (4b0 <configure_rgbled+0x64>) ;
label_47c:  ;
LDR_3(R1, R3, 4);// 47c:	6859      	ldr	r1, [r3, #4] ;
label_47e:  ;
ANDS_2(R1, R0 );// 47e:	4001      	ands	r1, r0 ;
label_480:  ;
STR_3(R1, R3, 4);// 480:	6059      	str	r1, [r3, #4] ;
label_482:  ;
LDR_3(R1, R3, 4);// 482:	6859      	ldr	r1, [r3, #4] ;
label_484:  ;
ORRS_2(R2, R1 );// 484:	430a      	orrs	r2, r1 ;
label_486:  ;
STR_3(R2, R3, 4);// 486:	605a      	str	r2, [r3, #4] ;
label_488:  ;
MOVS_2(R3, 192);// 488:	23c0      	movs	r3, #192	 ; 0xc0 ;
label_48a:  ;
R2 = 0x400ff040 ;// 48a:	4a0a      	ldr	r2, [pc, #40]	 ; (4b4 <configure_rgbled+0x68>) ;
label_48c:  ;
LSLS_3(R3, R3, 12);// 48c:	031b      	lsls	r3, r3, #12 ;
label_48e:  ;
LDR_3(R1, R2, 20);// 48e:	6951      	ldr	r1, [r2, #20] ;
label_490:  ;
ORRS_2(R3, R1 );// 490:	430b      	orrs	r3, r1 ;
label_492:  ;
STR_3(R3, R2, 20);// 492:	6153      	str	r3, [r2, #20] ;
label_494:  ;
MOVS_2(R3, 2);// 494:	2302      	movs	r3, #2 ;
label_496:  ;
R2 = 0x400ff0c0 ;// 496:	4a08      	ldr	r2, [pc, #32]	 ; (4b8 <configure_rgbled+0x6c>) ;
label_498:  ;
LDR_3(R1, R2, 20);// 498:	6951      	ldr	r1, [r2, #20] ;
label_49a:  ;
ORRS_2(R3, R1 );// 49a:	430b      	orrs	r3, r1 ;
label_49c:  ;
STR_3(R3, R2, 20);// 49c:	6153      	str	r3, [r2, #20] ;
label_49e:  ;
return ;// 49e:	4770      	bx	lr ;
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
MOVS_2(R3, 128);// 4bc:	2380      	movs	r3, #128	 ; 0x80 ;
label_4be:  ;
R2 = 0x400ff040 ;// 4be:	4a03      	ldr	r2, [pc, #12]	 ; (4cc <turn_on_green_led+0x10>) ;
label_4c0:  ;
LSLS_3(R3, R3, 12);// 4c0:	031b      	lsls	r3, r3, #12 ;
label_4c2:  ;
LDR_3(R1, R2, 8);// 4c2:	6891      	ldr	r1, [r2, #8] ;
label_4c4:  ;
ORRS_2(R3, R1 );// 4c4:	430b      	orrs	r3, r1 ;
label_4c6:  ;
STR_3(R3, R2, 8);// 4c6:	6093      	str	r3, [r2, #8] ;
label_4c8:  ;
return ;// 4c8:	4770      	bx	lr ;
label_4ca:  ;
//Could not parse:  4ca:	46c0      	nop			 ; (mov r8, r8) ;
label_4cc:  ;
//Could not parse:  4cc:	400ff040 	word	0x400ff040 ;
}
void turn_off_green_led() 
{label_4d0:  ;
MOVS_2(R3, 128);// 4d0:	2380      	movs	r3, #128	 ; 0x80 ;
label_4d2:  ;
R2 = 0x400ff040 ;// 4d2:	4a03      	ldr	r2, [pc, #12]	 ; (4e0 <turn_off_green_led+0x10>) ;
label_4d4:  ;
LSLS_3(R3, R3, 12);// 4d4:	031b      	lsls	r3, r3, #12 ;
label_4d6:  ;
LDR_3(R1, R2, 4);// 4d6:	6851      	ldr	r1, [r2, #4] ;
label_4d8:  ;
ORRS_2(R3, R1 );// 4d8:	430b      	orrs	r3, r1 ;
label_4da:  ;
STR_3(R3, R2, 4);// 4da:	6053      	str	r3, [r2, #4] ;
label_4dc:  ;
return ;// 4dc:	4770      	bx	lr ;
label_4de:  ;
//Could not parse:  4de:	46c0      	nop			 ; (mov r8, r8) ;
label_4e0:  ;
//Could not parse:  4e0:	400ff040 	word	0x400ff040 ;
}
void toggle_green_led() 
{label_4e4:  ;
MOVS_2(R3, 128);// 4e4:	2380      	movs	r3, #128	 ; 0x80 ;
label_4e6:  ;
R2 = 0x400ff040 ;// 4e6:	4a03      	ldr	r2, [pc, #12]	 ; (4f4 <toggle_green_led+0x10>) ;
label_4e8:  ;
LSLS_3(R3, R3, 12);// 4e8:	031b      	lsls	r3, r3, #12 ;
label_4ea:  ;
LDR_3(R1, R2, 12);// 4ea:	68d1      	ldr	r1, [r2, #12] ;
label_4ec:  ;
ORRS_2(R3, R1 );// 4ec:	430b      	orrs	r3, r1 ;
label_4ee:  ;
STR_3(R3, R2, 12);// 4ee:	60d3      	str	r3, [r2, #12] ;
label_4f0:  ;
return ;// 4f0:	4770      	bx	lr ;
label_4f2:  ;
//Could not parse:  4f2:	46c0      	nop			 ; (mov r8, r8) ;
label_4f4:  ;
//Could not parse:  4f4:	400ff040 	word	0x400ff040 ;
}
void turn_on_red_led() 
{label_4f8:  ;
MOVS_2(R3, 128);// 4f8:	2380      	movs	r3, #128	 ; 0x80 ;
label_4fa:  ;
R2 = 0x400ff040 ;// 4fa:	4a03      	ldr	r2, [pc, #12]	 ; (508 <turn_on_red_led+0x10>) ;
label_4fc:  ;
LSLS_3(R3, R3, 11);// 4fc:	02db      	lsls	r3, r3, #11 ;
label_4fe:  ;
LDR_3(R1, R2, 8);// 4fe:	6891      	ldr	r1, [r2, #8] ;
label_500:  ;
ORRS_2(R3, R1 );// 500:	430b      	orrs	r3, r1 ;
label_502:  ;
STR_3(R3, R2, 8);// 502:	6093      	str	r3, [r2, #8] ;
label_504:  ;
return ;// 504:	4770      	bx	lr ;
label_506:  ;
//Could not parse:  506:	46c0      	nop			 ; (mov r8, r8) ;
label_508:  ;
//Could not parse:  508:	400ff040 	word	0x400ff040 ;
}
void turn_off_red_led() 
{label_50c:  ;
MOVS_2(R3, 128);// 50c:	2380      	movs	r3, #128	 ; 0x80 ;
label_50e:  ;
R2 = 0x400ff040 ;// 50e:	4a03      	ldr	r2, [pc, #12]	 ; (51c <turn_off_red_led+0x10>) ;
label_510:  ;
LSLS_3(R3, R3, 11);// 510:	02db      	lsls	r3, r3, #11 ;
label_512:  ;
LDR_3(R1, R2, 4);// 512:	6851      	ldr	r1, [r2, #4] ;
label_514:  ;
ORRS_2(R3, R1 );// 514:	430b      	orrs	r3, r1 ;
label_516:  ;
STR_3(R3, R2, 4);// 516:	6053      	str	r3, [r2, #4] ;
label_518:  ;
return ;// 518:	4770      	bx	lr ;
label_51a:  ;
//Could not parse:  51a:	46c0      	nop			 ; (mov r8, r8) ;
label_51c:  ;
//Could not parse:  51c:	400ff040 	word	0x400ff040 ;
}
void toggle_red_led() 
{label_520:  ;
MOVS_2(R3, 128);// 520:	2380      	movs	r3, #128	 ; 0x80 ;
label_522:  ;
R2 = 0x400ff040 ;// 522:	4a03      	ldr	r2, [pc, #12]	 ; (530 <toggle_red_led+0x10>) ;
label_524:  ;
LSLS_3(R3, R3, 11);// 524:	02db      	lsls	r3, r3, #11 ;
label_526:  ;
LDR_3(R1, R2, 12);// 526:	68d1      	ldr	r1, [r2, #12] ;
label_528:  ;
ORRS_2(R3, R1 );// 528:	430b      	orrs	r3, r1 ;
label_52a:  ;
STR_3(R3, R2, 12);// 52a:	60d3      	str	r3, [r2, #12] ;
label_52c:  ;
return ;// 52c:	4770      	bx	lr ;
label_52e:  ;
//Could not parse:  52e:	46c0      	nop			 ; (mov r8, r8) ;
label_530:  ;
//Could not parse:  530:	400ff040 	word	0x400ff040 ;
}
void turn_on_blue_led() 
{label_534:  ;
MOVS_2(R3, 2);// 534:	2302      	movs	r3, #2 ;
label_536:  ;
R2 = 0x400ff0c0 ;// 536:	4a02      	ldr	r2, [pc, #8]	 ; (540 <turn_on_blue_led+0xc>) ;
label_538:  ;
LDR_3(R1, R2, 8);// 538:	6891      	ldr	r1, [r2, #8] ;
label_53a:  ;
ORRS_2(R3, R1 );// 53a:	430b      	orrs	r3, r1 ;
label_53c:  ;
STR_3(R3, R2, 8);// 53c:	6093      	str	r3, [r2, #8] ;
label_53e:  ;
return ;// 53e:	4770      	bx	lr ;
label_540:  ;
//Could not parse:  540:	400ff0c0 	word	0x400ff0c0 ;
}
void turn_off_blue_led() 
{label_544:  ;
MOVS_2(R3, 2);// 544:	2302      	movs	r3, #2 ;
label_546:  ;
R2 = 0x400ff0c0 ;// 546:	4a02      	ldr	r2, [pc, #8]	 ; (550 <turn_off_blue_led+0xc>) ;
label_548:  ;
LDR_3(R1, R2, 4);// 548:	6851      	ldr	r1, [r2, #4] ;
label_54a:  ;
ORRS_2(R3, R1 );// 54a:	430b      	orrs	r3, r1 ;
label_54c:  ;
STR_3(R3, R2, 4);// 54c:	6053      	str	r3, [r2, #4] ;
label_54e:  ;
return ;// 54e:	4770      	bx	lr ;
label_550:  ;
//Could not parse:  550:	400ff0c0 	word	0x400ff0c0 ;
}
void toggle_blue_led() 
{label_554:  ;
MOVS_2(R3, 128);// 554:	2380      	movs	r3, #128	 ; 0x80 ;
label_556:  ;
R2 = 0x400ff0c0 ;// 556:	4a03      	ldr	r2, [pc, #12]	 ; (564 <toggle_blue_led+0x10>) ;
label_558:  ;
LSLS_3(R3, R3, 11);// 558:	02db      	lsls	r3, r3, #11 ;
label_55a:  ;
LDR_3(R1, R2, 12);// 55a:	68d1      	ldr	r1, [r2, #12] ;
label_55c:  ;
ORRS_2(R3, R1 );// 55c:	430b      	orrs	r3, r1 ;
label_55e:  ;
STR_3(R3, R2, 12);// 55e:	60d3      	str	r3, [r2, #12] ;
label_560:  ;
return ;// 560:	4770      	bx	lr ;
label_562:  ;
//Could not parse:  562:	46c0      	nop			 ; (mov r8, r8) ;
label_564:  ;
//Could not parse:  564:	400ff0c0 	word	0x400ff0c0 ;
}
void set_rgbled_color_to() 
{label_568:  ;
PUSH(SP,0b0000100001);// 568:	b510      	push	r4, lr ;
label_56a:  ;
CMP_2(R0, 0);// 56a:	2800      	cmp	r0, #0 ;
label_56c:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_57c ; } ;// 56c:	d106      	bnen	57c <set_rgbled_color_to+0x14> ;
label_56e:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 56e:	f7ff ffe9 	bl	544 <turn_off_blue_led> ;
label_572:  ;
g_cycle_count += 3;
turn_off_green_led( );// 572:	f7ff ffad 	bl	4d0 <turn_off_green_led> ;
label_576:  ;
g_cycle_count += 3;
turn_off_red_led( );// 576:	f7ff ffc9 	bl	50c <turn_off_red_led> ;
label_57a:  ;
POP(SP,0b0000100001);
return ;// 57a:	bd10      	pop	r4, pc ;
label_57c:  ;
CMP_2(R0, 1);// 57c:	2801      	cmp	r0, #1 ;
label_57e:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_586 ; } ;// 57e:	d102      	bnen	586 <set_rgbled_color_to+0x1e> ;
label_580:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 580:	f7ff ffd8 	bl	534 <turn_on_blue_led> ;
label_584:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_572 ; } ;// 584:	e7f5      	bn	572 <set_rgbled_color_to+0xa> ;
label_586:  ;
CMP_2(R0, 2);// 586:	2802      	cmp	r0, #2 ;
label_588:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_594 ; } ;// 588:	d104      	bnen	594 <set_rgbled_color_to+0x2c> ;
label_58a:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 58a:	f7ff ffdb 	bl	544 <turn_off_blue_led> ;
label_58e:  ;
g_cycle_count += 3;
turn_on_green_led( );// 58e:	f7ff ff95 	bl	4bc <turn_on_green_led> ;
label_592:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_576 ; } ;// 592:	e7f0      	bn	576 <set_rgbled_color_to+0xe> ;
label_594:  ;
CMP_2(R0, 3);// 594:	2803      	cmp	r0, #3 ;
label_596:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_59e ; } ;// 596:	d102      	bnen	59e <set_rgbled_color_to+0x36> ;
label_598:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 598:	f7ff ffcc 	bl	534 <turn_on_blue_led> ;
label_59c:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_58e ; } ;// 59c:	e7f7      	bn	58e <set_rgbled_color_to+0x26> ;
label_59e:  ;
CMP_2(R0, 4);// 59e:	2804      	cmp	r0, #4 ;
label_5a0:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5b0 ; } ;// 5a0:	d106      	bnen	5b0 <set_rgbled_color_to+0x48> ;
label_5a2:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 5a2:	f7ff ffcf 	bl	544 <turn_off_blue_led> ;
label_5a6:  ;
g_cycle_count += 3;
turn_off_green_led( );// 5a6:	f7ff ff93 	bl	4d0 <turn_off_green_led> ;
label_5aa:  ;
g_cycle_count += 3;
turn_on_red_led( );// 5aa:	f7ff ffa5 	bl	4f8 <turn_on_red_led> ;
label_5ae:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_57a ; } ;// 5ae:	e7e4      	bn	57a <set_rgbled_color_to+0x12> ;
label_5b0:  ;
CMP_2(R0, 5);// 5b0:	2805      	cmp	r0, #5 ;
label_5b2:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5ba ; } ;// 5b2:	d102      	bnen	5ba <set_rgbled_color_to+0x52> ;
label_5b4:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 5b4:	f7ff ffbe 	bl	534 <turn_on_blue_led> ;
label_5b8:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5a6 ; } ;// 5b8:	e7f5      	bn	5a6 <set_rgbled_color_to+0x3e> ;
label_5ba:  ;
CMP_2(R0, 6);// 5ba:	2806      	cmp	r0, #6 ;
label_5bc:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5c8 ; } ;// 5bc:	d104      	bnen	5c8 <set_rgbled_color_to+0x60> ;
label_5be:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 5be:	f7ff ffc1 	bl	544 <turn_off_blue_led> ;
label_5c2:  ;
g_cycle_count += 3;
turn_on_green_led( );// 5c2:	f7ff ff7b 	bl	4bc <turn_on_green_led> ;
label_5c6:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5aa ; } ;// 5c6:	e7f0      	bn	5aa <set_rgbled_color_to+0x42> ;
label_5c8:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 5c8:	f7ff ffb4 	bl	534 <turn_on_blue_led> ;
label_5cc:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_5c2 ; } ;// 5cc:	e7f9      	bn	5c2 <set_rgbled_color_to+0x5a> ;
}