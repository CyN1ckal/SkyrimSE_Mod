#pragma once
#include "pch.h"

#include "UnbreakableLockpick.h"

bool UnbreakableLockpickClass::Initialize() {

  UpdateLockpickHealthInstructionAddress =
      PatternScan::Internal::PatternScanModule_ComboPattern(
          "SkyrimSE.exe", Signatures::UpdateLockpickHealthInstructionSignature,
          Signatures::UpdateLockpickHealthInstructionSignatureLength);
  if (!UpdateLockpickHealthInstructionAddress) {
    printf("UpdateLockpickHealthInstructionAddress PatternScan failed!\n");
    return 0;
  }

  if (UnbreakableLockpickOriginalBytes[0] == 0x00)
    memcpy(UnbreakableLockpickOriginalBytes,
           (void *)UpdateLockpickHealthInstructionAddress, 8);
}

bool UnbreakableLockpickClass::Enable() {
  DWORD oProtect;
  VirtualProtect((LPVOID)UpdateLockpickHealthInstructionAddress, 8,
                 PAGE_EXECUTE_READWRITE, &oProtect);
  memset((void *)UpdateLockpickHealthInstructionAddress, 0x90, 0x8);
  VirtualProtect((LPVOID)UpdateLockpickHealthInstructionAddress, 8, oProtect,
                 nullptr);
  PreviousUnbreakableLockpick = true;
  return 1;
}

bool UnbreakableLockpickClass::Disable() {
  DWORD oProtect;
  VirtualProtect((LPVOID)UpdateLockpickHealthInstructionAddress, 8,
                 PAGE_EXECUTE_READWRITE, &oProtect);
  memcpy((void *)UpdateLockpickHealthInstructionAddress,
         UnbreakableLockpickOriginalBytes, 0x8);
  VirtualProtect((LPVOID)UpdateLockpickHealthInstructionAddress, 8, oProtect,
                 nullptr);
  PreviousUnbreakableLockpick = false;
  return 1;
}

bool UnbreakableLockpickClass::Cheat_UnbreakableLockpick() {
  if (PreviousUnbreakableLockpick == UnbreakableLockpick)
    return 1;

  if (UnbreakableLockpick) {
    Enable();
  } else {
    Disable();
  }

  return 1;
}