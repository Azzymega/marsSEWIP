#include "include/console.hpp"
#include "../boot/include/main.hpp"

Console::Console() {
  this->Buffer = (u1 *)0xb8000;
  this->X = 0;
  this->Y = 0;
  for (int x = 0; x < (80 * 25) * 2; x++) {
    Buffer[x++] = 0;
  }
}

Console *Console::LoadResolve(const char *Object) {
  for (size_t x = 0; x < strlen(Object); x++) {
    if (Object[x] == '\n') {
      Y++;
      X = 0;
      continue;
    }
    if (X > 80) {
      X = 0;
      Y++;
      if (Y > 25) {
        Y = 0;
      }
    }
    this->Buffer[((X++) + (Y * 80)) * 2] = Object[x];
  }
  return nullptr;
}

Console *Console::LoadResolve(u4 *Object) {
	char x[15];
  this->LoadResolve(itoa(*Object, x, 10));
  return nullptr;
}

void Console::base(u4 *Object, int base) {
	char x[15];
  this->LoadResolve(itoa(*Object, x, base));
}
