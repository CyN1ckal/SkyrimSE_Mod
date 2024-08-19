#include "pch.h"

#define DIRECTINPUT_VERSION 0x0800

bool DirectInputHook::Initialize() {
  HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);

  IDirectInput8 *pDirectInput = NULL;

  if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
                         (LPVOID *)&pDirectInput, NULL) != DI_OK)
    return -1;

  LPDIRECTINPUTDEVICE8 lpdiKeyboard;
  if (pDirectInput->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL) !=
      DI_OK) {
    pDirectInput->Release();
    return -1;
  }

  GetDeviceStateFunctionAddress =
      *(uintptr_t *)(*(uintptr_t *)lpdiKeyboard + (9 * sizeof(uintptr_t)));

  GetDeviceDataFunctionAddress =
      *(uintptr_t *)(*(uintptr_t *)lpdiKeyboard + (10 * sizeof(uintptr_t)));


  return 1;
}

GetDeviceData_Template GetDeviceData_Original = nullptr;
HRESULT WINAPI DirectInputHook::GetDeviceData_Hooked(
    IDirectInputDevice8 *Device, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod,
    LPDWORD pdwInOut, DWORD dwFlags) {

  HRESULT ret =
      GetDeviceData_Original(Device, cbObjectData, rgdod, pdwInOut, dwFlags);

  if (ret == DI_OK) {
    // printf("Length of Queue: %d\n", *pdwInOut);

    for (int i = 0; i < *pdwInOut; i++) {
      if (LOBYTE(rgdod[i].dwData) > 0) {
        printf("%X ", rgdod[i].dwOfs);
      }
    }
  }

  if (BlockKeyboard) {
    *pdwInOut = 0;
    return DI_OK;
  }

  return ret;
}

bool DirectInputHook::EnableHooks() {

  if (MH_CreateHook((void *)GetDeviceDataFunctionAddress, &GetDeviceData_Hooked,
                    reinterpret_cast<LPVOID *>(&GetDeviceData_Original)) !=
      MH_OK) {
    printf("GetDeviceDataFunctionAddress MH_CreateHook failed!\n");
    return 0;
  }
  if (MH_EnableHook((void *)GetDeviceDataFunctionAddress) != MH_OK) {
    printf("GetDeviceDataFunctionAddress MH_EnableHook failed!\n");
    return 0;
  }

  return 1;
}