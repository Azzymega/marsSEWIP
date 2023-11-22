#pragma once
#include "stddef.h"
#include "stdint.h"

using u8 = uint64_t;
using u4 = uint32_t;
using u2 = uint16_t;
using u1 = uint8_t;
using Achar = char;

template <class T, class J> class LoadContradiction {
  virtual T LoadResolve(J Object) = 0;
};
