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
void _stop_init();
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
void set_init_clock();
void SLEEP(double seconds);

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

void SLEEP(double seconds){
	auto sleep_start = std::chrono::high_resolution_clock::now();
	auto sleep_finish = std::chrono::high_resolution_clock::now();
	double time_slept = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_finish - sleep_start).count() * pow(10, -9));
	while (time_slept < seconds) {
		sleep_finish = std::chrono::high_resolution_clock::now();
		time_slept = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_finish - sleep_start).count() * pow(10, -9));
}

}
//The init_clocks function in _startup.c
//has 4 while loops, it waits specifically for these sequence of numbers
//without these stores, the program will enter an infinite loop.
void set_init_clock(){
	STRB_2(0,0x40064006);
	SLEEP(.2);
	STRB_2(8,0x40064006);
	SLEEP(.2);
	// This number is the 32-bit inversion of the number 64
	STRB_2(4294967263,0x40064006);
	SLEEP(1);
	STRB_2(0xC,0x40064006);
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
std::thread last_hope(set_init_clock);
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
MOVS_2(R2, 136);//  c8:	2288      	movs	r2, #136	 ; 0x88 ;
label_ca:  ;
MOVS_2(R1, 0);//  ca:	2100      	movs	r1, #0 ;
label_cc:  ;
R3 = 0x40047000 ;//  cc:	4b2e      	ldr	r3, [pc, #184]	 ; (188 <_reset_init+0xc0>) ;
label_ce:  ;
LSLS_3(R2, R2, 5);//  ce:	0152      	lsls	r2, r2, #5 ;
label_d0:  ;
STR_3(R1, R3, R2 );//  d0:	5099      	str	r1, [r3, r2] ;
label_d2:  ;
R0 = 0x00000000 ;//  d2:	482e      	ldr	r0, [pc, #184]	 ; (18c <_reset_init+0xc4>) ;
label_d4:  ;
R2 = 0xe000ed00 ;//  d4:	4a2e      	ldr	r2, [pc, #184]	 ; (190 <_reset_init+0xc8>) ;
label_d6:  ;
STR_3(R0, R2, 8);//  d6:	6090      	str	r0, [r2, #8] ;
label_d8:  ;
MOVS_2(R2, 128);//  d8:	2280      	movs	r2, #128	 ; 0x80 ;
label_da:  ;
R0 = 0x00001038 ;//  da:	482e      	ldr	r0, [pc, #184]	 ; (194 <_reset_init+0xcc>) ;
label_dc:  ;
LSLS_3(R2, R2, 2);//  dc:	0092      	lsls	r2, r2, #2 ;
label_de:  ;
LDR_3(R4, R3, R0 );//  de:	581c      	ldr	r4, [r3, r0] ;
label_e0:  ;
ORRS_2(R2, R4 );//  e0:	4322      	orrs	r2, r4 ;
label_e2:  ;
STR_3(R2, R3, R0 );//  e2:	501a      	str	r2, [r3, r0] ;
label_e4:  ;
R0 = 0x10010000 ;//  e4:	482c      	ldr	r0, [pc, #176]	 ; (198 <_reset_init+0xd0>) ;
label_e6:  ;
R2 = 0x00001044 ;//  e6:	4a2d      	ldr	r2, [pc, #180]	 ; (19c <_reset_init+0xd4>) ;
label_e8:  ;
STR_3(R0, R3, R2 );//  e8:	5098      	str	r0, [r3, r2] ;
label_ea:  ;
LDR_3(R2, R3, 0);//  ea:	681a      	ldr	r2, [r3, #0] ;
label_ec:  ;
R0 = 0xfff3ffff ;//  ec:	482c      	ldr	r0, [pc, #176]	 ; (1a0 <_reset_init+0xd8>) ;
label_ee:  ;
ANDS_2(R2, R0 );//  ee:	4002      	ands	r2, r0 ;
label_f0:  ;
MOVS_2(R0, 128);//  f0:	2080      	movs	r0, #128	 ; 0x80 ;
label_f2:  ;
STR_3(R2, R3, 0);//  f2:	601a      	str	r2, [r3, #0] ;
label_f4:  ;
R2 = 0x00001004 ;//  f4:	4a2b      	ldr	r2, [pc, #172]	 ; (1a4 <_reset_init+0xdc>) ;
label_f6:  ;
LSLS_3(R0, R0, 9);//  f6:	0240      	lsls	r0, r0, #9 ;
label_f8:  ;
LDR_3(R4, R3, R2 );//  f8:	589c      	ldr	r4, [r3, r2] ;
label_fa:  ;
ORRS_2(R0, R4 );//  fa:	4320      	orrs	r0, r4 ;
label_fc:  ;
STR_3(R0, R3, R2 );//  fc:	5098      	str	r0, [r3, r2] ;
label_fe:  ;
LDR_3(R0, R3, R2 );//  fe:	5898      	ldr	r0, [r3, r2] ;
label_100:  ;
R4 = 0xfcffffff ;// 100:	4c29      	ldr	r4, [pc, #164]	 ; (1a8 <_reset_init+0xe0>) ;
label_102:  ;
ANDS_2(R4, R0 );// 102:	4004      	ands	r4, r0 ;
label_104:  ;
MOVS_2(R0, 128);// 104:	2080      	movs	r0, #128	 ; 0x80 ;
label_106:  ;
LSLS_3(R0, R0, 17);// 106:	0440      	lsls	r0, r0, #17 ;
label_108:  ;
ORRS_2(R0, R4 );// 108:	4320      	orrs	r0, r4 ;
label_10a:  ;
STR_3(R0, R3, R2 );// 10a:	5098      	str	r0, [r3, r2] ;
label_10c:  ;
R3 = 0x40049000 ;// 10c:	4b27      	ldr	r3, [pc, #156]	 ; (1ac <_reset_init+0xe4>) ;
label_10e:  ;
R4 = 0xfefff8ff ;// 10e:	4c28      	ldr	r4, [pc, #160]	 ; (1b0 <_reset_init+0xe8>) ;
label_110:  ;
LDR_3(R0, R3, 72);// 110:	6c98      	ldr	r0, [r3, #72]	 ; 0x48 ;
label_112:  ;
ANDS_2(R0, R4 );// 112:	4020      	ands	r0, r4 ;
label_114:  ;
STR_3(R0, R3, 72);// 114:	6498      	str	r0, [r3, #72]	 ; 0x48 ;
label_116:  ;
LDR_3(R2, R3, 76);// 116:	6cda      	ldr	r2, [r3, #76]	 ; 0x4c ;
label_118:  ;
MOVS_2(R0, 31);// 118:	201f      	movs	r0, #31 ;
label_11a:  ;
ANDS_2(R2, R4 );// 11a:	4022      	ands	r2, r4 ;
label_11c:  ;
STR_3(R2, R3, 76);// 11c:	64da      	str	r2, [r3, #76]	 ; 0x4c ;
label_11e:  ;
MOVS_2(R2, 36);// 11e:	2224      	movs	r2, #36	 ; 0x24 ;
label_120:  ;
R3 = 0x40065000 ;// 120:	4b24      	ldr	r3, [pc, #144]	 ; (1b4 <_reset_init+0xec>) ;
label_122:  ;
STRB_3(R1, R3, 0);// 122:	7019      	strb	r1, [r3, #0] ;
label_124:  ;
R3 = 0x40064000 ;// 124:	4b24      	ldr	r3, [pc, #144]	 ; (1b8 <_reset_init+0xf0>) ;
label_126:  ;
STRB_3(R2, R3, 1);// 126:	705a      	strb	r2, [r3, #1] ;
label_128:  ;
ADDS_2(R2, 116);// 128:	3274      	adds	r2, #116	 ; 0x74 ;
label_12a:  ;
STRB_3(R2, R3, 0);// 12a:	701a      	strb	r2, [r3, #0] ;
label_12c:  ;
LDRB_3(R2, R3, 3);// 12c:	78da      	ldrb	r2, [r3, #3] ;
label_12e:  ;
ANDS_2(R2, R0 );// 12e:	4002      	ands	r2, r0 ;
label_130:  ;
STRB_3(R2, R3, 3);// 130:	70da      	strb	r2, [r3, #3] ;
label_132:  ;
MOVS_2(R2, 1);// 132:	2201      	movs	r2, #1 ;
label_134:  ;
STRB_3(R2, R3, 4);// 134:	711a      	strb	r2, [r3, #4] ;
label_136:  ;
STRB_3(R1, R3, 5);// 136:	7159      	strb	r1, [r3, #5] ;
label_138:  ;
ADDS_2(R2, 15);// 138:	320f      	adds	r2, #15 ;
label_13a:  ;
LDRB_3(R1, R3, 6);// 13a:	7999      	ldrb	r1, [r3, #6] ;
std::cout << "1st while" << std::endl;
label_13c:  ;
TST_2(R1, R2 );// 13c:	4211      	tst	r1, r2 ;
label_13e:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_13a ; } ;// 13e:	d1fc      	bnen	13a <_reset_init+0x72> ;
label_140:  ;
MOVS_2(R1, 12);// 140:	210c      	movs	r1, #12 ;
label_142:  ;
LDRB_3(R2, R3, 6);// 142:	799a      	ldrb	r2, [r3, #6] ;
label_144:  ;
ANDS_2(R2, R1 );// 144:	400a      	ands	r2, r1 ;
label_146:  ;
CMP_2(R2, 8);// 146:	2a08      	cmp	r2, #8 ;
label_148:  ;
g_cycle_count++;
std::cout << "2nd while" << std::endl;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_142 ; } ;// 148:	d1fb      	bnen	142 <_reset_init+0x7a> ;
label_14a:  ;
ADDS_2(R2, 56);// 14a:	3238      	adds	r2, #56	 ; 0x38 ;
label_14c:  ;
STRB_3(R2, R3, 5);// 14c:	715a      	strb	r2, [r3, #5] ;
label_14e:  ;
LDRB_3(R1, R3, 6);// 14e:	7999      	ldrb	r1, [r3, #6] ;
label_150:  ;
TST_2(R1, R2 );// 150:	4211      	tst	r1, r2 ;
label_152:  ;
g_cycle_count++;
std::cout << "R1: " <<  R1 << std::endl;
std::cout << "R2: " <<  R2 << std::endl;
std::cout << "3rd while" << std::endl;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_14e ; } ;// 152:	d0fc      	beqn	14e <_reset_init+0x86> ;
label_154:  ;
MOVS_2(R2, 24);// 154:	2218      	movs	r2, #24 ;
label_156:  ;
MOVS_2(R1, 12);// 156:	210c      	movs	r1, #12 ;
label_158:  ;
STRB_3(R2, R3, 0);// 158:	701a      	strb	r2, [r3, #0] ;
label_15a:  ;
LDRB_3(R2, R3, 6);// 15a:	799a      	ldrb	r2, [r3, #6] ;
label_15c:  ;
ANDS_2(R2, R1 );// 15c:	400a      	ands	r2, r1 ;
label_15e:  ;
CMP_2(R2, 12);// 15e:	2a0c      	cmp	r2, #12 ;
label_160:  ;
g_cycle_count++;
std::cout << "4th while" << std::endl;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_15a ; } ;// 160:	d1fb      	bnen	15a <_reset_init+0x92> ;
label_162:  ;
MOVS_2(R2, 0);// 162:	2200      	movs	r2, #0 ;
label_164:  ;
R0 = 0x1ffff000 ;// 164:	4815      	ldr	r0, [pc, #84]	 ; (1bc <_reset_init+0xf4>) ;
label_166:  ;
R1 = 0x1ffff000 ;// 166:	4916      	ldr	r1, [pc, #88]	 ; (1c0 <_reset_init+0xf8>) ;
label_168:  ;
R4 = 0x000005ce ;// 168:	4c16      	ldr	r4, [pc, #88]	 ; (1c4 <_reset_init+0xfc>) ;
label_16a:  ;
ADDS_3(R3, R2, R0 );// 16a:	1813      	adds	r3, r2, r0 ;
label_16c:  ;
CMP_2(R3, R1 );// 16c:	428b      	cmp	r3, r1 ;
label_16e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_17c ; } ;// 16e:	d305      	bccn	17c <_reset_init+0xb4> ;
label_170:  ;
MOVS_2(R1, 0);// 170:	2100      	movs	r1, #0 ;
label_172:  ;
R2 = 0x1ffff000 ;// 172:	4a15      	ldr	r2, [pc, #84]	 ; (1c8 <_reset_init+0x100>) ;
label_174:  ;
CMP_2(R3, R2 );// 174:	4293      	cmp	r3, r2 ;
label_176:  ;
g_cycle_count++;
 if (C_flag == 0 && Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_184 ; } ;// 176:	d905      	blsn	184 <_reset_init+0xbc> ;
