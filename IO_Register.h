#include <iostream>
#include "memorymap.h"

#ifndef IO_Register_H
#define IO_Register_H

void clear_register_IO(uint32_t address, uint32_t value, MemoryMap* map)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg &= ~value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}
void set_register_IO(uint32_t address, uint32_t value, MemoryMap* map)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg |= value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}

void toggle_register_IO(uint32_t address, uint32_t value, MemoryMap* map)
{
	uint64_t port_reg = map->read(address, Size::WORD);
	port_reg ^= value;
	map->write(address, (uint32_t)port_reg, Size::WORD);
}


uint32_t read_register_IO(uint32_t address, uint32_t bit_value, MemoryMap* map)
{
	uint32_t register_value = map->read(address, Size::WORD);
	register_value &= ((1uL << bit_value));
	register_value = (register_value >> bit_value);
	return register_value;
}

#endif
