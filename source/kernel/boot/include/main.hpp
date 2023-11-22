#pragma once
#include "../../ng.hpp"
#include "multiboot.hpp"

struct String {
  const char *Value;
  String(const char *String);
};

extern "C" void kernel_main(u4 MultibootMagic,
                            struct MultibootData *MultibootHeader);
extern "C" void __cxa_pure_virtual();
extern "C" void *memcpy(void *dst, void *src, size_t len);
extern "C" char *itoa(int value, char *str, int base);
extern "C" void *memset(void *s, int c, size_t n);
extern "C" size_t strlen(const char *str);
