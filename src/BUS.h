#pragma once

#include <stdint.h>

#include "MEM.h"
#include "CPU.h"
#include "GPU.h"
#include "serial.h"

using namespace std;

#define MEMORY_END						0xFFFFFFFFFFFFFFFF
#define MEMORY_START					0x0000000000000000

/*
Memory mapped I/O
Serial		0xFFFFFFFFFC000000~0xFFFFFFFFFCFFFFFF
Graphics	0xFFFFFFFFFD000000~0xFFFFFFFFFFFFFFFF
*/

class MEM;
class CPU;
class GPU;
class serial;

class BUS {
	public:
		BUS(uint64_t memSize, string romDirectory);
		uint64_t read(uint64_t address);
		void write(uint64_t address, uint64_t data);

		
	private:

		MEM* memory;
		CPU* cpu;
		GPU* gpu;
		serial* com;

		

		uint64_t io;
		
};