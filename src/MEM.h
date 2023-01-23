#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>


using namespace std;

class MEM {
    public:
        MEM(uint64_t memSize, string romDirectory);
        uint64_t read(uint64_t address);
        
        void write(uint64_t address, uint64_t data);


    private:
        vector<uint8_t> RAM; 

        // Special memory mapped registers
        uint64_t memorySize;
        uint64_t videoStart;


};