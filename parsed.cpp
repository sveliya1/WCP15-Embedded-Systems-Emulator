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
#include "switch_interrupt.h"
#include "rgbled.h"
void InterruptVector();
void Default_Handler();
void HardFault_Handler();
void _stop_init();
void _reset_init();
void __startup_end();
void _cfm();
void main_thread();
void initialize_sw();
void PORTA_IRQHandler();
void get_and_clear_SW_count();
void get_SW_count();
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
void __aeabi_idiv();
void __aeabi_idivmod();
void __aeabi_idiv0();
void ISR();
void ISR()
{
void PORTA_IRQHandler(void)
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
std::thread button(check_button_INT,map);
std::thread led(led_read_state,map);
std::thread last_hope(set_init_clock);
_reset_init();
label_interuptout:  ;
//Could not parse: interuptout:     file format elf32-littlearm ;
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
//Could not parse:   b0:	c1 00 00 00 c1 00 00 00 8d 04 00 00 c1 00 00 00      ;
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
}
void _stop_init() 
{label_c4:  ;
MOVS_2(R1, 128);//  c4:	2180      	movs	r1, #128	 ; 0x80 ;
label_c6:  ;
R2 = 0x40047000 ;//  c6:	4a10      	ldr	r2, [pc, #64]	 ; (108 <_stop_init+0x44>) ;
label_c8:  ;
R3 = 0x00001038 ;//  c8:	4b10      	ldr	r3, [pc, #64]	 ; (10c <_stop_init+0x48>) ;
label_ca:  ;
LSLS_3(R1, R1, 6);//  ca:	0189      	lsls	r1, r1, #6 ;
label_cc:  ;
LDR_3(R0, R2, R3 );//  cc:	58d0      	ldr	r0, [r2, r3] ;
label_ce:  ;
PUSH(SP,0b0000011001);//  ce:	b530      	push	r4, r5, lr ;
label_d0:  ;
ORRS_2(R1, R0 );//  d0:	4301      	orrs	r1, r0 ;
label_d2:  ;
STR_3(R1, R2, R3 );//  d2:	50d1      	str	r1, [r2, r3] ;
label_d4:  ;
R1 = 0x4004d000 ;//  d4:	490e      	ldr	r1, [pc, #56]	 ; (110 <_stop_init+0x4c>) ;
label_d6:  ;
R4 = 0xfffff8ff ;//  d6:	4c0f      	ldr	r4, [pc, #60]	 ; (114 <_stop_init+0x50>) ;
label_d8:  ;
LDR_3(R0, R1, 4);//  d8:	6848      	ldr	r0, [r1, #4] ;
label_da:  ;
ANDS_2(R0, R4 );//  da:	4020      	ands	r0, r4 ;
label_dc:  ;
STR_3(R0, R1, 4);//  dc:	6048      	str	r0, [r1, #4] ;
label_de:  ;
MOVS_2(R0, 128);//  de:	2080      	movs	r0, #128	 ; 0x80 ;
label_e0:  ;
LDR_3(R4, R1, 4);//  e0:	684c      	ldr	r4, [r1, #4] ;
label_e2:  ;
LSLS_3(R0, R0, 1);//  e2:	0040      	lsls	r0, r0, #1 ;
label_e4:  ;
ORRS_2(R0, R4 );//  e4:	4320      	orrs	r0, r4 ;
label_e6:  ;
STR_3(R0, R1, 4);//  e6:	6048      	str	r0, [r1, #4] ;
label_e8:  ;
MOVS_2(R0, 2);//  e8:	2002      	movs	r0, #2 ;
label_ea:  ;
R4 = 0x400ff100 ;//  ea:	4c0b      	ldr	r4, [pc, #44]	 ; (118 <_stop_init+0x54>) ;
label_ec:  ;
LDR_3(R5, R4, 20);//  ec:	6965      	ldr	r5, [r4, #20] ;
label_ee:  ;
BICS_2(R5, R0 );//  ee:	4385      	bics	r5, r0 ;
label_f0:  ;
STR_3(R5, R4, 20);//  f0:	6165      	str	r5, [r4, #20] ;
label_f2:  ;
LDR_3(R5, R1, 4);//  f2:	684d      	ldr	r5, [r1, #4] ;
label_f4:  ;
ORRS_2(R5, R0 );//  f4:	4305      	orrs	r5, r0 ;
label_f6:  ;
STR_3(R5, R1, 4);//  f6:	604d      	str	r5, [r1, #4] ;
label_f8:  ;
LDR_3(R1, R4, 16);//  f8:	6921      	ldr	r1, [r4, #16] ;
label_fa:  ;
TST_2(R1, R0 );//  fa:	4201      	tst	r1, r0 ;
label_fc:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_f8 ; } ;//  fc:	d0fc      	beqn	f8 <_stop_init+0x34> ;
label_fe:  ;
LDR_3(R1, R2, R3 );//  fe:	58d1      	ldr	r1, [r2, r3] ;
label_100:  ;
R0 = 0xffffdfff ;// 100:	4806      	ldr	r0, [pc, #24]	 ; (11c <_stop_init+0x58>) ;
label_102:  ;
ANDS_2(R1, R0 );// 102:	4001      	ands	r1, r0 ;
label_104:  ;
STR_3(R1, R2, R3 );// 104:	50d1      	str	r1, [r2, r3] ;
label_106:  ;
POP(SP,0b0000011001);
return ;// 106:	bd30      	pop	r4, r5, pc ;
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
g_cycle_count += 3;
_stop_init( );// 120:	f7ff ffd0 	bl	c4 <_stop_init> ;
label_124:  ;
MOVS_2(R2, 136);// 124:	2288      	movs	r2, #136	 ; 0x88 ;
label_126:  ;
MOVS_2(R1, 1);// 126:	2101      	movs	r1, #1 ;
label_128:  ;
R3 = 0x40047000 ;// 128:	4b2e      	ldr	r3, [pc, #184]	 ; (1e4 <_reset_init+0xc4>) ;
label_12a:  ;
LSLS_3(R2, R2, 5);// 12a:	0152      	lsls	r2, r2, #5 ;
label_12c:  ;
STR_3(R1, R3, R2 );// 12c:	5099      	str	r1, [r3, r2] ;
label_12e:  ;
R0 = 0x00000000 ;// 12e:	482e      	ldr	r0, [pc, #184]	 ; (1e8 <_reset_init+0xc8>) ;
label_130:  ;
R2 = 0xe000ed00 ;// 130:	4a2e      	ldr	r2, [pc, #184]	 ; (1ec <_reset_init+0xcc>) ;
label_132:  ;
STR_3(R0, R2, 8);// 132:	6090      	str	r0, [r2, #8] ;
label_134:  ;
MOVS_2(R2, 128);// 134:	2280      	movs	r2, #128	 ; 0x80 ;
label_136:  ;
R0 = 0x00001038 ;// 136:	482e      	ldr	r0, [pc, #184]	 ; (1f0 <_reset_init+0xd0>) ;
label_138:  ;
LSLS_3(R2, R2, 2);// 138:	0092      	lsls	r2, r2, #2 ;
label_13a:  ;
LDR_3(R4, R3, R0 );// 13a:	581c      	ldr	r4, [r3, r0] ;
label_13c:  ;
ORRS_2(R2, R4 );// 13c:	4322      	orrs	r2, r4 ;
label_13e:  ;
STR_3(R2, R3, R0 );// 13e:	501a      	str	r2, [r3, r0] ;
label_140:  ;
R0 = 0x10010000 ;// 140:	482c      	ldr	r0, [pc, #176]	 ; (1f4 <_reset_init+0xd4>) ;
label_142:  ;
R2 = 0x00001044 ;// 142:	4a2d      	ldr	r2, [pc, #180]	 ; (1f8 <_reset_init+0xd8>) ;
label_144:  ;
STR_3(R0, R3, R2 );// 144:	5098      	str	r0, [r3, r2] ;
label_146:  ;
LDR_3(R2, R3, 0);// 146:	681a      	ldr	r2, [r3, #0] ;
label_148:  ;
R0 = 0xfff3ffff ;// 148:	482c      	ldr	r0, [pc, #176]	 ; (1fc <_reset_init+0xdc>) ;
label_14a:  ;
ANDS_2(R2, R0 );// 14a:	4002      	ands	r2, r0 ;
label_14c:  ;
MOVS_2(R0, 128);// 14c:	2080      	movs	r0, #128	 ; 0x80 ;
label_14e:  ;
STR_3(R2, R3, 0);// 14e:	601a      	str	r2, [r3, #0] ;
label_150:  ;
R2 = 0x00001004 ;// 150:	4a2b      	ldr	r2, [pc, #172]	 ; (200 <_reset_init+0xe0>) ;
label_152:  ;
LSLS_3(R0, R0, 9);// 152:	0240      	lsls	r0, r0, #9 ;
label_154:  ;
LDR_3(R4, R3, R2 );// 154:	589c      	ldr	r4, [r3, r2] ;
label_156:  ;
ORRS_2(R0, R4 );// 156:	4320      	orrs	r0, r4 ;
label_158:  ;
STR_3(R0, R3, R2 );// 158:	5098      	str	r0, [r3, r2] ;
label_15a:  ;
LDR_3(R0, R3, R2 );// 15a:	5898      	ldr	r0, [r3, r2] ;
label_15c:  ;
R4 = 0xfcffffff ;// 15c:	4c29      	ldr	r4, [pc, #164]	 ; (204 <_reset_init+0xe4>) ;
label_15e:  ;
ANDS_2(R4, R0 );// 15e:	4004      	ands	r4, r0 ;
label_160:  ;
MOVS_2(R0, 128);// 160:	2080      	movs	r0, #128	 ; 0x80 ;
label_162:  ;
LSLS_3(R0, R0, 17);// 162:	0440      	lsls	r0, r0, #17 ;
label_164:  ;
ORRS_2(R0, R4 );// 164:	4320      	orrs	r0, r4 ;
label_166:  ;
STR_3(R0, R3, R2 );// 166:	5098      	str	r0, [r3, r2] ;
label_168:  ;
R3 = 0x40049000 ;// 168:	4b27      	ldr	r3, [pc, #156]	 ; (208 <_reset_init+0xe8>) ;
label_16a:  ;
R4 = 0xfefff8ff ;// 16a:	4c28      	ldr	r4, [pc, #160]	 ; (20c <_reset_init+0xec>) ;
label_16c:  ;
LDR_3(R0, R3, 72);// 16c:	6c98      	ldr	r0, [r3, #72]	 ; 0x48 ;
label_16e:  ;
ANDS_2(R0, R4 );// 16e:	4020      	ands	r0, r4 ;
label_170:  ;
STR_3(R0, R3, 72);// 170:	6498      	str	r0, [r3, #72]	 ; 0x48 ;
label_172:  ;
LDR_3(R2, R3, 76);// 172:	6cda      	ldr	r2, [r3, #76]	 ; 0x4c ;
label_174:  ;
MOVS_2(R0, 0);// 174:	2000      	movs	r0, #0 ;
label_176:  ;
ANDS_2(R2, R4 );// 176:	4022      	ands	r2, r4 ;
label_178:  ;
STR_3(R2, R3, 76);// 178:	64da      	str	r2, [r3, #76]	 ; 0x4c ;
label_17a:  ;
MOVS_2(R2, 36);// 17a:	2224      	movs	r2, #36	 ; 0x24 ;
label_17c:  ;
MOVS_2(R4, 31);// 17c:	241f      	movs	r4, #31 ;
label_17e:  ;
R3 = 0x40065000 ;// 17e:	4b24      	ldr	r3, [pc, #144]	 ; (210 <_reset_init+0xf0>) ;
label_180:  ;
STRB_3(R0, R3, 0);// 180:	7018      	strb	r0, [r3, #0] ;
label_182:  ;
R3 = 0x40064000 ;// 182:	4b24      	ldr	r3, [pc, #144]	 ; (214 <_reset_init+0xf4>) ;
label_184:  ;
STRB_3(R2, R3, 1);// 184:	705a      	strb	r2, [r3, #1] ;
label_186:  ;
ADDS_2(R2, 116);// 186:	3274      	adds	r2, #116	 ; 0x74 ;
label_188:  ;
STRB_3(R2, R3, 0);// 188:	701a      	strb	r2, [r3, #0] ;
label_18a:  ;
LDRB_3(R2, R3, 3);// 18a:	78da      	ldrb	r2, [r3, #3] ;
label_18c:  ;
ANDS_2(R2, R4 );// 18c:	4022      	ands	r2, r4 ;
label_18e:  ;
STRB_3(R2, R3, 3);// 18e:	70da      	strb	r2, [r3, #3] ;
label_190:  ;
MOVS_2(R2, 16);// 190:	2210      	movs	r2, #16 ;
label_192:  ;
STRB_3(R1, R3, 4);// 192:	7119      	strb	r1, [r3, #4] ;
label_194:  ;
STRB_3(R0, R3, 5);// 194:	7158      	strb	r0, [r3, #5] ;
label_196:  ;
LDRB_3(R1, R3, 6);// 196:	7999      	ldrb	r1, [r3, #6] ;
label_198:  ;
TST_2(R1, R2 );// 198:	4211      	tst	r1, r2 ;
label_19a:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_196 ; } ;// 19a:	d1fc      	bnen	196 <_reset_init+0x76> ;
label_19c:  ;
MOVS_2(R1, 12);// 19c:	210c      	movs	r1, #12 ;
label_19e:  ;
LDRB_3(R2, R3, 6);// 19e:	799a      	ldrb	r2, [r3, #6] ;
label_1a0:  ;
ANDS_2(R2, R1 );// 1a0:	400a      	ands	r2, r1 ;
label_1a2:  ;
CMP_2(R2, 8);// 1a2:	2a08      	cmp	r2, #8 ;
label_1a4:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_19e ; } ;// 1a4:	d1fb      	bnen	19e <_reset_init+0x7e> ;
label_1a6:  ;
ADDS_2(R2, 56);// 1a6:	3238      	adds	r2, #56	 ; 0x38 ;
label_1a8:  ;
STRB_3(R2, R3, 5);// 1a8:	715a      	strb	r2, [r3, #5] ;
label_1aa:  ;
LDRB_3(R1, R3, 6);// 1aa:	7999      	ldrb	r1, [r3, #6] ;
label_1ac:  ;
TST_2(R1, R2 );// 1ac:	4211      	tst	r1, r2 ;
label_1ae:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1aa ; } ;// 1ae:	d0fc      	beqn	1aa <_reset_init+0x8a> ;
label_1b0:  ;
MOVS_2(R2, 24);// 1b0:	2218      	movs	r2, #24 ;
label_1b2:  ;
MOVS_2(R1, 12);// 1b2:	210c      	movs	r1, #12 ;
label_1b4:  ;
STRB_3(R2, R3, 0);// 1b4:	701a      	strb	r2, [r3, #0] ;
label_1b6:  ;
LDRB_3(R2, R3, 6);// 1b6:	799a      	ldrb	r2, [r3, #6] ;
label_1b8:  ;
ANDS_2(R2, R1 );// 1b8:	400a      	ands	r2, r1 ;
label_1ba:  ;
CMP_2(R2, 12);// 1ba:	2a0c      	cmp	r2, #12 ;
label_1bc:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1b6 ; } ;// 1bc:	d1fb      	bnen	1b6 <_reset_init+0x96> ;
label_1be:  ;
MOVS_2(R2, 0);// 1be:	2200      	movs	r2, #0 ;
label_1c0:  ;
R0 = 0x1ffff000 ;// 1c0:	4815      	ldr	r0, [pc, #84]	 ; (218 <_reset_init+0xf8>) ;
label_1c2:  ;
R1 = 0x1ffff000 ;// 1c2:	4916      	ldr	r1, [pc, #88]	 ; (21c <_reset_init+0xfc>) ;
label_1c4:  ;
R4 = 0x00000838 ;// 1c4:	4c16      	ldr	r4, [pc, #88]	 ; (220 <_reset_init+0x100>) ;
label_1c6:  ;
ADDS_3(R3, R2, R0 );// 1c6:	1813      	adds	r3, r2, r0 ;
label_1c8:  ;
CMP_2(R3, R1 );// 1c8:	428b      	cmp	r3, r1 ;
label_1ca:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1d8 ; } ;// 1ca:	d305      	bccn	1d8 <_reset_init+0xb8> ;
label_1cc:  ;
MOVS_2(R1, 0);// 1cc:	2100      	movs	r1, #0 ;
label_1ce:  ;
R2 = 0x1ffff004 ;// 1ce:	4a15      	ldr	r2, [pc, #84]	 ; (224 <_reset_init+0x104>) ;
label_1d0:  ;
CMP_2(R3, R2 );// 1d0:	4293      	cmp	r3, r2 ;
label_1d2:  ;
g_cycle_count++;
 if (C_flag == 0 && Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1e0 ; } ;// 1d2:	d905      	blsn	1e0 <_reset_init+0xc0> ;
