#pragma once
#include <wtypes.h>

class FastLoader
{
private:
    HINSTANCE handle;

    bool IsPluginNameValid();
    void ParseModloader();

public:
    FastLoader(HINSTANCE pluginHandle);
};