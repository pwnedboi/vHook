#include "main.h"
#include "../Hacks/clantag.h"
#include "../Hacks/autowall.h"
#include "walkbot.h"
#include "../Hacks/EnginePrediction.h"

Vector tpangles;
Vector atTargets;
vector<int64_t> aimbotfriends = { };

bool* bSendPacket = nullptr;

enum VIEW_ANTIAIM_PITCH {
    Emotion = 1,
    Up = 2,
    Down = 3,
    Fakedown = 4,
    Custom = 5
};

enum VIEW_ANTIAIM_YAW {
    Backwards = 1,
    Jitter = 2,
    FJitter = 3,
    SlowSpin = 4,
    FastSpin = 5,
    LowerYaw = 6,
    SidewaysLeft = 7,
    SidewaysRight = 8,
    CustomAA = 9
};


int last = 0;
auto MakeAntiAim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket) -> void {
    
    if(!vars.misc.enabled)
        return;
    
    static bool fakeswitch = false;
    static bool bFlip = false;
    bFlip = !bFlip;
    bool bAttack = true;
    
    if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
        bAttack = false;
        
    if(cmd->buttons & IN_ATTACK && (bAttack)) {
            
        bPacket = true;
            
    } else {
            
        bPacket = true;
            
        if (vars.misc.fakeaa) {
                
            fakeswitch = !fakeswitch;
                
            if (fakeswitch)
                bPacket = false;
            else bPacket = true;
                        
        }

        if(vars.misc.aaX > 0) {
                
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Emotion) {
                cmd->viewangles.x = 82;
            }
                
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Up) {
                cmd->viewangles.x = -89;
            }
                
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Down) {
                cmd->viewangles.x = 179;
            }
            
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Fakedown) {
                cmd->viewangles.x = 180;
            }
                
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Custom) {
                if(bPacket)
                    cmd->viewangles.x = 89;
                else
                    cmd->viewangles.x = vars.misc.customaa;
            }
                
        }
            
        if(vars.misc.aaY > 0) {
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Jitter) {
                static bool bjitter;
                cmd->viewangles.y = bjitter ? 90 : -90;
                bjitter = !bjitter;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::FJitter) {
                
                if(fakeswitch) cmd->viewangles.y = 90; else cmd->viewangles.y = local->GetLowerBodyYawTarget();
                
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SlowSpin) {
                if(fakeswitch) cmd->viewangles.y = 46; else cmd->viewangles.y = atTargets.y;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::FastSpin) {
                if(fakeswitch) cmd->viewangles.y = 46; else cmd->viewangles.y = atTargets.y;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LowerYaw) { // Twist.
                    
                static int fakeTick = 0;
                fakeTick++;
                    
                if (vars.misc.fakeaa) {
                        
                    if (!bSendPacket) {
                            
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        if (fakeTick > 600)
                            fakeTick = 0;
                                
                    } else {
                        cmd->viewangles.y += 180.f;
                    }
                } else {
                    cmd->viewangles.y += 180.f;
                }
                
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SidewaysLeft) {
                if(fakeswitch)
                    cmd->viewangles.y = 90;
                else
                    cmd->viewangles.y = atTargets.y;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SidewaysRight) {
                if(fakeswitch)
                    cmd->viewangles.y = -90;
                else
                    cmd->viewangles.y = atTargets.y;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SidewaysRight) {
                if(fakeswitch)
                    cmd->viewangles.y = -90;
                else
                    cmd->viewangles.y = atTargets.y;
            }
                
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::CustomAA) {
                if(bPacket) {
                    cmd->viewangles.y = vars.misc.fakeyaw;
                }
                else {
                    cmd->viewangles.y = vars.misc.realyaw;
                }
                
            }
        
            
        }
        
    }
    
}

