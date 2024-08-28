#pragma once
#include "pch.h"

#include "GameFunctionHooks.h"

bool GameFunctionHooks::Initialize() {
  using namespace Signatures;
  using namespace PatternScan::Internal;

  UpdateEntityPositionFunctionAddress = PatternScanModule_ComboPattern(
      "SkyrimSE.exe", UpdateEntityPositionFunctionSignature,
      UpdateEntityPositionFunctionSignatureLength);
  if (!UpdateEntityPositionFunctionAddress) {
    Console::PrintError(
        "UpdateEntityPositionFunctionAddress PatternScan Failed!");
    return 0;
  }

  UpdateCharacterPositionFunctionAddress = PatternScanModule_ComboPattern(
      "SkyrimSE.exe", UpdateCharacterPositionFunctionSignature,
      UpdateCharacterPositionFunctionSignatureLength);
  if (!UpdateCharacterPositionFunctionAddress) {
    Console::PrintError(
        "UpdateCharacterPositionFunctionAddress PatternScan Failed!");
    return 0;
  }

  PrintToScreenFunctionAddress = PatternScanModule_ComboPattern(
      "SkyrimSE.exe", PrintToScreenFunctionSignature,
      PrintToScreenFunctionSignatureLength);
  if (!PrintToScreenFunctionAddress) {
    Console::PrintError("PrintToScreenFunctionAddress PatternScan Failed!");
    return 0;
  }

  DecrementItemByAmountFunctionAddress = PatternScanModule_ComboPattern(
      "SkyrimSE.exe", DecrementItemByAmountFunctionSignature,
      DecrementItemByAmountFunctionSignatureLength);
  if (!DecrementItemByAmountFunctionAddress) {
    Console::PrintError(
        "DecrementItemByAmountFunctionAddress PatternScan Failed!");
    return 0;
  }

  return 1;
}

bool GameFunctionHooks::EnableGameFunctionHooks() {

  // EnableUpdateEntityPositionHook();

  if (!EnableUpdateCharacterPositionHook()) {
    Console::PrintError("EnableUpdateCharacterPositionHook");
    return 0;
  }

  EnableUpdateInventoryHook();

  // EnablePrintToScreenHook();

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

bool GameFunctionHooks::EnableUpdateInventoryHook() {
  if (MH_CreateHook(
          (void *)DecrementItemByAmountFunctionAddress, &DecrementItemByAmount,
          reinterpret_cast<LPVOID *>(&UpdateInventory_Original)) != MH_OK) {
    printf("MH_CreateHook UpdateInventoryFunctionAddress Error!\n");
    return 0;
  }

  if (MH_EnableHook((void *)DecrementItemByAmountFunctionAddress) != MH_OK) {
    printf("MH_EnableHook UpdateInventoryFunctionAddress Error!\n");
    return 0;
  }

  return 1;
}

void __fastcall GameFunctionHooks::UpdateEntityPosition_Hooked(
    Entity *Entity, UpdateEntityPositionArg arg) {
  return ChangePlayerPosition_Original(Entity, arg);
}

char __fastcall GameFunctionHooks::UpdateCharacterPosition_Hooked(
    Character *CharacterArg, Vector3 NewPosition) {
  if (CheatBase::TeleportAllEntitiesToPlayer) {
    if (CharacterArg != CheatBase::LocalCharacter) {
      NewPosition.x = CheatBase::LocalCharacter->Position.x;
      NewPosition.y = CheatBase::LocalCharacter->Position.y;
      NewPosition.z = CheatBase::LocalCharacter->Position.z + 1000;
    }
  }

  return UpdateCharacterPosition_Original(CharacterArg, NewPosition);
}

__int64 __fastcall GameFunctionHooks::PrintToScreen_Hooked(BYTE *string,
                                                           __int64 a2,
                                                           char a3) {
  printf("Print To Screen Called!\n");
  printf("  String: %s ; a2: %d ; a3: %d\n", string, a2, a3);
  return PrintToScreen_Original(string, a2, a3);
}

enum DecrementType {
  PlayerGoldReduction = 0x4,
  Direct = 0x7ff60000000,
  Merchant = 0x7ff600000002,
  Dropped = 0x7ff600000003
};

DWORD *__fastcall GameFunctionHooks::DecrementItemByAmount(
    uintptr_t *a1, DWORD *a2, __int64 a3, ItemClass *Item,
    int AmountToDecrement, int DecrementReason, __int64 a7, __int64 a8,
    __int64 a9, __int64 a10) {

  // Console::PrintTime();
  // printf(" - DecrementItemByAmount Called!\n");
  // printf("  a1: %llx    a2: %llx    AmountToDecrement: %d    a3: %llx    a6:
  // "
  //        "%llx\n",
  //        a1, a2, AmountToDecrement, a3, DecrementReason);
  // printf("a7: %llx    a8: %llx    a9: %llx    a10: %llx\n", a7, a8, a9, a10);
  // std::cout << *Item->pItemName << std::endl << std::endl;

  if (CheatBase::NoDecrementGold &&
      DecrementReason == DecrementType::PlayerGoldReduction)
    AmountToDecrement = 0;

  return (UpdateInventory_Original(a1, a2, a3, Item, AmountToDecrement,
                                   DecrementReason, a7, a8, a9, a10));
}