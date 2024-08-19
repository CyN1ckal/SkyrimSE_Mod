#pragma once

typedef long(__stdcall *Present_Template)(IDXGISwapChain *, UINT, UINT);

class DirectXHook {
public:
  static inline ID3D11Device *D3D11_Device;
  static inline ID3D11DeviceContext *D3D11_DeviceContext;
  static inline ID3D11RenderTargetView *MainRenderTargetView;

  static inline HWND SkyrimSE_hWnd;
  static inline HWND FullPath_hWnd;
  static inline HWND SwapChainOutputhWnd;
  static inline DWORD SkyrimSE_ProcessId;

  static inline uintptr_t PresentFunctionAddress;

  static bool Initialize();

  static bool GetPresentPointer();

  static bool EnableDirectXHooks();

  static long __stdcall Present_Hooked(IDXGISwapChain *SwapChain,
                                       UINT SyncInterval, UINT Flags);

  static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

  static inline bool ImGuiInit = false;

  static LRESULT __stdcall SKSE_WndProc(const HWND hWnd, UINT uMsg,
                                        WPARAM wParam, LPARAM lParam);

  static LRESULT __stdcall FullPath_WndProc(const HWND hWnd, UINT uMsg,
                                            WPARAM wParam, LPARAM lParam);

  static inline WNDPROC SKSE_WndProc_Original;
  static inline WNDPROC FullPath_WndProc_Original;

private:
};