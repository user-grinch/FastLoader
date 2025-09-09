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
    std::function<void(const std::filesystem::path&)> traverse;
    traverse = [&](const std::filesystem::path& dir) {
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            if (entry.is_directory())
            {
                std::string folderName = entry.path().filename().string();
                if (!folderName.empty() && folderName[0] == '.')
                {
                    continue; 
                }

                traverse(entry.path()); 
                continue;
            }

            if (!entry.is_regular_file())
            {
                continue;
            }

            std::string ext = entry.path().extension().string();
            std::string path = entry.path().string();
            std::string fileName = entry.path().filename().string();
            std::string parentPath = entry.path().parent_path().string();

            if (fileName == "object.dat" || fileName == "cargrp.dat") {
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

            if (ext == ".fastloader")
            {
                std::ifstream in(path);
                std::string line;
                while (getline(in, line))
                {
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
    };

    traverse(GAME_PATH((char *)"modloader"));
}