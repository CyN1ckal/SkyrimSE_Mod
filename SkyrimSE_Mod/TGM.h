#pragma once

class TGMClass
{
public:
  static bool Initialize();
  static bool Enable();
  static bool Disable();

  static inline uintptr_t TGMAddress = 0;
  static inline bool *TGM;
};