label_178:  ;
g_cycle_count += 3;
main_thread( );// 178:	f000 f958 	bl	42c <main_thread> ;
label_17c:  ;
LDR_3(R5, R4, R2 );// 17c:	58a5      	ldr	r5, [r4, r2] ;
label_17e:  ;
ADDS_2(R2, 4);// 17e:	3204      	adds	r2, #4 ;
label_180:  ;
STR_3(R5, R3, 0);// 180:	601d      	str	r5, [r3, #0] ;
label_182:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_16a ; } ;// 182:	e7f2      	bn	16a <_reset_init+0xa2> ;
label_184:  ;
STMIA(R3,0b000111111);// 184:	c302      	stmia	r3!, r1 ;
label_186:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_174 ; } ;// 186:	e7f5      	bn	174 <_reset_init+0xac> ;
label_188:  ;
//Could not parse:  188:	40047000 	word	0x40047000 ;
label_18c:  ;
//Could not parse:  18c:	00000000 	word	0x00000000 ;
label_190:  ;
//Could not parse:  190:	e000ed00 	word	0xe000ed00 ;
label_194:  ;
//Could not parse:  194:	00001038 	word	0x00001038 ;
label_198:  ;
//Could not parse:  198:	10010000 	word	0x10010000 ;
label_19c:  ;
//Could not parse:  19c:	00001044 	word	0x00001044 ;
label_1a0:  ;
//Could not parse:  1a0:	fff3ffff 	word	0xfff3ffff ;
label_1a4:  ;
//Could not parse:  1a4:	00001004 	word	0x00001004 ;
label_1a8:  ;
//Could not parse:  1a8:	fcffffff 	word	0xfcffffff ;
label_1ac:  ;
//Could not parse:  1ac:	40049000 	word	0x40049000 ;
label_1b0:  ;
//Could not parse:  1b0:	fefff8ff 	word	0xfefff8ff ;
label_1b4:  ;
//Could not parse:  1b4:	40065000 	word	0x40065000 ;
label_1b8:  ;
//Could not parse:  1b8:	40064000 	word	0x40064000 ;
label_1bc:  ;
//Could not parse:  1bc:	1ffff000 	word	0x1ffff000 ;
label_1c0:  ;
//Could not parse:  1c0:	1ffff000 	word	0x1ffff000 ;
label_1c4:  ;
//Could not parse:  1c4:	000005ce 	word	0x000005ce ;
label_1c8:  ;
//Could not parse:  1c8:	1ffff000 	word	0x1ffff000 ;
}
void _stop_init() 
{label_1cc:  ;
MOVS_2(R1, 128);// 1cc:	2180      	movs	r1, #128	 ; 0x80 ;
label_1ce:  ;
R2 = 0x40047000 ;// 1ce:	4a10      	ldr	r2, [pc, #64]	 ; (210 <_stop_init+0x44>) ;
label_1d0:  ;
R3 = 0x00001038 ;// 1d0:	4b10      	ldr	r3, [pc, #64]	 ; (214 <_stop_init+0x48>) ;
label_1d2:  ;
LSLS_3(R1, R1, 6);// 1d2:	0189      	lsls	r1, r1, #6 ;
label_1d4:  ;
LDR_3(R0, R2, R3 );// 1d4:	58d0      	ldr	r0, [r2, r3] ;
label_1d6:  ;
PUSH(SP,0b0000110001);// 1d6:	b530      	push	r4, r5, lr ;
label_1d8:  ;
ORRS_2(R1, R0 );// 1d8:	4301      	orrs	r1, r0 ;
label_1da:  ;
STR_3(R1, R2, R3 );// 1da:	50d1      	str	r1, [r2, r3] ;
label_1dc:  ;
R1 = 0x4004d000 ;// 1dc:	490e      	ldr	r1, [pc, #56]	 ; (218 <_stop_init+0x4c>) ;
label_1de:  ;
R4 = 0xfffff8ff ;// 1de:	4c0f      	ldr	r4, [pc, #60]	 ; (21c <_stop_init+0x50>) ;
label_1e0:  ;
LDR_3(R0, R1, 4);// 1e0:	6848      	ldr	r0, [r1, #4] ;
label_1e2:  ;
ANDS_2(R0, R4 );// 1e2:	4020      	ands	r0, r4 ;
label_1e4:  ;
STR_3(R0, R1, 4);// 1e4:	6048      	str	r0, [r1, #4] ;
label_1e6:  ;
MOVS_2(R0, 128);// 1e6:	2080      	movs	r0, #128	 ; 0x80 ;
label_1e8:  ;
LDR_3(R4, R1, 4);// 1e8:	684c      	ldr	r4, [r1, #4] ;
label_1ea:  ;
LSLS_3(R0, R0, 1);// 1ea:	0040      	lsls	r0, r0, #1 ;
label_1ec:  ;
ORRS_2(R0, R4 );// 1ec:	4320      	orrs	r0, r4 ;
label_1ee:  ;
STR_3(R0, R1, 4);// 1ee:	6048      	str	r0, [r1, #4] ;
label_1f0:  ;
MOVS_2(R0, 2);// 1f0:	2002      	movs	r0, #2 ;
label_1f2:  ;
R4 = 0x400ff100 ;// 1f2:	4c0b      	ldr	r4, [pc, #44]	 ; (220 <_stop_init+0x54>) ;
label_1f4:  ;
LDR_3(R5, R4, 20);// 1f4:	6965      	ldr	r5, [r4, #20] ;
label_1f6:  ;
BICS_2(R5, R0 );// 1f6:	4385      	bics	r5, r0 ;
label_1f8:  ;
STR_3(R5, R4, 20);// 1f8:	6165      	str	r5, [r4, #20] ;
label_1fa:  ;
LDR_3(R5, R1, 4);// 1fa:	684d      	ldr	r5, [r1, #4] ;
label_1fc:  ;
ORRS_2(R5, R0 );// 1fc:	4305      	orrs	r5, r0 ;
label_1fe:  ;
STR_3(R5, R1, 4);// 1fe:	604d      	str	r5, [r1, #4] ;
label_200:  ;
LDR_3(R1, R4, 16);// 200:	6921      	ldr	r1, [r4, #16] ;
label_202:  ;
TST_2(R1, R0 );// 202:	4201      	tst	r1, r0 ;
label_204:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_200 ; } ;// 204:	d0fc      	beqn	200 <_stop_init+0x34> ;
label_206:  ;
LDR_3(R1, R2, R3 );// 206:	58d1      	ldr	r1, [r2, r3] ;
label_208:  ;
R0 = 0xffffdfff ;// 208:	4806      	ldr	r0, [pc, #24]	 ; (224 <_stop_init+0x58>) ;
label_20a:  ;
ANDS_2(R1, R0 );// 20a:	4001      	ands	r1, r0 ;
label_20c:  ;
STR_3(R1, R2, R3 );// 20c:	50d1      	str	r1, [r2, r3] ;
label_20e:  ;
POP(SP,0b0000110001);
return ;// 20e:	bd30      	pop	r4, r5, pc ;
label_210:  ;
//Could not parse:  210:	40047000 	word	0x40047000 ;
label_214:  ;
//Could not parse:  214:	00001038 	word	0x00001038 ;
label_218:  ;
//Could not parse:  218:	4004d000 	word	0x4004d000 ;
label_21c:  ;
//Could not parse:  21c:	fffff8ff 	word	0xfffff8ff ;
label_220:  ;
//Could not parse:  220:	400ff100 	word	0x400ff100 ;
label_224:  ;
//Could not parse:  224:	ffffdfff 	word	0xffffdfff ;
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