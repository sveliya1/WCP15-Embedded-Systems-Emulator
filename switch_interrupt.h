#ifndef SWITCH_I
#define SWITCH_I
#include "memorymap.h"
#include "macros.h"

extern bool BUTTON;

void switch_set_state(uint32_t value, MemoryMap *memorymap)
{
	io_write(0x400FF010, (~ memorymap -> read(0x400FF010, Size::WORD)) | (value << 20));

}

void check_button_INT(MemoryMap *memorymap) {

	while (1) {
		if (GetAsyncKeyState(VK_LCONTROL))
		{
			BUTTON = true;
			switch_set_state(0, memorymap);
			std::cout << "Button is pressed" << std::endl;
			//PENDING_INTERRUPT = false;
		}
		else {
			switch_set_state(1);
			std::cout << "Button is not pressed" << std::endl;
			BUTTON = false;
		}
	}
	return;

}
#endif
