#pragma once
#include "pch.h"

#include "TGM.h"

bool TGMClass::Initialize() {
  TGMAddress = (CheatBase::SkyrimSEBaseAddress + Offsets::tgmOffset);

  TGM = (bool *)TGMAddress;

  return 1;
}

bool TGMClass::Enable() {
  *TGM = 1;
  return 1;
}

bool TGMClass::Disable() {
  *TGM = 0;
  return 1;
}