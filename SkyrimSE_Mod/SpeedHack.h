#pragma once

class SpeedHackClass {
public:
  static bool Initialize();
  static bool Handler();

  static inline float DesiredSpeedMult = 100.0f;

private:
  static inline uintptr_t SpeedMultAddress = 0;
};