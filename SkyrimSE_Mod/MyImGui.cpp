#include "pch.h"

bool MyImGui::Initialize(ID3D11Device *Device,
                         ID3D11DeviceContext *DeviceContext, HWND hWnd) {
  if (m_ImGuiInitialized)
    return true;

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  ImGui_ImplWin32_Init(hWnd);
  ImGui_ImplDX11_Init(Device, DeviceContext);

  MouseHandleToggleAddress =
      (BYTE *)(CheatBase::SkyrimSEBaseAddress + Offsets::MouseHandlerOffset);

  m_ImGuiInitialized = true;

  Console::PrintSuccess("MyImGui Initialized.");

  return true;
}

bool MyImGui::OnFrame() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  MyImGui::RenderWaterMark();

  if (MasterImGuiToggle) {
    ImGui::ShowDemoWindow();

    MyImGui::RenderExploitsMenu();

    MyImGui::RenderLocalPlayerMenu();
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

bool MyImGui::RenderLocalPlayerMenu() {
  // ImGui::SetNextWindowPos({0, 0});
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
  ImGui::Begin("Local Player", NULL, window_flags);
  ImGui::Checkbox("TGM", CheatBase::TGM->TGM);

  if (CheatBase::LocalCharacter->pWorld) {

    ImGui::SliderFloat("SpeedMult",
                       &CheatBase::LocalCharacter->pWorld->SpeedMult, 0, 1000);

    if (ImGui::Button("Set To Default"))
      CheatBase::LocalCharacter->pWorld->SpeedMult = 100.0f;
  }

  ImGui::End();
  return 1;
}

bool DEVTEST = false;
bool MyImGui::RenderExploitsMenu() {
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
  ImGui::Begin("Exploits", NULL, window_flags);
  ImGui::Checkbox("Teleport All To Me",
                  &CheatBase::TeleportAllEntitiesToPlayer);
  ImGui::Checkbox("Unbreakable Lockpick",
                  &CheatBase::UnbreakableLockpick->UnbreakableLockpick);
  ImGui::Checkbox("No Decrement Gold", &CheatBase::NoDecrementGold);
  ImGui::End();
  return 1;
}