label_1d4:  ;
g_cycle_count += 3;
main_thread( );// 1d4:	f000 f91c 	bl	410 <main_thread> ;
label_1d8:  ;
LDR_3(R5, R4, R2 );// 1d8:	58a5      	ldr	r5, [r4, r2] ;
label_1da:  ;
ADDS_2(R2, 4);// 1da:	3204      	adds	r2, #4 ;
label_1dc:  ;
STR_3(R5, R3, 0);// 1dc:	601d      	str	r5, [r3, #0] ;
label_1de:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1c6 ; } ;// 1de:	e7f2      	bn	1c6 <_reset_init+0xa6> ;
label_1e0:  ;
STMIA(R3,0b010000000);// 1e0:	c302      	stmia	r3!, r1 ;
label_1e2:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_1d0 ; } ;// 1e2:	e7f5      	bn	1d0 <_reset_init+0xb0> ;
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
//Could not parse:  220:	00000838 	word	0x00000838 ;
label_224:  ;
//Could not parse:  224:	1ffff004 	word	0x1ffff004 ;
}
void __startup_end() 
{}
void _cfm() 
{label_400:  ;
//Could not parse:  400:	ffffffff ffffffff ffffffff fffff77e     ~ ;
}
void main_thread() 
{label_410:  ;
PUSH(SP,0b0000010001);// 410:	b510      	push	r4, lr ;
label_412:  ;
//Could not parse:  412:	b672      	cpsid	i ;
label_414:  ;
g_cycle_count += 3;
initialize_sw( );// 414:	f000 f80c 	bl	430 <initialize_sw> ;
label_418:  ;
g_cycle_count += 3;
configure_rgbled( );// 418:	f000 f860 	bl	4dc <configure_rgbled> ;
label_41c:  ;
//Could not parse:  41c:	b662      	cpsie	i ;
label_41e:  ;
g_cycle_count += 3;
get_SW_count( );// 41e:	f000 f853 	bl	4c8 <get_SW_count> ;
label_422:  ;
MOVS_2(R1, 7);// 422:	2107      	movs	r1, #7 ;
label_424:  ;
g_cycle_count += 3;
__aeabi_idivmod( );// 424:	f000 fa02 	bl	82c <__aeabi_idivmod> ;
label_428:  ;
UXTB_2(R0, R1 );// 428:	b2c8      	uxtb	r0, r1 ;
label_42a:  ;
g_cycle_count += 3;
set_rgbled_color_to( );// 42a:	f000 f8e5 	bl	5f8 <set_rgbled_color_to> ;
label_42e:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_41e ; } ;// 42e:	e7f6      	bn	41e <main+0xe> ;
}
void initialize_sw() 
{label_430:  ;
MOVS_2(R3, 128);// 430:	2380      	movs	r3, #128	 ; 0x80 ;
label_432:  ;
R1 = 0x40047000 ;// 432:	490f      	ldr	r1, [pc, #60]	 ; (470 <initialize_sw+0x40>) ;
label_434:  ;
R2 = 0x00001038 ;// 434:	4a0f      	ldr	r2, [pc, #60]	 ; (474 <initialize_sw+0x44>) ;
label_436:  ;
LSLS_3(R3, R3, 5);// 436:	015b      	lsls	r3, r3, #5 ;
label_438:  ;
LDR_3(R0, R1, R2 );// 438:	5888      	ldr	r0, [r1, r2] ;
label_43a:  ;
ORRS_2(R3, R0 );// 43a:	4303      	orrs	r3, r0 ;
label_43c:  ;
STR_3(R3, R1, R2 );// 43c:	508b      	str	r3, [r1, r2] ;
label_43e:  ;
R2 = 0x000a0103 ;// 43e:	4a0e      	ldr	r2, [pc, #56]	 ; (478 <initialize_sw+0x48>) ;
label_440:  ;
R3 = 0x4004c000 ;// 440:	4b0e      	ldr	r3, [pc, #56]	 ; (47c <initialize_sw+0x4c>) ;
label_442:  ;
MOVS_2(R0, 199);// 442:	20c7      	movs	r0, #199	 ; 0xc7 ;
label_444:  ;
STR_3(R2, R3, 80);// 444:	651a      	str	r2, [r3, #80]	 ; 0x50 ;
label_446:  ;
R2 = 0x400ff0c0 ;// 446:	4a0e      	ldr	r2, [pc, #56]	 ; (480 <initialize_sw+0x50>) ;
label_448:  ;
R1 = 0xffefffff ;// 448:	490e      	ldr	r1, [pc, #56]	 ; (484 <initialize_sw+0x54>) ;
label_44a:  ;
LDR_3(R3, R2, 20);// 44a:	6953      	ldr	r3, [r2, #20] ;
label_44c:  ;
LSLS_3(R0, R0, 2);// 44c:	0080      	lsls	r0, r0, #2 ;
label_44e:  ;
ANDS_2(R3, R1 );// 44e:	400b      	ands	r3, r1 ;
label_450:  ;
MOVS_2(R1, 192);// 450:	21c0      	movs	r1, #192	 ; 0xc0 ;
label_452:  ;
STR_3(R3, R2, 20);// 452:	6153      	str	r3, [r2, #20] ;
label_454:  ;
R2 = 0xe000e100 ;// 454:	4a0c      	ldr	r2, [pc, #48]	 ; (488 <initialize_sw+0x58>) ;
label_456:  ;
LSLS_3(R1, R1, 24);// 456:	0609      	lsls	r1, r1, #24 ;
label_458:  ;
LDR_3(R3, R2, R0 );// 458:	5813      	ldr	r3, [r2, r0] ;
label_45a:  ;
LSLS_3(R3, R3, 8);// 45a:	021b      	lsls	r3, r3, #8 ;
label_45c:  ;
LSRS_3(R3, R3, 8);// 45c:	0a1b      	lsrs	r3, r3, #8 ;
label_45e:  ;
ORRS_2(R3, R1 );// 45e:	430b      	orrs	r3, r1 ;
label_460:  ;
STR_3(R3, R2, R0 );// 460:	5013      	str	r3, [r2, r0] ;
label_462:  ;
MOVS_2(R1, 192);// 462:	21c0      	movs	r1, #192	 ; 0xc0 ;
label_464:  ;
MOVS_2(R3, 128);// 464:	2380      	movs	r3, #128	 ; 0x80 ;
label_466:  ;
LSLS_3(R1, R1, 1);// 466:	0049      	lsls	r1, r1, #1 ;
label_468:  ;
LSLS_3(R3, R3, 24);// 468:	061b      	lsls	r3, r3, #24 ;
label_46a:  ;
STR_3(R3, R2, R1 );// 46a:	5053      	str	r3, [r2, r1] ;
label_46c:  ;
STR_3(R3, R2, 0);// 46c:	6013      	str	r3, [r2, #0] ;
label_46e:  ;
return ;// 46e:	4770      	bx	lr ;
label_470:  ;
//Could not parse:  470:	40047000 	word	0x40047000 ;
label_474:  ;
//Could not parse:  474:	00001038 	word	0x00001038 ;
label_478:  ;
//Could not parse:  478:	000a0103 	word	0x000a0103 ;
label_47c:  ;
//Could not parse:  47c:	4004c000 	word	0x4004c000 ;
label_480:  ;
//Could not parse:  480:	400ff0c0 	word	0x400ff0c0 ;
label_484:  ;
//Could not parse:  484:	ffefffff 	word	0xffefffff ;
label_488:  ;
//Could not parse:  488:	e000e100 	word	0xe000e100 ;
}
void PORTA_IRQHandler() 
{label_48c:  ;
PUSH(SP,0b0000010001);// 48c:	b510      	push	r4, lr ;
label_48e:  ;
MOVS_2(R0, 1);// 48e:	2001      	movs	r0, #1 ;
label_490:  ;
g_cycle_count += 3;
set_rgbled_color_to( );// 490:	f000 f8b2 	bl	5f8 <set_rgbled_color_to> ;
label_494:  ;
R2 = 0x1ffff000 ;// 494:	4a04      	ldr	r2, [pc, #16]	 ; (4a8 <PORTA_IRQHandler+0x1c>) ;
label_496:  ;
LDR_3(R3, R2, 0);// 496:	6813      	ldr	r3, [r2, #0] ;
label_498:  ;
ADDS_2(R3, 1);// 498:	3301      	adds	r3, #1 ;
label_49a:  ;
STR_3(R3, R2, 0);// 49a:	6013      	str	r3, [r2, #0] ;
label_49c:  ;
MOVS_2(R2, 128);// 49c:	2280      	movs	r2, #128	 ; 0x80 ;
label_49e:  ;
R3 = 0x4004c0a0 ;// 49e:	4b03      	ldr	r3, [pc, #12]	 ; (4ac <PORTA_IRQHandler+0x20>) ;
label_4a0:  ;
LSLS_3(R2, R2, 13);// 4a0:	0352      	lsls	r2, r2, #13 ;
label_4a2:  ;
STR_3(R2, R3, 0);// 4a2:	601a      	str	r2, [r3, #0] ;
label_4a4:  ;
POP(SP,0b0000010001);
return ;// 4a4:	bd10      	pop	r4, pc ;
label_4a6:  ;
//Could not parse:  4a6:	46c0      	nop			 ; (mov r8, r8) ;
label_4a8:  ;
//Could not parse:  4a8:	1ffff000 	word	0x1ffff000 ;
label_4ac:  ;
//Could not parse:  4ac:	4004c0a0 	word	0x4004c0a0 ;
}
void get_and_clear_SW_count() 
{label_4b0:  ;
MRS_2(R2, PRIMASK );// 4b0:	f3ef 8210 	mrs	r2, PRIMASK ;
label_4b4:  ;
//Could not parse:  4b4:	b672      	cpsid	i ;
label_4b6:  ;
MOVS_2(R1, 0);// 4b6:	2100      	movs	r1, #0 ;
label_4b8:  ;
R3 = 0x1ffff000 ;// 4b8:	4b02      	ldr	r3, [pc, #8]	 ; (4c4 <get_and_clear_SW_count+0x14>) ;
label_4ba:  ;
LDR_3(R0, R3, 0);// 4ba:	6818      	ldr	r0, [r3, #0] ;
label_4bc:  ;
STR_3(R1, R3, 0);// 4bc:	6019      	str	r1, [r3, #0] ;
label_4be:  ;
MSR_2(PRIMASK, R2 );// 4be:	f382 8810 	msr	PRIMASK, r2 ;
label_4c2:  ;
return ;// 4c2:	4770      	bx	lr ;
label_4c4:  ;
//Could not parse:  4c4:	1ffff000 	word	0x1ffff000 ;
}
void get_SW_count() 
{label_4c8:  ;
MRS_2(R3, PRIMASK );// 4c8:	f3ef 8310 	mrs	r3, PRIMASK ;
label_4cc:  ;
//Could not parse:  4cc:	b672      	cpsid	i ;
label_4ce:  ;
R2 = 0x1ffff000 ;// 4ce:	4a02      	ldr	r2, [pc, #8]	 ; (4d8 <get_SW_count+0x10>) ;
label_4d0:  ;
LDR_3(R0, R2, 0);// 4d0:	6810      	ldr	r0, [r2, #0] ;
label_4d2:  ;
MSR_2(PRIMASK, R3 );// 4d2:	f383 8810 	msr	PRIMASK, r3 ;
label_4d6:  ;
return ;// 4d6:	4770      	bx	lr ;
label_4d8:  ;
//Could not parse:  4d8:	1ffff000 	word	0x1ffff000 ;
}
void configure_rgbled() 
{label_4dc:  ;
MOVS_2(R3, 160);// 4dc:	23a0      	movs	r3, #160	 ; 0xa0 ;
label_4de:  ;
R1 = 0x40047000 ;// 4de:	4914      	ldr	r1, [pc, #80]	 ; (530 <configure_rgbled+0x54>) ;
label_4e0:  ;
R2 = 0x00001038 ;// 4e0:	4a14      	ldr	r2, [pc, #80]	 ; (534 <configure_rgbled+0x58>) ;
label_4e2:  ;
LSLS_3(R3, R3, 5);// 4e2:	015b      	lsls	r3, r3, #5 ;
label_4e4:  ;
LDR_3(R0, R1, R2 );// 4e4:	5888      	ldr	r0, [r1, r2] ;
label_4e6:  ;
ORRS_2(R3, R0 );// 4e6:	4303      	orrs	r3, r0 ;
label_4e8:  ;
STR_3(R3, R1, R2 );// 4e8:	508b      	str	r3, [r1, r2] ;
label_4ea:  ;
R3 = 0x4004a000 ;// 4ea:	4b13      	ldr	r3, [pc, #76]	 ; (538 <configure_rgbled+0x5c>) ;
label_4ec:  ;
R0 = 0xfffff8ff ;// 4ec:	4813      	ldr	r0, [pc, #76]	 ; (53c <configure_rgbled+0x60>) ;
label_4ee:  ;
LDR_3(R2, R3, 72);// 4ee:	6c9a      	ldr	r2, [r3, #72]	 ; 0x48 ;
label_4f0:  ;
ANDS_2(R2, R0 );// 4f0:	4002      	ands	r2, r0 ;
label_4f2:  ;
STR_3(R2, R3, 72);// 4f2:	649a      	str	r2, [r3, #72]	 ; 0x48 ;
label_4f4:  ;
MOVS_2(R2, 128);// 4f4:	2280      	movs	r2, #128	 ; 0x80 ;
label_4f6:  ;
LDR_3(R1, R3, 72);// 4f6:	6c99      	ldr	r1, [r3, #72]	 ; 0x48 ;
label_4f8:  ;
LSLS_3(R2, R2, 1);// 4f8:	0052      	lsls	r2, r2, #1 ;
label_4fa:  ;
ORRS_2(R1, R2 );// 4fa:	4311      	orrs	r1, r2 ;
label_4fc:  ;
STR_3(R1, R3, 72);// 4fc:	6499      	str	r1, [r3, #72]	 ; 0x48 ;
label_4fe:  ;
LDR_3(R1, R3, 76);// 4fe:	6cd9      	ldr	r1, [r3, #76]	 ; 0x4c ;
label_500:  ;
ANDS_2(R1, R0 );// 500:	4001      	ands	r1, r0 ;
label_502:  ;
STR_3(R1, R3, 76);// 502:	64d9      	str	r1, [r3, #76]	 ; 0x4c ;
label_504:  ;
LDR_3(R1, R3, 76);// 504:	6cd9      	ldr	r1, [r3, #76]	 ; 0x4c ;
label_506:  ;
ORRS_2(R1, R2 );// 506:	4311      	orrs	r1, r2 ;
label_508:  ;
STR_3(R1, R3, 76);// 508:	64d9      	str	r1, [r3, #76]	 ; 0x4c ;
label_50a:  ;
R3 = 0x4004c000 ;// 50a:	4b0d      	ldr	r3, [pc, #52]	 ; (540 <configure_rgbled+0x64>) ;
label_50c:  ;
LDR_3(R1, R3, 4);// 50c:	6859      	ldr	r1, [r3, #4] ;
label_50e:  ;
ANDS_2(R1, R0 );// 50e:	4001      	ands	r1, r0 ;
label_510:  ;
STR_3(R1, R3, 4);// 510:	6059      	str	r1, [r3, #4] ;
label_512:  ;
LDR_3(R1, R3, 4);// 512:	6859      	ldr	r1, [r3, #4] ;
label_514:  ;
ORRS_2(R2, R1 );// 514:	430a      	orrs	r2, r1 ;
label_516:  ;
STR_3(R2, R3, 4);// 516:	605a      	str	r2, [r3, #4] ;
label_518:  ;
MOVS_2(R3, 192);// 518:	23c0      	movs	r3, #192	 ; 0xc0 ;
label_51a:  ;
R2 = 0x400ff040 ;// 51a:	4a0a      	ldr	r2, [pc, #40]	 ; (544 <configure_rgbled+0x68>) ;
label_51c:  ;
LSLS_3(R3, R3, 12);// 51c:	031b      	lsls	r3, r3, #12 ;
label_51e:  ;
LDR_3(R1, R2, 20);// 51e:	6951      	ldr	r1, [r2, #20] ;
label_520:  ;
ORRS_2(R3, R1 );// 520:	430b      	orrs	r3, r1 ;
label_522:  ;
STR_3(R3, R2, 20);// 522:	6153      	str	r3, [r2, #20] ;
label_524:  ;
MOVS_2(R3, 2);// 524:	2302      	movs	r3, #2 ;
label_526:  ;
R2 = 0x400ff0c0 ;// 526:	4a08      	ldr	r2, [pc, #32]	 ; (548 <configure_rgbled+0x6c>) ;
label_528:  ;
LDR_3(R1, R2, 20);// 528:	6951      	ldr	r1, [r2, #20] ;
label_52a:  ;
ORRS_2(R3, R1 );// 52a:	430b      	orrs	r3, r1 ;
label_52c:  ;
STR_3(R3, R2, 20);// 52c:	6153      	str	r3, [r2, #20] ;
label_52e:  ;
return ;// 52e:	4770      	bx	lr ;
label_530:  ;
//Could not parse:  530:	40047000 	word	0x40047000 ;
label_534:  ;
//Could not parse:  534:	00001038 	word	0x00001038 ;
label_538:  ;
//Could not parse:  538:	4004a000 	word	0x4004a000 ;
label_53c:  ;
//Could not parse:  53c:	fffff8ff 	word	0xfffff8ff ;
label_540:  ;
//Could not parse:  540:	4004c000 	word	0x4004c000 ;
label_544:  ;
//Could not parse:  544:	400ff040 	word	0x400ff040 ;
label_548:  ;
//Could not parse:  548:	400ff0c0 	word	0x400ff0c0 ;
}
void turn_on_green_led() 
{label_54c:  ;
MOVS_2(R3, 128);// 54c:	2380      	movs	r3, #128	 ; 0x80 ;
label_54e:  ;
R2 = 0x400ff040 ;// 54e:	4a03      	ldr	r2, [pc, #12]	 ; (55c <turn_on_green_led+0x10>) ;
label_550:  ;
LSLS_3(R3, R3, 12);// 550:	031b      	lsls	r3, r3, #12 ;
label_552:  ;
LDR_3(R1, R2, 8);// 552:	6891      	ldr	r1, [r2, #8] ;
label_554:  ;
ORRS_2(R3, R1 );// 554:	430b      	orrs	r3, r1 ;
label_556:  ;
STR_3(R3, R2, 8);// 556:	6093      	str	r3, [r2, #8] ;
label_558:  ;
return ;// 558:	4770      	bx	lr ;
label_55a:  ;
//Could not parse:  55a:	46c0      	nop			 ; (mov r8, r8) ;
label_55c:  ;
//Could not parse:  55c:	400ff040 	word	0x400ff040 ;
}
void turn_off_green_led() 
{label_560:  ;
MOVS_2(R3, 128);// 560:	2380      	movs	r3, #128	 ; 0x80 ;
label_562:  ;
R2 = 0x400ff040 ;// 562:	4a03      	ldr	r2, [pc, #12]	 ; (570 <turn_off_green_led+0x10>) ;
label_564:  ;
LSLS_3(R3, R3, 12);// 564:	031b      	lsls	r3, r3, #12 ;
label_566:  ;
LDR_3(R1, R2, 4);// 566:	6851      	ldr	r1, [r2, #4] ;
label_568:  ;
ORRS_2(R3, R1 );// 568:	430b      	orrs	r3, r1 ;
label_56a:  ;
STR_3(R3, R2, 4);// 56a:	6053      	str	r3, [r2, #4] ;
label_56c:  ;
return ;// 56c:	4770      	bx	lr ;
label_56e:  ;
//Could not parse:  56e:	46c0      	nop			 ; (mov r8, r8) ;
label_570:  ;
//Could not parse:  570:	400ff040 	word	0x400ff040 ;
}
void toggle_green_led() 
{label_574:  ;
MOVS_2(R3, 128);// 574:	2380      	movs	r3, #128	 ; 0x80 ;
label_576:  ;
R2 = 0x400ff040 ;// 576:	4a03      	ldr	r2, [pc, #12]	 ; (584 <toggle_green_led+0x10>) ;
label_578:  ;
LSLS_3(R3, R3, 12);// 578:	031b      	lsls	r3, r3, #12 ;
label_57a:  ;
LDR_3(R1, R2, 12);// 57a:	68d1      	ldr	r1, [r2, #12] ;
label_57c:  ;
ORRS_2(R3, R1 );// 57c:	430b      	orrs	r3, r1 ;
label_57e:  ;
STR_3(R3, R2, 12);// 57e:	60d3      	str	r3, [r2, #12] ;
label_580:  ;
return ;// 580:	4770      	bx	lr ;
label_582:  ;
//Could not parse:  582:	46c0      	nop			 ; (mov r8, r8) ;
label_584:  ;
//Could not parse:  584:	400ff040 	word	0x400ff040 ;
}
void turn_on_red_led() 
{label_588:  ;
MOVS_2(R3, 128);// 588:	2380      	movs	r3, #128	 ; 0x80 ;
label_58a:  ;
R2 = 0x400ff040 ;// 58a:	4a03      	ldr	r2, [pc, #12]	 ; (598 <turn_on_red_led+0x10>) ;
label_58c:  ;
LSLS_3(R3, R3, 11);// 58c:	02db      	lsls	r3, r3, #11 ;
label_58e:  ;
LDR_3(R1, R2, 8);// 58e:	6891      	ldr	r1, [r2, #8] ;
label_590:  ;
ORRS_2(R3, R1 );// 590:	430b      	orrs	r3, r1 ;
label_592:  ;
STR_3(R3, R2, 8);// 592:	6093      	str	r3, [r2, #8] ;
label_594:  ;
return ;// 594:	4770      	bx	lr ;
label_596:  ;
//Could not parse:  596:	46c0      	nop			 ; (mov r8, r8) ;
label_598:  ;
//Could not parse:  598:	400ff040 	word	0x400ff040 ;
}
void turn_off_red_led() 
{label_59c:  ;
MOVS_2(R3, 128);// 59c:	2380      	movs	r3, #128	 ; 0x80 ;
label_59e:  ;
R2 = 0x400ff040 ;// 59e:	4a03      	ldr	r2, [pc, #12]	 ; (5ac <turn_off_red_led+0x10>) ;
label_5a0:  ;
LSLS_3(R3, R3, 11);// 5a0:	02db      	lsls	r3, r3, #11 ;
label_5a2:  ;
LDR_3(R1, R2, 4);// 5a2:	6851      	ldr	r1, [r2, #4] ;
label_5a4:  ;
ORRS_2(R3, R1 );// 5a4:	430b      	orrs	r3, r1 ;
label_5a6:  ;
STR_3(R3, R2, 4);// 5a6:	6053      	str	r3, [r2, #4] ;
label_5a8:  ;
return ;// 5a8:	4770      	bx	lr ;
label_5aa:  ;
//Could not parse:  5aa:	46c0      	nop			 ; (mov r8, r8) ;
label_5ac:  ;
//Could not parse:  5ac:	400ff040 	word	0x400ff040 ;
}
void toggle_red_led() 
{label_5b0:  ;
MOVS_2(R3, 128);// 5b0:	2380      	movs	r3, #128	 ; 0x80 ;
label_5b2:  ;
R2 = 0x400ff040 ;// 5b2:	4a03      	ldr	r2, [pc, #12]	 ; (5c0 <toggle_red_led+0x10>) ;
label_5b4:  ;
LSLS_3(R3, R3, 11);// 5b4:	02db      	lsls	r3, r3, #11 ;
label_5b6:  ;
LDR_3(R1, R2, 12);// 5b6:	68d1      	ldr	r1, [r2, #12] ;
label_5b8:  ;
ORRS_2(R3, R1 );// 5b8:	430b      	orrs	r3, r1 ;
label_5ba:  ;
STR_3(R3, R2, 12);// 5ba:	60d3      	str	r3, [r2, #12] ;
label_5bc:  ;
return ;// 5bc:	4770      	bx	lr ;
label_5be:  ;
//Could not parse:  5be:	46c0      	nop			 ; (mov r8, r8) ;
label_5c0:  ;
//Could not parse:  5c0:	400ff040 	word	0x400ff040 ;
}
void turn_on_blue_led() 
{label_5c4:  ;
MOVS_2(R3, 2);// 5c4:	2302      	movs	r3, #2 ;
label_5c6:  ;
R2 = 0x400ff0c0 ;// 5c6:	4a02      	ldr	r2, [pc, #8]	 ; (5d0 <turn_on_blue_led+0xc>) ;
label_5c8:  ;
LDR_3(R1, R2, 8);// 5c8:	6891      	ldr	r1, [r2, #8] ;
label_5ca:  ;
ORRS_2(R3, R1 );// 5ca:	430b      	orrs	r3, r1 ;
label_5cc:  ;
STR_3(R3, R2, 8);// 5cc:	6093      	str	r3, [r2, #8] ;
label_5ce:  ;
return ;// 5ce:	4770      	bx	lr ;
label_5d0:  ;
//Could not parse:  5d0:	400ff0c0 	word	0x400ff0c0 ;
}
void turn_off_blue_led() 
{label_5d4:  ;
MOVS_2(R3, 2);// 5d4:	2302      	movs	r3, #2 ;
label_5d6:  ;
R2 = 0x400ff0c0 ;// 5d6:	4a02      	ldr	r2, [pc, #8]	 ; (5e0 <turn_off_blue_led+0xc>) ;
label_5d8:  ;
LDR_3(R1, R2, 4);// 5d8:	6851      	ldr	r1, [r2, #4] ;
label_5da:  ;
ORRS_2(R3, R1 );// 5da:	430b      	orrs	r3, r1 ;
label_5dc:  ;
STR_3(R3, R2, 4);// 5dc:	6053      	str	r3, [r2, #4] ;
label_5de:  ;
return ;// 5de:	4770      	bx	lr ;
label_5e0:  ;
//Could not parse:  5e0:	400ff0c0 	word	0x400ff0c0 ;
}
void toggle_blue_led() 
{label_5e4:  ;
MOVS_2(R3, 128);// 5e4:	2380      	movs	r3, #128	 ; 0x80 ;
label_5e6:  ;
R2 = 0x400ff0c0 ;// 5e6:	4a03      	ldr	r2, [pc, #12]	 ; (5f4 <toggle_blue_led+0x10>) ;
label_5e8:  ;
LSLS_3(R3, R3, 11);// 5e8:	02db      	lsls	r3, r3, #11 ;
label_5ea:  ;
LDR_3(R1, R2, 12);// 5ea:	68d1      	ldr	r1, [r2, #12] ;
label_5ec:  ;
ORRS_2(R3, R1 );// 5ec:	430b      	orrs	r3, r1 ;
label_5ee:  ;
STR_3(R3, R2, 12);// 5ee:	60d3      	str	r3, [r2, #12] ;
label_5f0:  ;
return ;// 5f0:	4770      	bx	lr ;
label_5f2:  ;
//Could not parse:  5f2:	46c0      	nop			 ; (mov r8, r8) ;
label_5f4:  ;
//Could not parse:  5f4:	400ff0c0 	word	0x400ff0c0 ;
}
void set_rgbled_color_to() 
{label_5f8:  ;
PUSH(SP,0b0000010001);// 5f8:	b510      	push	r4, lr ;
label_5fa:  ;
CMP_2(R0, 0);// 5fa:	2800      	cmp	r0, #0 ;
label_5fc:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_60c ; } ;// 5fc:	d106      	bnen	60c <set_rgbled_color_to+0x14> ;
label_5fe:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 5fe:	f7ff ffe9 	bl	5d4 <turn_off_blue_led> ;
label_602:  ;
g_cycle_count += 3;
turn_off_green_led( );// 602:	f7ff ffad 	bl	560 <turn_off_green_led> ;
label_606:  ;
g_cycle_count += 3;
turn_off_red_led( );// 606:	f7ff ffc9 	bl	59c <turn_off_red_led> ;
label_60a:  ;
POP(SP,0b0000010001);
return ;// 60a:	bd10      	pop	r4, pc ;
label_60c:  ;
CMP_2(R0, 1);// 60c:	2801      	cmp	r0, #1 ;
label_60e:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_616 ; } ;// 60e:	d102      	bnen	616 <set_rgbled_color_to+0x1e> ;
label_610:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 610:	f7ff ffd8 	bl	5c4 <turn_on_blue_led> ;
label_614:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_602 ; } ;// 614:	e7f5      	bn	602 <set_rgbled_color_to+0xa> ;
label_616:  ;
CMP_2(R0, 2);// 616:	2802      	cmp	r0, #2 ;
label_618:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_624 ; } ;// 618:	d104      	bnen	624 <set_rgbled_color_to+0x2c> ;
label_61a:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 61a:	f7ff ffdb 	bl	5d4 <turn_off_blue_led> ;
label_61e:  ;
g_cycle_count += 3;
turn_on_green_led( );// 61e:	f7ff ff95 	bl	54c <turn_on_green_led> ;
label_622:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_606 ; } ;// 622:	e7f0      	bn	606 <set_rgbled_color_to+0xe> ;
label_624:  ;
CMP_2(R0, 3);// 624:	2803      	cmp	r0, #3 ;
label_626:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_62e ; } ;// 626:	d102      	bnen	62e <set_rgbled_color_to+0x36> ;
label_628:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 628:	f7ff ffcc 	bl	5c4 <turn_on_blue_led> ;
label_62c:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_61e ; } ;// 62c:	e7f7      	bn	61e <set_rgbled_color_to+0x26> ;
label_62e:  ;
CMP_2(R0, 4);// 62e:	2804      	cmp	r0, #4 ;
label_630:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_640 ; } ;// 630:	d106      	bnen	640 <set_rgbled_color_to+0x48> ;
label_632:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 632:	f7ff ffcf 	bl	5d4 <turn_off_blue_led> ;
label_636:  ;
g_cycle_count += 3;
turn_off_green_led( );// 636:	f7ff ff93 	bl	560 <turn_off_green_led> ;
label_63a:  ;
g_cycle_count += 3;
turn_on_red_led( );// 63a:	f7ff ffa5 	bl	588 <turn_on_red_led> ;
label_63e:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_60a ; } ;// 63e:	e7e4      	bn	60a <set_rgbled_color_to+0x12> ;
label_640:  ;
CMP_2(R0, 5);// 640:	2805      	cmp	r0, #5 ;
label_642:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_64a ; } ;// 642:	d102      	bnen	64a <set_rgbled_color_to+0x52> ;
label_644:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 644:	f7ff ffbe 	bl	5c4 <turn_on_blue_led> ;
label_648:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_636 ; } ;// 648:	e7f5      	bn	636 <set_rgbled_color_to+0x3e> ;
label_64a:  ;
CMP_2(R0, 6);// 64a:	2806      	cmp	r0, #6 ;
label_64c:  ;
g_cycle_count++;
 if (Z_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_658 ; } ;// 64c:	d104      	bnen	658 <set_rgbled_color_to+0x60> ;
