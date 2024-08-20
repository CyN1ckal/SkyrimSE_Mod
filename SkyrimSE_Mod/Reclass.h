#pragma once
// Created with ReClass.NET 1.2 by KN4CK3R
// Created with ReClass.NET 1.2 by KN4CK3R

class Entity {
public:
  char pad_0000[16];           // 0x0000
  class World *pWorld;         // 0x0010
  class Cache *pCache;         // 0x0018
  class ListShape *pListShape; // 0x0020
  char pad_0028[40];           // 0x0028
  float N000000E9;             // 0x0050
  float N00000056;             // 0x0054
  float N000000EB;             // 0x0058
  char pad_005C[4];            // 0x005C
  float N000000ED;             // 0x0060
  float N00000058;             // 0x0064
  float N000000EF;             // 0x0068
  char pad_006C[132];          // 0x006C
  Vector3 N00000111;           // 0x00F0
  char pad_00FC[4];            // 0x00FC
  Vector3 N00000113;           // 0x0100
  char pad_010C[4];            // 0x010C
  Vector3 N00000115;           // 0x0110
  char pad_011C[4];            // 0x011C
  Vector3 Position;            // 0x0120
  char pad_012C[864];          // 0x012C
};                             // Size: 0x048C

class World {
public:
  char pad_0000[248];    // 0x0000
  int32_t UnknownCheck1; // 0x00F8
  int32_t UnknownCheck2; // 0x00FC
  char pad_0100[1032];   // 0x0100
};                       // Size: 0x0508

class Cache {
public:
  char pad_0000[264]; // 0x0000
};                    // Size: 0x0108

class ListShape {
public:
  char pad_0000[264]; // 0x0000
};                    // Size: 0x0108

class UpdateEntityPositionArg {
public:
  Vector3 N00000349; // 0x0000
  char pad_000C[4];  // 0x000C
  Vector3 N00000379; // 0x0010
  char pad_001C[4];  // 0x001C
  Vector3 N00000373; // 0x0020
  char pad_002C[4];  // 0x002C
  Vector3 Position;  // 0x0030
  char pad_003C[76]; // 0x003C
};                   // Size: 0x0088

class Character // Pointer is LocalCharacter
{
public:
  char pad_0000[64];                                     // 0x0000
  class CharacterInfo *pCharacterInfo;                   // 0x0040
  char pad_0048[12];                                     // 0x0048
  Vector3 Position;                                      // 0x0054
  class TESObjectCELL *pTESObjectCELL;                   // 0x0060
  class UnknownClass *UnknownPtr;                        // 0x0068
  char pad_0070[8];                                      // 0x0070
  class ExtraReservedMarkers *pExtraReservedMarkers;     // 0x0078
  char pad_0080[120];                                    // 0x0080
  class CharacterStatsBaseBase *pCharacterStatsBaseBase; // 0x00F8
  char pad_0100[32];                                     // 0x0100
  int64_t UnknownInt;                                    // 0x0120
  char pad_0128[40];                                     // 0x0128
  class MovementControllerNPC *pMovementControllerNPC;   // 0x0150
  char pad_0158[1008];                                   // 0x0158
};                                                       // Size: 0x0548

class UnknownClass {
public:
  char pad_0000[264]; // 0x0000
};                    // Size: 0x0108

class CharacterInfo {
public:
  char pad_0000[88];                         // 0x0000
  class Voice *pVoice;                       // 0x0058
  char pad_0060[128];                        // 0x0060
  char (*pName)[32];                         // 0x00E0
  char pad_00E8[72];                         // 0x00E8
  class BGSAttackDataMap *pBGSAttackDataMap; // 0x0130
  char pad_0138[32];                         // 0x0138
  class TESRace *pTESRace;                   // 0x0158
};                                           // Size: 0x0160

class Voice {
public:
  char pad_0000[56]; // 0x0000
};                   // Size: 0x0038

class CurrentCharacterStats {
public:
  char pad_0000[24];    // 0x0000
  float CurrentHealth;  // 0x0018
  char pad_001C[4];     // 0x001C
  float CurrentMagicka; // 0x0020
  char pad_0024[4];     // 0x0024
  float CurrentStamina; // 0x0028
  char pad_002C[4];     // 0x002C
};                      // Size: 0x0030

class CharacterStatsBase {
public:
  char pad_0000[48];                                   // 0x0000
  class CurrentCharacterStats *pCurrentCharacterStats; // 0x0030
  char pad_0038[16];                                   // 0x0038
  class MaxCharacterStats *pMaxCharacterStats;         // 0x0048
  char pad_0050[48];                                   // 0x0050
};                                                     // Size: 0x0080

class CharacterStatsBaseBase {
public:
  char pad_0000[80];                             // 0x0000
  class CharacterStatsBase *pCharacterStatsBase; // 0x0050
  char pad_0058[232];                            // 0x0058
};                                               // Size: 0x0140

class MaxCharacterStats {
public:
  float MaxHealth;  // 0x0000
  char pad_0004[4]; // 0x0004
  float MaxMagicka; // 0x0008
  char pad_000C[4]; // 0x000C
  float MaxStamina; // 0x0010
  char pad_0014[4]; // 0x0014
};                  // Size: 0x0018

class BGSAttackDataMap {
public:
  char pad_0000[144]; // 0x0000
};                    // Size: 0x0090

class TESRace {
public:
  char pad_0000[192]; // 0x0000
};                    // Size: 0x00C0

class TESObjectCELL {
public:
  char pad_0000[40];     // 0x0000
  char (*pCellName)[32]; // 0x0028
  char pad_0030[280];    // 0x0030
};                       // Size: 0x0148

class MovementControllerNPC {
public:
  char pad_0000[464]; // 0x0000
};                    // Size: 0x01D0

class ExtraReservedMarkers {
public:
  char pad_0000[48]; // 0x0000
};                   // Size: 0x0030

class MouseHandlerArg {
public:
  char pad_0000[112];                          // 0x0000
  int8_t UnknownByte;                          // 0x0070
  char pad_0071[7];                            // 0x0071
  class IWrapMouseDevice8 *pIWrapMouseDevice8; // 0x0078
  int64_t N00000490;                           // 0x0080
  int64_t N00000491;                           // 0x0088
  int64_t N00000492;                           // 0x0090
  int64_t N00000493;                           // 0x0098
  int64_t N00000494;                           // 0x00A0
  char pad_00A8[216];                          // 0x00A8
};                                             // Size: 0x0180

class IWrapMouseDevice8 {
public:
  class IWrapMouseDevice8_vTable *pvTable; // 0x0000
  char pad_0008[576];                      // 0x0008
};                                         // Size: 0x0248

class MouseHandleToggle {
public:
  int8_t MouseHandleToggle; // 0x0000 0 handle full, set handle rotation but not
                            // cursor
  char pad_0001[63]; // 0x0001
};                   // Size: 0x0040

class IWrapMouseDevice8_vTable {
public:
  char pad_0000[88]; // 0x0000
  void *Call_2;      // 0x0058
  char pad_0060[8];  // 0x0060
  void *Call_1;      // 0x0068
  char pad_0070[24]; // 0x0070
};                   // Size: 0x0088