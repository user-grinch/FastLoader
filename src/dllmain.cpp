#include "pch.h"

extern bool IsPluginNameValid(HINSTANCE handle);
extern void ParseModloaderDir(std::vector<std::string> &store);
extern void UpdateFLAAudioFile(std::vector<std::string> &store);
extern void ShowPopupWindow();

void ModProcess(HINSTANCE handle)
{
    if (!IsPluginNameValid(handle))
    {
        return;
    }

    // Ini checks
    if (!gConfig.ReadBoolean("MISC", "PopupShown", false))
    {
        ShowPopupWindow();

        // Comment this out if you want popup to always show
        gConfig.WriteBoolean("MISC", "PopupShown", true);
    }

    // Check if credits are given
    // std::string authorStr = gConfig.ReadString("MAIN", "Author", "");
    // if (authorStr != "Damix")
    // {
    //     return;
    // }

    std::vector<std::string> store;
    ParseModloaderDir(store);
    UpdateFLAAudioFile(store);
}

BOOL WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
{
    if (nReason == DLL_PROCESS_ATTACH)
    {
        ModProcess(hDllHandle);
    }
    return TRUE;
}