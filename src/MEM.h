#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <iterator>

using namespace std;

class MEM {
    public:
        MEM(uint32_t memSize, string romDirectory);
        uint32_t read(uint32_t address);
        
        void write(uint32_t address, uint32_t data);


    private:
        vector<uint8_t> RAM;

        // Special memory mapped registers
        uint32_t memorySize;
        uint32_t videoStart;


};