#include "MyImGui.h"
#include "pch.h"

bool MyImGui::Initialize() {
  MouseHandleToggleAddress =
      (BYTE *)(CheatBase::SkyrimSEBaseAddress + 0x2029850);

  Console::CustomColor(ConsoleColors::darkGreen);
  printf("[+] MyImGui Initialized.\n");
  Console::CustomColor(ConsoleColors::white);

  return 1;
}

bool MyImGui::OnFrame() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  MyImGui::RenderWaterMark();

  if (MasterImGuiToggle) {
    ImGui::ShowDemoWindow();

    ImGui::Begin("Exploits");
    ImGui::Checkbox("Teleport All To Me",
                    &CheatBase::TeleportAllEntitiesToPlayer);
    ImGui::End();
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

bool MyImGui::RenderWaterMark() {
  ImGui::SetNextWindowPos({0, 0});
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  ImGui::Begin("Watermark", NULL, window_flags);
  ImGui::Text("Skyrim Special Edition: Modded");
  ImGui::End();
  return 1;
}