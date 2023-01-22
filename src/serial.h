#pragma once

#include <stdint.h>
#include "BUS.h"

using namespace std;

// Serial interface
#define MEMORY_SERIAL_START 			0xFC000000
#define MEMORY_SERIAL_END               0xFCFFFFFF
#define SERIAL_COM0                     0xFC000000
#define SERIAL_COM1                     0xFC000004
#define SERIAL_COM2                     0xFC000008
#define SERIAL_COM3                     0xFC00000C

class serial {
    public:
        serial(BUS* _bus);
        ~serial();

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t data);

    private:
        BUS* bus;
        uint8_t serialRead();
        void serialWrite(uint8_t data);

};