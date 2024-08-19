#include "pch.h"

#include "StartingThread.h"

#include "GameFunctionHooks.h"



LRESULT WINAPI StartingThread(HMODULE hModule) {
  Globals::hModule = hModule;

  Console::Initialize();

  MH_Initialize();

  DirectXHook::Initialize();
  DirectXHook::GetPresentPointer();
  DirectXHook::EnableDirectXHooks();

  CheatBase::Initialize();

  GameFunctionHooks::Initialize();
  GameFunctionHooks::EnableGameFunctionHooks();

  while (!GetAsyncKeyState(VK_END)) {
    Sleep(100);
  }

  Console::CustomColor(ConsoleColors::red);
  printf("[-] Exiting.\n");
  Console::CustomColor(ConsoleColors::white);

  MH_Uninitialize();

  Console::CleanUp();

  FreeLibraryAndExitThread(Globals::hModule, 0);

  return 1;
}