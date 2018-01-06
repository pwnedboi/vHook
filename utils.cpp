#include "main.h"

void SinCos(float radians, float *sine, float *cosine)
{
    double __cosr, __sinr;
    __asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));
    
    *sine = __sinr;
    *cosine = __cosr;
}

Vector CalcAngle(Vector src, Vector dst) {
    
    Vector delta, angles;
    delta.x = (src.x - dst.x);
    delta.y = (src.y - dst.y);
    delta.z = (src.z - dst.z);
    
    double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
    
    angles.x = (float)(atanf(delta.z / hyp) * M_RADPI);
    angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);
    
    angles.z = 0.0f;
    if (delta.x >= 0.0) { angles.y += 180.0f; }
    return angles;
}

void AngleVectors(const Vector & angles, Vector * forward) {
    Assert(s_bMathlibInitialized);
    Assert(forward);
    
    float	sp, sy, cp, cy;
    
    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));
    
    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));
    
    forward->x = cp*cy;
    forward->y = cp*sy;
    forward->z = -sp;
}

void AngleVectors(const Vector & angles, Vector * forward, Vector * right, Vector * up) {
    float angle;
    static float sr, sp, sy, cr, cp, cy;
    
    angle = angles[1] * (M_PI * 2 / 360);
    sy = sin(angle);
    cy = cos(angle);
    
    angle = angles[0] * (M_PI * 2 / 360);
    sp = sin(angle);
    cp = cos(angle);
    
    angle = angles[2] * (M_PI * 2 / 360);
    sr = sin(angle);
    cr = cos(angle);
    
    if (forward)
    {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }
    if (right)
    {
        right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
        right->y = (-1 * sr*sp*sy + -1 * cr*cy);
        right->z = -1 * sr*cp;
    }
    if (up)
    {
        up->x = (cr*sp*cy + -sr*-sy);
        up->y = (cr*sp*sy + -sr*cy);
        up->z = cr*cp;
    }
}

void VectorAngles(const Vector& forward, Vector &angles) {
    float	tmp, yaw, pitch;
    
    if (forward[1] == 0 && forward[0] == 0)
    {
        yaw = 0;
        if (forward[2] > 0)
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;
        
        tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
        pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
        if (pitch < 0)
            pitch += 360;
    }
    
    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}

void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
    // side/forward move correction
    float deltaView;
    float f1;
    float f2;
    
    if (vOldAngles.y < 0.f)
        f1 = 360.0f + vOldAngles.y;
    else
        f1 = vOldAngles.y;
    
    if (pCmd->viewangles.y < 0.0f)
        f2 = 360.0f + pCmd->viewangles.y;
    else
        f2 = pCmd->viewangles.y;
    
    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);
    
    deltaView = 360.0f - deltaView;
    
    pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

bool WorldToScreen(Vector& vFrom, Vector& vTo) {
    return (pOverlay->ScreenPosition(vFrom, vTo) != 1);
}



bool DrawPlayerBox(C_BaseEntity* pEntity, boxstruct& str) // Credit's to dude719 & keybode.
{
    if (!pEntity)
        return false;
    
    Vector vOrigin = pEntity->GetVecOrigin(); // Not sure if this is the right one...
    Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] = { Vector(min.x, min.y, min.z),
                        Vector(min.x, max.y, min.z),
                        Vector(max.x, max.y, min.z),
                        Vector(max.x, min.y, min.z),
                        Vector(max.x, max.y, max.z),
                        Vector(min.x, max.y, max.z),
                        Vector(min.x, min.y, max.z),
                        Vector(max.x, min.y, max.z) };
    
    /*
     .6-------5                     blb = 0
     .' |       .' |                brb = 1
     7---+--4'   |      0 = min     frb = 2
     |   |    |    |    4 = max     flb = 3
     y |  ,0---+---1                frt = 4
     |.'       | .'  z              brt = 5
     3------2                       blt = 6
     x                              flt = 7
     
     blt------brt           blt = back-left-top
     .' |        .'|        brt = back-right-top
     flt---+--frt  |        brb = back-right-bottom
     |   |     |   |        blb = back-left-bottom
     y |  blb---+--brb      flt = front-left-top
     |.'        | .'  z     frt = front-right-top
     flb------frb           frb = front-right-bottom
     x                      flb = front-left-bottom
     
     */
    
    Vector flb;
    Vector brt;
    Vector blb;
    Vector frt;
    Vector frb;
    Vector brb;
    Vector blt;
    Vector flt;
    
    
    if (!WorldToScreen(points[3], flb) || !WorldToScreen(points[5], brt)
        || !WorldToScreen(points[0], blb) || !WorldToScreen(points[4], frt)
        || !WorldToScreen(points[2], frb) || !WorldToScreen(points[1], brb)
        || !WorldToScreen(points[6], blt) || !WorldToScreen(points[7], flt))
        return false;
    
    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left = flb.x;     // left
    float top = flb.y;      // top
    float right = flb.x;    // right
    float bottom = flb.y;   // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    /*
     
     
               ^
               |
              TOP
     
     <-- LEFT      RIGHT -->
     
             BOTTOM
               |
               v
     
     
     
     */
    
    str.x = left;
    str.y = top;
    str.w = right - left;
    str.h = bottom - top;
    return true;
}

