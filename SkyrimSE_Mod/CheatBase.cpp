#pragma once
#include "pch.h"

bool CheatBase::Initialize() {

  SkyrimSEBaseAddress = (uintptr_t)GetModuleHandle(NULL);

  LocalCharacter = *(Character **)(SkyrimSEBaseAddress + 0x02014348);

  UnbreakableLockpick->Initialize();

  TGM->Initialize();


  return 1;
}

bool CheatBase::Uninitialize() {

  UnbreakableLockpick->Disable();

  TGM->Disable();

  return 1;
}

bool CheatBase::FeatureLoop() {

  UnbreakableLockpick->Handler();


  return 1;
}