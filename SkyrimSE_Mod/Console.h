#pragma once
#include "pch.h"

enum ConsoleColors {
  black = 0,
  darkBlue,
  darkGreen,
  babyBlue,
  red,
  purple,
  gold,
  lightGray,
  gray,
  skyBlue,
  lightGreen,
  cyan,
  peach,
  magenta,
  khaki,
  white
};

namespace Console {

bool Initialize();
bool CleanUp();
bool CustomColor(ConsoleColors Color);
void PrintTime();
void PrintWithTime(std::string Message);

static FILE *f;
static HANDLE hConsole;

}; // namespace Console