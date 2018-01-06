//
//  menu.h
//  vHook
//

#include "../main.h"

typedef int tabsize;

class cMenu
{
public:
    
    void renderCheckbox(int x, int y, const char* str, bool* var); // With string
    void renderCheckbox(int x, int y, bool *var); // Without string
    void renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min); // int
    void renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min); // float
    void colorSlider(int x, int y, Color color, int var);
    void renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend);
    void renderButton(int x, int y, const char* szString, bool* var);
    void playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString);
    
    void Border(int x, int y, int thickness, const char* str);
    
    
    void renderMenu();
    void renderConfigs(int x, int y);
    void renderAim(int x, int y);
    void renderVis(int x, int y);
    void renderMisc(int x, int y);
    void renderPlayer(int x, int y);
    void renderColors(int x, int y);
    void renderAntiAim(int x, int y);

    
};

extern cMenu* menu;

class menuT
{
public:
    
    tabsize w, h;
    
    bool quit = false;
    
    int tab = 1;
    
    bool aimtab     = false;
    bool vistab     = false;
    bool misctab    = false;
    bool playertab  = false;
    bool colorstab  = false;
    bool aatab      = false;
    
    int colTab  = 0;
    int aimtype = 0;
    
    bool tcolor     = false;
    bool ctcolor    = false;
    bool othercolor = false;
    
};

class colors
{
public:
    
    int menu = 1;
    
};


void setupConfig();
