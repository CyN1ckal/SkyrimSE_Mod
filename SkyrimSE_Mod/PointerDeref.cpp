#include "pch.h"

uintptr_t MultiLevelPointerDeref(uintptr_t BaseAddress,
                                 std::vector<uintptr_t> Offsets) {
  uintptr_t CurrentValue = BaseAddress;

  for (int i = 0; i < Offsets.size(); i++) {
    CurrentValue = *(uintptr_t *)(CurrentValue + Offsets[i]);
  }

  return CurrentValue;
}