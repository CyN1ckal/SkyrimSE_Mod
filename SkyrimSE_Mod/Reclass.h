#pragma once
// Created with ReClass.NET 1.2 by KN4CK3R

class Entity {
public:
  char pad_0008[8];            // 0x0008
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

  virtual void Function0();
  virtual void Function1();
  virtual void Function2();
  virtual void Function3();
  virtual void Function4();
  virtual void Function5();
  virtual void Function6();
  virtual void Function7();
  virtual void Function8();
  virtual void Function9();
  virtual void Function10();
  virtual void Function11();
  virtual void Function12();
  virtual void Function13();
  virtual void Function14();
  virtual void Function15();
  virtual void Function16();
  virtual void Function17();
  virtual void Function18();
}; // Size: 0x048C

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

class Character {
public:
  char pad_0000[64];                // 0x0000
  class UnknownClass1 *UnknownPtr1; // 0x0040
  char pad_0048[12];                // 0x0048
  Vector3 Position;                 // 0x0054
  char pad_0060[8];                 // 0x0060
  class UnknownClass *UnknownPtr;   // 0x0068
  char pad_0070[1240];              // 0x0070
};                                  // Size: 0x0548

class PotentialEntityList {
public:
  char pad_0000[10304]; // 0x0000
};                      // Size: 0x2840

class UnknownClass {
public:
  char pad_0000[264]; // 0x0000
};                    // Size: 0x0108

class UnknownClass1 {
public:
  char pad_0000[88];   // 0x0000
  class Voice *pVoice; // 0x0058
  char pad_0060[128];  // 0x0060
  char (*pName)[16];   // 0x00E0
  char pad_00E8[800];  // 0x00E8
};                     // Size: 0x0408

class Voice {
public:
  char pad_0000[56]; // 0x0000
};                   // Size: 0x0038