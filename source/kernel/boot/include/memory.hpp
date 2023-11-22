#pragma once
#include "../../ng.hpp"
#include "multiboot.hpp"

extern u4 ExecutionEngineEnd;

struct MemoryMap {
  u4 Size;
  u8 Address;
  u8 Length;
  MemoryMapType Type;
} __attribute__((packed));

struct MMU : LoadContradiction<MMU*, u4*>{
    MemoryMap Maps[5];
    MMU * LoadResolve(unsigned int *Object) override;
};