label_64e:  ;
g_cycle_count += 3;
turn_off_blue_led( );// 64e:	f7ff ffc1 	bl	5d4 <turn_off_blue_led> ;
label_652:  ;
g_cycle_count += 3;
turn_on_green_led( );// 652:	f7ff ff7b 	bl	54c <turn_on_green_led> ;
label_656:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_63a ; } ;// 656:	e7f0      	bn	63a <set_rgbled_color_to+0x42> ;
label_658:  ;
g_cycle_count += 3;
turn_on_blue_led( );// 658:	f7ff ffb4 	bl	5c4 <turn_on_blue_led> ;
label_65c:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_652 ; } ;// 65c:	e7f9      	bn	652 <set_rgbled_color_to+0x5a> ;
}
void __aeabi_idiv() 
{label_660:  ;
MOV_2(R3, R0 );// 660:	4603      	mov	r3, r0 ;
label_662:  ;
ORRS_2(R3, R1 );// 662:	430b      	orrs	r3, r1 ;
label_664:  ;
g_cycle_count++;
 if (N_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_766 ; } ;// 664:	d47f      	bmin	766 <__aeabi_idiv+0x106> ;
label_666:  ;
MOVS_2(R2, 0);// 666:	2200      	movs	r2, #0 ;
label_668:  ;
LSRS_3(R3, R0, 1);// 668:	0843      	lsrs	r3, r0, #1 ;
label_66a:  ;
CMP_2(R3, R1 );// 66a:	428b      	cmp	r3, r1 ;
label_66c:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_758 ; } ;// 66c:	d374      	bccn	758 <__aeabi_idiv+0xf8> ;
label_66e:  ;
LSRS_3(R3, R0, 4);// 66e:	0903      	lsrs	r3, r0, #4 ;
label_670:  ;
CMP_2(R3, R1 );// 670:	428b      	cmp	r3, r1 ;
label_672:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_734 ; } ;// 672:	d35f      	bccn	734 <__aeabi_idiv+0xd4> ;
label_674:  ;
LSRS_3(R3, R0, 8);// 674:	0a03      	lsrs	r3, r0, #8 ;
label_676:  ;
CMP_2(R3, R1 );// 676:	428b      	cmp	r3, r1 ;
label_678:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_704 ; } ;// 678:	d344      	bccn	704 <__aeabi_idiv+0xa4> ;
label_67a:  ;
LSRS_3(R3, R0, 12);// 67a:	0b03      	lsrs	r3, r0, #12 ;
label_67c:  ;
CMP_2(R3, R1 );// 67c:	428b      	cmp	r3, r1 ;
label_67e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6d2 ; } ;// 67e:	d328      	bccn	6d2 <__aeabi_idiv+0x72> ;
label_680:  ;
LSRS_3(R3, R0, 16);// 680:	0c03      	lsrs	r3, r0, #16 ;
label_682:  ;
CMP_2(R3, R1 );// 682:	428b      	cmp	r3, r1 ;
label_684:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6a2 ; } ;// 684:	d30d      	bccn	6a2 <__aeabi_idiv+0x42> ;
label_686:  ;
MOVS_2(R2, 255);// 686:	22ff      	movs	r2, #255	 ; 0xff ;
label_688:  ;
LSLS_3(R1, R1, 8);// 688:	0209      	lsls	r1, r1, #8 ;
label_68a:  ;
//Could not parse:  68a:	ba12      	rev	r2, r2 ;
label_68c:  ;
LSRS_3(R3, R0, 16);// 68c:	0c03      	lsrs	r3, r0, #16 ;
label_68e:  ;
CMP_2(R3, R1 );// 68e:	428b      	cmp	r3, r1 ;
label_690:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_698 ; } ;// 690:	d302      	bccn	698 <__aeabi_idiv+0x38> ;
label_692:  ;
//Could not parse:  692:	1212      	asrs	r2, r2, #8 ;
label_694:  ;
LSLS_3(R1, R1, 8);// 694:	0209      	lsls	r1, r1, #8 ;
label_696:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_764 ; } ;// 696:	d065      	beqn	764 <__aeabi_idiv+0x104> ;
label_698:  ;
LSRS_3(R3, R0, 12);// 698:	0b03      	lsrs	r3, r0, #12 ;
label_69a:  ;
CMP_2(R3, R1 );// 69a:	428b      	cmp	r3, r1 ;
label_69c:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6d2 ; } ;// 69c:	d319      	bccn	6d2 <__aeabi_idiv+0x72> ;
label_69e:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6a2 ; } ;// 69e:	e000      	bn	6a2 <__aeabi_idiv+0x42> ;
label_6a0:  ;
LSRS_3(R1, R1, 8);// 6a0:	0a09      	lsrs	r1, r1, #8 ;
label_6a2:  ;
LSRS_3(R3, R0, 15);// 6a2:	0bc3      	lsrs	r3, r0, #15 ;
label_6a4:  ;
CMP_2(R3, R1 );// 6a4:	428b      	cmp	r3, r1 ;
label_6a6:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6ac ; } ;// 6a6:	d301      	bccn	6ac <__aeabi_idiv+0x4c> ;
label_6a8:  ;
LSLS_3(R3, R1, 15);// 6a8:	03cb      	lsls	r3, r1, #15 ;
label_6aa:  ;
SUBS_3(R0, R0, R3 );// 6aa:	1ac0      	subs	r0, r0, r3 ;
label_6ac:  ;
//Could not parse:  6ac:	4152      	adcs	r2, r2 ;
label_6ae:  ;
LSRS_3(R3, R0, 14);// 6ae:	0b83      	lsrs	r3, r0, #14 ;
label_6b0:  ;
CMP_2(R3, R1 );// 6b0:	428b      	cmp	r3, r1 ;
label_6b2:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6b8 ; } ;// 6b2:	d301      	bccn	6b8 <__aeabi_idiv+0x58> ;
label_6b4:  ;
LSLS_3(R3, R1, 14);// 6b4:	038b      	lsls	r3, r1, #14 ;
label_6b6:  ;
SUBS_3(R0, R0, R3 );// 6b6:	1ac0      	subs	r0, r0, r3 ;
label_6b8:  ;
//Could not parse:  6b8:	4152      	adcs	r2, r2 ;
label_6ba:  ;
LSRS_3(R3, R0, 13);// 6ba:	0b43      	lsrs	r3, r0, #13 ;
label_6bc:  ;
CMP_2(R3, R1 );// 6bc:	428b      	cmp	r3, r1 ;
label_6be:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6c4 ; } ;// 6be:	d301      	bccn	6c4 <__aeabi_idiv+0x64> ;
label_6c0:  ;
LSLS_3(R3, R1, 13);// 6c0:	034b      	lsls	r3, r1, #13 ;
label_6c2:  ;
SUBS_3(R0, R0, R3 );// 6c2:	1ac0      	subs	r0, r0, r3 ;
label_6c4:  ;
//Could not parse:  6c4:	4152      	adcs	r2, r2 ;
label_6c6:  ;
LSRS_3(R3, R0, 12);// 6c6:	0b03      	lsrs	r3, r0, #12 ;
label_6c8:  ;
CMP_2(R3, R1 );// 6c8:	428b      	cmp	r3, r1 ;
label_6ca:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6d0 ; } ;// 6ca:	d301      	bccn	6d0 <__aeabi_idiv+0x70> ;
label_6cc:  ;
LSLS_3(R3, R1, 12);// 6cc:	030b      	lsls	r3, r1, #12 ;
label_6ce:  ;
SUBS_3(R0, R0, R3 );// 6ce:	1ac0      	subs	r0, r0, r3 ;
label_6d0:  ;
//Could not parse:  6d0:	4152      	adcs	r2, r2 ;
label_6d2:  ;
LSRS_3(R3, R0, 11);// 6d2:	0ac3      	lsrs	r3, r0, #11 ;
label_6d4:  ;
CMP_2(R3, R1 );// 6d4:	428b      	cmp	r3, r1 ;
label_6d6:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6dc ; } ;// 6d6:	d301      	bccn	6dc <__aeabi_idiv+0x7c> ;
label_6d8:  ;
LSLS_3(R3, R1, 11);// 6d8:	02cb      	lsls	r3, r1, #11 ;
label_6da:  ;
SUBS_3(R0, R0, R3 );// 6da:	1ac0      	subs	r0, r0, r3 ;
label_6dc:  ;
//Could not parse:  6dc:	4152      	adcs	r2, r2 ;
label_6de:  ;
LSRS_3(R3, R0, 10);// 6de:	0a83      	lsrs	r3, r0, #10 ;
label_6e0:  ;
CMP_2(R3, R1 );// 6e0:	428b      	cmp	r3, r1 ;
label_6e2:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6e8 ; } ;// 6e2:	d301      	bccn	6e8 <__aeabi_idiv+0x88> ;
label_6e4:  ;
LSLS_3(R3, R1, 10);// 6e4:	028b      	lsls	r3, r1, #10 ;
label_6e6:  ;
SUBS_3(R0, R0, R3 );// 6e6:	1ac0      	subs	r0, r0, r3 ;
label_6e8:  ;
//Could not parse:  6e8:	4152      	adcs	r2, r2 ;
label_6ea:  ;
LSRS_3(R3, R0, 9);// 6ea:	0a43      	lsrs	r3, r0, #9 ;
label_6ec:  ;
CMP_2(R3, R1 );// 6ec:	428b      	cmp	r3, r1 ;
label_6ee:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6f4 ; } ;// 6ee:	d301      	bccn	6f4 <__aeabi_idiv+0x94> ;
label_6f0:  ;
LSLS_3(R3, R1, 9);// 6f0:	024b      	lsls	r3, r1, #9 ;
label_6f2:  ;
SUBS_3(R0, R0, R3 );// 6f2:	1ac0      	subs	r0, r0, r3 ;
label_6f4:  ;
//Could not parse:  6f4:	4152      	adcs	r2, r2 ;
label_6f6:  ;
LSRS_3(R3, R0, 8);// 6f6:	0a03      	lsrs	r3, r0, #8 ;
label_6f8:  ;
CMP_2(R3, R1 );// 6f8:	428b      	cmp	r3, r1 ;
label_6fa:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_700 ; } ;// 6fa:	d301      	bccn	700 <__aeabi_idiv+0xa0> ;
label_6fc:  ;
LSLS_3(R3, R1, 8);// 6fc:	020b      	lsls	r3, r1, #8 ;
label_6fe:  ;
SUBS_3(R0, R0, R3 );// 6fe:	1ac0      	subs	r0, r0, r3 ;
label_700:  ;
//Could not parse:  700:	4152      	adcs	r2, r2 ;
label_702:  ;
g_cycle_count++;
 if (C_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_6a0 ; } ;// 702:	d2cd      	bcsn	6a0 <__aeabi_idiv+0x40> ;
