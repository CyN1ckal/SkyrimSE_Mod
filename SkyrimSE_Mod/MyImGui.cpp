#include "MyImGui.h"
#include "pch.h"

bool MyImGui::Initialize() {
  MouseHandleToggleAddress = (BYTE*)(CheatBase::SkyrimSEBaseAddress + 0x2029850);

  return 1;
}

bool MyImGui::OnFrame() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  if (MasterImGuiToggle) {
    ImGui::ShowDemoWindow();
  }

  ImGui::EndFrame();

  ImGui::Render();

  return 1;
}

bool MyImGui::ToggleMasterImGuiRenderer() {
  MasterImGuiToggle = !MasterImGuiToggle;
  if (MasterImGuiToggle) {
    *MouseHandleToggleAddress = 1;
  } else {
    *MouseHandleToggleAddress = 0;
  }
  return 1;
}