#include "pch.h"
#include "cargrp.h"
#include <CStreaming.h>
#include <CGeneral.h>
#include <CPopulation.h>
#include <windows.h>

CCargrpLoader CargrpLoader;

void CCargrpLoader::Parse(const std::string &line)
{
    if (line.starts_with("CARGRP_"))
    {
        store.push_back(line);
    }
}

int GetCarGroupIndex(const std::string &groupName)
{
    static const std::unordered_map<std::string, int> carGroupMap = {
        {"CARGRP_WORKERS", 0},
        {"CARGRP_BUSINESS", 1},
        {"CARGRP_CLUBBERS", 2},
        {"CARGRP_FARMERS", 3},
        {"CARGRP_BEACHFOLK", 4},
        {"CARGRP_PARKFOLK", 5},
        {"CARGRP_CASUAL_RICH", 6},
        {"CARGRP_CASUAL_AVERAGE", 7},
        {"CARGRP_CASUAL_POOR", 8},
        {"CARGRP_PROSTITUTES", 9},
        {"CARGRP_CRIMINALS", 10},
        {"CARGRP_GOLFERS", 11},
        {"CARGRP_SERVANTS", 12},
        {"CARGRP_AIRCREW", 13},
        {"CARGRP_ENTERTAINERS", 14},
        {"CARGRP_OUT_OF_TOWN_FACTORY", 15},
        {"CARGRP_DESERT_FOLK", 16},
        {"CARGRP_AIRCREW_RUNWAY", 17},
        {"CARGRP_GANG1", 18},
        {"CARGRP_GANG2", 19},
        {"CARGRP_GANG3", 20},
        {"CARGRP_GANG4", 21},
        {"CARGRP_GANG5", 22},
        {"CARGRP_GANG6", 23},
        {"CARGRP_GANG7", 24},
        {"CARGRP_GANG8", 25},
        {"CARGRP_GANG9", 26},
        {"CARGRP_GANG10", 27},
        {"CARGRP_DEALERS", 28},
        {"CARGRP_BOATS", 29},
        {"CARGRP_CHEAT1", 30},
        {"CARGRP_CHEAT2", 31},
        {"CARGRP_CHEAT3", 32},
        {"CARGRP_CHEAT4", 33}};

    auto it = carGroupMap.find(groupName);
    if (it != carGroupMap.end())
    {
        return it->second;
    }

    return -1; // Not found
}

short *GetCountInGroup(int groupID) {
    short *&m_nNumCarsInGroup = *(short**)0x421915;
    return &m_nNumCarsInGroup[groupID];
}

static int carsPerGroup = 23;
short *GetModel(int groupID, int idx) {
    if (GetModuleHandle("$fastman92limitAdjuster.asi")) {
        carsPerGroup = GetPrivateProfileIntA("CAR STREAMING", "Cargrp cars per group", 23, GAME_PATH((char*)"fastman92limitAdjuster_GTASA.ini"));
    }
    short** m_CarGroups = *(short***)0x421948;
    return (short*)((int)m_CarGroups + 2 * carsPerGroup * groupID + 2 * idx);
 }

// 0x421900
int CCarCtrl_ChooseCarModelToLoad(int groupID)
{
    int numCarsInGroup = *GetCountInGroup(groupID);
    if (!numCarsInGroup)
    {
        return -1;
    }
    const auto model = *GetModel(groupID, CGeneral::GetRandomNumberInRange(0, numCarsInGroup));
    if (CStreaming::ms_aInfoForModel[model].m_nLoadState != 1)
    {
        CStreaming::RequestModel(model, eStreamingFlags::PRIORITY_REQUEST);
        CStreaming::LoadAllRequestedModels(true);
    }

    if (CStreaming::ms_aInfoForModel[model].m_nLoadState)
    {
        return model;
    }
    else
    {
        return -1;
    }
}

// 0x614490
signed int __cdecl CPopulation_PickGangCar(int gangID)
{
    gangID = 0;
    int groupID = gangID + 18; // CARGRP_BALLAS
    const auto numCarsInGroup = *GetCountInGroup(groupID);
    if (!numCarsInGroup)
    {
        return -1;
    }

    const auto model = *GetModel(groupID, CGeneral::GetRandomNumberInRange(0, numCarsInGroup));
    if (CStreaming::ms_aInfoForModel[model].m_nLoadState != 1)
    {

        CStreaming::RequestModel(model, eStreamingFlags::KEEP_IN_MEMORY);
        CStreaming::LoadAllRequestedModels(false);
        plugin::Call<0x408000, int>(model); // CStreaming::AddToLoadedVehiclesList()
    }

    return model;
}

CCargrpLoader::CCargrpLoader()
{
    plugin::patch::ReplaceFunction(0x421900, CCarCtrl_ChooseCarModelToLoad);
    plugin::patch::ReplaceFunction(0x614490, CPopulation_PickGangCar);

    static plugin::CdeclEvent<plugin::AddressList<0X610EB0, plugin::H_JUMP>,
                              plugin::PRIORITY_AFTER, plugin::ArgPickNone, void()>
        loadCarGroups;

    loadCarGroups.after += [this]()
    {
        for (auto &line : store)
        {
            std::stringstream ss(line);
            std::string grpName;
            std::getline(ss, grpName, ',');
            int idx = GetCarGroupIndex(grpName);
            int idxinGroup = *GetCountInGroup(idx);

            std::string str;
            while (std::getline(ss, str, ','))
            {
                str.erase(std::remove_if(str.begin(), str.end(), ::isspace),
                          str.end());
                int model = NULL;
                CModelInfo::GetModelInfo((char *)str.c_str(), &model);
                if (model != NULL)
                {
                    *GetModel(idx, idxinGroup++) = model;
                    *GetCountInGroup(idx) = *GetCountInGroup(idx) + 1;
                }

                if (idxinGroup >= carsPerGroup)
                {
                    MessageBox(NULL, std::format("Limit exceeded for {}", grpName).c_str(), MODNAME, MB_OK);
                    break;
                }
            }
        }
    };
}