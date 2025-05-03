#include "pch.h"
#include <filesystem>
#include <fstream>
#include <plugin.h>
#include "tVehicleAudioSetting.h"
#include "parser.h"

void ParseModloaderDir(std::vector<std::string> &store)
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
        std::string parentPath = e.path().parent_path().string();

        // Ignore folders with '.' int their names .data / .profile etc
        if (parentPath.find('.') != std::string::npos)
        {
            continue;
        }

        // This could be any file but limiting it to txd and dat
        if (ext == ".txt")
        {
            std::ifstream in(path);
            std::string line;
            while (getline(in, line))
            {
                // Skip comments
                if (line.starts_with(";") || line.starts_with("//"))
                {
                    continue;
                }

                tVehicleAudioSetting setting;
                int count = sscanf(line.c_str(),
                                   "%255s %d %d %d %d %f %f %d %f %d %d %d %d %d %f",
                                   setting.Name,
                                   &setting.VehAudType,
                                   &setting.PlayerBank,
                                   &setting.DummyBank,
                                   &setting.BassSetting,
                                   &setting.BassFactor,
                                   &setting.EnginePitch,
                                   &setting.HornType,
                                   &setting.HornPitch,
                                   &setting.DoorType,
                                   &setting.EngineUpgrade,
                                   &setting.RadioStation,
                                   &setting.RadioType,
                                   &setting.VehicleAudioTypeForName,
                                   &setting.EngineVolumeOffset);

                // Check valid or not
                if (count == 15)
                {
                    store.push_back(std::move(line));
                }
            }
            in.close();
        }
    }
}

void UpdateFLAAudioFile(std::vector<std::string> &store)
{
    std::string settingsPath = GAME_PATH((char *)"data/gtasa_vehicleAudioSettings.cfg");
    std::string settingsPathTemp = settingsPath + ".bak";
    if (std::filesystem::exists(GAME_PATH((char *)"data/gtasa_vehicleAudioSettings.cfg")))
    {
        std::ifstream in(settingsPath);
        std::ofstream out(settingsPathTemp);

        if (in.is_open() && out.is_open())
        {
            std::string line;
            bool ignoreLines = false;
            while (getline(in, line))
            {
                ignoreLines = ignoreLines || line.find("added vehicles") != std::string::npos;
                if (line.find("the end") != std::string::npos)
                {
                    break;
                }

                if (!ignoreLines || line.starts_with(";"))
                {
                    out << line << "\n";
                }
            }

            for (auto &e : store)
            {
                out << e << "\n";
            }
            out << ";the end\n";

            if (in.is_open())
            {
                in.close();
            }

            if (out.is_open())
            {
                out.close();
            }

            std::filesystem::remove(settingsPath);
            std::filesystem::rename(settingsPathTemp, settingsPath);
        }

        if (in.is_open())
        {
            in.close();
        }

        if (out.is_open())
        {
            out.close();
        }
    }
}