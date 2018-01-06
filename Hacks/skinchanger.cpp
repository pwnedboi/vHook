//
// Created by toxicoverflow on 23.02.17.
//

#include "skinchanger.h"
#include "../Config/skins.h"
#include "../Config/Config.h"

int KnifeCT = skin.knifeCT; // Change Knife model here
int KnifeT = skin.knifeT;
int GloveCT = skin.gloveCT;
int GloveT = skin.gloveT;
bool skinsLoaded = false;

// make_pair(WEAPON, cSkin(Go to Skins.h, Seed, -1, Stattrak, (char*)"name", Wear))

unordered_map<int, cSkin> cSkinchanger::Skins = unordered_map<int, cSkin>( {
    
    make_pair( WEAPON_KNIFE,        cSkin( skin.CTknifeID, 0, KnifeCT, -1, nullptr, 0.00000001f ) ),    // kara Saphire
    make_pair( WEAPON_KNIFE_T,      cSkin( skin.TknifeID, 0, KnifeT, -1, nullptr, 0.00000001f )),       // M9 Ruby
     make_pair( GLOVE_T,             cSkin( skin.TgloveID, 0, GloveT, -1, nullptr, 0.0000001f)),         // Driver Crimson weave
     make_pair( GLOVE_CT,            cSkin( skin.CTgloveID, 0, GloveCT, -1, nullptr, 0.0000001f)),       // Driver Crimson weave
    
    make_pair( WEAPON_GALILAR,      cSkin( skin.galil, 0, -1, -1, nullptr, 0.00000001f) ),              // Cerberus
    make_pair( WEAPON_FAMAS,        cSkin( skin.famas, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_AK47,         cSkin( skin.ak, 0, -1, 78086, nullptr, 0.00000001f ) ),                // BloodSport
    make_pair( WEAPON_M4A1,         cSkin( skin.a4, 0, -1, -1, nullptr, 0.00000001f) ),                 // Howl
    make_pair( WEAPON_M4A1_SILENCER,cSkin( skin.a1, 0, -1, -1, nullptr, 0.00000001f) ),                 // Hot Rod
    make_pair( WEAPON_SSG08,        cSkin( skin.scout, 0, -1, -1, nullptr, 0.00000001f) ),              // Blood in the water
    make_pair( WEAPON_SG556,        cSkin( skin.sg, 0, -1, -1, nullptr, 0.00000001f) ),                 // Bulldozer
    make_pair( WEAPON_AUG,          cSkin( skin.aug, 0, -1, -1, nullptr, 0.00000001f) ),                // Akihabara's Accept
    make_pair( WEAPON_AWP,          cSkin( skin.awp, 0, -1, -1, (char*)"Wubba Lubba Dub Dub", 0.00000001f ) ),               // Dragon Lore
    make_pair( WEAPON_G3SG1,        cSkin( skin.g3, 0, -1, -1, nullptr, 0.00000001f) ),                 // Chronos
    make_pair( WEAPON_SCAR20,       cSkin( skin.scar, 0, -1, -1, nullptr, 0.00000001f) ),   // Splash Jam
    
    make_pair( WEAPON_GLOCK,        cSkin( skin.glock, 0, -1, -1, nullptr, 0.00000001f) ),              // Fade
    make_pair( WEAPON_USP_SILENCER, cSkin( skin.usp, 0, -1, -1, nullptr, 0.00000001f) ),                // Neo Noir
    make_pair( WEAPON_HKP2000,      cSkin( skin.p2000, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_ELITE,        cSkin( skin.dual, 0, -1, -1, nullptr, 0.0000000001f) ),
    make_pair( WEAPON_P250,         cSkin( skin.p2000, 0, -1, -1, nullptr, 0.00000001f) ),              // Whiteout
    make_pair( WEAPON_TEC9,         cSkin( skin.tec9, 0, -1, -1, nullptr, 0.00000001f) ),               // Nuclear Threat
    make_pair( WEAPON_FIVESEVEN,    cSkin( skin.five7, 0, -1, -1, nullptr, 0.00000001f) ),              // Doppler
    make_pair( WEAPON_CZ75A,        cSkin( skin.cz, 0, -1, -1, nullptr, 0.000000001f) ),
    make_pair( WEAPON_DEAGLE,       cSkin( skin.deagle, 0, -1, 6678, nullptr, 0.00000001f) ),             // Blaze
    make_pair( WEAPON_REVOLVER,     cSkin( skin.r8, 0, -1, -1, nullptr, 0.00000001f) ),                 // Saphire
    
    make_pair( WEAPON_MAC10,        cSkin( skin.mac10, 0, -1, -1, nullptr, 0.00000001f)),
    make_pair( WEAPON_MP9,          cSkin( skin.mp9, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_MP7,          cSkin( skin.mp7, 0, -1, -1, nullptr, 0.00000001f) ),                // Whiteout
    make_pair( WEAPON_UMP45,        cSkin( skin.ump, 0, -1, -1, nullptr, 0.00000001f) ),                // Blaze
    make_pair( WEAPON_P90,          cSkin( skin.p90, 0, -1, -1, nullptr, 0.00000001f) ),                // Emerald Dragon
    make_pair( WEAPON_BIZON,        cSkin( skin.bizon, 0, -1, -1, nullptr, 0.00000001f) ),
    
    make_pair( WEAPON_NOVA,         cSkin( skin.nova, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_SAWEDOFF,     cSkin( skin.sawed, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_MAG7,         cSkin( skin.mag7, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_XM1014,       cSkin( skin.xm, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_M249,         cSkin( skin.m249, 0, -1, -1, nullptr, 0.00000001f) ),
    make_pair( WEAPON_NEGEV,        cSkin( skin.negev, 0, -1, -1, nullptr, 0.00000001f) ),
    
} );

unordered_map<int, const char*> cSkinchanger::ModelList;

cSkinchanger* skinchanger = new cSkinchanger;


void cSkinchanger::FrameStageNotify(ClientFrameStage_t stage) {
    
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        
        local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if(local && local->GetHealth() > 0){
            
            if(!bInit){
                Init();
                bInit = true;
            }
            
            skins_cfg->LoadSkins();
            LoadSkins();
        }
    }
}


void cSkinchanger::FindModels() {
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")] = KnifeToModel[KnifeCT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")] = KnifeToModel[KnifeT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl")] = GloveToModel[GloveT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl")] = GloveToModel[GloveCT].c_str();
}

void cSkinchanger::LoadSkinsConfig() {
    
}

void cSkinchanger::LoadSkins() {
    
    player_info_t player_info;
    pEngine->GetPlayerInfo(local->GetId(), &player_info);
    
    int* pWeapons = local->GetWeapons();
    
    C_BaseViewModel* LocalPlayerViewModel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(local->GetViewModel());
    
    C_BaseAttributableItem* WeaponViewModel = nullptr;
    
    if(LocalPlayerViewModel)
        WeaponViewModel = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(LocalPlayerViewModel->GetWeapon());
    
    C_BaseCombatWeapon* localWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(local->GetActiveWeapon());
    
    if(pWeapons){
        for(int i = 0; pWeapons[i]; i++){
            C_BaseAttributableItem* attributableItem = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);
            C_BaseAttributableItem* glove = (C_BaseAttributableItem*)pEntList->GetClientEntity(local->GetWearables()[0] & 0xFFF);
            
            if(attributableItem){
                int* Definition = attributableItem->GetItemDefinitionIndex();
                
                unordered_map<int, cSkin>::iterator SkinIter = (*Definition == WEAPON_KNIFE ? (*Definition == WEAPON_KNIFE ? Skins.find(WEAPON_KNIFE) : Skins.find(WEAPON_KNIFE_T)) : Skins.find(*Definition));
                
                
                if(SkinIter != Skins.end()) {
                    if(*attributableItem->GetOriginalOwnerXuidLow() == player_info.xuidlow && *attributableItem->GetOriginalOwnerXuidHigh() == player_info.xuidhigh){
                        
                        int* model_index = attributableItem->GetModelIndex();
                        
                        unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                        
                        if(model_iter != ModelList.end())
                            *model_index = pModelInfo->GetModelIndex(model_iter->second);
                        
                        
                        cSkin skin = move(SkinIter->second);
                        
                        
                        if(KnifeCT && (*Definition == WEAPON_KNIFE))
                            *attributableItem->GetItemDefinitionIndex() = KnifeCT;
                        else if(KnifeT && (*Definition == WEAPON_KNIFE_T))
                            *attributableItem->GetItemDefinitionIndex() = KnifeT;
                        
                        
                        if(skin.name)
                            sprintf(attributableItem->GetCustomName(), "%s", skin.name);
                        
                        
                        *attributableItem->GetItemIDHigh() = -1;
                        *attributableItem->GetFallbackPaintKit() = skin.Paintkit;
                        *attributableItem->GetFallbackStatTrak() = skin.StatTrack;
                        *attributableItem->GetEntityQuality() = 4;
                        *attributableItem->GetFallbackSeed() = skin.Seed;
                        *attributableItem->GetFallbackWear() = 0.00000001f;
                        *attributableItem->GetAccountID() = player_info.xuidlow;
                        
                        ApplyCustomGloves(local);
                        
                    }
                }
            
                
                if (WeaponViewModel && WeaponViewModel == attributableItem)
                {
                    int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();
                    
                    unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                    
                    if (model_iter != ModelList.end())
                    {
                        *model_index = pModelInfo->GetModelIndex(model_iter->second);
                    }
                }
            }
        }
    }
}


void cSkinchanger::ApplyCustomGloves(C_BaseEntity* pLocal) {
    
    if (!pEntList->GetClientEntityFromHandle((void*)pLocal->GetWearables())) {
        for (ClientClass* pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
            if (pClass->m_ClassID != (int)EClassIds::CEconWearable)
                continue;
            
            int entry = (pEntList->GetHighestEntityIndex() + 1);
            int	serial = RandomInt(0x0, 0xFFF);
            
            pClass->m_pCreateFn(entry, serial);
            pLocal->GetWearables()[0] = entry | serial << 16;
            
            //glovesUpdated = true;
            
            break;
        }
    }
    
    player_info_t LocalPlayerInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &LocalPlayerInfo);
    
    C_BaseAttributableItem* glove = (C_BaseAttributableItem*)pEntList->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
    
    if (!glove)
        return;
    
    int* glove_index = glove->GetModelIndex();
    unordered_map<int, const char*>::iterator glove_iter = ModelList.find(*glove_index);
    unordered_map<int, cSkin>::iterator Iter = (pLocal->GetTeam() == TEAM_COUNTER_TERRORIST ? Skins.find(GLOVE_CT) : Skins.find(GLOVE_T));
    cSkin gloveskin = move(Iter->second);
    
    if(glove_iter != ModelList.end())
        *glove_index = pModelInfo->GetModelIndex(glove_iter->second);
    
    if(GloveCT && pLocal->GetTeam() == TEAM_COUNTER_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveCT;
    
    if(GloveT && pLocal->GetTeam() == TEAM_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveT;
    
    *glove->GetFallbackPaintKit() = skin.CTgloveID;
    *glove->GetFallbackPaintKit() = skin.TgloveID;
    *glove->GetItemIDHigh() = -1;
    *glove->GetEntityQuality() = 4;
    *glove->GetFallbackWear() = 0.00000001f;
    *glove->GetAccountID() = LocalPlayerInfo.xuidlow;
    
    if(glovesUpdated) {
        glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
        glovesUpdated = false;
    }
}


void cSkinchanger::Init() {
    ModelList.clear();
    FindModels();
}

void cSkinchanger::FireEventClientSide(IGameEvent *event) {
    
    if (!strcmp(event->GetName(), "game_newmap"))
    {
        //Init();
    }
}


// Fix Animations

inline const int RandomSequence(int low, int high) {
    return (rand() % (high - low + 1) + low);
}

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
    
    CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pStruct;
    
    if(!pViewModel)
        return g_pSequence(pDataConst, pStruct, pOut);
    
    C_BaseEntity* pOwner = (C_BaseEntity*)pEntList->GetClientEntityFromHandle(pViewModel->GetOwner());
    
    if (pViewModel && pOwner) {
        if (pOwner->GetIndex() == pEngine->GetLocalPlayer()) {
            
            const model_t* knife_model = pModelInfo->GetModel(*pViewModel->GetModelIndex());
            const char* model_filename = pModelInfo->GetModelName(knife_model);
            
            int m_nSequence = (int)pData->m_Value.m_Int;
            
            if (!strcmp(model_filename, "models/weapons/v_knife_butterfly.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
                        break;
                    default:
                        m_nSequence++;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_falchion_advanced.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_FALCHION_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence--;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_push.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_DAGGERS_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_LIGHT_MISS1:
                    case SEQUENCE_DEFAULT_LIGHT_MISS2:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_HIT1:
                    case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence += 3;
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence += 2;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_survival_bowie.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_BOWIE_IDLE1;
                        break;
                    default:
                        m_nSequence--;
                }
                
            }
            
            pData->m_Value.m_Int = m_nSequence;
        }
    }
    
    return g_pSequence(pData, pStruct, pOut);
}