void Normalize(Vector & vIn, Vector & vOut) {
    float flLen = vIn.Length();
    if (flLen == 0) {
        vOut.Init(0, 0, 1);
        return;
    }
    flLen = 1 / flLen;
    vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

void NormalizeVector(Vector& vecIn) {
    for (int axis = 0; axis < 3; ++axis)
    {
        while (vecIn[axis] > 180.f)
            vecIn[axis] -= 360.f;
        
        while (vecIn[axis] < -180.f)
            vecIn[axis] += 360.f;
        
    }
    
    vecIn[2] = 0.f;
}

void NormalizeAngles(Vector& angle) {
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}

void ClampAngles(Vector& angle) {
    if (angle.y > 180.0f)
        angle.y = 180.0f;
    else if (angle.y < -180.0f)
        angle.y = -180.0f;
    
    if (angle.x > 89.0f)
        angle.x = 89.0f;
    else if (angle.x < -89.0f)
        angle.x = -89.0f;
    
    angle.z = 0;
}


void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out) {
    out.x = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
    out.y = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
    out.z = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}

Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox) {
    matrix3x4_t matrix[128];
    
    if (!pEntity->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->pHitboxSet(0);
    
    mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    
    if(vars.aimbot.pointscale != 101) {
        float ptwoz = 50 - vars.aimbot.pointscale;
        float zval = (ptwoz*vMin.z + vars.aimbot.pointscale*vMax.z) / 50;
        vCenter.z = zval;
    }
    return vCenter;
}

bool IsVisible(C_BaseEntity* local, C_BaseEntity* entity) {
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = local;
    
    ray.Init(local->GetEyePosition(), entity->GetEyePosition());
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

bool IsVisible(C_BaseEntity* localPlayer, Vector position, bool exact) {
    
    if(localPlayer->GetHealth() < 1)
        return;
    
    trace_t tr;
    Ray_t ray;
    CTraceFilter filter;
    filter.pSkip = localPlayer;
    
    ray.Init(localPlayer->GetEyePosition(), position);
    uint32_t RayMask = MASK_SHOT;
    pEngineTrace->TraceRay(ray, RayMask, &filter, &tr);
    
    if (tr.allsolid || tr.startsolid)
        return false;
    
    float maxFraction = tr.fraction > 0.99f;
    
    if(exact)
        maxFraction = tr.fraction >= 1.f;
    
    if (tr.m_pEnt)
        if (tr.m_pEnt == localPlayer || maxFraction)
            return true;
    
    if (tr.fraction >= 1.0f)
        return true;

    
    return false;
}

void FixMovement(Vector& oang, CUserCmd* pCmd) {
    Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    Vector vMove2;
    VectorAngles(vMove, vMove2);
    
    flYaw = DEG2RAD(pCmd->viewangles.y - oang.y + vMove2.y);
    pCmd->forwardmove = cos(flYaw) * flSpeed;
    pCmd->sidemove = sin(flYaw) * flSpeed;
    
    if (pCmd->viewangles.x < -90.f || pCmd->viewangles.x > 90.f)
        pCmd->forwardmove = -pCmd->forwardmove;
}

long GetEpochTime() {
    auto duration = chrono::system_clock::now().time_since_epoch();
    
    return chrono::duration_cast<chrono::milliseconds>(duration).count();
}

void SetClanTag(const char* tag, const char* name) {
    SetTag(tag, name);
}

string GetWeaponName(C_BaseCombatWeapon* pWeapon) {
    
    int ID = *pWeapon->GetItemDefinitionIndex();
    
    switch (ID) {
            /*pistols*/
        case 4:
            return "Glock";
        case 2:
            return "Dualies";
        case 36:
            return "P250";
        case 30:
            return "Tec 9";
        case 1:
            return "Deagle";
        case 32:
            return "P2000";
        case 3:
            return "Five Seven";
        case 64:
            return "Revolver";
        case 63:
            return "CZ75";
        case 61:
            return "USP";
            /*heavy*/
        case 35:
            return "Nova";
        case 25:
            return "XM1014";
        case 29:
            return "Sawed Off";
        case 14:
            return "M249";
        case 28:
            return "Negev";
        case 27:
            return "Mag 7";
            /*smgs*/
        case 17:
            return "Mac 10";
        case 33:
            return "MP7";
        case 24:
            return "UMP45";
        case 19:
            return "P90";
        case 26:
            return "Bizon";
        case 34:
            return "MP9";
            /*C4*/
        case 49:
            return "C4";
            /*rifles*/
        case 10:
            return "Famas";
        case 16:
            return "M4A1";
        case 40:
            return "Scout";
        case 8:
            return "AUG";
        case 9:
            return "AWP";
        case 38:
            return "Scar 20";
        case 13:
            return "Galil";
        case 7:
            return "AK47";
        case 39:
            return "SG553";
        case 11:
            return "G3SG1";
        case 60:
            return "M4A1-S";
            /*grenades*/
        case 46:
        case 48:
            return "Molotov";
        case 44:
            return "Grenade";
        case 43:
            return "Flash";
        case 45:
            return "Smoke";
        case 47:
            return "Decoy";
            /*other*/
        case 31:
            return "Zeus";
        default:
            return "Knife";
    }
}

Vector GetHitboxPos(C_BaseEntity* pEntity, int Hitbox) {
    
    if (!pEntity)
        return Vector(0, 0, 0);
    
    matrix3x4_t matrix[128];
    
    if (!pEntity->SetupBones(matrix, 128, 0x00000100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    const model_t* mod = pEntity->GetModel();
    
    if (!mod)
        return Vector(0, 0, 0);
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(mod);
    
    if (!hdr)
        return Vector(0, 0, 0);
    
    mstudiohitboxset_t* set = hdr->pHitboxSet(0);
    if (!set)
        return Vector(0, 0, 0);
    
    mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector MIN, MAX, MIDDLE;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], MIN);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], MAX);
    
    MIDDLE = (MIN + MAX) * 0.5f;
    
    return MIDDLE;
}


