#pragma once
/*
    FLA File Structure
    gtasa_vehicleAudioSettings
*/
struct tVehicleAudioSetting
{
    char Name[256];
    int VehAudType;
    int PlayerBank;
    int DummyBank;
    int BassSetting;
    float BassFactor;
    float EnginePitch;
    int HornType;
    float HornPitch;
    int DoorType;
    int EngineUpgrade;
    int RadioStation;
    int RadioType;
    int VehicleAudioTypeForName;
    float EngineVolumeOffset;
};