#include "pch.h"
#include "loader/loader_core.h"

BOOL WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
{
    if (nReason == DLL_PROCESS_ATTACH)
    {
        LearLoader loader(hDllHandle);
    }
    return TRUE;
}