#pragma once

#include <stdlib.h>
#include <iostream>

#include "BUS.h"

using namespace std;

class BUS;

enum opcode_t : uint8_t {
    ADD, SUB, MUL, DIV,
    MOV, CMP, JMP, JPZ
};

enum operand_t : uint8_t {
    GPR0, GPR1, GPR2, GPR3,
    PCR, SPR, SBP, STR, memory, nothing
};

typedef union instruction_t {
    struct {
        opcode_t opcode:8;
        operand_t operand1:8;
        operand_t operand2:8;
        operand_t operand3:8;
    };
    uint32_t data;
}instruction_t;


#define EXCEPTION_INVALID_OPCODE        0b00000001
#define EXCEPTION_INVALID_OPERAND       0x02
#define EXCEPTION_DIVISION_BY_ZERO      0x04
#define EXCEPTION_ALIGNMENT             0x08    // Memory address not aligned to 4
#define EXCEPTION_STACK_ALIGNMENT       0x10    // Stack pointer out of bounds

typedef union status_t {
    struct {
        uint32_t zero:1;
        uint32_t exception:8;
        uint32_t reserved:23;   
    };
    uint32_t data;
}status_t;


class CPU {
    public:
        CPU(BUS* _bus);

        void clock();

        // DEBUG: dump contents of CPU during execution
        void dump();

    private:

        BUS* bus;

        // Registers
        uint32_t GP0, GP1, GP2, GP3;    // General purpose registers
        uint32_t PC;                    // Program counter
        uint32_t SP;                    // Stack pointer
        uint32_t BP;                    // Stack base pointer
        status_t ST;                    // Status register

        instruction_t instruction;

        // DEBUG: Save registers before exection
        struct {
            uint32_t GP0, GP1, GP2, GP3;    // General purpose registers
            uint32_t PC;                    // Program counter
            uint32_t SP;                    // Stack pointer
            uint32_t BP;                    // Stack base pointer
            status_t ST;                    // Status register
        } save;

        // operand registers
        uint32_t opReg1;
        uint32_t opReg2;
        uint32_t opReg3;

        void exception();
        
        void fetch();
        void decode();
        void execute();

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t data);


        // Add
        // 1 + 2 -> 3
        void AD();

        // Subtract
        // 1 - 2 -> 3
        void SB();

        // Multiply
        // 1 * 2 -> 3
        void ML();

        // Divide (Ignores remainders)
        // 1 / 2 -> 3
        void DV();

        // Move(copy)
        // 1 -> 3
        void MV();

        // Compare (Sets zero & negative flag)
        // 1 Compare 2
        void CP();

        // Unconditional jump
        // 1 -> PC
        void JP();

        // Jump if negative
        // 1 -> PC
        void JN();

        // Jump if zero
        // 1 -> PC
        void JZ();
        
    
};