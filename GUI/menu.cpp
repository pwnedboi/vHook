//
//  menu.cpp
//  vHook
//

#include "menu.h"
#include "../Config/Config.h"

cMenu* menu = new cMenu();
menuT tab;
colors col;
Config cfg;

Color ControlBackground = Color(18, 18, 18, 255);
Color ControlColor      = Color(30, 30, 30, 255);

Color FontColor         = Color(250, 250, 250, 250);
Color Orang             = Color(255, 0, 3, 255); // Red Menu
Color Green             = Color(0, 255, 9, 255); // Green Menu
Color Blu               = Color(0, 122, 255, 255); // Blue Menu
Color inactive          = Color(82, 82, 82, 255);
Color MainColor         = Color(9, 9, 9, 255);

bool WasPressed, WasReleased;
static float rainbow;

//=====================WasPressed=========================//

auto Pressed (ButtonCode_t code) -> void {
    if (pInputSystem->IsButtonDown(code))
    {
        WasPressed = true;
    }
    else if (!(pInputSystem->IsButtonDown(code)))
    {
        if (WasPressed)
            WasReleased = true;
            else
            {
                WasReleased = false;
            }
        WasPressed = false;
    }
}

//==================Buttons and shit=====================//

void cMenu::renderCheckbox(int x, int y, const char* str, bool *var) {
    
    int size = 8;
    
    draw->fillrgba(x, y, size, size, Color(78,78,78,255));
    draw->fillrgba(x + 1, y + 1, size - 2, size - 2, Color(67,67,67,255));
    
    if (*var) {
        draw->fillrgba( x, y, size, size, Color(92, 131, 152, 255) );
        draw->fillrgba( x + 1, y + 1, size - 2, size - 2, Color(85, 121, 141, 255) );
    }
    
    if (draw->inArea(x, y, size, size)) {
        
        if (*var) {
            draw->fillrgba( x, y, size, size, Color(92, 131, 152, 150) );
            draw->fillrgba( x + 1, y + 1, size - 2, size - 2, Color(85, 121, 141, 150) );
        }
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawbox(x, y, size, size, Color(9,9,9,255)); // Outline
    
    draw->drawstring(x - 100, y, FontColor, mFont, str);
    
}

void cMenu::renderCheckbox(int x, int y, bool *var) {
    
    int size = 8;
    
    draw->fillrgba(x, y, size, size, Color(78,78,78,255));
    draw->fillrgba(x + 1, y + 1, size - 2, size - 2, Color(67,67,67,255));
    
    if (*var) {
        draw->fillrgba( x, y, size, size, Color(92, 131, 152, 255) );
        draw->fillrgba( x + 1, y + 1, size - 2, size - 2, Color(85, 121, 141, 255) );
    }
    
    if (draw->inArea(x, y, size, size)) {
        
        if (*var) {
            draw->fillrgba( x, y, size, size, Color(92, 131, 152, 150) );
            draw->fillrgba( x + 1, y + 1, size - 2, size - 2, Color(85, 121, 141, 150) );
        }
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawbox(x, y, size, size, Color(9,9,9,255)); // Outline
    
}

void cMenu::renderSlider(int x, int y, int w, const char* szString, int &value, int max, int min) {
    
    int h = 6;
    
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - w / 2 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + w / 2 && draw->GetMouse().y < y + h + 2) {
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            if (value > max)
                value = max;
            if (value < min)
                value = min;
            
        }
    }
    
    
    draw->RectOutlined(x, y + 5, w + 2, h, 1, ControlBackground, Color::Black());
    draw->fillrgba( x, y + 5, curValue, h, Color(85, 121, 141, 255) );                       // Color till cursor
    
    draw->drawstring(x + curValue - 5, y + 3, Color::White(), sFont, to_string(value).c_str());
    draw->drawstring(x, y - 9, FontColor, mFont, szString);
    
}

void cMenu::renderSlider(int x, int y, int w, const char* szString, float &value, int max, int min) {
    
    int h = 6;
    
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - w / 2 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + w / 2 && draw->GetMouse().y < y + h + 2) {
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            if (value > max)
                value = max;
            if (value < min)
                value = min;
            
        }
    }
    
    
    draw->RectOutlined(x, y + 5, w + 2, h, 1, ControlBackground, Color::Black());
    draw->fillrgba( x, y + 5, curValue, h, Color(85, 121, 141, 255) );                       // Color till cursor
    
    draw->drawstring(x + curValue - 5, y + 3, Color::White(), sFont, to_string(value).c_str());
    draw->drawstring(x, y - 9, FontColor, mFont, szString);
    
}