label_704:  ;
LSRS_3(R3, R0, 7);// 704:	09c3      	lsrs	r3, r0, #7 ;
label_706:  ;
CMP_2(R3, R1 );// 706:	428b      	cmp	r3, r1 ;
label_708:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_70e ; } ;// 708:	d301      	bccn	70e <__aeabi_idiv+0xae> ;
label_70a:  ;
LSLS_3(R3, R1, 7);// 70a:	01cb      	lsls	r3, r1, #7 ;
label_70c:  ;
SUBS_3(R0, R0, R3 );// 70c:	1ac0      	subs	r0, r0, r3 ;
label_70e:  ;
//Could not parse:  70e:	4152      	adcs	r2, r2 ;
label_710:  ;
LSRS_3(R3, R0, 6);// 710:	0983      	lsrs	r3, r0, #6 ;
label_712:  ;
CMP_2(R3, R1 );// 712:	428b      	cmp	r3, r1 ;
label_714:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_71a ; } ;// 714:	d301      	bccn	71a <__aeabi_idiv+0xba> ;
label_716:  ;
LSLS_3(R3, R1, 6);// 716:	018b      	lsls	r3, r1, #6 ;
label_718:  ;
SUBS_3(R0, R0, R3 );// 718:	1ac0      	subs	r0, r0, r3 ;
label_71a:  ;
//Could not parse:  71a:	4152      	adcs	r2, r2 ;
label_71c:  ;
LSRS_3(R3, R0, 5);// 71c:	0943      	lsrs	r3, r0, #5 ;
label_71e:  ;
CMP_2(R3, R1 );// 71e:	428b      	cmp	r3, r1 ;
label_720:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_726 ; } ;// 720:	d301      	bccn	726 <__aeabi_idiv+0xc6> ;
label_722:  ;
LSLS_3(R3, R1, 5);// 722:	014b      	lsls	r3, r1, #5 ;
label_724:  ;
SUBS_3(R0, R0, R3 );// 724:	1ac0      	subs	r0, r0, r3 ;
label_726:  ;
//Could not parse:  726:	4152      	adcs	r2, r2 ;
label_728:  ;
LSRS_3(R3, R0, 4);// 728:	0903      	lsrs	r3, r0, #4 ;
label_72a:  ;
CMP_2(R3, R1 );// 72a:	428b      	cmp	r3, r1 ;
label_72c:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_732 ; } ;// 72c:	d301      	bccn	732 <__aeabi_idiv+0xd2> ;
label_72e:  ;
LSLS_3(R3, R1, 4);// 72e:	010b      	lsls	r3, r1, #4 ;
label_730:  ;
SUBS_3(R0, R0, R3 );// 730:	1ac0      	subs	r0, r0, r3 ;
label_732:  ;
//Could not parse:  732:	4152      	adcs	r2, r2 ;
label_734:  ;
LSRS_3(R3, R0, 3);// 734:	08c3      	lsrs	r3, r0, #3 ;
label_736:  ;
CMP_2(R3, R1 );// 736:	428b      	cmp	r3, r1 ;
label_738:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_73e ; } ;// 738:	d301      	bccn	73e <__aeabi_idiv+0xde> ;
label_73a:  ;
LSLS_3(R3, R1, 3);// 73a:	00cb      	lsls	r3, r1, #3 ;
label_73c:  ;
SUBS_3(R0, R0, R3 );// 73c:	1ac0      	subs	r0, r0, r3 ;
label_73e:  ;
//Could not parse:  73e:	4152      	adcs	r2, r2 ;
label_740:  ;
LSRS_3(R3, R0, 2);// 740:	0883      	lsrs	r3, r0, #2 ;
label_742:  ;
CMP_2(R3, R1 );// 742:	428b      	cmp	r3, r1 ;
label_744:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_74a ; } ;// 744:	d301      	bccn	74a <__aeabi_idiv+0xea> ;
label_746:  ;
LSLS_3(R3, R1, 2);// 746:	008b      	lsls	r3, r1, #2 ;
label_748:  ;
SUBS_3(R0, R0, R3 );// 748:	1ac0      	subs	r0, r0, r3 ;
label_74a:  ;
//Could not parse:  74a:	4152      	adcs	r2, r2 ;
label_74c:  ;
LSRS_3(R3, R0, 1);// 74c:	0843      	lsrs	r3, r0, #1 ;
label_74e:  ;
CMP_2(R3, R1 );// 74e:	428b      	cmp	r3, r1 ;
label_750:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_756 ; } ;// 750:	d301      	bccn	756 <__aeabi_idiv+0xf6> ;
label_752:  ;
LSLS_3(R3, R1, 1);// 752:	004b      	lsls	r3, r1, #1 ;
label_754:  ;
SUBS_3(R0, R0, R3 );// 754:	1ac0      	subs	r0, r0, r3 ;
label_756:  ;
//Could not parse:  756:	4152      	adcs	r2, r2 ;
label_758:  ;
SUBS_3(R1, R0, R1 );// 758:	1a41      	subs	r1, r0, r1 ;
label_75a:  ;
g_cycle_count++;
 if (C_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_75e ; } ;// 75a:	d200      	bcsn	75e <__aeabi_idiv+0xfe> ;
