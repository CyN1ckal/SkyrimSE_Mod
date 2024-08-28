#pragma once

class UnbreakableLockpickClass {
public:
  static bool Initialize();
  static bool Enable();
  static bool Disable();
  static bool Handler();

  // Unbreakable Lockpick
  static inline uintptr_t UpdateLockpickHealthInstructionAddress = 0;
  static inline BYTE UnbreakableLockpickOriginalBytes[8] = {0x0};
  static inline bool PreviousUnbreakableLockpick = false;

  static inline bool UnbreakableLockpick = false;
};
