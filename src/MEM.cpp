#include "MEM.h"

MEM::MEM(uint64_t memSize, string romDirectory) {
    
    // Align memSize to 4
    memSize -= memSize % 4;
    RAM.resize(memSize);

    cout << "Loading ROM" << endl;
    ifstream file(romDirectory, ios::binary);
    if (file.fail()) {
        cout << "ROM does not exist" << endl;
        exit(EXIT_FAILURE);
    }

    // Copy binary file to vector
    vector<uint64_t> buffer(istreambuf_iterator<char>(file), {});
    for (int x = 0; x < buffer.size(); x+=4) {
        RAM[x/4] = buffer[x] + (buffer[x+1] << 8) + (buffer[x+2] << 16) + (buffer[x+3] << 24);
    }
}

uint64_t MEM::read(uint64_t address) {
    uint64_t temp = RAM[address];
    temp += RAM[address + 1] << 8;
    temp += RAM[address + 2] << 16;
    temp += RAM[address + 3] << 24;
    temp += RAM[address + 4] << 32;
    temp += RAM[address + 5] << 40;
    temp += RAM[address + 6] << 48;
    temp += RAM[address + 7] << 56;
    return temp;
}

void MEM::write(uint64_t address, uint64_t data) {
    RAM[address] = data & 0x00000000000000FF;
    RAM[address + 1] = (data & 0x000000000000FF00) >> 8;
    RAM[address + 2] = (data & 0x0000000000FF0000) >> 16;
    RAM[address + 3] = (data & 0x00000000FF000000) >> 24;
    RAM[address + 4] = (data & 0x000000FF00000000) >> 32;
    RAM[address + 5] = (data & 0x0000FF0000000000) >> 40;
    RAM[address + 6] = (data & 0x00FF000000000000) >> 48;
    RAM[address + 7] = (data & 0xFF00000000000000) >> 56;
}