#pragma once

#include "pch.h"

bool FeatureBaseClass::Initialize() {

  UnbreakableLockpick = new UnbreakableLockpickClass;
  UnbreakableLockpick->Initialize();

  TGM = new TGMClass;
  TGM->Initialize();

  return 1;
}

bool FeatureBaseClass::Uninitialize() {

  UnbreakableLockpick->Disable();
  if (UnbreakableLockpick)
    delete UnbreakableLockpick;

  TGM->Disable();
  if (TGM)
    delete TGM;

  return 1;
}

bool FeatureBaseClass::Handler() {

  UnbreakableLockpick->Handler();

  return 1;
}