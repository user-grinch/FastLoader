#pragma once
#include <queue>
#include <string>

class CObjDatLoader
{
private:
    static inline std::queue<std::string> store;
    static inline char *__cdecl hkLoadLine(FILE *file);

public:
    CObjDatLoader();
    void Parse(const std::string &line) {};
    void Process() {};
};

extern CObjDatLoader ObjDatLoader;