void cMenu::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend) {
    
    int Y = y + h;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if (*bOpend) {
        
        for ( int i = 0; i < szValue.size(); i++ ) {
            
            auto bHover = draw->inArea(x, Y + 2 + ( i * 20 ), w, 18);
            
            draw->fillrgba( x, Y + 2 + ( i * 20 ), w, 18, bHover ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255) );
            draw->drawboxoutline( x, Y + 2 + ( i * 20 ), w, 18, Color( 90, 90, 90, 255 ) );
            draw->drawstring(x + 5, Y + 3 + (i*20), Color::White(), cFont, szValue[i].c_str());
            
            if (draw->inArea(x, Y + 2 + ( i * 20 ), w, 18)) {
                if(WasPressed){
                    currValue = i;
                    *bOpend = false;
                }
            }
        }
    }
    
    if(currValue == 0)
        szString = szString;
    else
        szString = szValue[currValue].c_str();
    
    // Draws the box
    draw->fillrgba( x, y, w, h, Color(25, 25, 25, 255) );
    draw->fillrgba( x + w - h, y, h, h, ControlBackground );
    draw->drawboxoutline( x, y, w, h, Color(9,9,9,255) );
    draw->drawboxoutline( x + 1, y + 1, w - 2, h - 2, Color(67, 67, 67,255) );
    draw->drawstring(x + 5, y + (h/2) - 7, FontColor, cFont, szString);
    
    
    if (!*bOpend)
    {
        // draw arrow pointing down
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
    else
    {
        // draw arrow pointing up
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
}

void cMenu::renderButton(int x, int y, const char* szString, bool* var) {
    
    int w = 60;
    int h = 20;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasPressed) {
            *var = true;
        }
    } else {
        *var = false;
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
    
}


void cMenu::playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString) {
    y += index * vars.buttonPadding;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            playercount = index;
        }
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
}




//=====================Menu Tabs=========================//

enum mTab
{
    Null    = 0,
    AimTab  = 1,
    VisTab  = 2,
    MiscTab = 3,
    PlayerTab = 4,
    ColorsTab = 5,
};

void cMenu::renderAim(int x, int y) {

    // Legit
    draw->drawstring(x + 240, y + 35, FontColor, heading, "Legit"); // 35
    
    this->renderCheckbox(x + 300, y + 65, "Enabled", &vars.aimbot.enabled); // +30
    this->renderCheckbox(x + 300, y + 95, "Smoothing", &vars.aimbot.smooth); // +30
    this->renderSlider(x + 200, y + 110, 110, "", vars.aimbot.smoothf, 1.f, 0.f); // +15
    this->renderCheckbox(x + 300, y + 130, "RCS", &vars.aimbot.rcs); // +30
    this->renderSlider(x + 200, y + 145, 110, "", vars.aimbot.rcsf, 50, 0); // +15
    this->renderSlider(x + 200, y + 185, 110, "FOV", vars.aimbot.fov, 180, 0); // +30
    this->renderSlider(x + 200, y + 225, 110, "Hitbox", vars.aimbot.hitbox, 6, 0); // +30
    this->renderCheckbox(x + 300, y + 255, "Triggerbot", &vars.aimbot.trigger); // +30
    
    
    // Rage
    draw->drawstring(x + 475, y + 35, FontColor, heading, "Rage"); // 25
    
    this->renderCheckbox(x + 535, y + 65, "Silent", &vars.aimbot.silent); // +10 to skip enabled slot +50 for next slot.
    this->renderCheckbox(x + 535, y + 95, "Auto Pistol", &vars.aimbot.autopistol); // +50
    this->renderCheckbox(x + 535, y + 125, "Auto Shoot", &vars.aimbot.autoshoot); // +50
    this->renderCheckbox(x + 535, y + 155, "Auto Stop", &vars.aimbot.autostop); // +50
    this->renderCheckbox(x + 535, y + 185, "Auto Crouch", &vars.aimbot.autocrouch); // +50


}

