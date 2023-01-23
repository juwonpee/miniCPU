#pragma once

#include <stdint.h>
#include "BUS.h"

using namespace std;

// Serial interface
#define MEMORY_SERIAL_START 			0xFFFFFFFFFC000000
#define MEMORY_SERIAL_END               0xFFFFFFFFFCFFFFFF
#define SERIAL_COM0                     0xFFFFFFFFFC000000
#define SERIAL_COM1                     0xFFFFFFFFFC000004
#define SERIAL_COM2                     0xFFFFFFFFFC000008
#define SERIAL_COM3                     0xFFFFFFFFFC00000C

#define SERIAL_OFFSET_ON                0x0

class serial {
    public:
        serial(BUS* _bus);
        ~serial();

        uint64_t read(uint64_t address);
        void write(uint64_t address, uint64_t data);

    private:
        BUS* bus;
        uint8_t serialRead();
        void serialWrite(uint8_t data);

};