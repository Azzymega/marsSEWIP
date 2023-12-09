#include "rolo.hpp"
#include "../boot/include/memory.hpp"

extern Console *konsole;

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
  if (strlen(Object)+1 > 16) {
    Element->Size = strlen(Object)+1;
  } else {
    Element->Size = 16;
  }
  strcpy(Element->String, Object); // HACKFIX???
  //memcpy(Element->String, (void *)Object, Element->Size);
  if (strlen(Object) > 16) {
    this->Superblock.AllocatedCount += sizeof(CPElement);
  } else {
    this->Superblock.AllocatedCount += sizeof(CPElement) - 16 + strlen(Object);
  }
  konsole->LoadResolve("[ROLO/HISTORY] Allocating String with length: ");
  konsole->LoadResolve(itoa(Element->Size, buffer, 10));
  konsole->LoadResolve("\n");
  return Element->String;
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
  if ((this->Superblock.AllocatedCount + sizeof(CPElement) - 16 + *Object +
       (*Object % 2)) > this->Superblock.Size) {
    return nullptr;
  }
  CPElement *Element = (CPElement *)((char *)this->Superblock.Start +
                       this->Superblock.AllocatedCount);
  Element->Tag = TEntity;
  if (*Object > 16) {
    Element->Size = *Object + (*Object % 2);
  } else {
    Element->Size = 16;
  }
  if (*Object + (*Object % 2) > 16) {
    this->Superblock.AllocatedCount += sizeof(CPElement);
  } else {
    this->Superblock.AllocatedCount +=
        sizeof(CPElement) - 16 + *Object + (*Object % 2);
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
  Element->Size = 16;
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
  Element->Size = 16;
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
  Element->Size = 16;
  this->Superblock.AllocatedCount += sizeof(CPElement);
  Element->Long = Object;
  konsole->LoadResolve(
      "[ROLO/HISTORY] Allocating Long with value: ");
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
