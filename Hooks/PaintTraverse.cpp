#include "../main.h"
#include "../Hacks/esp.h"
#include "../Hacks/recoilcrosshair.h"
#include "../GUI/menu.h"
#include "../Hacks/walkbot.h"
#include "../Config/skins.h"

bool qOnce = false;
bool bPanelOnce = false;

colors mColors;

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce) {
    
    painthook->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    static VPANEL last = 0;
    
    if(!last) {
        
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel")) {
            
            framefont       = draw->createfont(framefont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);
            espfont         = draw->createfont(espfont, "Arial Bold", 12, FONTFLAG_DROPSHADOW);
            
            mFont           = draw->createfont(mFont, "BigNoodleTitling", 15, FONTFLAG_ANTIALIAS);
            sFont           = draw->createfont(sFont, "BigNoodleTitling", 12, FONTFLAG_ANTIALIAS);     // Used for sliders
            tFont           = draw->createfont(tFont, "BigNoodleTitling", 18, FONTFLAG_ANTIALIAS);   // Used for tabs
            heading         = draw->createfont(heading, "BigNoodleTitling", 21, FONTFLAG_ANTIALIAS);   // Used for headings
            osFont          = draw->createfont(osFont, "osmiummenufont", 30, FONTFLAG_ANTIALIAS);
            cFont           = draw->createfont(cFont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS); // Combos
            titleFont       = draw->createfont(cFont, "BigNoodleTitling", 52, FONTFLAG_ANTIALIAS); // vlone.cc Title
            subtitleFont   = draw->createfont(cFont, "BigNoodleTitling", 12, FONTFLAG_ANTIALIAS); // vlone.cc Subtitle
            o4Font_03       = draw->createfont(o4Font_03, "04b03", 12, FONTFLAG_ANTIALIAS);
            o4Font_11       = draw->createfont(o4Font_11, "04b11", 12, FONTFLAG_ANTIALIAS);
            o4Font_20       = draw->createfont(o4Font_20, "04b_20", 12, FONTFLAG_ANTIALIAS);
            
            last = panel;
            
        }
    }
    
    if(!bPanelOnce) {
        
        vars.colors.ctchams     = Color(60, 53, 178, 255);
        vars.colors.ctchams_ign = Color(229, 22, 90, 255);
        
        vars.colors.tchams      = Color(60, 53, 178, 255);
        vars.colors.tchams_ign  = Color(229, 22, 90, 255);
        
        vars.colors.tbox        = Color(60, 53, 178, 255);
        vars.colors.tbox_ign    = Color(229, 22, 90, 255);
        
        vars.colors.ctbox       = Color(60, 53, 178, 255);
        vars.colors.ctbox_ign   = Color(229, 22, 90, 255);
        
        vars.colors.hands       = Color(255, 0, 83, 255);
        vars.colors.hands_ign   = Color(0, 0, 255, 255);
        
        vars.colors.weapons     = Color(0, 0, 255, 255);
        vars.colors.weapons_ign = Color(255, 0, 83, 255);
        
        vars.colors.dropped     = Color::Blue();
        vars.colors.dropped_ign = Color::Red();
        
        vars.colors.crosshair = Color::Green();
        
        vars.colors.world = Color::Green(); // :^)
        
        bPanelOnce = true;
        
    }

    if(panel == last) {
        
        pwnmymenu();
        
        // Disable premium features for vHook. This actually works surprisingly well!
        {
            vars.aimbot.prediciton = false;
            vars.aimbot.pointscale = 0;
            vars.aimbot.enginepred = false;
            vars.aimbot.hitscan = false;
            vars.aimbot.psilent = false;
            vars.aimbot.selfpred = false;
            
            vars.visuals.grenade = false;
            vars.visuals.weaponchams = false;
            vars.visuals.weapons = false;
            vars.visuals.box3d = false;
            vars.visuals.headhitbox = false;
            vars.visuals.crosshair = false;
            vars.visuals.weaponType = 0;
            vars.misc.crosshairType = 0;
            
            vars.misc.airstuck = false;
            vars.misc.nosky = false;
            vars.misc.noscope = false;
            vars.misc.thirdpersonmode = false;
            vars.misc.fakelag = false;
        }
        
        if(vars.menu && !(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())) {
            menu->renderMenu();
            draw->drawmouse();
        }

        if(!(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())) {
            DrawPlayerESP();
            rCrosshair(local);
        } else {
            pEngine->ExecuteClientCmd("crosshair 1");    // Enables crosshair
        }
        
        draw->DrawBasicString(10, 15, Color::White(), espfont, "[vlone.cc - Public vHook]");
    }
}
