#pragma once

#include <stdint.h>

#include "BUS.h"

using namespace std;


// Video Memory always starts at 0x0
// Resolution os 600 * 400 with one word to each pixel



class BUS;

class GPU {
    public:
        GPU(BUS* _bus);


    private:
        BUS* bus;

        vector<uint32_t> memory;
        void display();
};