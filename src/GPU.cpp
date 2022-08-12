#include "GPU.h"

GPU::GPU(BUS* _bus) {
    bus = _bus;
    memory.reserve(600 * 400);
}