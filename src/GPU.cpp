#include "GPU.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <thread>

using namespace sf;
using namespace std;


GPU::GPU(BUS* _bus) {
    bus = _bus;
    VRAM.resize(GPU_END - GPU_START);
    memcpy(&VRAM[GPU_FONT - GPU_START], &font, sizeof(font));

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

uint32_t GPU::read(uint32_t address) {
    uint32_t temp = VRAM[address - GPU_GRAPHICS_START];
    temp += VRAM[address - GPU_GRAPHICS_START + 1] << 8;
    temp += VRAM[address - GPU_GRAPHICS_START + 2] << 16;
    temp += VRAM[address - GPU_GRAPHICS_START + 3] << 24;
    return temp;
}

void GPU::write(uint32_t address, uint32_t data) {
    VRAM[address - GPU_GRAPHICS_START] = data & 0x000000FF;
    VRAM[address - GPU_GRAPHICS_START + 1] = (data & 0x0000FF00) >> 8;
    VRAM[address - GPU_GRAPHICS_START + 2] = (data & 0x00FF0000) >> 16;
    VRAM[address - GPU_GRAPHICS_START + 3] = (data & 0xFF000000) >> 24;
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