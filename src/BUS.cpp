#include "BUS.h"

BUS::BUS(uint32_t memSize, string romDirectory) {
	memory = new MEM(memSize, romDirectory);
	cpu = new CPU(this);
	gpu = new GPU(this);
	com = new serial(this);

	while(true) {
		cpu->clock();
	}
}

uint32_t BUS::read(uint32_t address) {
	switch (address) {
		case MEMORY_SERIAL_START ... MEMORY_SERIAL_END:
			return com->read(address);
			break;
		case GPU_START ... GPU_END:
			return gpu->read(address);
			break;
		default:
			return memory->read(address);
	}
}


void BUS::write(uint32_t address, uint32_t data) {
	switch (address) {
		case MEMORY_SERIAL_START ... MEMORY_SERIAL_END:
			com->write(address, data);
			break;
		case GPU_START ... GPU_END:
			gpu->write(address, data);
			break;
		default:
			memory->write(address, data);
	}
}


