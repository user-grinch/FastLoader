#include "pch.h"
#include "objdat.h"
#include <CStreaming.h>
#include <CGeneral.h>
#include <algorithm>
#include <CFileLoader.h> 

CObjDatLoader ObjDatLoader;

#define END_ID "*"

char* __cdecl CObjDatLoader::hkLoadLine(FILE* file) {
    static bool eof = false;
    static bool permaClose = false; // Prevent any other mod from making changes
    static std::string line;

    if (permaClose) {
        line = END_ID;
    } else {
        if (!eof) {
            line = CFileLoader::LoadLine(reinterpret_cast<int>(file));
            if (line.starts_with(END_ID)) {
                eof = true;
            } else {
                return const_cast<char*>(line.c_str());
            }
        }

        if (!store.empty()) {
            line = store.front();
            store.pop();
        } else {
            line = END_ID;
            permaClose = true;
        }
    }

    return const_cast<char*>(line.c_str());
}


CObjDatLoader::CObjDatLoader()
{
    plugin::patch::ReplaceFunctionCall(0x5B5798, CObjDatLoader::hkLoadLine);
}