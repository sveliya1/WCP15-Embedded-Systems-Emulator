#ifndef RGBLED_H
#define RGBLED_H
#include "memorymap.h"
#include "IO_Register.h"
void led_read_state(MemoryMap* memorymap)
{
	while (1) {
		//Read the LED values
		//Set to 100 because 100 is definitely not a value written to this register
		static uint32_t previous_result = 100; 
		uint32_t redled_value = read_register_IO(0x400FF040, 18, memorymap) << 2; //11 
		uint32_t greenled_value = read_register_IO(0x400FF040, 19, memorymap) << 1; //12
		uint32_t blueled_value = read_register_IO(0x400FF0c0, 1, memorymap); //8
		uint32_t result = redled_value + greenled_value + blueled_value;
		if (previous_result != result) {
			switch (result)
			{
			case 0:
				std::cout << "LED is WHITE\n";
				break;
			case 1: //001
				std::cout << "LED is YELLOW\n";
				break;
			case 2:
				std::cout << "LED is MAGENTA\n";
				break;
			case 3:
				std::cout << "LED is RED\n";
				break;
			case 4:
				std::cout << "LED is CYAN\n";
				break;

			case 5:
				std::cout << "LED is GREEN\n";
				break;

			case 6:
				std::cout << "LED is BLUE\n";
				break;
			case 7:
				std::cout << "LED is BLACK\n";
				break;
			default:
				std::cout << "Switch statement is broken...\n";
				break;
			}
		}
		previous_result = result;
	}
}
#endif