#pragma once
#include "pch.h"

#include "VersionCheck.h"

bool VersionCheckClass::Initialize() {

  HMODULE CommunityShadersModule = GetModuleHandleW(L"CommunityShaders.dll");

  if (CommunityShadersFound)
    CommunityShadersFound = true;

  return 1;
}