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

class InternalContradiction {
  virtual void InternalResolve() = 0;
};

template <class T, class J> class AllocateContradiction {
  virtual T AllocateResolve(J Object) = 0;
};

template <class T, class J> class IntroduceContradiction {
  virtual T IntroduceResolve() = 0;
};