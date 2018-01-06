#include "../main.h"
#include "../Hacks/clantag.h"
#include "../Hacks/spammer.h"

bool CreateMove::sendPacket = false;

void hkBeginFrame(void* thisptr, float frameTime) {
    
    MakeSpammer(frameTime);
    
    if (!pEngine->IsInGame()) {
        CreateMove::sendPacket = true;
        *bSendPacket = CreateMove::sendPacket;
    }
    
    return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
    
}

