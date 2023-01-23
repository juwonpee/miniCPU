#pragma once

#include <stdlib.h>
#include <iostream>

#include "BUS.h"

using namespace std;

class BUS;

enum opcode_t {
    EXC = 0, ADD = 1, SUB = 2, MUL = 3, 
    DIV = 4, MOV = 5, CMP = 6, JMP = 7, 
    JPZ = 8, PUSH = 9, HLT = 10
};

enum operand_t {
    GPR0 = 0, GPR1 = 1, GPR2 = 2, GPR3 = 3,
    PCR = 4, SPR = 5, SBP = 6, STR = 7, 
    memory = 8,
    nothing = 15
};

typedef union instruction_t {
    struct {
        opcode_t opcode:4;
        operand_t operand1:4;
        operand_t operand2:4;
        operand_t operand3:4;
        uint16_t reserved:16;
    };
    uint32_t data;
}instruction_t;


#define EXCEPTION_INVALID_OPCODE        0b00000001
#define EXCEPTION_INVALID_OPERAND       0b00000010
#define EXCEPTION_DIVISION_BY_ZERO      0b00000100
#define EXCEPTION_ALIGNMENT             0b00001000    // Memory address not aligned to 4
#define EXCEPTION_STACK_ALIGNMENT       0b00010000    // Stack pointer out of bounds

typedef union control_t {
    struct {
        uint32_t zero:1;
        uint32_t negative:1
        uint32_t reserved1:6;
        uint32_t exception:8;
        uint32_t reserved2:16;   
    };
    uint32_t data;
}control_t;


class CPU {
    public:
        CPU(BUS* _bus);

        void clock();

    private:

        BUS* bus;

        // Registers
        uint32_t GP0, GP1, GP2, GP3;    // General purpose registers
        uint32_t PC;                    // Program counter
        uint32_t SP;                    // Stack pointer
        uint32_t BP;                    // Stack base pointer
        control_t CR;                   // Control register

        instruction_t instruction;

        // DEBUG: Save registers before exection
        struct {
            uint32_t GP0, GP1, GP2, GP3;    // General purpose registers
            uint32_t PC;                    // Program counter
            uint32_t SP;                    // Stack pointer
            uint32_t BP;                    // Stack base pointer
            control_t CR;                    // Control register
        } save;

        // operand registers
        uint32_t* opReg1;
        uint32_t* opReg2;
        uint32_t* opReg3;

        void fetch();
        void decode();
        void (CPU::*lookup[256])() = {&CPU::exc, &CPU::add, &CPU::sub, &CPU::mul, &CPU::div, &CPU::mov, &CPU::cmp, &CPU::jmp, &CPU::jpz, &CPU::push, &CPU::hlt};
        void execute();
        void call(void (CPU::*func)());

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t data);

        // Exception
        // Print out registers to serial
        void exc();

        // Add
        // OP1 + OP2 -> OP3
        void add();

        // Subtract
        // OP1 - OP2 -> OP3
        void sub();

        // Multiply
        // OP1 * OP2 -> OP3
        void mul();

        // Divide (Ignores remainders)
        // OP1 / OP2 -> OP3
        void div();

        // Move(copy)
        // OP1 -> OP3
        void mov();

        // Compare (Sets zero flag)
        // OP1 Compare OP2
        void cmp();

        // Unconditional jump
        // OP1 -> PC
        void jmp();

        // Jump if zero
        // OP1 -> PC
        void jpz();

        // Push to stack
        // OP1 -> SP
        void push();
        
        //Halt
        void hlt();
};