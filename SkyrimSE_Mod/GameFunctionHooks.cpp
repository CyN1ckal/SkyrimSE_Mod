#pragma once
#include "pch.h"

#include "GameFunctionHooks.h"

UpdateEntityPosition_Template ChangePlayerPosition_Original = nullptr;
void __fastcall UpdateEntityPosition_Hooked(Entity *Entity,
                                            UpdateEntityPositionArg arg) {

  if (!CheatBase::LocalEntity) {
    CheatBase::InitializeLocalEntity();
    return ChangePlayerPosition_Original(Entity, arg);
  }

  //if (Entity != CheatBase::LocalEntity) {
  //  return ChangePlayerPosition_Original(Entity, arg);
  //}

  // Ghetto FlyHack
  if (GetAsyncKeyState(VK_NUMPAD5)) {
    arg.Position.x += 2;
  }
  if (GetAsyncKeyState(VK_NUMPAD2)) {
    arg.Position.x -= 2;
  }
  if (GetAsyncKeyState(VK_NUMPAD1)) {
    arg.Position.y += 2;
  }
  if (GetAsyncKeyState(VK_NUMPAD3)) {
    arg.Position.y -= 2;
  }
  if (GetAsyncKeyState(VK_NUMPAD7)) {
    arg.Position.z += 2;
  }
  if (GetAsyncKeyState(VK_NUMPAD4)) {
    arg.Position.z -= 2;
  }

  return ChangePlayerPosition_Original(Entity, arg);
}

UpdateCharacterPosition_Template UpdateCharacterPosition_Original = nullptr;
char __fastcall UpdateCharacterPosition_Hooked(Character *CharacterArg,
                                               Vector3 NewPosition) {
  if (CheatBase::TeleportAllEntitiesToPlayer) {
    if (CharacterArg != CheatBase::LocalCharacter) {
      NewPosition.x = CheatBase::LocalCharacter->Position.x;
      NewPosition.y = CheatBase::LocalCharacter->Position.y;
      NewPosition.z = CheatBase::LocalCharacter->Position.z + 1000;
    }
  }

  return UpdateCharacterPosition_Original(CharacterArg, NewPosition);
}

bool GameFunctionHooks::Initialize() {

  UpdateEntityPositionFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateEntityPositionFunctionSignature,
          Signatures::UpdateEntityPositionFunctionSignatureLength);

  UpdateCharacterPositionFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateCharacterPositionFunctionSignature,
          Signatures::UpdateCharacterPositionFunctionSignatureLength);

  Console::CustomColor(ConsoleColors::darkGreen);
  printf("[+] GameFunctionHooks Initialized.\n");
  Console::CustomColor(ConsoleColors::white);

  return 1;
}

bool GameFunctionHooks::EnableGameFunctionHooks() {
  if (MH_CreateHook((void *)UpdateEntityPositionFunctionAddress,
                    &UpdateEntityPosition_Hooked,
                    reinterpret_cast<LPVOID *>(
                        &ChangePlayerPosition_Original)) != MH_OK) {
    printf("MH_CreateHook UpdateEntityPositionFunctionAddress Error!\n");
    return 0;
  }

  if (MH_EnableHook((void *)UpdateEntityPositionFunctionAddress) != MH_OK) {
    printf("MH_EnableHook UpdateEntityPositionFunctionAddress Error!\n");
    return 0;
  }

  if (MH_CreateHook((void *)UpdateCharacterPositionFunctionAddress,
                    &UpdateCharacterPosition_Hooked,
                    reinterpret_cast<LPVOID *>(
                        &UpdateCharacterPosition_Original)) != MH_OK) {
    printf("MH_CreateHook UpdateCharacterPositionFunctionAddress Error!\n");
    return 0;
  }

  if (MH_EnableHook((void *)UpdateCharacterPositionFunctionAddress) != MH_OK) {
    printf("MH_EnableHook UpdateCharacterPositionFunctionAddress Error!\n");
    return 0;
  }

  Console::CustomColor(ConsoleColors::darkGreen);
  printf("[+] All Game Function Hooks Enabled.\n");
  Console::CustomColor(ConsoleColors::white);

  return 1;
}
