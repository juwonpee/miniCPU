#include "BUS.h"

BUS::BUS(uint64_t memSize, string romDirectory) {
	memory = new MEM(memSize, romDirectory);
	cpu = new CPU(this);
	gpu = new GPU(this);
	com = new serial(this);

	while(true) {
		cpu->clock();
	}
}

uint64_t BUS::read(uint64_t address) {
	switch (address) {
		case MEMORY_SERIAL_START ... MEMORY_SERIAL_END:
			return com->read(address);
			break;
		case MEMORY_GPU_START ... MEMORY_GPU_END:
			return gpu->read(address);
			break;
		default:
			return memory->read(address);
	}
}


void BUS::write(uint64_t address, uint64_t data) {
	switch (address) {
		case MEMORY_SERIAL_START ... MEMORY_SERIAL_END:
			com->write(address, data);
			break;
		case MEMORY_GPU_START ... MEMORY_GPU_END:
			gpu->write(address, data);
			break;
		default:
			memory->write(address, data);
	}
}


