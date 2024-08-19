#pragma once

uintptr_t MultiLevelPointerDeref(uintptr_t BaseAddress,
                                 std::vector<uintptr_t> Offsets);