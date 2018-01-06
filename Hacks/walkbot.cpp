#include "walkbot.h"

static unsigned int rally;
static bool reachedEnd;
static bool hasAutobought;
static bool hasDied;
static bool found;

// CT
const vector<Vector> CTbombsiteB = {
    Vector(272,2155,-63.29),
    Vector(-643,2194,-57.11),
    Vector(-1178,2201,70.48),
    Vector(-1284,2142,66.78),
    Vector(-1365,2274,66.92),
    Vector(-1771,2157,74.80),
    Vector(-2054,2165,71.13),
    Vector(-1982,1755,96.09),
    Vector(-1980,1320,96.09),
    Vector(-1660,1041,96.09),
    Vector(-1907,-784,195.31),
    Vector(-467,-778,186.43),
    Vector(162,-732,66.63),
    Vector(391,48,70.85),
    Vector(0,384,66.67),
    Vector(-160,402,66.48),
    Vector(-177,1320,64.09),
    Vector(326,1559,64.09),
    Vector(345,1818,160.09),
    Vector(390,2487,160.09),
    Vector(1141,2675,160.9),
};

const vector<Vector> CTshortA = {
    Vector(272,2155,-63.29),
    Vector(1437,2176,72.29),
    Vector(1307,2797,195.80),
    Vector(389,2383,160.09),
    Vector(352,1450,64.09),
    Vector(-160,1431,64.09),
    Vector(-162,397,66.62),
    Vector(348,237,72.64),
    Vector(285,-769,68.00),
};

const vector<Vector> CTlongA = {
    Vector(272,2155,-63.29),
    Vector(1306,2144,68),
    Vector(1316,1357,66),
    Vector(1400,1161,65),
    Vector(1145,607,66),
    Vector(884,932,66),
    Vector(587,692,65),
    Vector(704,333,67),
    Vector(400,37,70),
};

// T
const vector<Vector> TshortA =  {
    Vector(285,-769,68.00),
    Vector(348,237,72.64),
    Vector(-160,417,66.38),
    Vector(-160,1431,64.09),
    Vector(352,1450,64.09),
    Vector(389,2383,160.09),
    Vector(1307,2797,195.80),
};

const vector<Vector> TlongA = {
    Vector(285,-769,68.00),
    Vector(291,-2,80),
    Vector(668,319,68),
    Vector(571,712,65),
    Vector(830,870,65),
    Vector(1426,1044,67),
    Vector(1392,1764,67),
    Vector(1379,2384,91),
    Vector(1307,2797,195.80),
    Vector(1091,2579,160),
};


C_BaseEntity* local;

void inline Reset() {
    if(reachedEnd || vars.walk.forceReset || hasDied){
        rally = 0;
        reachedEnd = false;
        vars.walk.forceReset = false;
        hasDied = false;
        found = false;
    }
}

