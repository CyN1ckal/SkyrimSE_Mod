#pragma once
#include "pch.h"

#include "VersionCheck.h"

bool VersionCheckClass::Initialize() {

  HMODULE CommunityShadersModule = GetModuleHandleW(L"CommunityShaders.dll");

  if (CommunityShadersModule)
    CommunityShadersFound = true;

  return 1;
}