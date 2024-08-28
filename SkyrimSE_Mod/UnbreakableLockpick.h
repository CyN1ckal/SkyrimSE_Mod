#pragma once

class UnbreakableLockpickClass {
public:
  bool Initialize();
  bool Enable();
  bool Disable();
  bool Handler();

  // Unbreakable Lockpick
  uintptr_t UpdateLockpickHealthInstructionAddress = 0;
  BYTE UnbreakableLockpickOriginalBytes[8] = {0x0};
  bool PreviousUnbreakableLockpick = false;

  bool UnbreakableLockpick = false;
};
