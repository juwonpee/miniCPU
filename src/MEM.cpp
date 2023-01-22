#include "MEM.h"

MEM::MEM(uint32_t memSize, string romDirectory) {
    
    // Align memSize to 4
    memSize -= memSize % 4;
    RAM.resize(memSize/4);

    cout << "Loading ROM" << endl;
    ifstream file(romDirectory, ios::binary);
    if (file.fail()) {
        cout << "ROM does not exist" << endl;
        exit(EXIT_FAILURE);
    }

    // Copy binary file to vector
    vector<uint32_t> buffer(istreambuf_iterator<char>(file), {});
    for (int x = 0; x < buffer.size(); x+=4) {
        RAM[x/4] = buffer[x] + (buffer[x+1] << 8) + (buffer[x+2] << 16) + (buffer[x+3] << 24);
    }
}

uint32_t MEM::read(uint32_t address) {
    uint32_t temp = RAM[address];
    temp += RAM[address + 1] << 8;
    temp += RAM[address + 2] << 16;
    temp += RAM[address + 3] << 24;
    return temp;
}

void MEM::write(uint32_t address, uint32_t data) {
    RAM[address] = data & 0x000000FF;
    RAM[address + 1] = (data & 0x0000FF00) >> 8;
    RAM[address + 2] = (data & 0x00FF0000) >> 16;
    RAM[address + 3] = (data & 0xFF000000) >> 24;
}