label_75c:  ;
MOV_2(R1, R0 );// 75c:	4601      	mov	r1, r0 ;
label_75e:  ;
//Could not parse:  75e:	4152      	adcs	r2, r2 ;
label_760:  ;
MOV_2(R0, R2 );// 760:	4610      	mov	r0, r2 ;
label_762:  ;
return ;// 762:	4770      	bx	lr ;
label_764:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_822 ; } ;// 764:	e05d      	bn	822 <__aeabi_idiv+0x1c2> ;
label_766:  ;
LSRS_3(R2, R1, 31);// 766:	0fca      	lsrs	r2, r1, #31 ;
label_768:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_76c ; } ;// 768:	d000      	beqn	76c <__aeabi_idiv+0x10c> ;
label_76a:  ;
//Could not parse:  76a:	4249      	negs	r1, r1 ;
label_76c:  ;
//Could not parse:  76c:	1003      	asrs	r3, r0, #32 ;
label_76e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_772 ; } ;// 76e:	d300      	bccn	772 <__aeabi_idiv+0x112> ;
label_770:  ;
//Could not parse:  770:	4240      	negs	r0, r0 ;
label_772:  ;
//Could not parse:  772:	4053      	eors	r3, r2 ;
label_774:  ;
MOVS_2(R2, 0);// 774:	2200      	movs	r2, #0 ;
label_776:  ;
MOV_2(IP, R3 );// 776:	469c      	mov	ip, r3 ;
label_778:  ;
LSRS_3(R3, R0, 4);// 778:	0903      	lsrs	r3, r0, #4 ;
label_77a:  ;
CMP_2(R3, R1 );// 77a:	428b      	cmp	r3, r1 ;
label_77c:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7da ; } ;// 77c:	d32d      	bccn	7da <__aeabi_idiv+0x17a> ;
label_77e:  ;
LSRS_3(R3, R0, 8);// 77e:	0a03      	lsrs	r3, r0, #8 ;
label_780:  ;
CMP_2(R3, R1 );// 780:	428b      	cmp	r3, r1 ;
label_782:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7aa ; } ;// 782:	d312      	bccn	7aa <__aeabi_idiv+0x14a> ;
label_784:  ;
MOVS_2(R2, 252);// 784:	22fc      	movs	r2, #252	 ; 0xfc ;
label_786:  ;
LSLS_3(R1, R1, 6);// 786:	0189      	lsls	r1, r1, #6 ;
label_788:  ;
//Could not parse:  788:	ba12      	rev	r2, r2 ;
label_78a:  ;
LSRS_3(R3, R0, 8);// 78a:	0a03      	lsrs	r3, r0, #8 ;
label_78c:  ;
CMP_2(R3, R1 );// 78c:	428b      	cmp	r3, r1 ;
label_78e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7aa ; } ;// 78e:	d30c      	bccn	7aa <__aeabi_idiv+0x14a> ;
label_790:  ;
LSLS_3(R1, R1, 6);// 790:	0189      	lsls	r1, r1, #6 ;
label_792:  ;
//Could not parse:  792:	1192      	asrs	r2, r2, #6 ;
label_794:  ;
CMP_2(R3, R1 );// 794:	428b      	cmp	r3, r1 ;
label_796:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7aa ; } ;// 796:	d308      	bccn	7aa <__aeabi_idiv+0x14a> ;
label_798:  ;
LSLS_3(R1, R1, 6);// 798:	0189      	lsls	r1, r1, #6 ;
label_79a:  ;
//Could not parse:  79a:	1192      	asrs	r2, r2, #6 ;
label_79c:  ;
CMP_2(R3, R1 );// 79c:	428b      	cmp	r3, r1 ;
label_79e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7aa ; } ;// 79e:	d304      	bccn	7aa <__aeabi_idiv+0x14a> ;
label_7a0:  ;
LSLS_3(R1, R1, 6);// 7a0:	0189      	lsls	r1, r1, #6 ;
label_7a2:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_81a ; } ;// 7a2:	d03a      	beqn	81a <__aeabi_idiv+0x1ba> ;
label_7a4:  ;
//Could not parse:  7a4:	1192      	asrs	r2, r2, #6 ;
label_7a6:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7aa ; } ;// 7a6:	e000      	bn	7aa <__aeabi_idiv+0x14a> ;
label_7a8:  ;
LSRS_3(R1, R1, 6);// 7a8:	0989      	lsrs	r1, r1, #6 ;
label_7aa:  ;
LSRS_3(R3, R0, 7);// 7aa:	09c3      	lsrs	r3, r0, #7 ;
label_7ac:  ;
CMP_2(R3, R1 );// 7ac:	428b      	cmp	r3, r1 ;
label_7ae:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7b4 ; } ;// 7ae:	d301      	bccn	7b4 <__aeabi_idiv+0x154> ;
label_7b0:  ;
LSLS_3(R3, R1, 7);// 7b0:	01cb      	lsls	r3, r1, #7 ;
label_7b2:  ;
SUBS_3(R0, R0, R3 );// 7b2:	1ac0      	subs	r0, r0, r3 ;
label_7b4:  ;
//Could not parse:  7b4:	4152      	adcs	r2, r2 ;
label_7b6:  ;
LSRS_3(R3, R0, 6);// 7b6:	0983      	lsrs	r3, r0, #6 ;
label_7b8:  ;
CMP_2(R3, R1 );// 7b8:	428b      	cmp	r3, r1 ;
label_7ba:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7c0 ; } ;// 7ba:	d301      	bccn	7c0 <__aeabi_idiv+0x160> ;
label_7bc:  ;
LSLS_3(R3, R1, 6);// 7bc:	018b      	lsls	r3, r1, #6 ;
label_7be:  ;
SUBS_3(R0, R0, R3 );// 7be:	1ac0      	subs	r0, r0, r3 ;
label_7c0:  ;
//Could not parse:  7c0:	4152      	adcs	r2, r2 ;
label_7c2:  ;
LSRS_3(R3, R0, 5);// 7c2:	0943      	lsrs	r3, r0, #5 ;
label_7c4:  ;
CMP_2(R3, R1 );// 7c4:	428b      	cmp	r3, r1 ;
label_7c6:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7cc ; } ;// 7c6:	d301      	bccn	7cc <__aeabi_idiv+0x16c> ;
label_7c8:  ;
LSLS_3(R3, R1, 5);// 7c8:	014b      	lsls	r3, r1, #5 ;
label_7ca:  ;
SUBS_3(R0, R0, R3 );// 7ca:	1ac0      	subs	r0, r0, r3 ;
label_7cc:  ;
//Could not parse:  7cc:	4152      	adcs	r2, r2 ;
label_7ce:  ;
LSRS_3(R3, R0, 4);// 7ce:	0903      	lsrs	r3, r0, #4 ;
label_7d0:  ;
CMP_2(R3, R1 );// 7d0:	428b      	cmp	r3, r1 ;
label_7d2:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7d8 ; } ;// 7d2:	d301      	bccn	7d8 <__aeabi_idiv+0x178> ;
label_7d4:  ;
LSLS_3(R3, R1, 4);// 7d4:	010b      	lsls	r3, r1, #4 ;
label_7d6:  ;
SUBS_3(R0, R0, R3 );// 7d6:	1ac0      	subs	r0, r0, r3 ;
label_7d8:  ;
//Could not parse:  7d8:	4152      	adcs	r2, r2 ;
label_7da:  ;
LSRS_3(R3, R0, 3);// 7da:	08c3      	lsrs	r3, r0, #3 ;
label_7dc:  ;
CMP_2(R3, R1 );// 7dc:	428b      	cmp	r3, r1 ;
label_7de:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7e4 ; } ;// 7de:	d301      	bccn	7e4 <__aeabi_idiv+0x184> ;
label_7e0:  ;
LSLS_3(R3, R1, 3);// 7e0:	00cb      	lsls	r3, r1, #3 ;
label_7e2:  ;
SUBS_3(R0, R0, R3 );// 7e2:	1ac0      	subs	r0, r0, r3 ;
label_7e4:  ;
//Could not parse:  7e4:	4152      	adcs	r2, r2 ;
label_7e6:  ;
LSRS_3(R3, R0, 2);// 7e6:	0883      	lsrs	r3, r0, #2 ;
label_7e8:  ;
CMP_2(R3, R1 );// 7e8:	428b      	cmp	r3, r1 ;
label_7ea:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7f0 ; } ;// 7ea:	d301      	bccn	7f0 <__aeabi_idiv+0x190> ;
label_7ec:  ;
LSLS_3(R3, R1, 2);// 7ec:	008b      	lsls	r3, r1, #2 ;
label_7ee:  ;
SUBS_3(R0, R0, R3 );// 7ee:	1ac0      	subs	r0, r0, r3 ;
label_7f0:  ;
//Could not parse:  7f0:	4152      	adcs	r2, r2 ;
label_7f2:  ;
g_cycle_count++;
 if (C_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7a8 ; } ;// 7f2:	d2d9      	bcsn	7a8 <__aeabi_idiv+0x148> ;
