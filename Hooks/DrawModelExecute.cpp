#include "main.h"

std::string DirName(std::string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}

std::string GetWorkingPath()
{
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
    auto dirname = DirName(pathbuf);
    return dirname;
}

bool IsFileExists(const std::string& name)
{
    int res = access(name.c_str(), R_OK);
    if (res < 0) {
        if (errno == ENOENT) {
            return false;
        } else if (errno == EACCES) {
            return true;
        } else {
            return true;
        }
    }
    return true;
}

void AddMaterial(std::string filename, std::string type, bool ignorez, bool wireframe) {
    if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        std::stringstream ss;
        
        ss << "\"" + type + "\"\n" << std::endl;
        ss << "{\n" << std::endl;
        ss << "\t\"$basetexture\" \"VGUI/white_additive\"\n" << std::endl;
        ss << "\t\"$nofog\" \"1\"\n" << std::endl;
        ss << "\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n" << std::endl;
        ss << "\t\"$wireframe\" \""+ std::to_string(wireframe) +"\"\n" << std::endl;
        ss << "\t\"$halflambert\" \"1\"\n" << std::endl;
        ss << "}\n" << std::endl;
        
        std::ofstream(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

IMaterial* CreateMaterial(bool ignorez, bool wireframe, std::string szType) {
    IMaterial* createdMaterial = nullptr;
    
    if(szType == "VertexLitGeneric") {
        if(ignorez) {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_textured_ignorez").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_textured_ignorez", szType, ignorez, wireframe);
            }
             createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_textured_ignorez", TEXTURE_GROUP_MODEL);
        } else {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_textured").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_textured", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_textured", TEXTURE_GROUP_MODEL);
        }
    }
    
    if(szType == "UnlitGeneric") {
        if(ignorez) {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit_ignorez").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit_ignorez", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit_ignorez", TEXTURE_GROUP_MODEL);
        } else {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit", TEXTURE_GROUP_MODEL);
        }
    }
    
    if(szType == "WireFrame") {
        if(ignorez) {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit_ignorez_wirefame").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit_ignorez_wireframe", szType, ignorez, true);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit_ignorez_wireframe", TEXTURE_GROUP_MODEL);
        } else {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit_wireframe").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit_wireframe", szType, ignorez, true);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit_wireframe", TEXTURE_GROUP_MODEL);
        }
    }
    
    if(szType == "NoHands") {
        if(ignorez) {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit_ignorez_nohands").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit_ignorez_nohands", szType, ignorez, true);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit_ignorez_nohands", TEXTURE_GROUP_MODEL);
        } else {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("yEet_chamsmat_unlit_nohands").append(".vmt"))) {
                AddMaterial("yEet_chamsmat_unlit_wireframe", szType, ignorez, true);
            }
            createdMaterial = pMatSystem->FindMaterial("yEet_chamsmat_unlit_nohands", TEXTURE_GROUP_MODEL);
        }
    }
    
    createdMaterial->IncrementReferenceCount();
    
    return createdMaterial;
}

