#pragma once

#include "VersionCheck.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam);

typedef long(__stdcall *Present_Template)(IDXGISwapChain *, UINT, UINT);

class DirectXHook {
public:
  // Interface functions
  static bool Initialize();
  static bool Uninitialize();
  static bool EnableDirectXHooks();

public:
  // "Globals"
  static inline ID3D11Device *D3D11_Device = 0;
  static inline ID3D11DeviceContext *D3D11_DeviceContext = 0;
  static inline ID3D11RenderTargetView *MainRenderTargetView = 0;
  static inline HWND SkyrimSE_hWnd = 0;
  static inline DWORD SkyrimSE_ProcessId = 0;
  static inline uintptr_t PresentFunctionAddress = 0;

private:
  // Helper Classes
  static VersionCheckClass *VersionCheck;

private:
  // Private "hook" functions
  static inline Present_Template Present_Original = nullptr;
  static long __stdcall Present_Hooked(IDXGISwapChain *SwapChain,
                                       UINT SyncInterval, UINT Flags);

  static inline WNDPROC SKSE_Original_WndProc;
  static LRESULT __stdcall SKSE_MyWndProc(const HWND hWnd, UINT uMsg,
                                          WPARAM wParam, LPARAM lParam);

private:
  // Private functions
  static bool GetPresentPointer();
  static bool GetCommunityShadersPresentPointer();
  static bool GetD3D11Device(IDXGISwapChain *SwapChain);
};
