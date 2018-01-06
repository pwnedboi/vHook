//
//  Config.cpp
//  vHook
//
//  Created by Finn Le var on 6/05/17.
//  Copyright © 2017 ViKiNG. All rights reserved.
//

#include "../main.h"
#include "Config.h"
#include "skins.h"
#include <sys/stat.h>

using namespace std;

Config* config = new Config();
Config* skins_cfg = new Config();
Skins skin;

const char* ConfigName;
string user = getenv("USER");
string legit = "/Users/"+user+"/vlone/configs/Legit.cfg";
string rage = "/Users/"+user+"/vlone/configs/Rage.cfg";
string stop = "/Users/"+user+"/vlone/configs/Panic.cfg";
string skins_file = "/Users/"+user+"/vlone/configs/Skins.cfg";

bool DoesDirectoryExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISDIR(info.st_mode);
}

bool GetBoolValue(bool Value)
{
    return Value;
}

int GetIntValue(bool Value)
{
    return Value;
}

float GetFloatValue(float Value)
{
    return Value;
}

void Config::getConfig(int ConfigNo) {
    if(ConfigNo == 0) ConfigName = legit.c_str();
    if(ConfigNo == 1) ConfigName = rage.c_str();
    if(ConfigNo == 2) ConfigName = stop.c_str();
}

bool fileExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

void Config::CreateConfigDirectories() {
    std::string usr = getenv("USER");
    std::string vln = "/Users/" + usr + "/vlone/";
    std::string cfg = "/Users/" + usr + "/vlone/configs/";
    
    if(!DoesDirectoryExist(vln.c_str()))
        mkdir(vln.c_str(), 0777);
    
    if(!DoesDirectoryExist(cfg.c_str()))
        mkdir(cfg.c_str(), 0777);
}

