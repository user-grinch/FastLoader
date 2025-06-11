#pragma once
#include <wtypes.h>

class LearLoader
{
private:
    HINSTANCE handle;

    bool IsPluginNameValid();
    void ParseModloader();

public:
    LearLoader(HINSTANCE pluginHandle);
};