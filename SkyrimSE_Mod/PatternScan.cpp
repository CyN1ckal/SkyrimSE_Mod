#pragma once
#include "PatternScan.h"

bool PatternScan::Internal::GetModuleEntryFromName(const char *Name,
                                         MODULEENTRY32 *me32Return) {
  HANDLE hSnap =
      CreateToolhelp32Snapshot(TH32CS_SNAPALL, GetCurrentProcessId());

  if (hSnap == INVALID_HANDLE_VALUE) {
    printf("Invalid Handle Value.\n");
    return 0;
  }

  bool ModuleFound = false;

  MODULEENTRY32 me32;
  me32.dwSize = sizeof(MODULEENTRY32);
  if (!Module32First(hSnap, &me32)) {
    printf("Module32First failed!\n");
    return 0;
  }

  do {
    if (!strcmp(me32.szModule, Name)) {
      ModuleFound = true;
      break;
    }
  } while (Module32Next(hSnap, &me32));

  CloseHandle(hSnap);

  if (!ModuleFound)
    return 0;

  *me32Return = me32;

  return 1;
}

uintptr_t
PatternScan::Internal::PatternScanModule_ComboPattern(const char *ProcName,
                                      const char *SignatureString,
                                      const int SignatureLengthBytes) {
  // Get process entry info
  MODULEENTRY32 me32;
  me32.dwSize = sizeof(MODULEENTRY32);

  if (!GetModuleEntryFromName(ProcName, &me32)) {
    printf("GetModuleEntryFromName failed!\n");
    return 0;
  }

  // Separate the combo input into a mask
  char *Mask = new char[SignatureLengthBytes];

  for (int i = 0; i < SignatureLengthBytes; i++) {
    if (*(SignatureString + i) == 0x3f) {
      Mask[i] = 0x3f;
    } else {
      Mask[i] = 0x78;
    }
  }

  // Separate the combo input to the signature to search for
  BYTE *Signature = new BYTE[SignatureLengthBytes]{0x0};
  for (int i = 0; i < SignatureLengthBytes; i++) {
    if (Mask[i] == 0x78) {
      Signature[i] = *(BYTE *)(SignatureString + i);
    }
  }

  // Scan given range of memory for signature
  BYTE *CurrentByte = me32.modBaseAddr;
  bool SignatureFound = false;

  for (int i = 0; i < (me32.modBaseSize - SignatureLengthBytes); i++) {

    for (int x = 0; x < SignatureLengthBytes; x++) {

      if (*(CurrentByte + x) != Signature[x] && Mask[x] == 0x78) {
        break;
      }

      if (x == SignatureLengthBytes - 1) {
        SignatureFound = true;
        break;
      }
    }

    if (SignatureFound)
      break;

    CurrentByte++;
  }

  delete[] Mask;
  delete[] Signature;

  if (!SignatureFound) {
    printf("Signature Not Found!\n");
    return 0;
  }

  return (uintptr_t)CurrentByte;
}