/* No Recoil */
auto MakeNoRecoil(C_BaseEntity* local, CUserCmd* cmd) -> void {
    if(!vars.misc.enabled)
        return;
    
    if(!vars.misc.norecoil)
        return;
    
    if(cmd->buttons & IN_ATTACK) {
        Vector localVec = local->GetPunchAngles() * 2.f;
        
        cmd->viewangles.x -= localVec.x;
        cmd->viewangles.y -= localVec.y;
    }
}

auto LegitRecoil(C_BaseEntity* local, CUserCmd* cmd) -> void {
    if(!vars.misc.enabled)
        return;
    
    if(!vars.aimbot.rcs)
        return;
    
    if(cmd->buttons & IN_ATTACK) {
        Vector localVec = local->GetPunchAngles() * 2.f;
        
        cmd->viewangles.x -= localVec.x * (2.f / 100.f * vars.aimbot.rcsf);;
        cmd->viewangles.y -= localVec.y * (2.f / 100.f * vars.aimbot.rcsf);;
    }
}

string GetLocalName() {
    player_info_t localInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &localInfo);
    return localInfo.name;
}

void ChangeName(const char* szName) {
    ConVar* cvar_name = pCvar->FindVar("name");
    *(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
    cvar_name->SetValue(szName);
}

float GetFOV(Vector start, Vector src, Vector dst) {
    Vector ang, aim;
    ang = CalcAngle(src, dst);
    AngleVectors(start, &aim);
    AngleVectors(ang, &ang);
    
    float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
    float mag_d = mag_s;
    float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
    float fov = acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI_F);
    return fov;
}

