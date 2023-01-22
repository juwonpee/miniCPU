#pragma once

#include <stdint.h>

#include "MEM.h"
#include "CPU.h"
#include "GPU.h"
#include "serial.h"

using namespace std;

#define MEMORY_END						0xFFFFFFFF
#define MEMORY_START					0x00000000

class MEM;
class CPU;
class GPU;
class serial;

class BUS {
	public:
		BUS(uint32_t memSize, string romDirectory);
		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t data);

		
	private:

		MEM* memory;
		CPU* cpu;
		GPU* gpu;
		serial* com;

		

		uint32_t io;
		
};