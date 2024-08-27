#pragma once

class MyImGui {
public:
  static bool Initialize(ID3D11Device *Device,
                         ID3D11DeviceContext *DeviceContext, HWND hWnd);
  static bool OnFrame();
  static bool ToggleMasterImGuiRenderer();

  static inline bool m_ImGuiInitialized = false;

private:
  inline static bool MasterImGuiToggle = false;
  inline static BYTE *MouseHandleToggleAddress;

private:
  static bool RenderWaterMark();
  static bool RenderLocalPlayerMenu();
  static bool RenderExploitsMenu();
};