float GetFov(Vector viewAngle, Vector playerHeadPosition, Vector entityHeadPosition) {
    Vector ang, aim;
    
    AngleVectors(viewAngle, &aim);
    Vector newAngles = CalcAngle(playerHeadPosition, entityHeadPosition);
    AngleVectors(newAngles, &ang);
    
    return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

auto MakeAutoPistolas(CUserCmd* cmd, C_BaseCombatWeapon* weapon) -> void {
    if(!vars.aimbot.autopistol) return;
    if(!weapon->IsPistol()) return;
    if (cmd->buttons & IN_ATTACK) {
        static bool bAttack = false;
        if (bAttack)
            cmd->buttons |= IN_ATTACK;
            else
            cmd->buttons &= ~IN_ATTACK;
            bAttack = !bAttack;
      }
}



auto MakeHitscan(C_BaseEntity* entity, C_BaseCombatWeapon* weapon, CUserCmd* cmd) -> int {
    
    //C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    vector<int> hitboxes;
    
    hitboxes.push_back((int)CSGOBones::Head);
    hitboxes.push_back((int)CSGOBones::Neck);
    hitboxes.push_back((int)CSGOBones::Neck_Lower);
    hitboxes.push_back((int)CSGOBones::Pelvis);
    hitboxes.push_back((int)CSGOBones::Stomach);
    hitboxes.push_back((int)CSGOBones::Lower_Chest);
    hitboxes.push_back((int)CSGOBones::Chest);
    hitboxes.push_back((int)CSGOBones::Upper_Chest);
    hitboxes.push_back((int)CSGOBones::Right_Thigh);
    hitboxes.push_back((int)CSGOBones::Left_Thigh);
    hitboxes.push_back((int)CSGOBones::Right_Shin);
    hitboxes.push_back((int)CSGOBones::Left_Shin);
    hitboxes.push_back((int)CSGOBones::Right_Foot);
    hitboxes.push_back((int)CSGOBones::Left_Foot);
    
    if(vars.aimbot.hitscan) {
        for(auto hit : hitboxes) {
            Vector vDest = GetHitboxPosition(entity, hit);
            float flDmg = 0.f;
            //if(Autowall::GetDamage(vDest, true, flDmg)) {
             //   return hit;
            //}
        }
    } else {
        return vars.aimbot.bone;
    }
    return (int)CSGOBones::Chest;
}

Vector ExtrapolateTick( Vector p0, Vector v0 ) {
    return p0 + ( v0 * pGlobals->interval_per_tick );
}

Vector C_BaseEntity::GetPredicted( Vector p0 ) {
    return ExtrapolateTick( p0, this->GetVelocity() );
}

Vector C_BaseEntity::GetPredicted(int hitbox) {
    return ExtrapolateTick(GetHitboxPosition(this, hitbox), this->GetVelocity());
}

Vector Smooth(Vector& angle) {
    
    if(!vars.aimbot.enabled)
        return;
    
    if(!vars.aimbot.smooth)
        return;
    
    if(vars.aimbot.silent)
        return;
    
    if(vars.aimbot.silent && vars.aimbot.smooth)
        vars.aimbot.smooth = false;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAngles(delta);
 
    float smooth = powf(vars.aimbot.smoothf, 0.4f);
    smooth = min(0.99f, smooth);
    
    Vector toChange = delta - delta * smooth;
    
    return angle = viewAngles + toChange;
    
}

C_BaseCombatWeapon* GetWeapon(C_BaseEntity* local) {
    auto hWeapon = local->GetActiveWeapon();
    if (!hWeapon)
        return nullptr;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(hWeapon);
}

bool getDamage(Vector & vecPoint, float* Damage) {
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    Vector dst = vecPoint;
    FireBulletData data;
    data.src = local->GetEyePosition();
    data.filter.pSkip = local;
    
    Vector angles;
    angles = CalcAngle(data.src, dst);
    AngleVectors(angles, &data.direction);
    Vector dataNormalized;
    
    VectorNormalize(data.direction);
    
    C_BaseCombatWeapon* pWeap = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(local->GetActiveWeapon());
    if (SimulateFireBullet(pWeap, true, data)) {
        *Damage = data.current_damage;
        return true;
    }
    
    return false;
}

C_BaseEntity* findt(C_BaseEntity* local) {
    
}

Vector Spiral(C_BaseEntity* local, Vector vTo) {
    
    Vector viewangles = Vector(0, 0, 0);
    pEngine->GetViewAngles(viewangles);
    
    Vector delta = vTo - viewangles;
    NormalizeAngles(delta);
    
    vec_t x = delta.x / vars.aimbot.spiralx;
    vec_t y = delta.y / vars.aimbot.spiraly;
    
    delta = delta + Vector(x, y, 0.0f);
    delta = delta / vars.aimbot.smoothf;
    
    vTo = viewangles + delta;
    
    return vTo;
}


auto MakeAimbot(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide, bool& bSendPacket) -> void {
    
    Vector eyepos = local->GetEyePosition();
    
    if(!vars.aimbot.enabled)
        return;
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++) {
        
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        Vector vFrom, vTo;
        
        vFrom = GetHitboxPosition(entity, MakeHitscan(entity, weapon, pCmd)); // Bone
        vFrom = GetHitboxPos(entity, vars.aimbot.hitbox); // Hitbox
        
        if(vars.aimbot.selfpred)
            eyepos += entity->GetVelocity() * pGlobals->interval_per_tick;
            
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
            
        atTargets = vTo;
        float getdmg = 0.f;
        
        if(vars.aimbot.autowall ? getDamage(vFrom, &getdmg) || isVISIBLE : isVISIBLE) {
            
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) < vars.aimbot.fov) {
                
                if(vars.aimbot.autoshoot)
                    pCmd->buttons |= IN_ATTACK;
                
                if(vars.aimbot.autostop) {
                    flForward = 0.f;
                    flSide = 0.f;
                }
                
                if(vars.aimbot.autocrouch)
                    pCmd->buttons |= IN_DUCK;
                
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(vars.aimbot.psilent) {
                    if(pCmd->buttons & IN_ATTACK && (bAttack))
                        bSendPacket = false;
                    else
                        bSendPacket = true;
                }
                
                if(vars.aimbot.spiral)
                    pCmd->viewangles = Spiral(local, vTo);
                    
                if(vars.aimbot.smooth && !vars.aimbot.spiral)
                    pCmd->viewangles = Smooth(vTo);
                    
                
                if(pCmd->buttons & IN_ATTACK) {
                    if(!vars.aimbot.silent) {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    } else {
                        pCmd->viewangles = vTo;
                    }
                }
            }
        }
    } 
}

