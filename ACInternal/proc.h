#pragma once


#include <vector>
#include <windows.h>
#include <Tlhelp32.h>

DWORD GetProcId(const TCHAR* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const TCHAR* modName);

