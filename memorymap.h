#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cassert>
#include <iostream>
#include <vector>
/*
 * RAM STORAGE
 * 	MEM[R1]= R2; -> STR R2, [R1]
 * 	R2=MEM[R1] -> LDR R2, [R1]
 * IO
 * 	No memory storage, but triggers an doI0() method
 *
 * if (addr > IOSTART)
 * 	do IO
 * else if(addr in RAM RANGE)
 * 	RAM[addr]
 *
 *
 */

typedef enum endian_t { ENDIAN_LITTLE, ENDIAN_BIG } endian_t;
class MemoryDevice
{
	private:
		uint32_t offset;
		uint32_t end_address;
		uint32_t size_B;
		uint32_t num_address_bits;
		uint8_t* memory_array;
		endian_t endianness;
	public:
		MemoryDevice(uint32_t offset, uint32_t size,  endian_t endianness) : offset(offset), size_B(size),endianness(endianness)
		{
			if(size==0)
				memory_array=0;
			else
				memory_array=new uint8_t[size];
			while(size) 
			{
				num_address_bits++;
				size=size>>1;
			}
			end_address=offset+this->size_B;
		}
		~MemoryDevice()
		{
			free(memory_array);
		}
		//Including a copy constructor
		
		MemoryDevice(const MemoryDevice& device)
		{
			this->offset=device.offset;
			this->size_B=device.size_B;
			this->num_address_bits=device.num_address_bits;
			for(uint64_t i=0; i < size_B; i++)
				this->memory_array[i]=device.memory_array[i];
			this->endianness=device.endianness;
			this->end_address=device.end_address;
	
		}
		MemoryDevice& operator=(const MemoryDevice& device)
		{
			if(this==&device)
				return *this;
			delete[] this->memory_array;
			this->offset=device.offset;
			this->size_B=device.size_B;
			this->num_address_bits=device.num_address_bits;	
			this->endianness=device.endianness;
			this->end_address=device.end_address;
			if(device.memory_array)
			{
				this->memory_array=new uint8_t[device.size_B];
				for(uint32_t i=0; i < size_B; i++)
					this->memory_array[i]=device.memory_array[i];
			}
			else
				this->memory_array=0;
			return *this;
		}
		
	public:
		uint8_t virtual read_byte(uint32_t address)
		{
			return this->memory_array[address-offset];
		}
		uint16_t virtual read_halfword(uint32_t address)
		{
			if(endianness==ENDIAN_LITTLE)
				return read_byte(address) | (read_byte(address+1) <<8);
			else
				return (read_byte(address) << 8) | read_byte(address+1); 
		}
		uint32_t virtual read_word(uint32_t address)
		{	
			if(endianness==ENDIAN_LITTLE)
				return read_halfword(address) | read_halfword(address+2) << 16;
			else
				return read_halfword(address) <<16 | read_halfword(address+2);
		}
		void virtual write_byte(uint32_t address, uint8_t data)
		{
			this->memory_array[address-offset]=data;
		}
		void write_halfword(uint32_t address, uint16_t data)
		{
			if(endianness==ENDIAN_LITTLE)
			{
				write_byte(address, data & 0x00FF);
				write_byte(address+1, data>>8);
			}
			else
			{
				write_byte(address, data>>8);
				write_byte(address+1, data & 0x00FF);
			}
		}
		void write_word(uint32_t address, uint32_t data)
		{
			if(endianness==ENDIAN_LITTLE)
			{
				write_halfword(address,data);
				write_halfword(address+2,data>>16);
			}
			else
			{
				write_halfword(address, data>>16);
				write_halfword(address+2,data);

			}
		}
		void setOffset(uint32_t offset)
		{
			this->offset=offset;
		}
		uint64_t getOffset()
		{
			return this->offset;
		}
		uint64_t getSize()
		{
			return this->size_B;
		}
		uint64_t getEndAddress()
		{
			return this->end_address;
		}
};
class RAMDevice: public MemoryDevice
{
	public:
	RAMDevice(uint32_t offset, uint32_t size, endian_t endianness) : MemoryDevice(offset,size,endianness)
	{
	}
	RAMDevice( RAMDevice const& d) : MemoryDevice(d)
	{
	}
	RAMDevice& operator=(const RAMDevice& source)
	{
		return *this;

	}

};		
class ROMDevice: public RAMDevice
{
	public:
	ROMDevice(uint32_t offset, uint32_t size, endian_t endianness) : RAMDevice( offset, size, endianness)
	{
	}
	void programROM(const uint8_t* contents)
	{
		for(uint64_t i=this->getOffset(); i < (this->getSize()+this->getOffset()); i++)
			
			RAMDevice::write_byte(contents[i],i);
	}
	void programROM(uint32_t address, uint8_t data)
	{
		RAMDevice::write_byte(address,data);
	}

	void write_byte(uint32_t address, uint8_t data) {std::cout << "Write to flash failed"<<std::endl;}
	void write_halfword(uint32_t address, uint16_t data) {;}
	void write_word(uint32_t address, uint32_t data) {;}

};

//Slot_size enables byte-addressable, 2-byte addressable, etc memories
enum class Size
	{
		BYTE, HALF_WORD,WORD
	};

class MemoryMap
{

	public:
		std::vector<MemoryDevice*> map;

	//Need to fix this so it copy constructs in this future
	/*
	void addDevice(const MemoryDevice& device)
	{
		MemoryDevice* mydevice;
		*mydevice=device;	device->write_word(index,value);
		map.push_back(mydevice);
	}
	*/
	void addDevice(MemoryDevice *device)
	{
		map.push_back(device);
	}
	void write(uint64_t index, uint32_t value, Size s)
	{
		for(auto &device : map)
		{
			std::cout << "Offset is: " << device->getOffset() << std::endl;
			std::cout << "End Address is : " << device->getEndAddress() << std::endl;
			if((device->getOffset() <=index) &&( index < device->getEndAddress()))
			{
				std::cout << "Value of index is: " << index << std::endl;
				if(s==Size::BYTE){
					device->write_byte(index,value);
				}
				else if(s==Size::HALF_WORD)
					device->write_halfword(index,value);
				else
				{	
					std::cout << "Writing word" << std::endl;
					device->write_word(index,value);
				}
				return;
			}
		}
		std::cout << "No device found with that memory address " << index << '\n';
	}
	uint64_t read(uint32_t index, Size s)
	{
		for(auto &device : map)
		{
			if((device->getOffset() <=index) && (index < device->getEndAddress()))
			{
				if(s==Size::BYTE)
					return device->read_byte(index);
				else if(s==Size::HALF_WORD)
					return device->read_halfword(index);
				else
					return device->read_word(index);

			}
		}
		std::cout << "No device found with that memory address " << index << '\n';
		return 0;
	}
	
};

#endif








