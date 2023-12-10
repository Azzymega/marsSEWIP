#pragma once
#include "../ng.hpp"
#include "../boot/include/main.hpp"
struct CPElement;
using CPString = char *;
using CPFloat = float;
using CPLong = u8;
using CPInteger = u4;
using CPShort = u2;
using CPByte = u1;

enum CPTag : u1 { TString, TFloat, TLong, TInteger, TShort, TByte, TEntity };

struct MMU;
struct ConstantPool {
  u4 ElementsCount;
};

struct CPEntity {
  u4 ElementsCount;
  CPElement *Elements;
};

struct Region : IntroduceContradiction<void, void>{
  void *Start;
  void *End;
  u4 AllocatedCount;
  u4 Size;
  void IntroduceResolve() override;
};

struct ArrayList {
  u4* ItemsCount;
  u4* AllocatedCount;
  void* Entity;
  ArrayList();
  ArrayList(u4 Size);
  void* Get(u4 Index);
  void Add(void* Structure);
  void Set(u4 Index, void* Structure);
  void Remove(u4 Index);
};

struct Namespace : AllocateContradiction<u1 *, u1>,
                   AllocateContradiction<float *, float>,
                   AllocateContradiction<u8 *, u8>,
                   AllocateContradiction<const char *, const char *>,
                   AllocateContradiction<u2 *, u2>,
                   AllocateContradiction<u4 *, u4>,
                   AllocateContradiction<void*, u4*>,
                   LoadContradiction<Namespace*, MMU*> {
  Region Superblock;
  Namespace(void *StartAddress, void *EndAddress);
  Namespace();
  float *AllocateResolve(float Object) override;
  const char *AllocateResolve(const char *Object) override;
  unsigned int *AllocateResolve(unsigned int Object) override;
  void * AllocateResolve(unsigned int *Object) override;
  unsigned char * AllocateResolve(unsigned char Object) override;
  unsigned short * AllocateResolve(unsigned short Object) override;
  unsigned long long * AllocateResolve(unsigned long long Object) override;
  Namespace * LoadResolve(MMU *Object) override;
};

struct CPElement {
  CPTag Tag;
  u4 Size;
  union {
    CPString String;
    CPFloat Float;
    CPLong Long;
    CPInteger Integer;
    CPShort Short;
    CPByte Byte;
    CPEntity Entity;
  };
};