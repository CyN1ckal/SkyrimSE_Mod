#pragma once
#include "UnbreakableLockpick.h"
#include "TGM.h"

class CheatBase {
public:
  static bool Initialize();
  static bool Uninitialize();
  static bool FeatureLoop();

  // "Global" Variables
  static inline uintptr_t SkyrimSEBaseAddress = 0;
  static inline Character *LocalCharacter = nullptr;

  // ImGui Interface Variables
  static inline bool TeleportAllEntitiesToPlayer = false;

public:
  // Cheat Feature Classes
  static UnbreakableLockpickClass *UnbreakableLockpick;
  static TGMClass *TGM;
};
