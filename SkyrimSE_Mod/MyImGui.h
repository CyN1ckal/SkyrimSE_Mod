#pragma once

class MyImGui {
public:
  static bool Initialize();
  static bool OnFrame();
  static bool ToggleMasterImGuiRenderer();

  inline static BYTE* MouseHandleToggleAddress;

  inline static bool MasterImGuiToggle = false;

private:
};