#pragma once

class CheatBase {
public:
  static bool Initialize();

  static inline uintptr_t SkyrimSEBaseAddress = 0;
  static inline uintptr_t LocalPlayerAddress = 0;

private:
};