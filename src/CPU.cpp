#include "CPU.h"

CPU::CPU(BUS* _bus) {
    bus = _bus;
    GP0 = GP1 = GP2 = GP3 = 0;
    PC = 0;
    SP = 0;
    BP = 0;
    ST.data = 0;
}

void CPU::clock() {
    fetch();
    decode();
    execute();
}

void CPU::dump() {
    cout << "CPU dump" << endl;
    printf("GP0: %x GP1: %x GP2: %x GP3 %x\n", GP0, GP1, GP2, GP3);
    printf("PC: %x\n", PC);
    printf("SP: %x BP: %x\n", SP, BP);
    printf("ST: %x\n", ST.data);

    cout << endl << "Instruction dump" << endl;

    printf("Opcode: %x\n", instruction.opcode);
    printf("operand1: %x, operand1: %x, operand1: %x\n", instruction.operand1, instruction.operand2, instruction.operand3);
}

void CPU::exception() {
    cout << "exception, ";
    if (ST.exception && EXCEPTION_INVALID_OPCODE) {
        cout << "Invalid Opcode" << endl;
    }
    if (ST.exception && EXCEPTION_INVALID_OPERAND) {
        cout << "Invalid Operand" << endl;
    }
    if (ST.exception && EXCEPTION_DIVISION_BY_ZERO) {
        cout << "Division By Zero" << endl;
        }
    if (ST.exception && EXCEPTION_ALIGNMENT) {
        cout << "Memory not aligned by 4" << endl;
    }
    if (ST.exception && EXCEPTION_STACK_ALIGNMENT) {
        cout << "Stack out of range" << endl;
    }

    cout << "CPU dump before execution" << endl;
    printf("GP0: %x GP1: %x GP2: %x GP3 %x\n", GP0, GP1, GP2, GP3);
    printf("PC: %x\n", PC);
    printf("SP: %x BP: %x\n", SP, BP);
    printf("ST: %x\n", ST.data);

    cout << endl << "CPU dump during exection" << endl;
    dump();
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
    save.ST = ST;
}

void CPU::decode() {
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
        case SBP:
            opReg1 = BP;
            break;
        case STR:
            opReg1 = ST.data;
            break;
        case memory:
            if (!(PC % 4)) {
                ST.exception &= EXCEPTION_ALIGNMENT;
                exception();
            }
            else {
                PC+=4;
                opReg1 = read(PC);
            }
            break;
        default:
            ST.exception &= EXCEPTION_INVALID_OPCODE;
            exception();
    }

    switch (instruction.operand2) {
        case GPR0:
            opReg2 = GP0;
            break;
        case GPR1:
            opReg2 = GP1;
            break;
        case GPR2:
            opReg2 = GP2;
            break;
        case GPR3:
            opReg2 = GP3;
            break;
        case PCR:
            opReg2 = PC;
            break;
        case SPR:
            opReg2 = SP;
            break;
        case SBP:
            opReg1 = BP;
            break;
        case STR:
            opReg2 = ST.data;
            break;
        case memory:
            if (!(PC % 4)) {
                ST.exception &= EXCEPTION_ALIGNMENT;
                exception();
            }
            else {
                PC+=4;
                opReg2 = read(PC);
            }
            break;
        default:
            ST.exception &= EXCEPTION_INVALID_OPCODE;
            exception();
    }


    switch(instruction.operand3) {
        case GPR0:
            break;
        case GPR1:
            break;
        case GPR2:
            break;
        case GPR3:
            break;
        case PCR:
            break;
        case SPR:
            break;
        case SBP:
            break;
        case STR:
            break;
        case memory:
            if (!(PC % 4)) {
                ST.exception &= EXCEPTION_ALIGNMENT;
                exception();
            }
            else {
                PC+=4;
                opReg3 = read(PC);
            }
            break;
        case nothing:
            break;
        default:
            ST.exception &= EXCEPTION_INVALID_OPCODE;
            exception();
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
        case JPZ:
            JZ();
            break;
        default:
            ST.exception &= EXCEPTION_INVALID_OPCODE;
            exception();
    }
}

