#include "include/main.hpp"
#include "../console/include/console.hpp"
#include "include/panic.hpp"

MultibootData *Header;
Console *konsole;
extern "C" u8 KernelStart;
extern "C" u8 KernelEnd;

extern "C" void kernel_main(u4 MultibootMagic,
                            struct MultibootData *MultibootHeader) {
  Header = MultibootHeader;
  Console console = Console();
  // PanicController Panic = PanicController(&console);
  konsole = &console;
  char str[12];
  if (MultibootMagic == 0x2BADB002) {
    console.LoadResolve("[KERNEL] Multiboot header is present!\n");
        console.LoadResolve("[KERNEL] Kernel ends at: 0x");
        console.LoadResolve(itoa(KernelEnd-KernelStart, str, 16));
  } else {
    console.LoadResolve("[KERNEL] Multiboot header is NOT present!\n");
    return;
  }
  MultibootController Controller = MultibootController();
  Controller.LoadResolve(MultibootHeader);
}

extern "C" void __cxa_pure_virtual() {}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

void *memset(void *s, int c, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((char *)s)[i] = c;
  }

  return s;
}

void *memcpy(void *dst, void *src, size_t len) {
  for (size_t i = 0; i < len; i++) {
    *(char *)dst = *(char *)src;
  }
  return dst;
}

char *itoa(int value, char *str, int base) {
  char *rc;
  char *ptr;
  char *low;
  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }
  rc = ptr = str;
  if (value < 0 && base == 10) {
    *ptr++ = '-';
  }
  low = ptr;
  do {
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
             "uvwxyz"[35 + value % base];
    value /= base;
  } while (value);
  *ptr-- = '\0';
  while (low < ptr) {
    char tmp = *low;
    *low++ = *ptr;
    *ptr-- = tmp;
  }
  return rc;
}
