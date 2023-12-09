#pragma once
#include "memory.hpp"
#include "../../ng.hpp"

struct SegmentSelector {
  
};

struct GDTEntry {
  u2 LimitLow;
  u2 BaseLow;
  u1 BaseMiddle;
  u1 Access;
};

struct GlobalDescriptorTable {

};

struct Segmenter {

};