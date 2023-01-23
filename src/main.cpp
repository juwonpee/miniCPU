#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdlib.h>

#include "BUS.h"

using namespace std;

void cmdHelp() {
    cout << "Custom CPU emulator" << endl;
    cout << "Parameters" << endl;
    cout << "-h Help" << endl;
    cout << "-r ROM. Must be compiled with miniGCC" << endl;
    cout << "-m Memory Size, If not specified, defaults to 128MB. Input in multiple of K, M, G (ex. 128M)" << endl;
}


int main(int argc, char* argv[]) {
    int opt;
    uint64_t memorySize;
    string romDirectory;
    while ((opt = getopt(argc, argv, "hr:m:")) != -1) {
        switch (opt) {
            case 'h':
                cmdHelp();
                exit(0);
                continue;
            case 'r':
                romDirectory = optarg;
                continue;
            case 'm':
                memorySize = atoi(optarg);
                continue;
                //char multiplier = temp[temp.size()-1];
                // TODO: Complete memory size argument parser
        }
    }
    if (romDirectory == "") {
        cmdHelp();
        exit(EXIT_FAILURE);
    }

    // Start emulation
    BUS emulator(memorySize, romDirectory); 
}