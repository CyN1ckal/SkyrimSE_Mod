#include "pch.h"

bool DirectXHook::Initialize() {
  SkyrimSE_ProcessId = GetCurrentProcessId();

  SkyrimSE_hWnd = FindWindowA(NULL, "Skyrim Special Edition");

  if (!SkyrimSE_hWnd) {
    Console::PrintError("FindWindowA Failed!");
    return 0;
  }

  SKSE_Original_WndProc = (WNDPROC)SetWindowLongPtrA(
      SkyrimSE_hWnd, GWLP_WNDPROC, (LONG_PTR)SKSE_MyWndProc);

  VersionCheck->Initialize();

  if (VersionCheck->CommunityShadersFound) {
    Console::PrintSuccess("CommunityShaders.dll Found!");

    DirectXHook::GetCommunityShadersPresentPointer();

  } else {
    Console::PrintSuccess("Non-Modded Version Found!");

    DirectXHook::GetPresentPointer();
  }

  if (!PresentFunctionAddress) {
    Console::PrintError("PresentFunctionAddress Missing!");
    return 0;
  }

  return 1;
}

bool DirectXHook::Uninitialize() {
  SetWindowLongPtrA(DirectXHook::SkyrimSE_hWnd, GWLP_WNDPROC,
                    (LONG_PTR)DirectXHook::SKSE_Original_WndProc);
  return 1;
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

long __stdcall DirectXHook::Present_Hooked(IDXGISwapChain *SwapChain,
                                           UINT SyncInterval, UINT Flags) {
  if (!D3D11_Device && !DirectXHook::GetD3D11Device(SwapChain)) {
    Console::PrintError("GetD3D11Device Error!");
    return Present_Original(SwapChain, SyncInterval, Flags);
  }

  if (MyImGui::m_ImGuiInitialized) {
    MyImGui::OnFrame();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

  return Present_Original(SwapChain, SyncInterval, Flags);
}

LRESULT __stdcall DirectXHook::SKSE_MyWndProc(const HWND hWnd, UINT uMsg,
                                              WPARAM wParam, LPARAM lParam) {
  // Reminder, I need to set the MouseHandleToggle if I want messages to come
  // here...

  if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    return true;

  return CallWindowProc(SKSE_Original_WndProc, hWnd, uMsg, wParam, lParam);
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
    Console::PrintError("D3D11CreateDeviceAndSwapChain Failed!");
    printf("    Return Value: %llX\n", ReturnValue);
    return 0;
  }

  void **p_vtable = *reinterpret_cast<void ***>(SwapChain);
  SwapChain->Release();
  Device->Release();

  PresentFunctionAddress = (uintptr_t)p_vtable[8];
  // printf("Present Function %llx\n", PresentFunctionAddress);

  return 1;
}

bool DirectXHook::GetD3D11Device(IDXGISwapChain *SwapChain) {

  if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device),
                                     (void **)&D3D11_Device))) {

    D3D11_Device->GetImmediateContext(&D3D11_DeviceContext);

    ID3D11Texture2D *pBackBuffer;

    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);

    D3D11_Device->CreateRenderTargetView(pBackBuffer, NULL,
                                         &MainRenderTargetView);

    pBackBuffer->Release();

    MyImGui::Initialize(D3D11_Device, D3D11_DeviceContext, SkyrimSE_hWnd);

    return 1;
  }

  Console::PrintError("SwapChain->GetDevice Failed!");

  return 0;
}

bool DirectXHook::GetCommunityShadersPresentPointer() {

  PresentFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "CommunityShaders.dll",
          Signatures::CommunityShadersPresentFunctionSignature,
          Signatures::CommunityShadersPresentFunctionSignatureLength);

  if (!PresentFunctionAddress) {
    Console::PrintError("GetCommunityShadersPresentPointer Failed!");
    return 0;
  }

  return 1;
}