uint32_t CPU::read(uint32_t address) {
    return bus->read(address);
}
void CPU::write(uint32_t address, uint32_t data) {
    bus->write(address, data);
}

void CPU::AD() {
    uint32_t temp = opReg1 + opReg2;

    switch (instruction.operand3) {
        case GPR0:
            GP0 = temp;
            break;
        case GPR1:
            GP1 = temp;
            break;
        case GPR2:
            GP2 = temp;
            break;
        case GPR3:
            GP3 = temp;
            break;
        case PCR:
            PC = temp;
            break;
        case SPR:
            SP = temp;
            break;
        case SBP:
            BP = temp;
            break;
        case STR:
            ST.data = temp;
            break;
        case memory:
            write(opReg3, temp);
            break;
    }

}

void CPU::SB() {
    uint32_t operand1, operand2, operand3;
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            opReg2 = GP0;
            break;
        case GPR1:
            opReg2 = GP1;
            break;
        case GPR2:
            opReg2 = GP2;
            break;
        case GPR3:
            opReg2 = GP3;
            break;
        case PCR:
            opReg2 = PC;
            break;
        case SPR:
            opReg2 = SP;
            break;
        case STR:
            opReg2 = ST.data;
            break;
        case memory:
            opReg2 = opReg2;
            break;
    }
    
    opReg3 = operand1 - operand2;

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
            write(opReg3, operand3);
            break;
    }
    
}

void CPU::ML() {
    uint32_t operand1, operand2, operand3;
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            opReg2 = GP0;
            break;
        case GPR1:
            opReg2 = GP1;
            break;
        case GPR2:
            opReg2 = GP2;
            break;
        case GPR3:
            opReg2 = GP3;
            break;
        case PCR:
            opReg2 = PC;
            break;
        case SPR:
            opReg2 = SP;
            break;
        case STR:
            opReg2 = ST.data;
            break;
        case memory:
            opReg2 = opReg2;
            break;
    }
    
    opReg3 = operand1 * operand2;

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
            write(opReg3, operand3);
            break;
    }
    
}

void CPU::DV() {
    uint32_t operand1, operand2, operand3;
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            opReg2 = GP0;
            break;
        case GPR1:
            opReg2 = GP1;
            break;
        case GPR2:
            opReg2 = GP2;
            break;
        case GPR3:
            opReg2 = GP3;
            break;
        case PCR:
            opReg2 = PC;
            break;
        case SPR:
            opReg2 = SP;
            break;
        case STR:
            opReg2 = ST.data;
            break;
        case memory:
            opReg2 = opReg2;
            break;
    }
    
    opReg3 = operand1 / operand2;

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
            write(opReg3, operand3);
            break;
    }
    
}

void CPU::MV() {
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }
    
    opReg3 = operand1;

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
            write(opReg3, operand3);
            break;
    }
    
}

void CPU::CP() {
    uint32_t operand1, operand2, operand3;
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }
    switch (instruction.operand2) {
        case GPR0:
            opReg2 = GP0;
            break;
        case GPR1:
            opReg2 = GP1;
            break;
        case GPR2:
            opReg2 = GP2;
            break;
        case GPR3:
            opReg2 = GP3;
            break;
        case PCR:
            opReg2 = PC;
            break;
        case SPR:
            opReg2 = SP;
            break;
        case STR:
            opReg2 = ST.data;
            break;
        case memory:
            opReg2 = opReg2;
            break;
    }

    ST.zero = operand1 == operand2;
}

void CPU::JP() {
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }

    PC = operand1;
}

void CPU::JN() {
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }

}

void CPU::JZ() {
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
            opReg1 = ST.data;
            break;
        case memory:
            opReg1 = opReg1;
            break;
    }

    if (ST.zero) PC = operand1;
}