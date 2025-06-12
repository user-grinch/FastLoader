#include "pch.h"
#include "objdat.h"
#include <CStreaming.h>
#include <CGeneral.h>
#include <algorithm>
#include <CFileLoader.h> 
#include <CObjectData.h>

CObjDatLoader ObjDatLoader;

#define END_ID "*"

char* __cdecl CObjDatLoader::hkLoadLine(FILE* file) {
    static bool eof = false;
    static std::string line;
    
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
    }

    return const_cast<char*>(line.c_str());
}

void CObjDatLoader::Parse(const std::string &line) {

    std::string s = line;
    std::replace(s.begin(), s.end(), ',', ' ');
    CObjectInfo curInfo;
    char modelName[256], effectName[256];
    float fPercentSubmerged;
    int32_t iColDamEffect, iSpecialColResp, iCameraAvoid, iCausesExplosion, iFxType; // Have to be read as 32-bit integers and later assigned to 8 bit int32
    if (sscanf_s(s.c_str(), "%s %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %s %f %f %f %f %f %d %d", // FIX_BUGS: Sized string read
        modelName, sizeof(modelName),
        &curInfo.m_fMass,
        &curInfo.m_fTurnMass,
        &curInfo.m_fAirResistance,
        &curInfo.m_fElasticity,
        &fPercentSubmerged,
        &curInfo.m_fUprootLimit,
        &curInfo.m_fColDamageMultiplier,
        &iColDamEffect,
        &iSpecialColResp,
        &iCameraAvoid,
        &iCausesExplosion,
        &iFxType,
        &curInfo.m_vFxOffset.x,        
        &curInfo.m_vFxOffset.y,        
        &curInfo.m_vFxOffset.z,        
        effectName, sizeof(effectName),
        &curInfo.m_fSmashMultiplier,   
        &curInfo.m_vecBreakVelocity.x, 
        &curInfo.m_vecBreakVelocity.y, 
        &curInfo.m_vecBreakVelocity.z, 
        &curInfo.m_fBreakVelocityRand, 
        &curInfo.m_nGunBreakMode,      
        &curInfo.m_nSparksOnImpact     
    ) >= 13) {
        store.push(std::move(s));
    }
}

CObjDatLoader::CObjDatLoader()
{
    plugin::patch::ReplaceFunctionCall(0x5B5798, CObjDatLoader::hkLoadLine);
}