void cMenu::renderVis(int x, int y) {
    
    vector<string> weaponsvector;
    weaponsvector.push_back("Lit");
    weaponsvector.push_back("Texture");
    weaponsvector.push_back("WireFrame");
    weaponsvector.push_back("No Weapon");
    weaponsvector.push_back("Multi");
    
    this->renderCheckbox(x + 300, y + 35, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x + 300, y + 65, "Enemies Only", &vars.visuals.enemyonly);
    this->renderCheckbox(x + 300, y + 95, "Name ESP", &vars.visuals.name);
    this->renderCheckbox(x + 300, y + 125, "2D Health ESP", &vars.visuals.healthtext);
    this->renderCheckbox(x + 300, y + 245, "Weapon Chams", &vars.visuals.weaponchams);
    this->renderCheckbox(x + 300, y + 275, "Dropped Weapons", &vars.visuals.weapons);
    this->renderCheckbox(x + 300, y + 305, "Snaplines", &vars.visuals.snapline);
    this->renderCheckbox(x + 300, y + 335, "Skeleton", &vars.visuals.skeleton);
    
    
    
    // Right Side
    
    vector<string> chamsvector;
    vector<string> handsvector;
    
    chamsvector.push_back("Lit");
    chamsvector.push_back("Texture");
    chamsvector.push_back("Outlined");
    handsvector.push_back("Lit");
    handsvector.push_back("Texture");
    handsvector.push_back("Wireframe");
    handsvector.push_back("No Hands");
    handsvector.push_back("Multi");
    
    
    this->renderCheckbox(x + 535, y + 35, "3D Health ESP", &vars.visuals.health);
    this->renderCheckbox(x + 535, y + 65, "2D Box ESP", &vars.visuals.box);
    this->renderCheckbox(x + 535, y + 95, "No Recoil", &vars.misc.norecoil);
    this->renderCheckbox(x + 535, y + 125, "No Visual", &vars.misc.novisualrecoil);
    
    
    if(!vars.hands_opend && !vars.weapon_opend) {
        this->renderCheckbox(x + 535, y + 275, "Skin Changer", &vars.misc.skinchanger);
    }
    if(!vars.hands_opend) {
        this->renderCombo(x + 435, y + 245, 110, 20, "Lit", weaponsvector, vars.visuals.weaponType, &vars.weapon_opend);
    }
    
    this->renderCheckbox(x + 300, y + 185, "Player Chams", &vars.visuals.chams);
    
    if(!vars.crossT_opend)
        this->renderCheckbox(x + 300, y + 215, "Hand Chams", &vars.visuals.handchams);
        this->renderCombo(x + 435, y + 180, 110, 20, "Lit", chamsvector, vars.visuals.playersType, &vars.players_opend);
    
    if(!vars.players_opend)
        this->renderCombo(x + 435, y + 210, 110, 20, "Lit", handsvector, vars.visuals.handsType, &vars.hands_opend);
    
}

void cMenu::renderConfigs(int x, int y) {
    vector<string> conf;
    
    conf.push_back("Legit");
    conf.push_back("Rage");
    conf.push_back("Panic");
    
    this->renderCombo(x, y, 125, 20, "Legit", conf, cfg.cfgcombo, &vars.cfg_opend);
    if(!vars.cfg_opend) {
        this->renderButton(x, y + 22, "Save", &cfg.saveconfig);
        this->renderButton(x + 65, y + 22, "Load", &cfg.loadconfig);
    }
}