auto RotateMovement(CUserCmd* pCmd, float rotation) -> void{
    
    rotation = DEG2RAD(rotation);
    
    float cos_rot = cos(rotation);
    float sin_rot = sin(rotation);
    
    float new_forwardmove = (cos_rot * pCmd->forwardmove) - (sin_rot * pCmd->sidemove);
    float new_sidemove = (sin_rot * pCmd->forwardmove) + (cos_rot * pCmd->sidemove);
    
    pCmd->forwardmove = new_forwardmove;
    pCmd->sidemove = new_sidemove;
}

int CircleFactor = 0;
auto doCircularStrafe(CUserCmd* pCmd, C_BaseEntity* local, Vector& OriginalView) -> void {
    
    if (!vars.misc.circlestrafe)
        return;
    
    if (!local)
        return;
    
    CircleFactor++;
    if (CircleFactor > 361)
        CircleFactor = 0;
    
    int GetItDoubled = 3.0 * CircleFactor - pGlobals->interval_per_tick;
        
    pCmd->viewangles = OriginalView;
    RotateMovement(pCmd, GetItDoubled);
    
}

void CircleStrafer(CUserCmd* pCmd, C_BaseEntity* local, Vector& OldAngle) {
    
    if (!vars.misc.circlestrafe)
        return;
    
    if (!local)
        return;
    
    static int Angle = 0;
    
    if(OldAngle.y - Angle > 360)
        Angle -= 360;
    
    static bool shouldspin = false;
    static bool enabled = false;
    static bool check = false;
    
    if(pInputSystem->IsButtonDown((ButtonCode_t)vars.misc.cStrafeKey)) {
        if(!check)
            enabled = !enabled;
        check = true;
    }
    else
        check = false;
    
    if(enabled)
        shouldspin = true;
    
    if(shouldspin) {
        
        Vector Dir;
        AngleVectors(Vector(0, Angle, 0), &Dir);
        Dir *= 8218;
        Ray_t ray;
        CTraceFilterWorldOnly filter;
        trace_t trace;
        ray.Init(local->GetEyePosition(), local->GetVecOrigin() + Dir);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        auto temp = 3.4f / ((trace.endpos - local->GetVecOrigin()).Length() / 100.f);
        
        if(temp < 3.4f)
            temp = 3.4f;
        if(enabled) {
            Angle += temp;
            pCmd->sidemove = -450;
        } else {
            if( OldAngle.y - Angle < temp ) {
                Angle = OldAngle.y;
                shouldspin = false;
            }
            else
                Angle += temp;
        }
        OldAngle.y = Angle;
    }
    else
        Angle = OldAngle.y;
}





auto MakeAutoStrafer(CUserCmd* cmd, C_BaseEntity* local) -> void {
    
    if(!vars.misc.enabled)
        return;
    
    if(!vars.misc.autostrafe)
        return;
    
    if (cmd->buttons & IN_JUMP && !(local->GetFlags() & FL_ONGROUND)) {
        if (local->GetVelocity().Length2D() == 0 && (cmd->forwardmove == 0 && cmd->sidemove == 0)) {
            cmd->forwardmove = 450.f;
        } else if (cmd->forwardmove == 0 && cmd->sidemove == 0) {
            if (cmd->mousedx > 0 || cmd->mousedx < -0) {
                cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
            } else {
                float temp1 = 5850.f / local->GetVelocity().Length2D();
                cmd->forwardmove = temp1;
                if (cmd->forwardmove > 450)
                    cmd->forwardmove = 450;
                float temp = 450 - (temp1 - cmd->forwardmove);
                if (temp < 450)
                    temp = 450;
                cmd->sidemove = (cmd->command_number % 2) == 0 ? -temp : temp;
            }
        }
    }
}

