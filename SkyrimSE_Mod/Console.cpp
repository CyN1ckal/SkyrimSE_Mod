#include "Console.h"

bool Console::Initialize() {
  AllocConsole();
  freopen_s(&Console::f, "CONOUT$", "w", stdout);
  Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  Console::CustomColor(ConsoleColors::darkGreen);
  printf("[+] Console Allocated.\n");
  Console::CustomColor(ConsoleColors::white);

  return 1;
}

bool Console::CleanUp() {
  FreeConsole();
  return 1;
}

bool Console::CustomColor(ConsoleColors Color) {
  return SetConsoleTextAttribute(Console::hConsole, Color);
}

void Console::PrintTime() {

  time_t MyTime = time(NULL);
  tm timeInfo;
  localtime_s(&timeInfo, &MyTime);
  printf("%02u:%02u:%02u", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

void Console::PrintWithTime(std::string Message) {
  Console::PrintTime();
  printf(" - %s\n", Message.c_str());
}