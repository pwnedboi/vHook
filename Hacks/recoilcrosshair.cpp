#include "recoilcrosshair.h"

void rCrosshair(C_BaseEntity* local) {
    
    if(!vars.visuals.crosshair)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if(!local)
        return;
    
    if(vars.visuals.crosshair && !vars.aimbot.silent && !(vars.misc.novisualrecoil && vars.misc.norecoil))
        pEngine->ExecuteClientCmd("cl_crosshairsize -1");   // Disables Crosshair
    else
        pEngine->ExecuteClientCmd("cl_crosshairsize 1.8");    // Enables crosshair
    
    static int Height, Width;
    pEngine->GetScreenSize(Width, Height);
    
    Vector punchAngles = local->GetPunchAngles();
        
    int x = Width / 2;
    int y = Height / 2;
    int dy = Height / 90;
    int dx = Width / 90;
    
    int X = x - (dx * punchAngles.y);
    int Y = y + (dy * punchAngles.x);
    
    Color col;
    
    if(vars.colors.cColor == 0)
        col = Color::Green();
    else if(vars.colors.cColor == 1)
        col = Color::Magenta();
    else if(vars.colors.cColor == 2)
        col = Color::White();
    else if(vars.colors.cColor == 3)
        col = Color::Blue();
    else if(vars.colors.cColor == 4)
        col = Color::Red();
    
    if(vars.misc.crosshairType == 0)
        draw->drawCrosshair1(X, Y, col);
    else if(vars.misc.crosshairType == 1)
        draw->drawCrosshair2(X, Y, col);
    else if(vars.misc.crosshairType == 2)
        draw->drawCrosshair3(X, Y, col);

}
