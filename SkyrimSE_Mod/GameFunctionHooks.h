#pragma once

typedef void(__fastcall *UpdateEntityPosition_Template)(
    Entity *Entity, UpdateEntityPositionArg arg);

typedef char(__fastcall *UpdateCharacterPosition_Template)(
    Character *CharacterArg, Vector3 NewPosition);

typedef __int64(__fastcall *PrintToScreen_Template)(BYTE *string, __int64 a2,
                                                    char a3);

typedef DWORD *(__fastcall *UpdateInventory_Template)(
    uintptr_t *a1, DWORD *a2, __int64 a3, ItemClass *Item,
    int AmountToDecrement, int DecrementReason, __int64 a7, __int64 a8,
    __int64 a9, __int64 a10);

class GameFunctionHooks {

public:
  // Public interface functions
  static bool Initialize();
  static bool EnableGameFunctionHooks();

private:
  // Private functions
  static bool EnableUpdateEntityPositionHook();
  static bool EnableUpdateCharacterPositionHook();
  static bool EnablePrintToScreenHook();
  static bool EnableUpdateInventoryHook();

private:
  // Private variables
  static inline uintptr_t UpdateEntityPositionFunctionAddress = 0;
  static inline uintptr_t UpdateCharacterPositionFunctionAddress = 0;
  static inline uintptr_t PrintToScreenFunctionAddress = 0;
  static inline uintptr_t DecrementItemByAmountFunctionAddress = 0;

private:
  // Original game function pointers
  static inline UpdateEntityPosition_Template ChangePlayerPosition_Original =
      nullptr;
  static inline UpdateCharacterPosition_Template
      UpdateCharacterPosition_Original = nullptr;
  static inline PrintToScreen_Template PrintToScreen_Original = nullptr;
  static inline UpdateInventory_Template UpdateInventory_Original = nullptr;

private:
  // Hooked game functions
  static void __fastcall UpdateEntityPosition_Hooked(
      Entity *Entity, UpdateEntityPositionArg arg);
  static char __fastcall UpdateCharacterPosition_Hooked(Character *CharacterArg,
                                                        Vector3 NewPosition);
  static __int64 __fastcall PrintToScreen_Hooked(BYTE *string, __int64 a2,
                                                 char a3);
  static DWORD *__fastcall DecrementItemByAmount(uintptr_t *a1, DWORD *a2,
                                                  __int64 a3, ItemClass *Item,
                                                  int AmountToDecrement,
                                                  int DecrementReason,
                                                  __int64 a7, __int64 a8,
                                                  __int64 a9, __int64 a10);
};