void CallOriginalModel(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld) {
    modelhook->GetOriginalMethod<tDrawModelExecute>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld) {
    
    if((vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())) {
        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        pModelRender->ForcedMaterialOverride(NULL);
        return;
    }
    
    static IMaterial* firstLayer    = CreateMaterial(false, false, "VertexLitGeneric");
    static IMaterial* secondLayer   = CreateMaterial(true, false, "VertexLitGeneric");
    
    static IMaterial* firstLit      = CreateMaterial(false, false, "UnlitGeneric");
    static IMaterial* secondLit     = CreateMaterial(true, false, "UnlitGeneric");
    
    static IMaterial* firstWire     = CreateMaterial(false, true, "WireFrame");
    static IMaterial* secondWire    = CreateMaterial(true, true, "WireFrame");
    
    static IMaterial* firstNo       = CreateMaterial(false, false, "NoHands");
    static IMaterial* secondNo      = CreateMaterial(true, false, "NoHands");
    
    static IMaterial* firstMult     = CreateMaterial(false, true, "WireFrame");
    static IMaterial* secondMult    = CreateMaterial(false, false, "UnlitGeneric");
    
    static IMaterial* firstOut      = CreateMaterial(false, false, "UnlitGeneric");
    static IMaterial* secondOut     = CreateMaterial(true, false, "UnlitGeneric");
    static IMaterial* thirdOut      = CreateMaterial(false, true, "WireFrame");
    
    if(pInfo.pModel) {
        std::string pszModel = pModelInfo->GetModelName(pInfo.pModel);
        
        // Weapon In Hand
        if(pszModel.find("weapons") != std::string::npos  && vars.visuals.weaponchams) {
            if(!(pszModel.find("arms") != std::string::npos)) {
            
                IMaterial* materialCheckFirst = [&]() -> IMaterial* {
                    
                    if(vars.visuals.weaponType == 0)
                        return firstLit;
                    else if(vars.visuals.weaponType == 1)
                        return firstLayer;
                    else if (vars.visuals.weaponType == 2)
                        return firstWire;
                    else if(vars.visuals.weaponType == 3)
                        return firstNo;
                    else if(vars.visuals.weaponType == 4)
                        return firstMult;
                }();
            
                IMaterial* materialCheckSecond = [&]() -> IMaterial* {
                    if(vars.visuals.weaponType == 0)
                        return secondLit;
                    else if(vars.visuals.weaponType == 1)
                        return secondLayer;
                    else if (vars.visuals.weaponType == 2)
                        return secondWire;
                    else if(vars.visuals.weaponType == 3)
                        return secondNo;
                    else if(vars.visuals.weaponType == 4)
                        return secondMult;
                }();
            
                materialCheckSecond->ColorModulate(vars.colors.weapons_ign);
            
                if (vars.visuals.weaponType == 3){
                    materialCheckSecond->AlphaModulate(0.f);
                } else {
                    materialCheckSecond->AlphaModulate(vars.visuals.weapons_alpha / 255.f);
                }
            
                pModelRender->ForcedMaterialOverride(materialCheckSecond);
                CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
            
                materialCheckFirst->ColorModulate(vars.colors.weapons);
            
                if (vars.visuals.weaponType == 3){
                    materialCheckFirst->AlphaModulate(0.f);
                } else {
                    materialCheckFirst->AlphaModulate(vars.visuals.weapons_alpha / 255.f);
                }
                pModelRender->ForcedMaterialOverride(materialCheckFirst);
                CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
            
            }
        }
    
        
        // Hand Chams
        if(pszModel.find("arms") != std::string::npos && vars.visuals.handchams) {
            
            IMaterial* materialCheckFirst = [&]() -> IMaterial* {
                if(vars.visuals.handsType == 0)
                    return firstLit;
                else if(vars.visuals.handsType == 1)
                    return firstLayer;
                else if (vars.visuals.handsType == 2)
                    return firstWire;
                else if(vars.visuals.handsType == 3)
                    return firstNo;
                else if(vars.visuals.handsType == 4)
                    return firstMult;
            }();
            
            IMaterial* materialCheckSecond = [&]() -> IMaterial* {
                if(vars.visuals.handsType == 0)
                    return secondLit;
                else if(vars.visuals.handsType == 1)
                    return secondLayer;
                else if (vars.visuals.handsType == 2)
                    return secondWire;
                else if(vars.visuals.handsType == 3)
                    return secondNo;
                else if(vars.visuals.handsType == 4)
                    return secondMult;
            }();
            
            materialCheckSecond->ColorModulate(vars.colors.hands_ign);
            
            if (vars.visuals.handsType == 3){
                materialCheckSecond->AlphaModulate(0.f);
            } else {
                materialCheckSecond->AlphaModulate(vars.visuals.handchams_alpha / 255.f);
            }
            
            pModelRender->ForcedMaterialOverride(materialCheckSecond);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);

            materialCheckFirst->ColorModulate(vars.colors.hands);
            
            if (vars.visuals.handsType == 3){
                materialCheckFirst->AlphaModulate(0.f);
            } else {
                materialCheckFirst->AlphaModulate(vars.visuals.handchams_alpha / 255.f);
            }
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
    
        
        // Player Chams
            if(pszModel.find("models/player") != std::string::npos && vars.visuals.chams) {
            
            auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            auto* entity = pEntList->GetClientEntity(pInfo.entity_index);
            
            if(entity) {
                if(entity->GetHealth() > 0) {
                    
                    Color ColorIgnorez = [&]() -> Color {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams;
                    }();
                    
                    Color ColorNonIgnorez = [&]() -> Color {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams_ign;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams_ign;
                    }();
                    
                    IMaterial* materialCheckFirst = [&]() -> IMaterial* {
                        if(vars.visuals.playersType == 0)
                            return firstLit;
                        else if(vars.visuals.playersType == 1)
                            return firstLayer;
                        else if(vars.visuals.playersType == 2)
                            return firstOut;
                    }();
                    
                    IMaterial* materialCheckSecond = [&]() -> IMaterial* {
                        if(vars.visuals.playersType == 0)
                            return secondLit;
                        else if(vars.visuals.playersType == 1)
                            return secondLayer;
                        else if(vars.visuals.playersType == 2)
                            return secondOut;
                    }();
                    
                    
                    if(vars.visuals.enemyonly && local->GetTeam() == entity->GetTeam()) {
                        // this is a proper way of doing "enemy only", i don't see why so many paste 2 cheat, pay 2 cheat fails at this.
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(NULL);
                    } else {
                        if(vars.visuals.playersType == 2) {
                            materialCheckFirst->ColorModulate(Color::White());
                            materialCheckFirst->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                            pModelRender->ForcedMaterialOverride(thirdOut);
                            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        }
                        materialCheckSecond->ColorModulate(ColorNonIgnorez);
                        materialCheckSecond->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                        pModelRender->ForcedMaterialOverride(materialCheckSecond);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                    
                        materialCheckFirst->ColorModulate(ColorIgnorez);
                        materialCheckFirst->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                    
                    }
                }
            }
        }
    }
    
    CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
