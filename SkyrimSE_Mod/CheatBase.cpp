#pragma once
#include "pch.h"

#include "PointerDeref.h"

bool CheatBase::InitializeLocalEntity() {
  printf("InitializeLocalEntity\n");
  LocalEntity = (Entity *)MultiLevelPointerDeref(
      **(uintptr_t **)(SkyrimSEBaseAddress + 0x20FAF00),
      {0x148, 0x250, 0x340, 0x80});
  return 1;
}

bool CheatBase::Initialize() {
  SkyrimSEBaseAddress = (uintptr_t)GetModuleHandle(NULL);

  LocalCharacter = *(Character **)(SkyrimSEBaseAddress + 0x02014348);

  InitializeLocalEntity();

  Console::CustomColor(ConsoleColors::darkGreen);
  printf("[+] Cheat Base Initialized.\n");
  Console::CustomColor(ConsoleColors::white);

  return 1;
}
