#pragma once

class TGMClass {
public:
  bool Initialize();
  bool Enable();
  bool Disable();

  uintptr_t TGMAddress = 0;
  bool *TGM;
};