#include "main.h"
#include "Config.h"

int hkKeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding) {
    
    if(eventcode == 0) { // Pressed.
        if(keynum == KEY_INSERT || keynum == KEY_LALT || keynum == KEY_RALT ) {
            vars.menu = !vars.menu;
            
            if(vars.menu) {
                pEngine->ExecuteClientCmd("cl_mouseenable 0");
            } else {
                pEngine->ExecuteClientCmd("cl_mouseenable 1");
            }
        }
    }
    
    if(eventcode == 1) { // Released.
        if(vars.menu && (vars.misc_clantag || vars.misc_name || vars.misc_changename)) {
            draw->handleinput(keynum, draw->m_szCurrentString);
            return 0;
        }
    }
    
    return clientvmt->GetOriginalMethod<tKeyEvent>(20)(thisptr, eventcode, keynum, currentbinding);
    
}




