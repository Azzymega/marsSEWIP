#include "include/multiboot.hpp"


extern Console *konsole;

MultibootController *MultibootController::LoadResolve(MultibootData *Object) {
  this->Data = *Object;
  konsole->LoadResolve("[KERNEL] Data is obtained\n");
  return nullptr;
}
