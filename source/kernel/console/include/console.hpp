#pragma once
#include "../../ng.hpp"

struct Console : LoadContradiction<Console *, const char *>,
                 LoadContradiction<Console *, u4 *> {
  u1 *Buffer;
  u1 X;
  u1 Y;
  Console();
  Console *LoadResolve(const char *Object) override;
  Console *LoadResolve(u4 *Object) override;
  void base(u4 *Object, int base);
};

enum VGAColor : u1 {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

/*
struct ConsoleCharacter {
    Achar Char;
    VGAColor ForegroungColor : 4;
    VGAColor BackgroundColor : 3;
    bool Blink : 1;
};
*/
