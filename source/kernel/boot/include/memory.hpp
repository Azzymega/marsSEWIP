#pragma once
#include "../../memory/rolo.hpp"
#include "../../ng.hpp"
#include "main.hpp"
#include "multiboot.hpp"
#include "paging.hpp"


struct MemoryMap {
  u4 Size;
  u8 Address;
  u8 Length;
  MemoryMapType Type;
} __attribute__((packed));

struct Chunck {
  Chunck();
  char *StartAddress;
  char *CurrentAddress;
  u4 Size;
  u4 SizeAvailable;
  u4 ElementsCount;
};

struct MMU;

struct Heap : LoadContradiction<Heap *, MMU *> {
  Chunck Main;
  u8 PointerCount;
  Heap *LoadResolve(MMU *Object) override;
};

struct MMU : LoadContradiction<MMU *, MultibootController *> {
  MemoryMap Maps[5];
// Heap Memory;
  Namespace Kernel;
  MMU * LoadResolve(MultibootController *Object) override;
//void SetupPaging(u4 *entry, page *pentry) asm("paging");
};

void *malloc(size_t size);