void Config::LoadConfig() {
    
    cfg.SetUnicode(true);
    this->CreateConfigDirectories();
    if(!fileExist(legit.c_str()))
        SaveConfig();
    cfg.LoadFile(ConfigName);
    
    // Aimbot
    vars.aimbot.enabled     = cfgget_b("Aimbot", "Enabled");
    vars.aimbot.smooth      = cfgget_b("Aimbot", "Smoothing");
    vars.aimbot.smoothf     = cfgget_f("Aimbot", "Smoothf");
    vars.aimbot.rcs         = cfgget_b("Aimbot", "RCS");
    vars.aimbot.rcsf        = cfgget_f("Aimbot", "RCSf");
    vars.aimbot.trigger     = cfgget_b("Aimbot", "Trigger");
    vars.aimbot.fov         = cfgget_f("Aimbot", "FOV");
    vars.aimbot.hitbox      = cfgget_f("Aimbot", "Hitbox");
    
    vars.aimbot.silent      = cfgget_b("Aimbot", "Silent");
    vars.aimbot.prediciton  = cfgget_b("Aimbot", "Prediction");
    
    vars.aimbot.autowall    = cfgget_b("Aimbot", "Autowall");
    vars.aimbot.pointscale  = cfgget_f("Aimbot", "Pointscale");
    vars.aimbot.autostop    = cfgget_b("Aimbot", "Autostop");
    vars.aimbot.autoshoot   = cfgget_b("Aimbot", "Autoshoot");
    vars.aimbot.autocrouch  = cfgget_b("Aimbot", "Autocrouch");
    vars.aimbot.autopistol  = cfgget_b("Aimbot", "Autopistol");
    
    //vars.aimbot.triggerKey  = (ButtonCode_t)cfgget_f("Aimbot", "Trigger Key");
    
    // Visuals
    vars.visuals.enabled    = cfgget_b("Visuals", "Enabled");
    vars.visuals.box        = cfgget_b("Visuals", "Box");
    vars.visuals.box3d      = cfgget_b("Visuals", "3D Box");
    vars.visuals.name       = cfgget_b("Visuals", "Name");
    vars.visuals.health     = cfgget_b("Visuals", "Health");
    vars.visuals.healthtext = cfgget_b("Visuals", "Health text");
    vars.visuals.active     = cfgget_b("Visuals", "Active");
    vars.visuals.snapline   = cfgget_b("Visuals", "Snapline");
    vars.visuals.handchams  = cfgget_b("Visuals", "Hand Chams");
    vars.visuals.weaponchams= cfgget_b("Visuals", "Weapon Chams");
    vars.visuals.weapons    = cfgget_b("Visuals", "Weapons");
    vars.visuals.skeleton   = cfgget_b("Visuals", "Skeleton");
    vars.visuals.chams      = cfgget_b("Visuals", "Chams");
    vars.visuals.headhitbox = cfgget_b("Visuals", "Head Hitbox");
    vars.visuals.enemyonly  = cfgget_b("Visuals", "Enemy Only");
    vars.visuals.bombtimer  = cfgget_b("Visuals", "Bomb Timer");
    vars.visuals.crosshair  = cfgget_b("Visuals", "Crosshair");
    vars.visuals.grenade    = cfgget_b("Visuals", "Grenade");
    
    vars.visuals.handsType  = cfgget_f("Visuals", "Hands Type");
    vars.visuals.playersType= cfgget_f("Visuals", "Players Type");
    vars.visuals.weaponType = cfgget_f("Visuals", "Weapons Type");
    
    // Misc
    vars.misc.norecoil      = cfgget_b("Misc", "No Recoil");
    vars.misc.novisualrecoil= cfgget_b("Misc", "No Vis Recoil");
    vars.misc.bhop          = cfgget_b("Misc", "Bhop");
    vars.misc.autostrafe    = cfgget_b("Misc", "Autostrafe");
    vars.misc.circlestrafe  = cfgget_b("Misc", "cStrafe");
    vars.misc.fov           = cfgget_f("Misc", "FOV");
    vars.misc.airstuck      = cfgget_b("Misc", "Airstuck");
    vars.misc.showrank      = cfgget_b("Misc", "Show Rank");
    vars.misc.asuswalls     = cfgget_b("Misc", "Asus");
    vars.misc.noflash       = cfgget_b("Misc", "No Flash");
    vars.misc.flashalpha    = cfgget_b("Misc", "FlashAlpha");
    vars.misc.spammer       = cfgget_b("Misc", "Spammer");
    vars.misc.clantag       = cfgget_b("Misc", "Clantag");
    vars.misc.skinchanger   = cfgget_b("Misc", "Skin Changer");
    vars.misc.crosshairType = cfgget_f("Misc", "Crosshair T");
    vars.misc.antiuntrust   = cfgget_b("Misc", "Antiunt");
    //vars.misc.cStrafeKey    = (ButtonCode_t)cfgget_f("Misc", "cStrafe Key");
    //vars.misc.airstuckKey   = (ButtonCode_t)cfgget_f("Misc", "Airstuck Key");
    // AA
    vars.misc.thirdpersonmode= cfgget_b("Misc", "Thirdperson");
    vars.misc.anitaim       = cfgget_b("Misc", "aa");
    vars.misc.aaX           = cfgget_f("Misc", "aaX");
    vars.misc.aaY           = cfgget_f("Misc", "aaY");
    vars.misc.attargets     = cfgget_b("Misc", "At Target");
    vars.misc.customaa      = cfgget_f("Misc", "Custom aa");
    vars.misc.fakeyaw       = cfgget_f("Misc", "Fake Yaw");
    vars.misc.realyaw       = cfgget_f("Misc", "Real Yaw");
    vars.misc.fakeaa        = cfgget_b("Misc", "Fake aa");
    
}



