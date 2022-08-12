#include "BUS.h"

BUS::BUS(uint32_t memSize, string romDirectory) {
	memory = new MEM(memSize, romDirectory);
	cpu = new CPU(this);
	gpu = new GPU(this);

	while(true) {
		cpu->clock();
	}
}

uint32_t BUS::readMEM(uint32_t address) {
	return memory->read(address);
}


void BUS::writeMEM(uint32_t address, uint32_t data) {
	memory->write(address, data);
}

void BUS::writeIO(uint32_t data) {
	io = data;
}
