#pragma once

#include "pch.h"

#include "FeatureBase.h"

bool CheatBase::Initialize() {

  SkyrimSEBaseAddress = (uintptr_t)GetModuleHandle(NULL);

  LocalCharacter = *(Character **)(SkyrimSEBaseAddress + 0x02014348);

  FeatureBase = new FeatureBaseClass;

  FeatureBase->Initialize();

  return 1;
}

bool CheatBase::Uninitialize() {

  FeatureBase->Uninitialize();

  if (FeatureBase)
    delete FeatureBase;

  return 1;
}
