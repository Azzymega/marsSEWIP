#include "include/memory.hpp"

extern Console *konsole;
extern MMU *gc;
extern "C" void loadPageDirectory(unsigned int *);
extern "C" void enablePaging();

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
/*
void MMU::SetupPaging(u4 *entry, page *pentry) {
  for (int x = 0; x < 1024; x++) {
    ((PageDirectoryEntry *)entry[x])->SupervisorFlag = 1;
    ((PageDirectoryEntry *)entry[x])->ReadWriteFlag = 1;
    ((PageDirectoryEntry *)entry[x])->PresentFlag = 0;
  }
  for (int i = 0; i < 1024; i++) {
    //pentry[i] = (i * 0x1000) | 3;
    //memset(&pentry[i], 0, sizeof(page));
    pentry[i].frame = (0x1000 >> 12)*i;
    pentry[i].user = 0;
    pentry[i].rw = 1;
    pentry[i].present = 1;
  }
  // page pe;
  // memset(&pe, 0, sizeof(page));
  // pe.frame = (0x1000 >> 12)*2;
  // pe.user = 0; // 12 бит!
  // pe.rw = 1;
  // pe.present = 1;
  // u4 size = sizeof(page);
  //    konsole->LoadResolve("\n");
  //   konsole->base(&pentry[2], 16);
  //   konsole->LoadResolve("\n");
  // konsole->base((u4*)&pe, 16);
  // konsole->LoadResolve("\n");
  entry[0] = ((unsigned int)pentry) | 3;
  loadPageDirectory((unsigned int *)entry);
  enablePaging();
  // volatile const char *bfd = 0x0;
  // bfd = "Q";
  konsole->LoadResolve("[MMU] Paging is on!\n");
}
*/

Chunck::Chunck() {
  this->ElementsCount = 0;
  this->Size = 0;
  this->StartAddress = nullptr;
  this->SizeAvailable = 0;
}

Heap *Heap::LoadResolve(MMU *Object) {
  for (auto &&chunk : Object->Maps) {
    if (chunk.Type == Avaliable) {
      this->Main.SizeAvailable = chunk.Length;
      this->Main.StartAddress = (char *)(chunk.Address + 1000000);
      this->Main.CurrentAddress = this->Main.StartAddress;
      konsole->LoadResolve("[MMU] Chunck founded!\n");
      break;
    }
  }
  return nullptr;
}

void *malloc(size_t size) {
  return gc->Kernel.AllocateResolve(&size);
}

void *operator new(size_t size) { return malloc(size); }

void *operator new[](size_t size) { return malloc(size); }
