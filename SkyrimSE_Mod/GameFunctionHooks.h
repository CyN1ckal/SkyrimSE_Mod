#pragma once

typedef void(__fastcall *UpdateEntityPosition_Template)(
    __int64 LocalPlayer, UpdateEntityPositionArg arg);

typedef char(__fastcall *UpdateCharacterPosition_Template)(
    Character* CharacterArg, Vector3 NewPosition);

class GameFunctionHooks {
public:
  static bool Initialize();
  static bool EnableGameFunctionHooks();

private:
  static inline uintptr_t UpdateEntityPositionFunctionAddress = 0;
  static inline uintptr_t UpdateCharacterPositionFunctionAddress = 0;
};