void cMenu::renderMisc(int x, int y) {
    
    this->renderCheckbox(x + 300, y + 35, "Bunnyhop", &vars.misc.bhop);
    this->renderCheckbox(x + 300, y + 65, "Field of View", &vars.misc.fov); // +30
    this->renderSlider(x + 200, y + 80, 110, "", vars.misc.fovf, 50, 0); // +15
    this->renderCheckbox(x + 300, y + 100, "Show Ranks", &vars.misc.showrank);
    this->renderCheckbox(x + 300, y + 130, "Auto Strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x + 300, y + 165, "At Targers", &vars.misc.attargets);
    this->renderCheckbox(x + 300, y + 195, "Fake", &vars.misc.fakeaa);
    this->renderCheckbox(x + 300, y + 225, "Clantag", &vars.misc.clantag);
    
    // Left Side
    vector<string> antiaim_pitch;
    vector<string> antiaim_yaw;
    
    antiaim_pitch.push_back("Off");
    antiaim_pitch.push_back("Emotion");
    antiaim_pitch.push_back("Up");
    
    antiaim_yaw.push_back("Off");
    antiaim_yaw.push_back("Backwards");
    antiaim_yaw.push_back("Jitter");
    antiaim_yaw.push_back("FJitter");
    antiaim_yaw.push_back("Slow Spin");
    antiaim_yaw.push_back("Fast Spin");
    
    this->renderCheckbox(x + 535, y + 35, "Anti Untrust", &vars.misc.antiuntrust);
    this->renderCheckbox(x + 535, y + 65, "Anti Screenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 535, y + 95, "Circle Strafe", &vars.misc.circlestrafe);
    this->renderCheckbox(x + 535, y + 125, "No Flash", &vars.misc.noflash); // +30
    this->renderSlider(x + 435, y + 140, 110, "", vars.misc.flashalpha, 255, 0);
    
    this->renderCombo(x + 435, y + 160, 110, 20, "Off", antiaim_pitch, vars.misc.aaX, &vars.aaX_opend);
    if(!vars.aaX_opend)
        this->renderCombo(x + 435, y + 190, 112, 20, "Off", antiaim_yaw, vars.misc.aaY, &vars.aaY_opend);
    
//    draw->textbox(x + 200, y + 215, 110, "Name", draw-> m_szCurrentString, 2, 2, &vars.misc_changename);
//    draw->textbox(x + 200, y + 225, 110, "Clantag", draw->m_szCurrentString, 3, 0, &vars.misc_clantag);
    
}

void cMenu::renderPlayer(int x, int y) {

    draw->drawstring(x + 200, y + 35, FontColor, heading, "Player List");
    
    if(!pEngine->IsInGame())
        draw->drawstring(x + 200, y + 65, MainColor, heading, "Not in game");
    
    
    std::vector<std::string> PitchResolver, YawResolver;
    
    PitchResolver.push_back("Auto");
    PitchResolver.push_back("Down");
    PitchResolver.push_back("Up");
    
    YawResolver.push_back("Auto");
    YawResolver.push_back("Half Left");
    YawResolver.push_back("Half Right");
    YawResolver.push_back("Jitter");
    YawResolver.push_back("Spin");
    YawResolver.push_back("Lower Body");
    YawResolver.push_back("45 Step");
    
    int bPadding = 0;
    char plinfo[255];
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 1; i < 64; i++) {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        player_info_t info;
        pEngine->GetPlayerInfo(i, &info);
        
        this->playerbutton(x + 215, y + 60, 110, 20, bPadding, vars.playerTab, info.name);
        
        if(bPadding == vars.playerTab) {
            
//            draw->drawstringINDEX(x + 365, y + 25, FontColor, plinfo, 0, false);
            this->renderCheckbox(x + 535, y + 60, "Resolve", &gCorrections[entity->GetIndex()].resolved);
            this->renderCheckbox(x + 535, y + 80, "Whitelist", &gCorrections[entity->GetIndex()].whitelist);
            
            draw->drawstring(x + 435, y + 100, FontColor, mFont, "Pitch");
            this->renderCombo(x + 435, y + 120, 110, 20, "Auto", PitchResolver, gCorrections[entity->GetIndex()].dropdown_x, &vars.playerlist_opend_x[entity->GetIndex()]);
            
            if(!vars.playerlist_opend_x[entity->GetIndex()]) {
                draw->drawstring(x + 435, y + 140, FontColor, mFont, "Yaw");
                this->renderCombo(x + 435, y + 155, 110, 20, "Auto", YawResolver, gCorrections[entity->GetIndex()].dropdown_y, &vars.playerlist_opend_y[entity->GetIndex()]);
            }
            
        }
        bPadding++;
    }
}

void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("CT Colors");
    Colors.push_back("T Colors");
    Colors.push_back("Others");
    
    this->renderCombo(x + 200, y + 45, 125, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    
    if(vars.colors.combo == 0) {
    
        draw->drawcolorpicker(x + 345, y + 45, "CT Box", vars.colors.ctbox, 0);
        draw->drawcolorpicker(x + 345, y + 180, "CT Box Ignore", vars.colors.ctbox_ign, 0);
        
        draw->drawcolorpicker(x + 490, y + 45, "CT Chams", vars.colors.ctchams, 0);
        draw->drawcolorpicker(x + 490, y + 180, "CT Chams Ignore", vars.colors.ctchams, 0);
    
    }
    
    if(vars.colors.combo == 1) {
    
        draw->drawcolorpicker(x + 345, y + 45, "T Box", vars.colors.tbox, 0);
        draw->drawcolorpicker(x + 345, y + 180, "T Box Ignore", vars.colors.tbox_ign, 0);
        
        draw->drawcolorpicker(x + 490, y + 45, "T Chams", vars.colors.tchams, 0);
        draw->drawcolorpicker(x + 490, y + 180, "T Chams Ignore", vars.colors.tchams, 0);
    
    }
    
    if(vars.colors.combo == 2) {
        vector<string> CrosshairColor, MenuColor;
        
        CrosshairColor.push_back("Green");
        CrosshairColor.push_back("Magenta");
        CrosshairColor.push_back("White");
        CrosshairColor.push_back("Blue");
        CrosshairColor.push_back("Red");
        
        MenuColor.push_back("Blue");
        MenuColor.push_back("Green");
        MenuColor.push_back("Red");
        MenuColor.push_back("Orange");
        MenuColor.push_back("Purple");
        
        draw->drawstring(x + 200, y + 105, FontColor, mFont, "Crosshair Color");
        this->renderCombo(x + 200, y + 120, 100, 20, "Red", CrosshairColor, vars.colors.cColor, &vars.crossC_opend);
        
//        if(!vars.crossC_opend) {
//            draw->drawstring(x + 200, y + 185, FontColor, mFont, "Menu Color Color");
//            this->renderCombo(x + 200, y + 200, 100, 20, "Blue", MenuColor, col.menu, &vars.mCol_opend);
//        }
        
        draw->drawcolorpicker(x + 355, y + 45, "Hands", vars.colors.hands, 0);
        draw->drawcolorpicker(x + 355, y + 180, "Hands Ignore", vars.colors.hands_ign, 0);
        
        
    }
    
    
}

//=======================Menu==========================//

void cMenu::renderMenu() {
    
    int wScreen, hScreen;
    pEngine->GetScreenSize(wScreen, hScreen);
    
    // Tab menu measurements
    static int x = 100;
    static int y = 100;
    int w = 710;
    int h = 420;
    int hh = 10;
    tab.w = 170;
    tab.h = 48;
    
    
    draw->RectOutlined(x, y, w, h, 1, Color(18,18,18,255), Color(0, 0, 0, 255));
    draw->RectOutlined(x + 1, y + 1, w - 2, h - 2, 1, Color(18,18,18,255), Color(67, 67, 67, 255));
    draw->RectOutlined(x + 2, y + 2, w - 4, h - 4, 1, Color(18,18,18,255), Color(42, 42, 42, 255));
    draw->RectOutlined(x + 3, y + 3, w - 6, h - 6, 1, Color(18,18,18,255), Color(42, 42, 42, 255));
    draw->RectOutlined(x + 4, y + 4, w - 8, h - 8, 1, Color(18,18,18,255), Color(42, 42, 42, 255));
    draw->RectOutlined(x + 5, y + 5, w - 10, h - 10, 1, Color(18,18,18,255), Color(67, 67, 67, 255));
    draw->RectOutlined(x + tab.w + 2, y + 6, w - 6 - tab.w - 2, h - 12, 1, Color(26,26,26,255), Color(26,26,26,255));
    
    
    draw->drawline(x + tab.w, y + 6, x + tab.w, y + h - 6, Color(67, 67, 67, 255));
    draw->drawline(x + tab.w + 1, y + 6, x + tab.w + 1, y + h - 6, Color(0, 0, 0, 255));
    
    draw->drawstring(x + 32, y + 25, Color(255,255,255,255), titleFont, "vHook");
    
    if(tab.tab != 1) {
        draw->drawstring(x + 15 + 6, y + 110, inactive, osFont, "A");
        draw->drawstring(x + 55, y + 115, inactive, tFont, "Aimbot");
    }
    
    if(tab.tab != 2) {
        draw->drawstring(x + 13 + 6, y + 162, inactive, osFont, "B");
        draw->drawstring(x + 55, y + 168, inactive, tFont, "Visuals");
    }
    
    if(tab.tab != 3) {
        draw->drawstring(x + 15 + 6, y + 214, inactive, osFont, "C");
        draw->drawstring(x + 55, y + 218, inactive, tFont, "Miscellaneous");
    }
    
    if(tab.tab != 4) {
        draw->drawstring(x + 17 + 6, y + 266, inactive, osFont, "D");
        draw->drawstring(x + 55, y + 271, inactive, tFont, "Players");
    }
    
    if(tab.tab != 5) {
        draw->drawstring(x + 13 + 6, y + 318, inactive, osFont, "G");
        draw->drawstring(x + 55, y + 325, inactive, tFont, "Colors");
    }
    
    
    if(draw->inArea(x, y + 100, tab.w, tab.h) && WasReleased)
        tab.tab = mTab::AimTab;
    
    if(draw->inArea(x, y + 152, tab.w, tab.h) && WasReleased)
        tab.tab = mTab::VisTab;
    
    if(draw->inArea(x, y + 204, tab.w, tab.h) && WasReleased)
        tab.tab = mTab::MiscTab;
    
//    if(draw->inArea(x, y + 256, tab.w, tab.h) && WasReleased)
//        tab.tab = mTab::PlayerTab;
    
    if(draw->inArea(x, y + 308, tab.w, tab.h) && WasReleased)
        tab.tab = mTab::ColorsTab;
    
    
    
    if(tab.tab == 1) {
        
        draw->fillrgba(x + 6, y + 100, tab.w - 6, tab.h, Color(9,9,9,255));
        draw->drawstring(x + 15 + 6, y + 110, Color(255,255,255,255), osFont, "A");
        draw->drawstring(x + 55, y + 115, Color(255,255,255,255), tFont, "Aimbot");
        
        this->renderAim(x + 60, y);
        
    }
    
    if(tab.tab == 2) {
        
        draw->fillrgba(x + 6, y + 152, tab.w - 6, tab.h, Color(9,9,9,255));
        draw->drawstring(x + 13 + 6, y + 162, Color(255,255,255,255), osFont, "B");
        draw->drawstring(x + 55, y + 168, Color(255,255,255,255), tFont, "Visuals");
        
        this->renderVis(x + 60, y);
        
    }
    
    if(tab.tab == 3) {
        
        draw->fillrgba(x + 6, y + 204, tab.w - 6, tab.h, Color(9,9,9,255));
        draw->drawstring(x + 15 + 6, y + 214, Color(255,255,255,255), osFont, "C");
        draw->drawstring(x + 55, y + 218, Color(255,255,255,255), tFont, "Miscellaneous");
        
        this->renderMisc(x + 60, y);
        
    }
    
    if(tab.tab == 4) {
        
        draw->fillrgba(x + 6, y + 256, tab.w - 6, tab.h, Color(9,9,9,255));
        draw->drawstring(x + 17 + 6, y + 266, Color(255,255,255,255), osFont, "D");
        draw->drawstring(x + 55, y + 271, Color(255,255,255,255), tFont, "Players");
        
        
        this->renderPlayer(x + 60, y);
        
    }
    
    if(tab.tab == 5) {
        
        draw->fillrgba(x + 6, y + 308, tab.w - 6, tab.h, Color(9,9,9,255));
        draw->drawstring(x + 13 + 6, y + 318, Color(255,255,255,255), osFont, "G");
        draw->drawstring(x + 55, y + 325, Color(255,255,255,255), tFont, "Colors");
        
        this->renderColors(x + 60, y);
        
    }
    
    if(col.menu == 0)
        MainColor = Orang;
    else if(col.menu == 1)
        MainColor = Green;
    else if(col.menu == 2)
        MainColor == Blu;
    
    this->renderConfigs(x + 25, y + h - 56);
    
    config->getConfig(cfg.cfgcombo);
    
    if(!vars.cfgInit) {
        skins_cfg->LoadSkins();
        config->LoadConfig();
        vars.cfgInit = true;
    }
    
    if(cfg.loadconfig) {
        skins_cfg->LoadSkins();
        config->LoadConfig();
    }

    if(cfg.saveconfig) {
        config->SaveConfig();
    }
    
    draw->MoveMenu(x, y, w, hh, 0);    // Drag tabs menu
    
    Pressed(MOUSE_LEFT);
    
}