label_7f4:  ;
LSRS_3(R3, R0, 1);// 7f4:	0843      	lsrs	r3, r0, #1 ;
label_7f6:  ;
CMP_2(R3, R1 );// 7f6:	428b      	cmp	r3, r1 ;
label_7f8:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_7fe ; } ;// 7f8:	d301      	bccn	7fe <__aeabi_idiv+0x19e> ;
label_7fa:  ;
LSLS_3(R3, R1, 1);// 7fa:	004b      	lsls	r3, r1, #1 ;
label_7fc:  ;
SUBS_3(R0, R0, R3 );// 7fc:	1ac0      	subs	r0, r0, r3 ;
label_7fe:  ;
//Could not parse:  7fe:	4152      	adcs	r2, r2 ;
label_800:  ;
SUBS_3(R1, R0, R1 );// 800:	1a41      	subs	r1, r0, r1 ;
label_802:  ;
g_cycle_count++;
 if (C_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_806 ; } ;// 802:	d200      	bcsn	806 <__aeabi_idiv+0x1a6> ;
label_804:  ;
MOV_2(R1, R0 );// 804:	4601      	mov	r1, r0 ;
label_806:  ;
MOV_2(R3, IP );// 806:	4663      	mov	r3, ip ;
label_808:  ;
//Could not parse:  808:	4152      	adcs	r2, r2 ;
label_80a:  ;
//Could not parse:  80a:	105b      	asrs	r3, r3, #1 ;
label_80c:  ;
MOV_2(R0, R2 );// 80c:	4610      	mov	r0, r2 ;
label_80e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_814 ; } ;// 80e:	d301      	bccn	814 <__aeabi_idiv+0x1b4> ;
label_810:  ;
//Could not parse:  810:	4240      	negs	r0, r0 ;
label_812:  ;
CMP_2(R3, 0);// 812:	2b00      	cmp	r3, #0 ;
label_814:  ;
g_cycle_count++;
 if (N_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_818 ; } ;// 814:	d500      	bpln	818 <__aeabi_idiv+0x1b8> ;
