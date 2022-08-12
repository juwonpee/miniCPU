#pragma once

#include <stdint.h>

#include "MEM.h"
#include "CPU.h"
#include "GPU.h"

using namespace std;

class MEM;
class CPU;
class GPU;

class BUS {
	public:
		BUS(uint32_t memSize, string romDirectory);
		uint32_t readMEM(uint32_t address);
		void writeMEM(uint32_t address, uint32_t data);

		
	private:

		MEM* memory;
		CPU* cpu;
		GPU* gpu;

		uint32_t io;
		
		void writeIO(uint32_t data);
};