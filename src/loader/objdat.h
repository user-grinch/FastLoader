#pragma once
#include <queue>
#include <string>

class CObjDatLoader
{
private:
    static inline std::queue<std::string> store;
    static char *__cdecl hkLoadLine(FILE *file);
    static int __cdecl hkSetDir(LPCSTR lpPathName);

public:
    CObjDatLoader();
    void Parse(const std::string &line);
    void Process() {};
};

extern CObjDatLoader ObjDatLoader;