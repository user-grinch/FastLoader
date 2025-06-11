#pragma once
#include <vector>
#include <string>

class CCargrpLoader
{
private:
    std::vector<std::string> store;

public:
    CCargrpLoader();
    void Parse(const std::string &line);
    void Process() {};
};

extern CCargrpLoader CargrpLoader;