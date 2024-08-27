#include "pch.h"

#include "StartingThread.h"

#include "GameFunctionHooks.h"

LRESULT WINAPI StartingThread(HMODULE hModule) {
  Globals::hModule = hModule;

  Console::Initialize();

  MH_Initialize();

  CheatBase::Initialize();

  if (DirectXHook::Initialize()) {
    Console::PrintSuccess("DirectXHook Initialized.");
  } else {
    Console::PrintError("DirectXHook Initialize Failed!");
  }

  if (!DirectXHook::EnableDirectXHooks()) {
    Console::PrintError("EnableDirectXHooks Failed!");
    return 0;
  }

  if (GameFunctionHooks::Initialize()) {
    Console::PrintSuccess("GameFunctionHooks Initialized.");
  } else {
    Console::PrintError("GameFunctionHooks Initialize Failed!");
  }

  if (GameFunctionHooks::EnableGameFunctionHooks()) {
    Console::PrintSuccess("GameFunctionHooks Enabled.");
  } else {
    Console::PrintError("EnableGameFunctionHooks Failed!");
  }

  while (!GetAsyncKeyState(VK_END)) {

    if (GetAsyncKeyState(VK_INSERT) & 1) {
      MyImGui::ToggleMasterImGuiRenderer();
    }

    CheatBase::FeatureLoop();

    Sleep(25);
  }

  Console::PrintError("Exiting.");

  CheatBase::Uninitialize();

  DirectXHook::Uninitialize();

  MH_Uninitialize();

  Console::CleanUp();

  Sleep(100);

  FreeLibraryAndExitThread(Globals::hModule, 0);

  return 1;
}