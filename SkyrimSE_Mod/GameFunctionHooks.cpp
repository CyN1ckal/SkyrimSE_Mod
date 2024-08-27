#pragma once
#include "pch.h"

#include "GameFunctionHooks.h"

UpdateEntityPosition_Template ChangePlayerPosition_Original = nullptr;
void __fastcall UpdateEntityPosition_Hooked(Entity *Entity,
                                            UpdateEntityPositionArg arg) {
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

PrintToScreen_Template PrintToScreen_Original = nullptr;
__int64 __fastcall PrintToScreen_Hooked(BYTE *string, __int64 a2, char a3) {
  printf("Print To Screen Called!\n");
  printf("  String: %s ; a2: %d ; a3: %d\n", string, a2, a3);
  return PrintToScreen_Original(string, a2, a3);
}

bool GameFunctionHooks::Initialize() {

  UpdateEntityPositionFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateEntityPositionFunctionSignature,
          Signatures::UpdateEntityPositionFunctionSignatureLength);
  if (!UpdateEntityPositionFunctionAddress) {
    printf("UpdateEntityPositionFunctionAddress PatternScan failed!\n");
    return 0;
  }

  UpdateCharacterPositionFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateCharacterPositionFunctionSignature,
          Signatures::UpdateCharacterPositionFunctionSignatureLength);
  if (!UpdateCharacterPositionFunctionAddress) {
    printf("UpdateCharacterPositionFunctionAddress PatternScan failed!\n");
    return 0;
  }

  PrintToScreenFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::PrintToScreenFunctionSignature,
          Signatures::PrintToScreenFunctionSignatureLength);
  if (!PrintToScreenFunctionAddress) {
    printf("PrintToScreenFunctionAddress PatternScan failed!\n");
    return 0;
  }

  UpdateLockpickHealthFunctionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateLockpickHealthFunctionSignature,
          Signatures::UpdateLockpickHealthFunctionSignatureLength);
  if (!UpdateLockpickHealthFunctionAddress) {
    printf("UpdateLockpickHealthFunctionAddress PatternScan failed!\n");
    return 0;
  }

  GameFunctionHooks::EnableGameFunctionHooks();

  return 1;
}

bool GameFunctionHooks::EnableGameFunctionHooks() {

  // EnableUpdateEntityPositionHook();

  EnableUpdateCharacterPositionHook();

  // EnablePrintToScreenHook();

  Console::PrintSuccess("GameFunctionHooks Enabled.");

  return 1;
}

bool GameFunctionHooks::EnableUpdateEntityPositionHook() {
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
  return 1;
}

bool GameFunctionHooks::EnableUpdateCharacterPositionHook() {
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
  return 1;
}

bool GameFunctionHooks::EnablePrintToScreenHook() {
  if (MH_CreateHook((void *)PrintToScreenFunctionAddress, &PrintToScreen_Hooked,
                    reinterpret_cast<LPVOID *>(&PrintToScreen_Original)) !=
      MH_OK) {
    printf("MH_CreateHook UpdateCharacterPositionFunctionAddress Error!\n");
    return 0;
  }

  if (MH_EnableHook((void *)PrintToScreenFunctionAddress) != MH_OK) {
    printf("MH_EnableHook UpdateCharacterPositionFunctionAddress Error!\n");
    return 0;
  }

  return 1;
}