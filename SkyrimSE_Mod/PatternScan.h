#pragma once
#include "pch.h"

#include <TlHelp32.h>



namespace PatternScan {

namespace Internal {

bool GetModuleEntryFromName(const char *Name, MODULEENTRY32 *me32Return);

uintptr_t PatternScanModule_ComboPattern(const char *ProcName,
                                         const char *SignatureString,
                                         const int SignatureLengthBytes);
} // namespace Internal

} // namespace PatternScan