label_816:  ;
//Could not parse:  816:	4249      	negs	r1, r1 ;
label_818:  ;
return ;// 818:	4770      	bx	lr ;
label_81a:  ;
MOV_2(R3, IP );// 81a:	4663      	mov	r3, ip ;
label_81c:  ;
//Could not parse:  81c:	105b      	asrs	r3, r3, #1 ;
label_81e:  ;
g_cycle_count++;
 if (C_flag == 0) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_822 ; } ;// 81e:	d300      	bccn	822 <__aeabi_idiv+0x1c2> ;
label_820:  ;
//Could not parse:  820:	4240      	negs	r0, r0 ;
label_822:  ;
PUSH(SP,0b0100000001);// 822:	b501      	push	r0, lr ;
label_824:  ;
MOVS_2(R0, 0);// 824:	2000      	movs	r0, #0 ;
label_826:  ;
g_cycle_count += 3;
__aeabi_idiv0( );// 826:	f000 f805 	bl	834 <__aeabi_idiv0> ;
label_82a:  ;
POP(SP,0b0010000001);
return ;// 82a:	bd02      	pop	r1, pc ;
}
void __aeabi_idivmod() 
{label_82c:  ;
CMP_2(R1, 0);// 82c:	2900      	cmp	r1, #0 ;
label_82e:  ;
g_cycle_count++;
 if (Z_flag == 1) {g_cycle_count+=2; //thumb 'narrow' version
 goto label_822 ; } ;// 82e:	d0f8      	beqn	822 <__aeabi_idiv+0x1c2> ;
label_830:  ;
g_cycle_count++;
 {g_cycle_count+=2; //thumb 'narrow' version
 goto label_660 ; } ;// 830:	e716      	bn	660 <__aeabi_idiv> ;
label_832:  ;
return ;// 832:	4770      	bx	lr ;
}
void __aeabi_idiv0() 
{label_834:  ;
return ;// 834:	4770      	bx	lr ;
label_836:  ;
//Could not parse:  836:	46c0      	nop			 ; (mov r8, r8) ;
}