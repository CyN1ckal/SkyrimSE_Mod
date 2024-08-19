#pragma once

typedef long(__stdcall *Present_Template)(IDXGISwapChain *, UINT, UINT);

class DirectXHook {
public:
  static inline IDXGISwapChain* SwapChain;
  static inline ID3D11Device *Device;

  static inline HWND SkyrimSE_hWnd;
  static inline DWORD SkyrimSE_ProcessId;

  static inline uintptr_t PresentFunctionAddress;

  static bool Initialize();

  static bool GetPresentPointer();

  static bool EnableDirectXHooks();

  static long __stdcall Present_Hooked(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);

  static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

private:
};