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

  GetDeviceDataFunctionAddress =
      *(uintptr_t *)(*(uintptr_t *)lpdiKeyboard + (10 * sizeof(uintptr_t)));
  printf("IDirectInputDevice8_GetDeviceData: %llx\n",
         GetDeviceDataFunctionAddress);

  return 1;
}