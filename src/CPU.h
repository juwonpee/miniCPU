#pragma once

#include "BUS.h"

using namespace std;

class BUS;

enum registerMode_t : uint8_t {
    GPR0 = 0, GPR1 = 1, GPR2 = 2, GPR3 = 3,
    PCR = 4, SPR = 5, STR = 6, memory = 7, nothing = 8
};

enum instructionRaw_t : uint8_t {
    ADD = 0, SUB = 1, MUL = 2, DIV = 3,
    MOV = 4, CMP = 5, JMP = 6, JPN = 7, JPZ = 8
};

typedef struct instruction_t {
    union {
        struct {
            instructionRaw_t instruction:8;
            registerMode_t register1:8;
            registerMode_t register2:8;
            registerMode_t register3:8;
        };
        uint32_t data;
    };
}instruction_t;



typedef struct status_t {
    union {
        struct {
            uint32_t negative:1;
            uint32_t zero:1;
            uint32_t error:1;
            uint32_t ignore:29;   
        };
        uint32_t data;
    };
}status_t;


class CPU {
    public:
        CPU(BUS* _bus);

        void clock();

    private:

        BUS* bus;

        // Registers
        uint32_t GP0, GP1, GP2, GP3;    // General purpose registers
        uint32_t PC;       // Program counter
        uint32_t SP;       // Stack pointer
        status_t ST;       // Status register

        instruction_t instruction;

        uint32_t memory1;
        uint32_t memory2;
        uint32_t memory3;


        
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