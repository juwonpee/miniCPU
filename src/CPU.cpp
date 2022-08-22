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
    if (instruction.operand1 == memory) {
        PC++;
        memory1 = read(PC);
    }
    if (instruction.operand2 == memory) {
        PC++;
        memory2 = read(PC);
    }
    if (instruction.operand3 == memory) {
        PC++;
        memory3 = read(PC);
    }
}

void CPU::execute() {
    switch (instruction.opcode) {
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
        default:
            ST.error = true;
            cout << "Invalid instruction" << endl;
            exit(EXIT_FAILURE);
    }
}

uint32_t CPU::read(uint32_t address) {
    return bus->readMEM(address);
}
void CPU::write(uint32_t address, uint32_t data) {
    bus->writeMEM(address, data);
}

void CPU::AD() {
    uint32_t operand1, operand2, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            operand2 = GP0;
            break;
        case GPR1:
            operand2 = GP1;
            break;
        case GPR2:
            operand2 = GP2;
            break;
        case GPR3:
            operand2 = GP3;
            break;
        case PCR:
            operand2 = PC;
            break;
        case SPR:
            operand2 = SP;
            break;
        case STR:
            operand2 = ST.data;
            break;
        case memory:
            operand2 = memory2;
            break;
    }
    
    operand3 = operand1 + operand2;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = operand3;
            break;
        case GPR1:
            GP1 = operand3;
            break;
        case GPR2:
            GP2 = operand3;
            break;
        case GPR3:
            GP3 = operand3;
            break;
        case PCR:
            PC = operand3;
            break;
        case SPR:
            SP = operand3;
            break;
        case STR:
            ST.data = operand3;
            break;
        case memory:
            write(memory3, operand3);
            break;
    }

}

void CPU::SB() {
    uint32_t operand1, operand2, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            operand2 = GP0;
            break;
        case GPR1:
            operand2 = GP1;
            break;
        case GPR2:
            operand2 = GP2;
            break;
        case GPR3:
            operand2 = GP3;
            break;
        case PCR:
            operand2 = PC;
            break;
        case SPR:
            operand2 = SP;
            break;
        case STR:
            operand2 = ST.data;
            break;
        case memory:
            operand2 = memory2;
            break;
    }
    
    operand3 = operand1 - operand2;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = operand3;
            break;
        case GPR1:
            GP1 = operand3;
            break;
        case GPR2:
            GP2 = operand3;
            break;
        case GPR3:
            GP3 = operand3;
            break;
        case PCR:
            PC = operand3;
            break;
        case SPR:
            SP = operand3;
            break;
        case STR:
            ST.data = operand3;
            break;
        case memory:
            write(memory3, operand3);
            break;
    }
    
}

void CPU::ML() {
    uint32_t operand1, operand2, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            operand2 = GP0;
            break;
        case GPR1:
            operand2 = GP1;
            break;
        case GPR2:
            operand2 = GP2;
            break;
        case GPR3:
            operand2 = GP3;
            break;
        case PCR:
            operand2 = PC;
            break;
        case SPR:
            operand2 = SP;
            break;
        case STR:
            operand2 = ST.data;
            break;
        case memory:
            operand2 = memory2;
            break;
    }
    
    operand3 = operand1 * operand2;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = operand3;
            break;
        case GPR1:
            GP1 = operand3;
            break;
        case GPR2:
            GP2 = operand3;
            break;
        case GPR3:
            GP3 = operand3;
            break;
        case PCR:
            PC = operand3;
            break;
        case SPR:
            SP = operand3;
            break;
        case STR:
            ST.data = operand3;
            break;
        case memory:
            write(memory3, operand3);
            break;
    }
    
}

void CPU::DV() {
    uint32_t operand1, operand2, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            operand2 = GP0;
            break;
        case GPR1:
            operand2 = GP1;
            break;
        case GPR2:
            operand2 = GP2;
            break;
        case GPR3:
            operand2 = GP3;
            break;
        case PCR:
            operand2 = PC;
            break;
        case SPR:
            operand2 = SP;
            break;
        case STR:
            operand2 = ST.data;
            break;
        case memory:
            operand2 = memory2;
            break;
    }
    
    operand3 = operand1 / operand2;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = operand3;
            break;
        case GPR1:
            GP1 = operand3;
            break;
        case GPR2:
            GP2 = operand3;
            break;
        case GPR3:
            GP3 = operand3;
            break;
        case PCR:
            PC = operand3;
            break;
        case SPR:
            SP = operand3;
            break;
        case STR:
            ST.data = operand3;
            break;
        case memory:
            write(memory3, operand3);
            break;
    }
    
}

void CPU::MV() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    
    operand3 = operand1;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = operand3;
            break;
        case GPR1:
            GP1 = operand3;
            break;
        case GPR2:
            GP2 = operand3;
            break;
        case GPR3:
            GP3 = operand3;
            break;
        case PCR:
            PC = operand3;
            break;
        case SPR:
            SP = operand3;
            break;
        case STR:
            ST.data = operand3;
            break;
        case memory:
            write(memory3, operand3);
            break;
    }
    
}

void CPU::CP() {
    uint32_t operand1, operand2, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            operand2 = GP0;
            break;
        case GPR1:
            operand2 = GP1;
            break;
        case GPR2:
            operand2 = GP2;
            break;
        case GPR3:
            operand2 = GP3;
            break;
        case PCR:
            operand2 = PC;
            break;
        case SPR:
            operand2 = SP;
            break;
        case STR:
            operand2 = ST.data;
            break;
        case memory:
            operand2 = memory2;
            break;
    }

    ST.negative = operand1 < operand2;
    ST.zero = operand1 == operand2;
}

void CPU::JP() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }

    PC = operand1;
}

void CPU::JN() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }

    if (ST.negative) PC = operand1;
}

void CPU::JZ() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            operand1 = GP0;
            break;
        case GPR1:
            operand1 = GP1;
            break;
        case GPR2:
            operand1 = GP2;
            break;
        case GPR3:
            operand1 = GP3;
            break;
        case PCR:
            operand1 = PC;
            break;
        case SPR:
            operand1 = SP;
            break;
        case STR:
            operand1 = ST.data;
            break;
        case memory:
            operand1 = memory1;
            break;
    }

    if (ST.zero) PC = operand1;
}