void ClampMoves(float& flForward, float& flSide, float& flUp) {
    if(flForward > 450) flForward = 450;
    if(flSide > 450) flSide = 450;
    if(flUp > 450) flUp = 450;
    if(flForward < -450) flForward = -450;
    if(flSide < -450) flSide = -450;
    if(flUp < -450) flUp = -450;
}

auto MakeBhop(CUserCmd* cmd, C_BaseEntity* local) -> void {
    if(!vars.misc.enabled) return;
    if(!vars.misc.bhop) return;
    
    static bool shouldJump = false;
    static bool shouldFake = false;
    
    if (shouldFake && !shouldJump) {
        cmd->buttons |= IN_JUMP;
        shouldFake = false;
    }
    else if (cmd->buttons & IN_JUMP) {
        if (local->GetFlags() & FL_ONGROUND) {
            shouldFake = false;
            shouldJump = false;
            
        }
        else {
            cmd->buttons &= ~IN_JUMP;
            shouldJump = false;
        }
    }
    else {
        shouldJump = false;
        shouldFake = false;
    }
}

void MakeAirstuck(CUserCmd* cmd) {
    
    return;
    
    if (!vars.misc.airstuck)
        return;
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
        return;
    
    if (pInputSystem->IsButtonDown((ButtonCode_t)vars.misc.airstuckKey))
        cmd->tick_count = 16777216;
}

static int ticks = 0;
int ticksMax = 16;

void MakeFakeLag(CUserCmd* cmd, bool& sendPacket) {
    
    return;
    
    if (!vars.misc.fakelag)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;
    
    if (localplayer->GetFlags() & FL_ONGROUND && vars.misc.adaptive)
        return;
    
    if (cmd->buttons & IN_ATTACK) {
        sendPacket = true;
        return;
    }
    
    if (ticks >= ticksMax) {
        sendPacket = true;
        ticks = 0;
    } else {
        
        if (vars.misc.adaptive) {
            
            int packetsToChoke;
            
            if (localplayer->GetVelocity().Length() > 0.f)
            {
                packetsToChoke = (int)((64.f / pGlobals->interval_per_tick) / localplayer->GetVelocity().Length()) + 1;
                if (packetsToChoke >= 15)
                    packetsToChoke = 14;
                if (packetsToChoke < vars.misc.fakelagfactor)
                    packetsToChoke = vars.misc.fakelagfactor;
            } else {
                packetsToChoke = 0;
            }
            
            sendPacket = ticks < 16 - packetsToChoke;
            
        } else {
            sendPacket = ticks < 16 - vars.misc.fakelagfactor;
        }
    }
    ticks++;
}


void MakeTrigger(CUserCmd *Cmd) {
    
    if(!vars.aimbot.trigger)
        return;
    
    if(pInputSystem->IsButtonDown((ButtonCode_t)vars.aimbot.triggerKey)) {
        
        C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if (!LocalPlayer || LocalPlayer->GetHealth() < 0) {
            return;
        }
    
        C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(LocalPlayer->GetActiveWeapon());
        if (!activeWeapon || activeWeapon->GetAmmo() == 0)
            return;
        
        
        Vector traceStart, traceEnd;
        
        Vector viewAngles;
        pEngine->GetViewAngles(viewAngles);
        Vector viewAngles_rcs = viewAngles + (LocalPlayer->GetPunchAngles() * 2.0f);
        
        AngleVectors(viewAngles_rcs, &traceEnd);
        
        traceStart = LocalPlayer->GetEyePosition();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t trace;
        CTraceFilter filter;
        filter.pSkip = LocalPlayer;
        
        ray.Init(traceStart, traceEnd);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        
        if (trace.allsolid || trace.startsolid) {
            return;
        }
        
        C_BaseEntity* player = (C_BaseEntity*)trace.m_pEnt;
        if(!player || player->GetHealth() < 0 || player->GetImmune()) {
            return;
        }
        
        if(player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer) {
            return;
        }
        
        if(LocalPlayer->GetTeam() == player->GetTeam()) {
            return;
        }
        
        if (activeWeapon->GetNextPrimaryAttack() > pGlobals->curtime) {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER) {
                Cmd->buttons &= ~IN_ATTACK2;
            } else {
                Cmd->buttons &= ~IN_ATTACK;
            }
        } else {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER) {
                Cmd->buttons |= IN_ATTACK2;
            } else {
                Cmd->buttons |= IN_ATTACK;
            }
        }
    }
}

