#include "include/memory.hpp"

u4 pages[1024] __attribute__((aligned(4096)));


MMU * MMU::LoadResolve(unsigned int *Object) {
    for (int i = 0; i < 1024; i++) {
        Object[i] = 0x00000002;
    }
    return nullptr;
} 

