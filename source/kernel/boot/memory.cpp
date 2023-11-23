#include "include/memory.hpp"

extern Console *konsole;

MMU *MMU::LoadResolve(MultibootController *Object) {
  u4 y = 0;
  for (u4 x = 0; x < Object->Data->MemoryMapData.MemoryMapLength;
       x += sizeof(MemoryMap)) {
    char Address[16];
    char Length[16];
    this->Maps[y] =
        *(MemoryMap *)(Object->Data->MemoryMapData.MemoryMapAddress + x);
    konsole->LoadResolve("[MMU] Memory map start: 0x");
    konsole->LoadResolve(itoa(this->Maps[y].Address, Address, 16));
    konsole->LoadResolve(", length: 0x");
    konsole->LoadResolve(itoa(this->Maps[y].Length, Length, 16));
    konsole->LoadResolve(", type: ");
    switch (this->Maps[y].Type) {

    case Avaliable:
      if (this->Maps[y].Address == 0) {
        this->Maps[y].Type = Reserved;
        konsole->LoadResolve("Reserved\n");
        break;
      }
      konsole->LoadResolve("Available\n");
      break;
    case Reserved:
      konsole->LoadResolve("Reserved\n");
      break;
    case ACPI_Reclaimable:
      konsole->LoadResolve("ACPI\n");
      break;
    case NVS:
      konsole->LoadResolve("NVS\n");
      break;
    case BADRAM:
      konsole->LoadResolve("BADRAM\n");
      break;
      break;
    }
    y++;
  }
  return nullptr;
}

Chunck::Chunck() {
  this->ElementsCount = 0;
  this->Size = 0;
  this->StartAddress = nullptr;
  this->SizeAvailable = 0;
}

KernelGC *KernelGC::LoadResolve(MMU *Object) {
  for (auto &&chunk : Object->Maps) {
    if (chunk.Type == Avaliable) {
      this->Heap.SizeAvailable = chunk.Length;
      this->Heap.StartAddress = (void *)(chunk.Address + 300 + 1000000);
      this->Pointers.AllocatedCount += 300 / sizeof(Pointer);
      this->Pointers.Data = this->Heap.StartAddress;
      this->Pointers.Sizeof = sizeof(Pointer);
      konsole->LoadResolve("[MMU] Chunck founded!\n");
      break;
    }
  }
  return nullptr;
}

void *KernelGC::rawmalloc(size_t size) {
  if (this->Heap.SizeAvailable < size) {
    return nullptr;
  } else {
    this->Heap.ElementsCount++;
    this->Heap.Size += size;
    this->Heap.SizeAvailable -= size;
    char data[16];
    konsole->LoadResolve("[KERNELGC] Raw allocating ");
    konsole->LoadResolve(itoa(size, data, 10));
    konsole->LoadResolve(" bytes\n");
    return (void *)((char *)this->Heap.StartAddress + this->Heap.Size);
  }
}

void RelocArray::Add(void *Data) {
  char *Address = (char *)this->Data;
  Address += (this->Sizeof * this->Count);
  memcpy(Address, Data, this->Sizeof);
  konsole->LoadResolve("[KERNELGC] Adding new pointer\n");
}