void MakeShowRanks(CUserCmd* cmd) {
    if (!vars.misc.showrank)
        return;
    
    if (!(cmd->buttons & IN_SCORE))
        return;
    
    float input[3] = { 0.f };
    MsgFunc_ServerRankRevealAll(input);
}

auto hacks(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, Vector& vOldAngles, float& flForwardmove, float& flSidemove, bool& sendpacket) -> void {
    
    MakeAutoStrafer(cmd, local);
    
    MakeBhop(cmd, local);
        
    if(vars.aimbot.prediciton)
        CEnginePrediction::Instance()->Start(cmd);

    MakeAimbot(cmd, local, weapon, flForwardmove, flSidemove, sendpacket);  // Add some black magic shit.
    
    MakeAntiAim(cmd, local, weapon, sendpacket);                            // Add antiaims.
    
//    MakeAutoPistolas(cmd, weapon);
    
    MakeNoRecoil(local, cmd);
    
    MakeAirstuck(cmd);
        
    if(vars.aimbot.prediciton)
        CEnginePrediction::Instance()->End();
    
    MakeShowRanks(cmd);
    
    MakeTrigger(cmd);
        
    skeet();
    
    Walk(cmd);
    
    if(vars.aimbot.rcs && !vars.misc.norecoil) {
        LegitRecoil(local, cmd);
    }
    
    if(pInputSystem->IsButtonDown((ButtonCode_t)vars.misc.cStrafeKey))
        CircleStrafer(cmd, local, vOldAngles);
    
        
}
bool bOnce = false;


void ClampYaw(float& angle) {
    while(angle > 180) {
        angle -= 360;
    }
    while(angle < -180) {
        angle += 360;
    }
}


bool SendPacket = true;
bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd) {
    createmovehook->GetOriginalMethod<tCreateMove>(25)(thisptr, flSampleInput, cmd);
    
    if(!cmd->command_number)
        return true;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return false;
    
    if(local->GetLifeState() != 0)
        return false;
    
    if(local->GetHealth() < 1)
        return false;
    
    if(local->GetDormant())
        return false;
    
    if(bSendPacket == nullptr)
        return false;
    
    if(!bOnce) {
        if(draw->m_szCurrentString[2].empty()) {
            draw->m_szCurrentString[2] = GetLocalName();
        }
        bOnce = true;
    }
    
    auto* weapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(local->GetActiveWeapon());
    
    if(!weapon)
        return false;

    SendPacket = true;
    *bSendPacket = SendPacket;
    
    
    Vector vOldAngles = cmd->viewangles;
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    Vector qAimAngles;
    
    float forward = cmd->forwardmove;
    float sidemove = cmd->sidemove;
    float upmove = cmd->upmove;
    
    if(pEngine->IsInGame() && pEngine->IsConnected()) {
        
        hacks(cmd, local, weapon, vOldAngles, forward, sidemove, *bSendPacket);
        
        if(!vars.misc.antiuntrust)
            ClampYaw(cmd->viewangles.y);
        
        FixMovement(vOldAngles, cmd);
        ClampMoves(forward, sidemove, upmove);
        
        if(vars.misc.enabled && vars.misc.antiuntrust) {
            cmd->viewangles.ClampAngles();
        }
        
        if(*bSendPacket)
        tpangles = cmd->viewangles;
    }
    return false;
}
