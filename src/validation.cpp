#include "pch.h"

bool IsPluginNameValid(HINSTANCE handle)
{
    char buf[MAX_PATH];
    DWORD result = GetModuleFileName(handle, buf, MAX_PATH);
    if (!result)
    {
        MessageBox(NULL, "Failed to fetch filename", MODNAME, MB_OK);
        return false;
    }

    std::string curName = buf;
    size_t lastSlash = curName.find_last_of("\\/");
    if (lastSlash != std::string::npos)
    {
        curName = curName.substr(lastSlash + 1);
    }

    if (curName != MODNAME_EXT)
    {
        MessageBox(NULL, "The plugin was renamed. Exiting...!", MODNAME, MB_OK);
        return false;
    }

    return true;
}