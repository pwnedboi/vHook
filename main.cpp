#include "main.h"
#include "Config.h"



int __attribute__((constructor)) Init() {
    /* do shiz her. */
    
    config->LoadSkins();
    
    InitializeInterfaces();
    
    InitializeVMTs();
    
    InitializeHooks();
    
    NetVarManager::DumpNetvars();
    
    Offsets::getOffsets();
    
    UpdateResolver();
    
    pCvar->ConsoleColorPrintf(Color::White(), "[vlone.cc - vHook Public] Welcome to vHook!\n");
    pCvar->ConsoleColorPrintf(Color::White(), "[vlone.cc - vHook Public] Press ");
    pCvar->ConsoleColorPrintf(Color::Green(), "ALT ");
    pCvar->ConsoleColorPrintf(Color::White(), "or ");
    pCvar->ConsoleColorPrintf(Color::Green(), "INSERT ");
    pCvar->ConsoleColorPrintf(Color::White(), "to open the menu.\n");
    pCvar->ConsoleColorPrintf(Color::White(), "[vlone.cc - vHook Public] Public vHook brought to you by http://vlone.cc!\n");
    
    return 0;
}

void __attribute__((constructor)) DeInit() {
}

/*

 Goals:
 Config System
 Glove Changer
 Skin Changer in Menu
 
 Improve Aimbot
 
 
 unlock cursor
 DrawKeyField
 
 
 // osmium
 buybot
 
 // gerd
 GetTargetCrosshair
 AutoStrafe
 DrawRecoilCrosshair

 // Muhui
 CircleStrafer
 Draw_Corner_Box_Faster
 Cornerbox
 Aimbot - curve
 
 // Sinister
 Aimbot.cpp
 SafeDelete
 UnHook
 vis_weaponchams
 LegitAimbot.cpp
 CircleStrafer
 GetWeaponName

 
 
 CorrectMovement
 

*/
