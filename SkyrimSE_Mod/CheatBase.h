#pragma once

class CheatBase {
public:
  static bool Initialize();
  static bool InitializeLocalEntity();

  static inline uintptr_t SkyrimSEBaseAddress = 0;
  static inline Entity *LocalEntity = nullptr;
  static inline Character *LocalCharacter = nullptr;

  // Cheat Features
  static inline bool TeleportAllEntitiesToPlayer = false;

private:
};