#include "CPU.h"

CPU::CPU(BUS* _bus) {
    bus = _bus;
    GP0 = GP1 = GP2 = GP3 = 0;
    PC = 0;
    SP = 0;
    BP = 0;
    CR.data = 0;
}

void CPU::clock() {
    fetch();
    decode();
    execute();
}



void CPU::fetch() {
    instruction.data = read(PC);
    save.GP0 = GP0;
    save.GP1 = GP1;
    save.GP2 = GP2;
    save.GP3 = GP3;
    save.PC = PC;
    save.SP = SP;
    save.BP = BP;
    save.CR = CR;

    PC+=4;
}

void CPU::decode() {
    switch (instruction.operand1) {
        case GPR0:
            opReg1 = &GP0;
            break;
        case GPR1:
            opReg1 = &GP1;
            break;
        case GPR2:
            opReg1 = &GP2;
            break;
        case GPR3:
            opReg1 = &GP3;
            break;
        case PCR:
            opReg1 = &PC;
            break;
        case SPR:
            opReg1 = &SP;
            break;
        case SBP:
            opReg1 = &BP;
            break;
        case STR:
            opReg1 = &CR.data;
            break;
        case memory:
            if (!(PC % 8)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exc();
            }
            else {
                opReg1 = (uint64_t*)PC;
                PC+=8;
            }
            break;
        default:
            CR.exception &= EXCEPTION_INVALID_OPCODE;
            exc();
    }

    switch (instruction.operand2) {
        case GPR0:
            opReg2 = &GP0;
            break;
        case GPR1:
            opReg2 = &GP1;
            break;
        case GPR2:
            opReg2 = &GP2;
            break;
        case GPR3:
            opReg2 = &GP3;
            break;
        case PCR:
            opReg2 = &PC;
            break;
        case SPR:
            opReg2 = &SP;
            break;
        case SBP:
            opReg2 = &BP;
            break;
        case STR:
            opReg2 = &CR.data;
            break;
        case memory:
            if (!(PC % 8)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exc();
            }
            else {
                opReg2 = (uint64_t*)PC;
                PC+=8;
            }
            break;
        case nothing:
            break;
        default:
            CR.exception &= EXCEPTION_INVALID_OPCODE;
            exc();
    }


    switch(instruction.operand3) {
        case GPR0:
            opReg3 = &GP0;
            break;
        case GPR1:
            opReg3 = &GP1;
            break;
        case GPR2:
            opReg3 = &GP2;
            break;
        case GPR3:
            opReg3 = &GP3;
            break;
        case PCR:
            opReg3 = &PC;
            break;
        case SPR:
            opReg3 = &SP;
            break;
        case SBP:
            opReg3 = &BP;
            break;
        case STR:
            opReg3 = &CR.data;
            break;
        case memory:
            if (!(PC % 8)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exception();
            }
            else {
                opReg3 = (uint64_t*)PC;
                PC+=8;
            }
            break;
        case nothing:
            break;
        default:
            CR.exception &= EXCEPTION_INVALID_OPCODE;
            exception();
    }
}

void CPU::call(void (CPU::*func)()) {
    (this ->*func)();
}

void CPU::execute() {
    if (instruction.opcode == 0) {
        CR.exception &= EXCEPTION_INVALID_OPCODE;
        exc();
    }
    else call(lookup[instruction.opcode]);
    
}

uint64_t CPU::read(uint64_t address) {
    return bus->read(address);
}
void CPU::write(uint64_t address, uint64_t data) {
    bus->write(address, data);
}

void CPU::exc() {
    cout << "Exception" << endl;;
    if (CR.exception && EXCEPTION_INVALID_OPCODE) {
        cout << "Invalid instruction" << endl;
    }
    if (CR.exception && EXCEPTION_INVALID_OPERAND) {
        cout << "Invalid Operand" << endl;
    }
    if (CR.exception && EXCEPTION_DIVISION_BY_ZERO) {
        cout << "Division By Zero" << endl;
    }
    if (CR.exception && EXCEPTION_ALIGNMENT) {
        cout << "Memory not aligned by 4" << endl;
    }
    if (CR.exception && EXCEPTION_STACK_ALIGNMENT) {
        cout << "Stack out of range" << endl;
    }

    cout << "CPU dump" << endl;
    printf("GP0: %lx GP1: %lx GP2: %lx GP3 %lx\n", GP0, GP1, GP2, GP3);
    printf("PC: %lx\n", PC);
    printf("SP: %lx BP: %lx\n", SP, BP);
    printf("ST: %lx\n", CR.data);

    hlt();
}

void CPU::add() {
    uint64_t temp = *opReg1 + *opReg2;
    if (instruction.operand3 == memory) {
        write((uint64_t)opReg3, temp);
    }
    else *opReg3 = temp;

}

void CPU::sub() {
    uint64_t temp = *opReg1 - *opReg2;
    if (instruction.operand3 == memory) {
        write((uint64_t)opReg3, temp);
    }
    else *opReg3 = temp;
}

void CPU::mul() {
    uint64_t temp = *opReg1 * *opReg2;
    if (instruction.operand3 == memory) {
        write((uint64_t)opReg3, temp);
    }
    else *opReg3 = temp;
    
}

void CPU::div() {
    if (*opReg2 <= 0) {
        CR.exception &= EXCEPTION_DIVISION_BY_ZERO;
        exc();
    }

    uint64_t temp = *opReg1 / *opReg2;
    if (instruction.operand3 == memory) {
        write((uint64_t)opReg3, temp);
    }
    else *opReg3 = temp;
}

void CPU::mov() {
    if (instruction.operand3 == memory) {
        write((uint64_t)opReg3, *opReg1);
    }
    else *opReg3 = *opReg1;
}

void CPU::cmp() {
    if (*opReg1 == *opReg2) CR.zero = 1;
    else CR.zero = 0;
}

void CPU::jmp() {
    PC = (uint64_t)opReg1;
}

void CPU::jpn() {
    if (CR.negative) PC = (uint64_t)opReg1;
}

void CPU::jpz() {
    if (CR.zero) PC = (uint64_t)opReg1;
}

void CPU::push() {
    write(SP, *opReg1);
}

void CPU::hlt() {
    while(true) {
        PC++;
    }
}