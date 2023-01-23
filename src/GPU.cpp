#include "GPU.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <thread>
#include <cstring>

using namespace sf;
using namespace std;


GPU::GPU(BUS* _bus) {
    bus = _bus;
    VRAM.resize(MEMORY_GPU_END - MEMORY_GPU_START + 1);
    memcpy(&VRAM[GPU_FONT - MEMORY_GPU_START], &font, sizeof(font));

    // Window
    window = new RenderWindow(VideoMode(GPU_RESOLUTION_WIDTH, GPU_RESULUTION_HEIGHT), "miniCPU");
    texture.create(GPU_RESOLUTION_WIDTH, GPU_RESULUTION_HEIGHT);
    sprite.setTexture(texture);

    display();
}

GPU::~GPU() {
    window->close();
    VRAM.clear();
}

uint64_t GPU::read(uint64_t address) {
    uint64_t temp = VRAM[address - MEMORY_GPU_START];
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 1] << 8;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 2] << 16;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 3] << 24;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 4] << 32;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 5] << 40;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 6] << 48;
    temp += (uint64_t)VRAM[address - MEMORY_GPU_START + 7] << 56;
    return temp;
}

void GPU::write(uint64_t address, uint64_t data) {
    VRAM[address - MEMORY_GPU_START + 0] = data & 0x00000000000000FF;
    VRAM[address - MEMORY_GPU_START + 1] = (data & 0x000000000000FF00) >> 8;
    VRAM[address - MEMORY_GPU_START + 2] = (data & 0x0000000000FF0000) >> 16;
    VRAM[address - MEMORY_GPU_START + 3] = (data & 0x00000000FF000000) >> 24;
    VRAM[address - MEMORY_GPU_START + 4] = (data & 0x000000FF00000000) >> 32;
    VRAM[address - MEMORY_GPU_START + 5] = (data & 0x0000FF0000000000) >> 40;
    VRAM[address - MEMORY_GPU_START + 6] = (data & 0x00FF000000000000) >> 48;
    VRAM[address - MEMORY_GPU_START + 7] = (data & 0xFF00000000000000) >> 56;
}

void GPU::display() {
    switch(read(GPU_MODE)) {
        case graphics:
            texture.update(VRAM.data());
            sprite.setTexture(texture);
            break;
        case text:
            // TODO: make text mode 
            break;
        case none:
            break;
    }
    
    // Update window
    window->clear(Color::Black);
    window->draw(sprite);
    window->display();
}