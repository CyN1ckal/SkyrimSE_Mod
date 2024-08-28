#pragma once

#include "FeatureBase.h"

class CheatBase {
public:
  static bool Initialize();
  static bool Uninitialize();

  // "Global" Variables
  static inline uintptr_t SkyrimSEBaseAddress = 0;
  static inline Character *LocalCharacter = nullptr;

  // ImGui Interface Variables
  static inline bool TeleportAllEntitiesToPlayer = false;
  static inline bool NoDecrementGold = false;

public:
  static inline FeatureBaseClass *FeatureBase = nullptr;
};
