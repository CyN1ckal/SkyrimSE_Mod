// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for
// future builds. This also affects IntelliSense performance, including code
// completion and many code browsing features. However, files listed here are
// ALL re-compiled if any one of them is updated between builds. Do not add
// files here that you will be updating frequently as this negates the
// performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <windows.h>

#include <iostream>

#include <vector>

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include <dinput.h>

#include "ImGui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "PatternScan.h"
#include "Vector.h"

#include "MinHook.h"

#include "Offsets.h"
#include "Reclass.h"
#include "Signatures.h"

#include "Globals.h"

#include "PointerDeref.h"

#include "Console.h"

#include "CheatBase.h"

#include "DirectXHook.h"

#include "MyImGui.h"

#endif // PCH_H
