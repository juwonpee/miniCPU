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

    PC+=4
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
            if (!(PC % 4)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exc();
            }
            else {
                opReg1 = (uint32_t*)PC;
                PC+=4;
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
            if (!(PC % 4)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exc();
            }
            else {
                opReg2 = (uint32_t*)PC;
                PC+=4;
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
            if (!(PC % 4)) {
                CR.exception &= EXCEPTION_ALIGNMENT;
                exception();
            }
            else {
                opReg3 = (uint32_t*)PC;
                PC+=4;
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

uint32_t CPU::read(uint32_t address) {
    return bus->read(address);
}
void CPU::write(uint32_t address, uint32_t data) {
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
    printf("GP0: %x GP1: %x GP2: %x GP3 %x\n", GP0, GP1, GP2, GP3);
    printf("PC: %x\n", PC);
    printf("SP: %x BP: %x\n", SP, BP);
    printf("ST: %x\n", CR.data);

    hlt();
}

void CPU::add() {
    uint32_t temp = *opReg1 + *opReg2;
    if (instruction.operand3 == memory) {
        write((uint32_t)opReg3, temp);
    }
    else *opReg3 = temp;

}

void CPU::sub() {
    uint32_t temp = *opReg1 - *opReg2;
    if (instruction.operand3 == memory) {
        write((uint32_t)opReg3, temp);
    }
    else *opReg3 = temp;
}

void CPU::mul() {
    uint32_t temp = *opReg1 * *opReg2;
    if (instruction.operand3 == memory) {
        write((uint32_t)opReg3, temp);
    }
    else *opReg3 = temp;
    
}

void CPU::div() {
    if (*opReg2 =< 0) {
        CR.exception &= EXCEPTION_DIVISION_BY_ZERO;
        exc();
    }

    uint32_t temp = *opReg1 / *opReg2;
    if (instruction.operand3 == memory) {
        write((uint32_t)opReg3, temp);
    }
    else *opReg3 = temp;
}

void CPU::mov() {
    if (instruction.operand3 == memory) {
        write((uint32_t)opReg3, *opReg1);
    }
    else *opReg3 = *opReg1;
    }
    
}

void CPU::cmp() {
    uint32_t operand1, operand2, operand3;
    
    CR.zero = operand1 == operand2;
}

void CPU::jmp() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            opReg1 = GP0;
            break;
        case GPR1:
            opReg1 = GP1;
            break;
        case GPR2:
            opReg1 = GP2;
            break;
        case GPR3:
            opReg1 = GP3;
            break;
        case PCR:
            opReg1 = PC;
            break;
        case SPR:
            opReg1 = SP;
            break;
        case STR:
            opReg1 = CR.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }

    PC = operand1;
}

void CPU::jpz() {
    uint32_t operand1, operand3;
    switch (instruction.operand1) {
        case GPR0:
            opReg1 = GP0;
            break;
        case GPR1:
            opReg1 = GP1;
            break;
        case GPR2:
            opReg1 = GP2;
            break;
        case GPR3:
            opReg1 = GP3;
            break;
        case PCR:
            opReg1 = PC;
            break;
        case SPR:
            opReg1 = SP;
            break;
        case STR:
            opReg1 = CR.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }

    if (CR.zero) PC = operand1;
}

void CPU::push() {

}

void CPU::hlt() {
    while(true) {
        PC++;
    }
}