void drawMarker(const vector<Vector> points) {
    
    Vector pos;
    Vector top  = points[rally]; // Rally point
    
    // Top
    Vector t1   = Vector(top.x, top.y, top.z);      // start    1 > 2, 2 > 3, 3 > 4, 4 > 1
    Vector t2   = Vector(top.x + 5, top.y, top.z);  // Right
    Vector t3   = Vector(top.x + 5, top.y + 5, top.z);
    Vector t4   = Vector(top.x, top.y + 5, top.z);  //
    
    // Bottom
    Vector b1   = Vector(top.x, top.y, top.z - 50);
    Vector b2   = Vector(top.x + 5, top.y, top.z - 50);
    Vector b3   = Vector(top.x + 5, top.y + 5, top.z - 50);
    Vector b4   = Vector(top.x, top.y + 5, top.z - 50);
    
    // Top
    pOverlay->AddLineOverlay(t1, t2, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t2, t3, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t3, t4, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t4, t1, 250, 5, 5, false, 0.1f);
    
    // Bottom
    pOverlay->AddLineOverlay(b1, b2, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(b2, b3, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(b3, b4, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(b4, b1, 250, 5, 5, false, 0.1f);
    
    // Top to bottom / middle
    pOverlay->AddLineOverlay(t1, b1, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t2, b2, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t3, b3, 250, 5, 5, false, 0.1f);
    pOverlay->AddLineOverlay(t4, b4, 250, 5, 5, false, 0.1f);
    
}

int index(const vector<Vector>& vec, Vector key) {
    
    for(int i = 0; i < vec.size(); ++i) {
        if(vec[i] == key)   //key found at index i
            return i;
    }
    
    return -1;   //key not found
}

void closestPoint(C_BaseEntity* local, const vector<Vector> point) {
    
    if(found)
        return;
    
    Vector start;
    Vector closest = Vector(0,0,0);
    Vector curPos = local->GetEyePosition();
    
    for(int i = 0; i < point.size(); i ++) {
        
        if((curPos.x - closest.x) > (curPos.x - point[i].x))
            closest = closest;
        else
            closest = point[i];
        
    }
    
    int vecPos = index(point, closest);
    draw->drawstring(10, 50, Color::Magenta(), espfont, to_string(vecPos).c_str());
    rally = vecPos;
    found = true;
    
}


bool DoRally(const vector<Vector> points, CUserCmd *cmd) { // return true if rally is completed.

    if(reachedEnd)
        return true;
    
    if((abs(local->GetEyePosition().x - points[rally].x) < 5.f) && (abs(local->GetEyePosition().y - points[rally].y) < 5.f)) {
        
        if(rally == points.size() - 1){
            
            if(!reachedEnd){
                pCvar->ConsoleDPrintf("Reached point #%d\n", rally);
                pCvar->ConsoleColorPrintf(Color(50, 200, 100), "Finished Rally Points!\n");
                pEngine->ExecuteClientCmd("say Finished Rally Points!");
                reachedEnd = true;
            }
            return true; // Finished Walking
        }
        
        rally++;
    }
    
    Vector move = CalcAngle(local->GetEyePosition(), points[rally]);
    
    cmd->forwardmove = 250.0f;
    cmd->sidemove = 0;
    cmd->buttons |= IN_WALK;
    
    CorrectMovement(move, cmd, cmd->forwardmove, cmd->sidemove);
    return false;
    
}

void Walk(CUserCmd *cmd) {
    
    local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    TeamID ourTeam = (TeamID)local->GetTeam();
    
    if (!local || !pEngine->IsInGame() || vars.walk.forceReset || !vars.walk.walk || pInputSystem->IsButtonDown(KEY_COMMA)) {
        vars.walk.forceReset = true;
        Reset();
        return;
    }
    
    if(!local->GetAlive()){
        if( ourTeam == TeamID::TEAM_UNASSIGNED ){
            pEngine->ExecuteClientCmd("teammenu");
            return;
        } else {
            hasDied = true;
            hasAutobought = false;
            return;
        }
    }
    
    if(ourTeam == TEAM_COUNTER_TERRORIST && vars.walk.CTroute == 0) {
        drawMarker(CTshortA);
        //closestPoint(local, CTshortA);
        DoRally(CTshortA, cmd);
    } else if(ourTeam == TEAM_COUNTER_TERRORIST && vars.walk.CTroute == 1) {
        drawMarker(CTbombsiteB);
        DoRally(CTbombsiteB, cmd);
    } else if(ourTeam == TEAM_COUNTER_TERRORIST && vars.walk.CTroute == 2) {
        drawMarker(CTlongA);
        DoRally(CTlongA, cmd);
    } else if(ourTeam == TEAM_TERRORIST && vars.walk.Troute == 0) {
        drawMarker(TshortA);
        DoRally(TshortA, cmd);
    } else if(ourTeam == TEAM_TERRORIST && vars.walk.Troute == 1) {
        drawMarker(TlongA);
        DoRally(TlongA, cmd);
    }

}
