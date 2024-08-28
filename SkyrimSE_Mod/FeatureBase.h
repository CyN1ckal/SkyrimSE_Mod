#pragma once

#include "TGM.h"
#include "UnbreakableLockpick.h"

class FeatureBaseClass {

public:
  bool Initialize();
  bool Uninitialize();
  bool Handler();

public:
  UnbreakableLockpickClass *UnbreakableLockpick;
  TGMClass *TGM;
};