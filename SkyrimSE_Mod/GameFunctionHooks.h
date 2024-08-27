#pragma once

typedef void(__fastcall *UpdateEntityPosition_Template)(
    Entity *Entity, UpdateEntityPositionArg arg);

typedef char(__fastcall *UpdateCharacterPosition_Template)(
    Character *CharacterArg, Vector3 NewPosition);

typedef __int64(__fastcall *PrintToScreen_Template)(BYTE *string, __int64 a2, char a3);



class GameFunctionHooks {
public:
  static bool Initialize();
  static bool EnableGameFunctionHooks();

  static inline uintptr_t UpdateEntityPositionFunctionAddress = 0;
  static inline uintptr_t UpdateCharacterPositionFunctionAddress = 0;
  static inline uintptr_t PrintToScreenFunctionAddress = 0;
  static inline uintptr_t UpdateLockpickHealthFunctionAddress = 0;

private:
  static bool EnableUpdateEntityPositionHook();
  static bool EnableUpdateCharacterPositionHook();
  static bool EnablePrintToScreenHook();
};
