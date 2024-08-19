#include "pch.h"

BOOL DirectXHook::EnumWindowsProc(HWND hWnd, LPARAM lParam) {
  DWORD CurrentHWNDProcID;
  GetWindowThreadProcessId(hWnd, &CurrentHWNDProcID);
  if (CurrentHWNDProcID == SkyrimSE_ProcessId) {
    SkyrimSE_hWnd = hWnd;
    return 0;
  }

  return 1;
}

bool DirectXHook::GetPresentPointer() {
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = SkyrimSE_hWnd;
  sd.SampleDesc.Count = 1;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  const D3D_FEATURE_LEVEL feature_levels[] = {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_0,
  };

  HRESULT ReturnValue = D3D11CreateDeviceAndSwapChain(
      NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels, 2,
      D3D11_SDK_VERSION, &sd, &SwapChain, &Device, nullptr, nullptr);
  if (ReturnValue != S_OK) {
    printf("D3D11CreateDeviceAndSwapChain Error!\n");
    printf("Return Value: %llX\n", ReturnValue);
    return 0;
  }

  void **p_vtable = *reinterpret_cast<void ***>(SwapChain);
  SwapChain->Release();
  Device->Release();

  PresentFunctionAddress = (uintptr_t)p_vtable[8];

  return 1;
}

bool DirectXHook::Initialize() {
  SkyrimSE_ProcessId = GetCurrentProcessId();

  EnumWindows(DirectXHook::EnumWindowsProc, NULL);

  return 1;
}

Present_Template Present_Original = nullptr;
long __stdcall DirectXHook::Present_Hooked(IDXGISwapChain *SwapChain,
                                           UINT SyncInterval, UINT Flags) {
  return Present_Original(SwapChain, SyncInterval, Flags);
}

bool DirectXHook::EnableDirectXHooks() {

  if (MH_CreateHook((void *)PresentFunctionAddress, &Present_Hooked,
                    reinterpret_cast<LPVOID *>(&Present_Original)) != MH_OK) {
    printf("PresentFunctionAddress MH_CreateHook Failed!\n");
    return 0;
  }

  if (MH_EnableHook((void *)PresentFunctionAddress) != MH_OK) {
    printf("PresentFunctionAddress MH_EnableHook Failed!\n");
    return 0;
  }

  return 1;
}
