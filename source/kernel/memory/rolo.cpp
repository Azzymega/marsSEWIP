#include "rolo.hpp"
#include "../boot/include/memory.hpp"

extern Console *konsole;
extern MMU *gc;

Namespace::Namespace(void *StartAddress, void *EndAddress) {
  this->Superblock.Start = StartAddress;
  this->Superblock.End = EndAddress;
  this->Superblock.Size = (u8)StartAddress - (u8)EndAddress;
  this->Superblock.AllocatedCount = 0;
}

Namespace::Namespace() {}

float *Namespace::AllocateResolve(float Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start) +
                       this->Superblock.AllocatedCount;
  Element->Tag = TFloat;
  Element->Size = 16;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Float = Object;
  konsole->LoadResolve("[ROLO/HISTORY] Allocating Float with value: ");
  konsole->LoadResolve(itoa(Object, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Float;
}

const char *Namespace::AllocateResolve(const char *Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement) + strlen(Object)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start) +
                       this->Superblock.AllocatedCount;
  Element->Tag = TString;
  if (strlen(Object) + 1 > 16) {
    Element->Size = strlen(Object) + 1;
  } else {
    Element->Size = 16;
  }
  strcpy((char*)&Element->String, Object);
  if (strlen(Object) < 16) {
    this->Superblock.AllocatedCount += sizeof(CPElement);
  } else {
    this->Superblock.AllocatedCount += sizeof(CPElement) - 8 + strlen(Object) + 1;
  }
  konsole->LoadResolve("[ROLO/HISTORY] Allocating String with length: ");
  konsole->LoadResolve(itoa(Element->Size, buffer, 10));
  konsole->LoadResolve("\n");
  return (const char*)&Element->String;
}

unsigned int *Namespace::AllocateResolve(unsigned int Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                                     this->Superblock.AllocatedCount);
  Element->Tag = TInteger;
  Element->Size = 16;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Integer = Object;
  konsole->LoadResolve(
      "[ROLO/HISTORY] Allocating unsigned Integer with value: ");
  konsole->LoadResolve(itoa(Object, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Integer;
}

void *Namespace::AllocateResolve(unsigned int *Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement) - 8 + *Object +
       (*Object % 2)) > this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                                     this->Superblock.AllocatedCount);
  Element->Tag = TEntity;
  if (*Object > 8) {
    Element->Size = *Object + (*Object % 2);
  } else {
    Element->Size = 16;
  }
  if (*Object + (*Object % 2) < 8) {
    this->Superblock.AllocatedCount += sizeof(CPElement);
  } else {
    this->Superblock.AllocatedCount +=
        sizeof(CPElement) - 8 + *Object + (*Object % 2);
  }
  this->Superblock.AllocatedCount += sizeof(CPElement);
  memset(Element->Entity.Elements, 0, Element->Size);
  konsole->LoadResolve("[ROLO/HISTORY] Allocating Entity with length: ");
  konsole->LoadResolve(itoa(Element->Size, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Entity;
}

unsigned char *Namespace::AllocateResolve(unsigned char Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                                     this->Superblock.AllocatedCount);
  Element->Tag = TByte;
  Element->Size = 8;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Byte = Object;
  konsole->LoadResolve("[ROLO/HISTORY] Allocating Byte with value: ");
  konsole->LoadResolve(itoa(Object, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Byte;
}

unsigned short *Namespace::AllocateResolve(unsigned short Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                                     this->Superblock.AllocatedCount);
  Element->Tag = TShort;
  Element->Size = 8;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Short = Object;
  konsole->LoadResolve("[ROLO/HISTORY] Allocating Short with value: ");
  konsole->LoadResolve(itoa(Object, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Short;
}

unsigned long long *Namespace::AllocateResolve(unsigned long long Object) {
  char buffer[50];
  if ((this->Superblock.AllocatedCount + sizeof(CPElement)) >
      this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                                     this->Superblock.AllocatedCount);
  Element->Tag = TLong;
  Element->Size = 8;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Long = Object;
  konsole->LoadResolve("[ROLO/HISTORY] Allocating Long with value: ");
  konsole->LoadResolve(itoa(Object, buffer, 10));
  konsole->LoadResolve("\n");
  return &Element->Long;
}

Namespace *Namespace::LoadResolve(MMU *Object) {
  for (auto &&chunk : Object->Maps) {
    if (chunk.Type == Avaliable) {
      this->Superblock.Size = chunk.Length;
      this->Superblock.Start = (char *)(chunk.Address + 1100000);
      this->Superblock.End =
          (void *)(((u8)this->Superblock.Start) + this->Superblock.Size);
      this->Superblock.AllocatedCount = 0;
      konsole->LoadResolve("[MMU] Chunck founded!\n");
      this->Superblock.IntroduceResolve();
      break;
    }
  }
  return nullptr;
}

void Region::IntroduceResolve() {
  char buffer[15];
  konsole->LoadResolve("[ROLO/HISTORY] Superblock defined:\n");
  konsole->LoadResolve("[ROLO/HISTORY] Starts at: 0x");
  konsole->LoadResolve(itoa((u8)this->Start, buffer, 16));
  konsole->LoadResolve("\n");
  konsole->LoadResolve("[ROLO/HISTORY] Ends at: 0x");
  konsole->LoadResolve(itoa((u8)this->End, buffer, 16));
  konsole->LoadResolve("\n");
  konsole->LoadResolve("[ROLO/HISTORY] Size: 0x");
  konsole->LoadResolve(itoa((u8)this->Size, buffer, 16));
  konsole->LoadResolve("\n");
}

ArrayList::ArrayList() {
  u4 Allocation = 10 * sizeof(uintptr_t);
  this->ItemsCount = gc->Kernel.AllocateResolve(u4(0));
  this->AllocatedCount = gc->Kernel.AllocateResolve(u4(10));
  this->Entity = gc->Kernel.AllocateResolve(&Allocation);
}

ArrayList::ArrayList(u4 Size) {
  u4 Allocation = Size * sizeof(uintptr_t);
  this->ItemsCount = gc->Kernel.AllocateResolve(u4(0));
  this->AllocatedCount = gc->Kernel.AllocateResolve(u4(Size));
  this->Entity = gc->Kernel.AllocateResolve(&Allocation);
}

void *ArrayList::Get(u4 Index) {
  return *(void **)(((char *)(this->Entity)) + (Index * sizeof(uintptr_t)));
}

void ArrayList::Add(void *Structure) {
  if (this->ItemsCount + 1 > this->AllocatedCount) {
    void *OldEntity = this->Entity;
    u4 AllocationSize = *this->AllocatedCount * 2;
    this->Entity = gc->Kernel.AllocateResolve(&AllocationSize);
    *this->AllocatedCount = AllocationSize;
    memcpy(this->Entity, OldEntity, *this->ItemsCount * sizeof(uintptr_t));
  }
  this->Set(*this->ItemsCount, Structure);
  *(this->ItemsCount)+=1;
}

void ArrayList::Set(u4 Index, void *Structure) {
  *(((u4 *)this->Entity) + Index) = (u4)Structure;
}

void ArrayList::Remove(u4 Index) {
  this->ItemsCount--;
  memset((void *)(((u4 *)this->Entity) + Index), 0, sizeof(uintptr_t));
  memcpy(((u4 *)this->Entity) + Index, ((u4 *)this->Entity) + Index + 1,
         (*this->ItemsCount - Index) * sizeof(uintptr_t));
}
