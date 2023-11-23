#pragma once
#include "../../ng.hpp"
#include "main.hpp"
#include "multiboot.hpp"

struct MemoryMap {
  u4 Size;
  u8 Address;
  u8 Length;
  MemoryMapType Type;
} __attribute__((packed));

struct Chunck {
  Chunck();
  void *StartAddress;
  u4 Size;
  u4 SizeAvailable;
  u4 ElementsCount;
};

struct Pointer;

template <class T> struct Object {
  u4 *LinkCounter;
  T *Data = nullptr;
  Object(Pointer *Info);
  ~Object();
  Object(const Object &data);
};

struct RelocArray {
  void *Data;
  void Add(void *Data);
  u4 Count;
  u4 Sizeof;
  u4 AllocatedCount;
};

struct Pointer {
  u4 Size = 0;
  void *Data;
  u4 LinkCounter = 0;
};

struct KernelGC;
struct MMU;

struct KernelGC : LoadContradiction<KernelGC *, MMU *> {
  Chunck Heap;
  u8 PointerCount;
  RelocArray Pointers;
  KernelGC *LoadResolve(MMU *Object) override;
  template <class T> Object<T> malloc(size_t size);
  template <class T> Object<T> malloc();
  void Normalize();

private:
  void *rawmalloc(size_t size);
};

struct MMU : LoadContradiction<MMU *, MultibootController *> {
  MemoryMap Maps[5];
  KernelGC GC;
  MMU *LoadResolve(MultibootController *Object) override;
};


template <class T> Object<T>::Object(Pointer *Info) {
  this->Data = (T*)Info->Data;
  this->LinkCounter = &Info->LinkCounter;
}

template <class T> Object<T>::~Object() { *this->LinkCounter--; }

template <class T> Object<T> KernelGC::malloc() {
  if (this->Heap.SizeAvailable < sizeof(T)) {
    return Object<T>(nullptr);
  } else {
    if (this->Pointers.AllocatedCount + 1 == this->Pointers.Count) {
      void *OldData = this->Pointers.Data;
      u8 OldDataSize = this->Pointers.Count * sizeof(Pointer);
      this->Pointers.Data =
          (void **)rawmalloc(this->Pointers.Count * sizeof(Pointer) * 2);
      this->Pointers.AllocatedCount *= 2;
      memcpy(this->Pointers.Data, OldData, OldDataSize);
    }
    Pointer *pnt = (Pointer *)rawmalloc(sizeof(Pointer));
    pnt->Size = sizeof(T);
    pnt->Data = rawmalloc(sizeof(T));
    pnt->LinkCounter = 1;
    this->Pointers.Add(pnt);
    return Object<T>(pnt);
  }
}

template <class T> Object<T> KernelGC::malloc(size_t size) {
  if (this->Heap.SizeAvailable < size) {
    return Object<T>(nullptr);
  } else {
    if (this->Pointers.AllocatedCount + 1 == this->Pointers.Count) {
      void *OldData = this->Pointers.Data;
      u8 OldDataSize = this->Pointers.Count * sizeof(Pointer);
      this->Pointers.Data =
          (void **)rawmalloc(this->Pointers.Count * sizeof(Pointer) * 2);
      this->Pointers.AllocatedCount *= 2;
      memcpy(this->Pointers.Data, OldData, OldDataSize);
    }
    Pointer *pnt = (Pointer *)rawmalloc(sizeof(Pointer));
    pnt->Size = size;
    pnt->Data = rawmalloc(size);
    pnt->LinkCounter = 1;
    this->Pointers.Add(pnt);
    return Object<T>(pnt);
  }
}