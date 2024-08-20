#include "pch.h"

#include "StartingThread.h"

#include "GameFunctionHooks.h"

LRESULT WINAPI StartingThread(HMODULE hModule) {
  Globals::hModule = hModule;

  Console::Initialize();

  MH_Initialize();

  CheatBase::Initialize();

  MyImGui::Initialize();

  DirectXHook::Initialize();
  DirectXHook::GetPresentPointer();
  DirectXHook::EnableDirectXHooks();

  // DirectInputHook::Initialize();
  // DirectInputHook::EnableHooks();

  GameFunctionHooks::Initialize();
  GameFunctionHooks::EnableGameFunctionHooks();

  while (!GetAsyncKeyState(VK_END)) {

    if (GetAsyncKeyState(VK_DELETE) & 1) {
      DirectInputHook::BlockKeyboard = !DirectInputHook::BlockKeyboard;
    }
    if (GetAsyncKeyState(VK_INSERT) & 1) {
      MyImGui::ToggleMasterImGuiRenderer();
    }

    Sleep(100);
  }

  Console::CustomColor(ConsoleColors::red);
  printf("[-] Exiting.\n");
  Console::CustomColor(ConsoleColors::white);

  SetWindowLongPtr(DirectXHook::SkyrimSE_hWnd, GWLP_WNDPROC,
                   (LONG_PTR)DirectXHook::SKSE_WndProc_Original);

  MH_Uninitialize();

  Console::CleanUp();

  FreeLibraryAndExitThread(Globals::hModule, 0);

  return 1;
}