#include "pch.h"
#include "audio.h"
#include "tVehicleAudioSetting.h"

CFLAAudioLoader FLAAudioLoader;
void CFLAAudioLoader::UpdateAudioFile()
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

void CFLAAudioLoader::Parse(const std::string &line)
{
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
        store.push_back(line);
    }
}