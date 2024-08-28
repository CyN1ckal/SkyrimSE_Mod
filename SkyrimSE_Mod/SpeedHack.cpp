#pragma once

#include "pch.h"

#include "SpeedHack.h"

bool SpeedHackClass::Initialize() {

  SpeedMultAddress = (uintptr_t)&CheatBase::LocalCharacter->pWorld->SpeedMult;

  return 1;
}

bool SpeedHackClass::Handler() {


  return 1;
}