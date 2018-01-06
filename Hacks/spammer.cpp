#include "spammer.h"

vector<string> spamMessages = {
    "WOAH!!!",
    "HOES MAD",
    "sieg heil",
    "vlone.cc",
};


void MakeSpammer(float frameTime) {
    
    if (!pEngine->IsInGame())
        return;
    
    if (!vars.misc.spammer)
        return;
    
    long currentTime_ms = GetEpochTime();
    static long timeStamp = currentTime_ms;
    
    if (currentTime_ms - timeStamp < 500)
        return;
        
    if (spamMessages.empty())
        return;
        
    string message =spamMessages[rand() % spamMessages.size()];
        
    pstring str;
    str << "say" << " ";
    str << message;
        
        
    pEngine->ExecuteClientCmd(str.c_str());
    
    timeStamp = currentTime_ms;
}
