#pragma once
#include <vector>

class CFLAAudioLoader
{
private:
    std::vector<std::string> store;
    void UpdateAudioFile();

public:
    void Parse(const std::string &line);
    void Process();
};

extern CFLAAudioLoader FLAAudioLoader;