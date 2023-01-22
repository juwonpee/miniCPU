#include "serial.h"

#include <iostream>

using namespace std;

string buffer;

serial::serial(BUS* _bus) {
    bus = _bus;
}

serial::~serial() {

}

uint32_t serial::read(uint32_t address) {
    if (address == MEMORY_SERIAL_START) return serialRead();
    return 0;
}

void serial::write(uint32_t address, uint32_t data) {
    if (address == MEMORY_SERIAL_START) serialWrite((uint8_t)data);
}

uint8_t serial::serialRead() {

    if (buffer.length() == 0) {
        cin >> buffer;
    }
    uint8_t temp = buffer[0];
    buffer = buffer.substr(1, buffer.length()-1);
    return temp;
}

void serial::serialWrite(uint8_t data) {
    cout << (char)data;
}