void Config::SaveConfig() {
    
    //CSimpleIniA cfg;
    cfg.SetUnicode(true);
    this->CreateConfigDirectories();

    // Aimbot
    cfg.SetBoolValue("Aimbot", "Enabled", GetBoolValue(vars.aimbot.enabled));
    cfg.SetBoolValue("Aimbot", "Smoothing", GetBoolValue(vars.aimbot.smooth));
    cfg.SetDoubleValue("Aimbot", "Smoothf", GetFloatValue(vars.aimbot.smoothf));
    cfg.SetBoolValue("Aimbot", "RCS", GetBoolValue(vars.aimbot.rcs));
    cfg.SetDoubleValue("Aimbot", "RCSf", GetFloatValue(vars.aimbot.rcsf));
    cfg.SetBoolValue("Aimbot", "Trigger", GetBoolValue(vars.aimbot.trigger));
    
    cfg.SetDoubleValue("Aimbot", "FOV", GetFloatValue(vars.aimbot.fov));
    cfg.SetDoubleValue("Aimbot", "Hitbox", GetFloatValue(vars.aimbot.hitbox));
    
    cfg.SetBoolValue("Aimbot", "Silent", GetBoolValue(vars.aimbot.silent));
    cfg.SetBoolValue("Aimbot", "Prediction", GetBoolValue(vars.aimbot.prediciton));
    
    cfg.SetBoolValue("Aimbot", "Autowall", GetBoolValue(vars.aimbot.autowall));
    cfg.SetDoubleValue("Aimbot", "Pointscale", GetFloatValue(vars.aimbot.pointscale));
    cfg.SetBoolValue("Aimbot", "Autostop", GetBoolValue(vars.aimbot.autostop));
    cfg.SetBoolValue("Aimbot", "Autoshoot", GetBoolValue(vars.aimbot.autoshoot));
    cfg.SetBoolValue("Aimbot", "Autocrouch", GetBoolValue(vars.aimbot.autocrouch));
    cfg.SetBoolValue("Aimbot", "Autopistol", GetBoolValue(vars.aimbot.autopistol));
    
    cfg.SetDoubleValue("Aimbot", "Trigger Key", GetFloatValue((int)vars.aimbot.triggerKey));
    
    // Visuals
    cfg.SetBoolValue("Visuals", "Enabled", GetBoolValue(vars.visuals.enabled));
    cfg.SetBoolValue("Visuals", "Box", GetBoolValue(vars.visuals.box));
    cfg.SetBoolValue("Visuals", "3D Box", GetBoolValue(vars.visuals.box3d));
    cfg.SetBoolValue("Visuals", "Name", GetBoolValue(vars.visuals.name));
    cfg.SetBoolValue("Visuals", "Health", GetBoolValue(vars.visuals.health));
    cfg.SetBoolValue("Visuals", "Health text", GetBoolValue(vars.visuals.healthtext));
    cfg.SetBoolValue("Visuals", "Active", GetBoolValue(vars.visuals.active));
    cfg.SetBoolValue("Visuals", "Snapline", GetBoolValue(vars.visuals.snapline));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    cfg.SetBoolValue("Visuals", "Weapons", GetBoolValue(vars.visuals.weapons));
    cfg.SetBoolValue("Visuals", "Skeleton", GetBoolValue(vars.visuals.skeleton));
    cfg.SetBoolValue("Visuals", "Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "Head Hitbox", GetBoolValue(vars.visuals.headhitbox));
    cfg.SetBoolValue("Visuals", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    cfg.SetBoolValue("Visuals", "Bomb Timer", GetBoolValue(vars.visuals.bombtimer));
    cfg.SetBoolValue("Visuals", "Crosshair", GetBoolValue(vars.visuals.crosshair));
    
    cfg.SetDoubleValue("Visuals", "Hands Type", GetFloatValue(vars.visuals.handsType));
    cfg.SetDoubleValue("Visuals", "Players Type", GetFloatValue(vars.visuals.playersType));
    cfg.SetDoubleValue("Visuals", "Weapons Type", GetFloatValue(vars.visuals.weaponType));
    
    // Misc
    cfg.SetBoolValue("Misc", "No Recoil", GetBoolValue(vars.misc.norecoil));
    cfg.SetBoolValue("Misc", "No Vis Recoil", GetBoolValue(vars.misc.novisualrecoil));
    cfg.SetBoolValue("Misc", "Bhop", GetBoolValue(vars.misc.bhop));
    cfg.SetBoolValue("Misc", "Autostrafe", GetBoolValue(vars.misc.autostrafe));
    cfg.SetBoolValue("Misc", "cStrafe", GetBoolValue(vars.misc.circlestrafe));
    cfg.SetBoolValue("Misc", "Airstuck", GetBoolValue(vars.misc.airstuck));
    cfg.SetBoolValue("Misc", "Show Rank", GetBoolValue(vars.misc.showrank));
    cfg.SetBoolValue("Misc", "Asus", GetBoolValue(vars.misc.asuswalls));
    cfg.SetBoolValue("Misc", "No Flash", GetBoolValue(vars.misc.noflash));
    cfg.SetBoolValue("Misc", "Spammer", GetBoolValue(vars.misc.spammer));
    cfg.SetBoolValue("Misc", "Clantag", GetBoolValue(vars.misc.clantag));
    cfg.SetBoolValue("Misc", "Skin Changer", GetBoolValue(vars.misc.skinchanger));
    cfg.SetBoolValue("Misc", "Antiunt", GetBoolValue(vars.misc.antiuntrust));
    
    cfg.SetDoubleValue("Misc", "FOV", GetFloatValue(vars.misc.fov));
    cfg.SetDoubleValue("Misc", "Crosshair T", GetFloatValue(vars.misc.crosshairType));
    
    cfg.SetDoubleValue("Misc", "cStrafe Key", GetFloatValue((int)vars.misc.cStrafeKey));
    cfg.SetDoubleValue("Misc", "Airstuck Key", GetFloatValue((int)vars.misc.airstuckKey));
    
    // AA
    cfg.SetBoolValue("Misc", "Thirdperson", GetBoolValue(vars.misc.thirdpersonmode));
    cfg.SetBoolValue("Misc", "aa", GetBoolValue(vars.misc.anitaim));
    cfg.SetBoolValue("Misc", "At Target", GetBoolValue(vars.misc.attargets));
    cfg.SetBoolValue("Misc", "Fake aa", GetBoolValue(vars.misc.fakeaa));
    
    cfg.SetDoubleValue("Misc", "aaX", GetFloatValue(vars.misc.aaX));
    cfg.SetDoubleValue("Misc", "aaY", GetFloatValue(vars.misc.aaY));
    cfg.SetDoubleValue("Misc", "Custom aa", GetFloatValue(vars.misc.customaa));
    cfg.SetDoubleValue("Misc", "Fake Yaw", GetFloatValue(vars.misc.fakeyaw));
    cfg.SetDoubleValue("Misc", "Real Yaw", GetFloatValue(vars.misc.realyaw));
    
    
    cfg.SaveFile(ConfigName);
    
}

void Config::SaveSkins() {
    
    skins_cfg.SetUnicode(true);
    this->CreateConfigDirectories();
    
    skins_cfg.SetDoubleValue("Knife", "T Knife", GetFloatValue(skin.knifeT));
    skins_cfg.SetDoubleValue("Knife", "CT Knife", GetFloatValue(skin.knifeCT));
    skins_cfg.SetDoubleValue("Knife", "T Knife ID", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("Knife", "CT Knife ID", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("Knife", "T Knife Seed", GetFloatValue(skin.TknifeSeed));
    skins_cfg.SetDoubleValue("Knife", "CT Knife Seed", GetFloatValue(skin.CTknfieSeed));
    
    skins_cfg.SetDoubleValue("Glove", "T Glove", GetFloatValue(skin.gloveT));
    skins_cfg.SetDoubleValue("Glove", "CT Glove", GetFloatValue(skin.gloveCT));
    skins_cfg.SetDoubleValue("Glove", "T Glove ID", GetFloatValue(skin.TgloveID));
    skins_cfg.SetDoubleValue("Glove", "CT Glove ID", GetFloatValue(skin.CTgloveID));
    
    skins_cfg.SetDoubleValue("Rifles", "Galil", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("Rifles", "Famas", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("Rifles", "AK47", GetFloatValue(skin.ak));
    skins_cfg.SetDoubleValue("Rifles", "M4A4", GetFloatValue(skin.a4));
    skins_cfg.SetDoubleValue("Rifles", "M4A1S", GetFloatValue(skin.a1));
    skins_cfg.SetDoubleValue("Rifles", "Scout", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("Rifles", "SG", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("Rifles", "AUG", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("Rifles", "AWP", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("Rifles", "G3SG1", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("Rifles", "Scar 20", GetFloatValue(skin.scar));
    
    skins_cfg.SetDoubleValue("Pistols", "Glock", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("Pistols", "USP", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("Pistols", "P2000", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("Pistols", "Dual", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("Pistols", "P250", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("Pistols", "Tec 9", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("Pistols", "Five Seven", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("Pistols", "CZ 75", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("Pistols", "Deagle", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("Pistols", "R8", GetFloatValue(skin.r8));
    
    skins_cfg.SetDoubleValue("SMGs", "Mac 10", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("SMGs", "MP9", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("SMGs", "MP7", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("SMGs", "UMP", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("SMGs", "P90", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("SMGs", "Bizon", GetFloatValue(skin.bizon));
    
    skins_cfg.SetDoubleValue("Heavy", "Nova", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("Heavy", "Sawed off", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("Heavy", "Mag 7", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("Heavy", "XM", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("Heavy", "M249", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("Heavy", "Negev", GetFloatValue(skin.negev));
    
    // Seeds
    skins_cfg.SetDoubleValue("Rifles", "Galil Seed", GetFloatValue(skin.galil_Seed));
    skins_cfg.SetDoubleValue("Rifles", "Famas Seed", GetFloatValue(skin.famas_Seed));
    skins_cfg.SetDoubleValue("Rifles", "AK47 Seed", GetFloatValue(skin.ak_Seed));
    skins_cfg.SetDoubleValue("Rifles", "M4A4 Seed", GetFloatValue(skin.a4_Seed));
    skins_cfg.SetDoubleValue("Rifles", "M4A1S Seed", GetFloatValue(skin.a1_Seed));
    skins_cfg.SetDoubleValue("Rifles", "Scout Seed", GetFloatValue(skin.scout_Seed));
    skins_cfg.SetDoubleValue("Rifles", "SG Seed", GetFloatValue(skin.sg_Seed));
    skins_cfg.SetDoubleValue("Rifles", "AUG Seed", GetFloatValue(skin.aug_Seed));
    skins_cfg.SetDoubleValue("Rifles", "AWP Seed", GetFloatValue(skin.awp_Seed));
    skins_cfg.SetDoubleValue("Rifles", "G3 Seed", GetFloatValue(skin.g3_Seed));
    skins_cfg.SetDoubleValue("Rifles", "Scar Seed", GetFloatValue(skin.scar_Seed));
    
    skins_cfg.SetDoubleValue("Pistols", "Glock Seed", GetFloatValue(skin.glock_Seed));
    skins_cfg.SetDoubleValue("Pistols", "USP Seed", GetFloatValue(skin.usp_Seed));
    skins_cfg.SetDoubleValue("Pistols", "P2000 Seed", GetFloatValue(skin.p2000_Seed));
    skins_cfg.SetDoubleValue("Pistols", "Dual Seed", GetFloatValue(skin.dual_Seed));
    skins_cfg.SetDoubleValue("Pistols", "P250 Seed", GetFloatValue(skin.p250_Seed));
    skins_cfg.SetDoubleValue("Pistols", "Tec 9 Seed", GetFloatValue(skin.tec9_Seed));
    skins_cfg.SetDoubleValue("Pistols", "Five Seven Seed", GetFloatValue(skin.five7_Seed));
    skins_cfg.SetDoubleValue("Pistols", "CZ Seed", GetFloatValue(skin.cz_Seed));
    skins_cfg.SetDoubleValue("Pistols", "Deagle Seed", GetFloatValue(skin.deagle_Seed));
    skins_cfg.SetDoubleValue("Pistols", "R8 Seed", GetFloatValue(skin.r8_Seed));
    
    skins_cfg.SetDoubleValue("SMGs", "Mac 10 Seed", GetFloatValue(skin.mac10_Seed));
    skins_cfg.SetDoubleValue("SMGs", "MP9 Seed", GetFloatValue(skin.mp9_Seed));
    skins_cfg.SetDoubleValue("SMGs", "MP7 Seed", GetFloatValue(skin.mp7_Seed));
    skins_cfg.SetDoubleValue("SMGs", "UMP Seed", GetFloatValue(skin.ump_Seed));
    skins_cfg.SetDoubleValue("SMGs", "P90 Seed", GetFloatValue(skin.p90_Seed));
    skins_cfg.SetDoubleValue("SMGs", "Bizon Seed", GetFloatValue(skin.bizon_Seed));
    
    skins_cfg.SetDoubleValue("Heavy", "Nova Seed", GetFloatValue(skin.nova_Seed));
    skins_cfg.SetDoubleValue("Heavy", "Sawed Seed", GetFloatValue(skin.sawed_Seed));
    skins_cfg.SetDoubleValue("Heavy", "Mag 7 Seed", GetFloatValue(skin.mag7_Seed));
    skins_cfg.SetDoubleValue("Heavy", "XM Seed", GetFloatValue(skin.xm_Seed));
    skins_cfg.SetDoubleValue("Heavy", "M249 Seed", GetFloatValue(skin.m249_Seed));
    skins_cfg.SetDoubleValue("Heavy", "Negev Seed", GetFloatValue(skin.negev_Seed));
    
    skins_cfg.SaveFile(skins_file.c_str());
    
}

void Config::LoadSkins() {
    
    this->CreateConfigDirectories();
    
    if(!fileExist(skins_file.c_str()))
        SaveSkins();
    
    skins_cfg.SetUnicode(true);
    skins_cfg.LoadFile(skins_file.c_str());
    
    skin.knifeT     = skin_cfgget_f("Knife", "T Knife");
    skin.knifeCT    = skin_cfgget_f("Knife", "CT Knife");
    skin.TknifeID   = skin_cfgget_f("Knife", "T Knife ID");
    skin.CTknifeID  = skin_cfgget_f("Knife", "CT Knife ID");
    skin.TknifeSeed = skin_cfgget_f("Knife", "T Knife Seed");
    skin.CTknfieSeed= skin_cfgget_f("Knife", "CT Knife Seed");
    
    skin.gloveT     = skin_cfgget_f("Glove", "T Glove");
    skin.gloveCT    = skin_cfgget_f("Glove", "CT Glove");
    skin.TgloveID   = skin_cfgget_f("Glove", "T Glove ID");
    skin.CTgloveID  = skin_cfgget_f("Glove", "CT Glove ID");
    
    skin.galil   = skin_cfgget_f("Rifles", "Galil");
    skin.famas   = skin_cfgget_f("Rifles", "Famas");
    skin.ak      = skin_cfgget_f("Rifles", "AK47");
    skin.a4      = skin_cfgget_f("Rifles", "M4A4");
    skin.a1      = skin_cfgget_f("Rifles", "M4A1S");
    skin.scout   = skin_cfgget_f("Rifles", "Scout");
    skin.sg      = skin_cfgget_f("Rifles", "SG");
    skin.aug     = skin_cfgget_f("Rifles", "AUG");
    skin.awp     = skin_cfgget_f("Rifles", "AWP");
    skin.g3      = skin_cfgget_f("Rifles", "G3SG1");
    skin.scar    = skin_cfgget_f("Rifles", "Scar 20");
    
    skin.glock   = skin_cfgget_f("Pistols", "Glock");
    skin.usp     = skin_cfgget_f("Pistols", "USP");
    skin.p2000   = skin_cfgget_f("Pistols", "P2000");
    skin.dual    = skin_cfgget_f("Pistols", "Dual");
    skin.p250    = skin_cfgget_f("Pistols", "P250");
    skin.tec9    = skin_cfgget_f("Pistols", "Tec 9");
    skin.five7   = skin_cfgget_f("Pistols", "Five Seven");
    skin.cz      = skin_cfgget_f("Pistols", "CZ 75");
    skin.deagle  = skin_cfgget_f("Pistols", "Deagle");
    skin.r8      = skin_cfgget_f("Pistols", "R8");
    
    skin.mac10   = skin_cfgget_f("SMGs", "Mac 10");
    skin.mp9     = skin_cfgget_f("SMGs", "MP9");
    skin.mp7     = skin_cfgget_f("SMGs", "MP7");
    skin.ump     = skin_cfgget_f("SMGs", "UMP");
    skin.p90     = skin_cfgget_f("SMGs", "P90");
    skin.bizon   = skin_cfgget_f("SMGs", "Bizon");
    
    skin.nova    = skin_cfgget_f("Heavy", "Nova");
    skin.sawed   = skin_cfgget_f("Heavy", "Sawed off");
    skin.mag7    = skin_cfgget_f("Heavy", "Mag 7");
    skin.xm      = skin_cfgget_f("Heavy", "XM");
    skin.m249    = skin_cfgget_f("Heavy", "M249");
    skin.negev   = skin_cfgget_f("Heavy", "Negev");
    
    skin.galil_Seed   = skin_cfgget_f("Rifles", "Galil Seed");
    skin.famas_Seed   = skin_cfgget_f("Rifles", "Famas Seed");
    skin.ak_Seed      = skin_cfgget_f("Rifles", "AK47 Seed");
    skin.a4_Seed      = skin_cfgget_f("Rifles", "M4A4 Seed");
    skin.a1_Seed      = skin_cfgget_f("Rifles", "M4A1S Seed");
    skin.scout_Seed   = skin_cfgget_f("Rifles", "Scout Seed");
    skin.sg_Seed      = skin_cfgget_f("Rifles", "SG Seed");
    skin.aug_Seed     = skin_cfgget_f("Rifles", "AUG Seed");
    skin.awp_Seed     = skin_cfgget_f("Rifles", "AWP Seed");
    skin.g3_Seed      = skin_cfgget_f("Rifles", "G3 Seed");
    skin.scar_Seed    = skin_cfgget_f("Rifles", "Scar Seed");
    
    skin.glock_Seed   = skin_cfgget_f("Pistols", "Glock Seed");
    skin.usp_Seed     = skin_cfgget_f("Pistols", "USP Seed");
    skin.p2000_Seed   = skin_cfgget_f("Pistols", "P2000 Seed");
    skin.dual_Seed    = skin_cfgget_f("Pistols", "Dual Seed");
    skin.p250_Seed    = skin_cfgget_f("Pistols", "P250 Seed");
    skin.tec9_Seed    = skin_cfgget_f("Pistols", "Tec 9 Seed");
    skin.five7_Seed   = skin_cfgget_f("Pistols", "Five Seven Seed");
    skin.cz_Seed      = skin_cfgget_f("Pistols", "CZ Seed");
    skin.deagle_Seed  = skin_cfgget_f("Pistols", "Deagle Seed");
    skin.r8_Seed      = skin_cfgget_f("Pistols", "R8 Seed");
    
    skin.mac10_Seed   = skin_cfgget_f("SMGs", "Mac 10 Seed");
    skin.mp9_Seed     = skin_cfgget_f("SMGs", "MP9 Seed");
    skin.mp7_Seed     = skin_cfgget_f("SMGs", "MP7 Seed");
    skin.ump_Seed     = skin_cfgget_f("SMGs", "UMPv");
    skin.p90_Seed     = skin_cfgget_f("SMGs", "P90 Seed");
    skin.bizon_Seed   = skin_cfgget_f("SMGs", "Bizon Seed");
    
    skin.nova_Seed    = skin_cfgget_f("Heavy", "Nova Seed");
    skin.sawed_Seed   = skin_cfgget_f("Heavy", "Sawed Seed");
    skin.mag7_Seed    = skin_cfgget_f("Heavy", "Mag 7 Seed");
    skin.xm_Seed      = skin_cfgget_f("Heavy", "Xm Seed");
    skin.m249_Seed    = skin_cfgget_f("Heavy", "M249 Seed");
    skin.negev_Seed   = skin_cfgget_f("Heavy", "Negev Seed");
    
}

/*
cSkin Config::GetWeaponConfiguration(const char *section) {
    
    if(!fileExist(skins.c_str()))
        SaveSkins();
    
    cfg.SetUnicode(true);
    cfg.LoadFile(skins.c_str());
    cSkin weapon_config;
    
    weapon_config.Paintkit = (int)cfg.GetLongValue(section, "Skin ID");
    weapon_config.Seed = (int)cfg.GetLongValue(section, "Seed");
    weapon_config.Wear = (float)cfg.GetDoubleValue(section, "Float Value");
    weapon_config.ItemDefinition = (int)cfg.GetLongValue(section, "Item Definition");
    
    return weapon_config;
}
*/

