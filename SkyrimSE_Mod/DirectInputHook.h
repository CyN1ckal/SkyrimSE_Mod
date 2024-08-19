#pragma once

typedef HRESULT(WINAPI *GetDeviceData_Template)(IDirectInputDevice8 *Device,
                                                DWORD cbObjectData,
                                                LPDIDEVICEOBJECTDATA rgdod,
                                                LPDWORD pdwInOut,
                                                DWORD dwFlags);

class DirectInputHook {
public:
  static bool Initialize();
  static bool EnableHooks();

  static inline uintptr_t GetDeviceDataFunctionAddress;
  static HRESULT WINAPI GetDeviceData_Hooked(IDirectInputDevice8 *Device,
                                             DWORD cbObjectData,
                                             LPDIDEVICEOBJECTDATA rgdod,
                                             LPDWORD pdwInOut, DWORD dwFlags);

private:
};