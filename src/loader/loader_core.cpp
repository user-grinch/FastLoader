#include "pch.h"
#include "loader_core.h"
#include "audio.h"
#include "cargrp.h"
#include "objdat.h"

FastLoader::FastLoader(HINSTANCE pluginHandle)
{
    handle = pluginHandle;
    if (!IsPluginNameValid())
    {
        return;
    }

    ParseModloader();
    FLAAudioLoader.Process();
}

bool FastLoader::IsPluginNameValid()
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

void FastLoader::ParseModloader()
{
    for (auto &e : std::filesystem::recursive_directory_iterator(GAME_PATH((char *)"modloader")))
    {
        // Skipping directories or links here
        if (!e.is_regular_file() || e.is_directory())
        {
            continue;
        }

        std::string ext = e.path().extension().string();
        std::string path = e.path().string();
        std::string fileName = e.path().filename().string();
        std::string parentPath = e.path().parent_path().string();

        // Ignore folders with '.' int their names .data / .profile etc
        if (parentPath.find('.') != std::string::npos)
        {
            continue;
        }

        if (fileName == "object.dat" || fileName == "cargrp.dat") {
            // Intentionally static, ask only once
            static int result = MessageBox(NULL, "Found object.dat or cargrp.dat in your modloader folder. Do you want to rename?", MODNAME, MB_YESNO | MB_ICONQUESTION);
            if (result == IDYES) {
                std::string newName = fileName + ".bak";
                std::string newPath = parentPath + "\\" + newName;
                try {
                    std::filesystem::rename(path, newPath);
                }
                catch (const std::exception& e) {
                    MessageBox(NULL, ("Failed to rename: " + std::string(e.what())).c_str(), MODNAME, MB_OK | MB_ICONERROR);
                }
            }
        }

        // This could be any file but limiting it to txd and dat
        if (ext == ".txt" || ext == ".dat")
        {
            std::ifstream in(path);
            std::string line;
            while (getline(in, line))
            {
                // Skip comments
                if (line.starts_with(";") || line.starts_with("//") || line.starts_with("#"))
                {
                    continue;
                }

                CargrpLoader.Parse(line);
                ObjDatLoader.Parse(line);
                FLAAudioLoader.Parse(line);
            }
            in.close();
        }
    }
}