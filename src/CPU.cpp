#include "CPU.h"

CPU::CPU(BUS* _bus) {
    bus = _bus;
}

void CPU::clock() {
    fetch();
    decode();
    execute();
}

void CPU::fetch() {
    instruction.data = read(PC);
}

void CPU::decode() {
    if (instruction.register1 == memory) {
        PC++;
        memory1 = read(PC);
    }
    if (instruction.register2 == memory) {
        PC++;
        memory2 = read(PC);
    }
    if (instruction.register3 == memory) {
        PC++;
        memory3 = read(PC);
    }
}

void CPU::execute() {
    switch (instruction.instruction) {
        case ADD:
            AD();
            break;
        case SUB:
            SB();
            break;
        case MUL:
            ML();
            break;
        case DIV:
            DV();
            break;
        case MOV:
            MV();
            break;
        case CMP:
            CP();
            break;
        case JMP:
            JP();
            break;
        case JPN:
            JN();
            break;
        case JPZ:
            JZ();
            break;
    }
}

uint32_t CPU::read(uint32_t address) {
    return bus->readMEM(address);
}
void CPU::write(uint32_t address, uint32_t data) {
    bus->writeMEM(address, data);
}

void CPU::AD() {
    uint32_t register1, register2, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    switch (instruction.register2) {
        case GPR0:
            register2 = GP0;
            break;
        case GPR1:
            register2 = GP1;
            break;
        case GPR2:
            register2 = GP2;
            break;
        case GPR3:
            register2 = GP3;
            break;
        case PCR:
            register2 = PC;
            break;
        case SPR:
            register2 = SP;
            break;
        case STR:
            register2 = ST.data;
            break;
        case memory:
            register2 = memory2;
            break;
    }
    
    register3 = register1 + register2;

    switch (instruction.register3) {
        case GPR0:
            GP0 = register3;
            break;
        case GPR1:
            GP1 = register3;
            break;
        case GPR2:
            GP2 = register3;
            break;
        case GPR3:
            GP3 = register3;
            break;
        case PCR:
            PC = register3;
            break;
        case SPR:
            SP = register3;
            break;
        case STR:
            ST.data = register3;
            break;
        case memory:
            write(memory3, register3);
            break;
    }

}

void CPU::SB() {
    uint32_t register1, register2, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    switch (instruction.register2) {
        case GPR0:
            register2 = GP0;
            break;
        case GPR1:
            register2 = GP1;
            break;
        case GPR2:
            register2 = GP2;
            break;
        case GPR3:
            register2 = GP3;
            break;
        case PCR:
            register2 = PC;
            break;
        case SPR:
            register2 = SP;
            break;
        case STR:
            register2 = ST.data;
            break;
        case memory:
            register2 = memory2;
            break;
    }
    
    register3 = register1 - register2;

    switch (instruction.register3) {
        case GPR0:
            GP0 = register3;
            break;
        case GPR1:
            GP1 = register3;
            break;
        case GPR2:
            GP2 = register3;
            break;
        case GPR3:
            GP3 = register3;
            break;
        case PCR:
            PC = register3;
            break;
        case SPR:
            SP = register3;
            break;
        case STR:
            ST.data = register3;
            break;
        case memory:
            write(memory3, register3);
            break;
    }
    
}

void CPU::ML() {
    uint32_t register1, register2, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    switch (instruction.register2) {
        case GPR0:
            register2 = GP0;
            break;
        case GPR1:
            register2 = GP1;
            break;
        case GPR2:
            register2 = GP2;
            break;
        case GPR3:
            register2 = GP3;
            break;
        case PCR:
            register2 = PC;
            break;
        case SPR:
            register2 = SP;
            break;
        case STR:
            register2 = ST.data;
            break;
        case memory:
            register2 = memory2;
            break;
    }
    
    register3 = register1 * register2;

    switch (instruction.register3) {
        case GPR0:
            GP0 = register3;
            break;
        case GPR1:
            GP1 = register3;
            break;
        case GPR2:
            GP2 = register3;
            break;
        case GPR3:
            GP3 = register3;
            break;
        case PCR:
            PC = register3;
            break;
        case SPR:
            SP = register3;
            break;
        case STR:
            ST.data = register3;
            break;
        case memory:
            write(memory3, register3);
            break;
    }
    
}

void CPU::DV() {
    uint32_t register1, register2, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    switch (instruction.register2) {
        case GPR0:
            register2 = GP0;
            break;
        case GPR1:
            register2 = GP1;
            break;
        case GPR2:
            register2 = GP2;
            break;
        case GPR3:
            register2 = GP3;
            break;
        case PCR:
            register2 = PC;
            break;
        case SPR:
            register2 = SP;
            break;
        case STR:
            register2 = ST.data;
            break;
        case memory:
            register2 = memory2;
            break;
    }
    
    register3 = register1 / register2;

    switch (instruction.register3) {
        case GPR0:
            GP0 = register3;
            break;
        case GPR1:
            GP1 = register3;
            break;
        case GPR2:
            GP2 = register3;
            break;
        case GPR3:
            GP3 = register3;
            break;
        case PCR:
            PC = register3;
            break;
        case SPR:
            SP = register3;
            break;
        case STR:
            ST.data = register3;
            break;
        case memory:
            write(memory3, register3);
            break;
    }
    
}

void CPU::MV() {
    uint32_t register1, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    
    register3 = register1;

    switch (instruction.register3) {
        case GPR0:
            GP0 = register3;
            break;
        case GPR1:
            GP1 = register3;
            break;
        case GPR2:
            GP2 = register3;
            break;
        case GPR3:
            GP3 = register3;
            break;
        case PCR:
            PC = register3;
            break;
        case SPR:
            SP = register3;
            break;
        case STR:
            ST.data = register3;
            break;
        case memory:
            write(memory3, register3);
            break;
    }
    
}

void CPU::CP() {
    uint32_t register1, register2, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }
    switch (instruction.register2) {
        case GPR0:
            register2 = GP0;
            break;
        case GPR1:
            register2 = GP1;
            break;
        case GPR2:
            register2 = GP2;
            break;
        case GPR3:
            register2 = GP3;
            break;
        case PCR:
            register2 = PC;
            break;
        case SPR:
            register2 = SP;
            break;
        case STR:
            register2 = ST.data;
            break;
        case memory:
            register2 = memory2;
            break;
    }

    ST.negative = register1 < register2;
    ST.zero = register1 == register2;
}

void CPU::JP() {
    uint32_t register1, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }

    PC = register1;
}

void CPU::JN() {
    uint32_t register1, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }

    if (ST.negative) PC = register1;
}

void CPU::JZ() {
    uint32_t register1, register3;
    switch (instruction.register1) {
        case GPR0:
            register1 = GP0;
            break;
        case GPR1:
            register1 = GP1;
            break;
        case GPR2:
            register1 = GP2;
            break;
        case GPR3:
            register1 = GP3;
            break;
        case PCR:
            register1 = PC;
            break;
        case SPR:
            register1 = SP;
            break;
        case STR:
            register1 = ST.data;
            break;
        case memory:
            register1 = memory1;
            break;
    }

    if (ST.zero) PC = register1;
}