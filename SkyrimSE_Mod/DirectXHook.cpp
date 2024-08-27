#include "pch.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam);
LRESULT __stdcall DirectXHook::SKSE_WndProc(const HWND hWnd, UINT uMsg,
                                            WPARAM wParam, LPARAM lParam) {
  // Reminder, I need to set the MouseHandleToggle if I want messages to come
  // here...

  if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    return true;

  return CallWindowProc(SKSE_WndProc_Original, hWnd, uMsg, wParam, lParam);
}

BOOL DirectXHook::EnumWindowsProc(HWND hWnd, LPARAM lParam) {

  DWORD CurrentHWNDProcID;
  GetWindowThreadProcessId(hWnd, &CurrentHWNDProcID);

  if (CurrentHWNDProcID != SkyrimSE_ProcessId)
    return 1;

  std::wstring title(GetWindowTextLength(hWnd) + 1, L'\0');
  GetWindowTextW(hWnd, &title[0], title.size());

  std::wstring SKSE_Title = L"Skyrim Special Edition";

  int ReturnValue = wcscmp(title.c_str(), SKSE_Title.c_str());

  if (!ReturnValue) {
    SkyrimSE_hWnd = hWnd;

    SKSE_WndProc_Original = (WNDPROC)SetWindowLongPtr(
        SkyrimSE_hWnd, GWLP_WNDPROC, (LONG_PTR)SKSE_WndProc);

    return 1;
  }

  return 1;
}

bool DirectXHook::GetPresentPointer() {
  IDXGISwapChain *SwapChain;
  ID3D11Device *Device;

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
  printf("Present Function %llx\n", PresentFunctionAddress);

  return 1;
}

bool DirectXHook::Initialize() {
  SkyrimSE_ProcessId = GetCurrentProcessId();

  EnumWindows(DirectXHook::EnumWindowsProc, NULL);

  // Checking for modded version
  HMODULE ShadersModule = 0;
  bool CommunityShadersFound = false;

  ShadersModule = GetModuleHandleW(L"CommunityShaders.dll");
  if (ShadersModule) {
    Console::PrintSuccess("CommunityShaders.dll Found!");

    DirectXHook::PresentFunctionAddress =
        PatternScan::Internal::PatternScanModule_ComboPattern(
            "CommunityShaders.dll",
            Signatures::CommunityShadersPresentFunctionSignature,
            Signatures::CommunityShadersPresentFunctionSignatureLength);
    CommunityShadersFound = true;
  }

  // Revert to default method for non-modded
  if (!CommunityShadersFound) {
    if (!DirectXHook::GetPresentPointer()) {
      Console::PrintError("GetPresentPointer Failed!");
      return 0;
    }
  }

  if (!PresentFunctionAddress) {
    Console::PrintError("PresentFunctionAddress");
    printf("%X\n", GetLastError());
    return 0;
  }

  if (!DirectXHook::EnableDirectXHooks()) {
    Console::PrintError("EnableDirectXHooks Failed!");
    return 0;
  }

  return 1;
}

Present_Template Present_Original = nullptr;
long __stdcall DirectXHook::Present_Hooked(IDXGISwapChain *SwapChain,
                                           UINT SyncInterval, UINT Flags) {
  if (!m_DXInitialized) {
    if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device),
                                       (void **)&D3D11_Device))) {
      D3D11_Device->GetImmediateContext(&D3D11_DeviceContext);
      ID3D11Texture2D *pBackBuffer;
      SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                           (LPVOID *)&pBackBuffer);
      D3D11_Device->CreateRenderTargetView(pBackBuffer, NULL,
                                           &MainRenderTargetView);
      pBackBuffer->Release();

      m_DXInitialized = true;

      MyImGui::Initialize(D3D11_Device, D3D11_DeviceContext, SkyrimSE_hWnd);

      // ESP::Initialize();

    } else {
      printf("SwapChain->GetDevice Error!\n");
      return Present_Original(SwapChain, SyncInterval, Flags);
    }
  }

  if (MyImGui::m_ImGuiInitialized) {
    MyImGui::OnFrame();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

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

bool DirectXHook::Uninitialize() {
  SetWindowLongPtr(DirectXHook::SkyrimSE_hWnd, GWLP_WNDPROC,
                   (LONG_PTR)DirectXHook::SKSE_WndProc_Original);
  return 1;
}