#include "esp.h"


void DrawSkeleton(C_BaseEntity* pEntity, Color color) {
    
    studiohdr_t* pStudioModel = pModelInfo->GetStudioModel( pEntity->GetModel() );
    
    if ( pStudioModel ) {
        
        static matrix3x4_t pBoneToWorldOut[128];
        
        if ( pEntity->SetupBones( pBoneToWorldOut, 128, 256, 0) )
        {
            for ( int i = 0; i < pStudioModel->numbones; i++ )
            {
                mstudiobone_t* pBone = pStudioModel->pBone( i );
                
                if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
                    continue;
                
                Vector vBone1 = pEntity->GetBonePosition(i);
                Vector vBoneOut1;
                
                Vector vBone2 = pEntity->GetBonePosition(pBone->parent);
                Vector vBoneOut2;
                
                if(WorldToScreen(vBone1, vBoneOut1) && WorldToScreen(vBone2, vBoneOut2)) {
                    draw->drawline(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, color);
                }
            }
        }
    }
}

void RenderBones(Vector* vBones, Color color) {
    
    draw->drawline((int)vBones[0].x, (int)vBones[0].y, (int)vBones[1].x, (int)vBones[1].y, color); // head to neck
    draw->drawline((int)vBones[1].x, (int)vBones[1].y, (int)vBones[2].x, (int)vBones[2].y, color); // neck to lower neck
    draw->drawline((int)vBones[2].x, (int)vBones[2].y, (int)vBones[7].x, (int)vBones[7].y, color); // lower neck to upper chest
    
    draw->drawline((int)vBones[7].x, (int)vBones[7].y, (int)vBones[6].x, (int)vBones[6].y, color); // upper chest to chest
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[18].x, (int)vBones[18].y, color);
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[16].x, (int)vBones[16].y, color);
    
    draw->drawline((int)vBones[16].x, (int)vBones[16].y, (int)vBones[17].x, (int)vBones[17].y, color);
    draw->drawline((int)vBones[17].x, (int)vBones[17].y, (int)vBones[14].x, (int)vBones[14].y, color);
    draw->drawline((int)vBones[18].x, (int)vBones[18].y, (int)vBones[15].x, (int)vBones[15].y, color);
    
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[5].x, (int)vBones[5].y, color);
    draw->drawline((int)vBones[5].x, (int)vBones[5].y, (int)vBones[4].x, (int)vBones[4].y, color);
    draw->drawline((int)vBones[4].x, (int)vBones[4].y, (int)vBones[3].x, (int)vBones[3].y, color);
    
    draw->drawline((int)vBones[3].x, (int)vBones[3].y, (int)vBones[9].x, (int)vBones[9].y, color);
    draw->drawline((int)vBones[3].x, (int)vBones[3].y, (int)vBones[8].x, (int)vBones[8].y, color);
    
    draw->drawline((int)vBones[9].x, (int)vBones[9].y, (int)vBones[11].x, (int)vBones[11].y, color);
    draw->drawline((int)vBones[11].x, (int)vBones[11].y, (int)vBones[13].x, (int)vBones[13].y, color);
    
    draw->drawline((int)vBones[8].x, (int)vBones[8].y, (int)vBones[10].x, (int)vBones[10].y, color);
    draw->drawline((int)vBones[10].x, (int)vBones[10].y, (int)vBones[12].x, (int)vBones[12].y, color);
}


Color GetColorBase(Color& col) {
    return Color(col.r(), col.g(), col.b(), 255);
}

C_BaseCombatWeapon* getWeapon(C_BaseEntity* local) {
    auto hWeapon = local->GetActiveWeapon();
    if (!hWeapon)
        return;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(hWeapon);
}

void bombTimer() {
    
    C_BasePlantedC4* bomb = nullptr;
    
    for (int i = 1; i < pEntList->GetHighestEntityIndex(); i++) {
        C_BaseEntity* entity = pEntList->GetClientEntity(i);
        if (!entity)
            continue;
        
        if (entity->GetClientClass()->m_ClassID == CPlantedC4) {
            bomb = (C_BasePlantedC4*)entity;
            break;
        }
    }
    
    if (!bomb || bomb->IsBombDefused())
        return;
    
    float bombTimer = bomb->GetBombTime() - pGlobals->curtime;
    
    draw->drawstring(10, 320, Color::White(), espfont, to_string(bombTimer).c_str());
    
}

void box3d(C_BaseEntity* entity, Color color) {
    
    Vector vOrigin = entity->GetVecOrigin();
    Vector min = entity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = entity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] = { Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(min.x, min.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(max.x, max.y, max.z),
        Vector(max.x, min.y, max.z) };
    
    int edges[12][2] = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
    };
    
    for (auto it : edges) {
        Vector p1, p2;
        if (pOverlay->ScreenPosition(points[it[0]], p1) || pOverlay->ScreenPosition(points[it[1]], p2))
            return;
        draw->Line(Vector2D(p1.x, p1.y), Vector2D(p2.x, p2.y), color);
    }
}

void DrawHealthbar(int x, int y, int w, int h, int health, Color color) {
    
    if(health > 100)
        health = 100;
    
    int hw = h - ((h) * health) / 100;
    draw->fillrgba(x, y - 1, w, h + 2, Color(0, 0, 0, 120));
    draw->fillrgba(x, y + hw - 1, w, h - hw + 2, color);
    draw->drawbox(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
}

void DrawDroppedWeapons(C_BaseCombatWeapon* weapon) {
    
    Vector vOrig = weapon->GetVecOrigin();
    int owner = weapon->GetOwner();
    
    if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
        return;
    
    string model = GetWeaponName(weapon);
    
    boxstruct wBox;
    
    if(DrawPlayerBox(weapon, wBox)) {
        draw->drawstring(wBox.x + wBox.w / 2, wBox.y, Color::Yellow(), espfont, model.c_str(), true);
    }
}

void grenadeESP(C_BaseEntity* entity){
    
    if(!vars.visuals.grenade)
        return;
    
    if(!strstr(entity->GetClientClass()->m_pNetworkName, "Projectile"))
        return;
    
    const model_t* model = entity->GetModel();
    
    if(!model)
        return;
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(model);
    
    if(!hdr || (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped")))
        return;
    
    Color color;
    char* name = nullptr;
    
    IMaterial* mats[32];
    pModelInfo->GetModelMaterials(model, hdr->numtextures, mats);
    for(int i = 0; i < hdr->numtextures; i++){
        IMaterial* mat = mats[i];
        
        if(!mat)
            continue;
        
        if(strstr(mat->GetName(), "flashbang")){
            color = Color(255, 235, 59, 255);
            name = "Flashbang";
            break;
        }
        if(strstr(mat->GetName(), "smoke")){
            color = Color(97, 97, 97, 255);
            name = "Smoke";
            break;
        }
        if(strstr(mat->GetName(), "decoy")){
            color = Color(97, 97, 97, 255);
            name = "Decoy";
            break;
        }
        if(strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade")){
            color = Color(244, 67, 54, 255);
            name = "HE Grenade";
            break;
        }
        if(strstr(mat->GetName(), "incendiary")){
            color = Color(244, 67, 54, 255);
            name = "Incendiary";
            break;
        }
        if(strstr(mat->GetName(), "molotov")){
            color = Color(244, 67, 54, 255);
            name = "Molotov";
        }
    }
    
    boxstruct nBox;
    
    if(DrawPlayerBox(entity, nBox)){
        draw->drawstring(nBox.x + nBox.w + 3, nBox.y - (nBox.h/2), Color::White(), espfont, name);
        box3d(entity, color);
    }
    
    
}


void DrawPlantedBomb(C_BasePlantedC4* bomb){
    
    float bombTimer = bomb->GetBombTime() - pGlobals->curtime;
    
    if(!bomb->IsBombTicking())
        return;
    
    char* displayText;
    
    if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f) {
        displayText = "Bomb";
    } else {
        std::string str = "Bomb: " + to_string(bombTimer);
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
        displayText = cstr;
        delete [] cstr;
    }
    
    boxstruct bBox;
    
    if(DrawPlayerBox(bomb, bBox)) {
        draw->drawstring(bBox.x + bBox.w / 2, bBox.y, Color::White(), espfont, displayText);
    }
    
}

auto DrawPlayerESP() -> void {
    
    int getscreenw, getscreenh;

    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    if(!vars.visuals.enabled)
        return;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++) {
        
        auto* entity = pEntList->GetClientEntity(i);

        if(!entity)
            continue;
        
        int classID = entity->GetClientClass()->m_ClassID;
        C_BaseCombatWeapon* weapon = (C_BaseCombatWeapon*)entity;
        C_BasePlantedC4* pC4 = (C_BasePlantedC4*)entity;
        
        // Non player ESP
        
        /* Draw bomb timer */
        if(vars.visuals.bombtimer && classID == EClassIds::CPlantedC4)
            DrawPlantedBomb(pC4);
            
        
        if(vars.visuals.weapons) {
            if(classID != EClassIds::CBaseWeaponWorldModel) {
                if (strstr(entity->GetClientClass()->m_pNetworkName, "Weapon") || classID == EClassIds::CDEagle || classID == EClassIds::CAK47) {
                    DrawDroppedWeapons(weapon);
                }
            }
        }
         
            
        if (vars.visuals.grenade)
            grenadeESP(entity);
        
        // End
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        if(vars.visuals.enemyonly && entity->GetTeam() == local->GetTeam())
            continue;
        
        player_info_t info;
        
        pEngine->GetPlayerInfo(i, &info);
        
        auto vis = IsVisible(local, entity);
        
        Color playercolor = [&]() -> Color {
            
            if(entity->GetTeam() == 3)
                return vis ? GetColorBase(vars.colors.ctbox) : GetColorBase(vars.colors.ctbox_ign);
            
            else if(entity->GetTeam() == 2)
                return vis ? GetColorBase(vars.colors.tbox) : GetColorBase(vars.colors.tbox_ign);
            
        }();
        
        boxstruct players;
        
        Vector vFrom = GetHitboxPosition(entity, (int)CSGOBones::Head);
        Vector vW2s;
        Vector vvvv;
        Vector origin = entity->GetVecOrigin();
        
        
        if(DrawPlayerBox(entity, players)) {
            
            /* Draw box */
            if(vars.visuals.box)
                draw->drawboxoutline(players.x, players.y, players.w, players.h, playercolor);
                
            /* Draw 3D Box */
            if(vars.visuals.box3d)
                box3d(entity, playercolor);
                
            /* Draw name */
            if(vars.visuals.name)
                draw->drawstring(players.x + players.w / 2, players.y - 12, Color::White(), espfont, info.name, true);
                
            /* Draw health as text */
            if(vars.visuals.healthtext)
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::White(), espfont, std::to_string(entity->GetHealth()).c_str(), true);
            
            /* Draw health bar */
            if(vars.visuals.health)
                DrawHealthbar(players.x - 5, players.y, 3, players.h, entity->GetHealth(), Color::Green());
            
            /* Draw snaplines */
            if(vars.visuals.snapline)
                draw->drawline(getscreenw / 2, getscreenh, players.x + players.w / 2, players.y + players.h, playercolor);
                
            /* Draw head hitbox */
            if(vars.visuals.headhitbox) {
                if(WorldToScreen(origin, vvvv) && WorldToScreen(vFrom, vW2s)) {
                    draw->drawline(getscreenw / 2, getscreenh, vW2s.x, vW2s.y, playercolor);
                }
            }
            
            /* Is defusing */
            if(entity->IsDefusing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "DEFUSING", true);
                
            /* Is defusing */
            if(entity->IsScoped())
                draw->drawstring(players.x + players.w / 2, players.y - 29, Color::Red(), espfont, "SCOPING", true);

            /* Draw skeleton */
            if(vars.visuals.skeleton)
                DrawSkeleton(entity, Color::White());
                
            /* Draw Weapon */
            if(vars.visuals.active) {
                string active = GetWeaponName(getWeapon(entity));
                draw->drawstring(players.x + players.w + 3, players.y + 1, Color::White(), espfont, active.c_str());

            }
                
            /* Is Rescuing */
            if(entity->IsGrabbingHostage())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "RESCUING", true);
             
             /* Is Carry */
            if(entity->IsRescuing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "CARRYING", true);
            
                
        }
        
    }
    
}


/* Getting the module and library address */
void getModule(task_t task, mach_vm_address_t * start, off_t * length, const char * module, Byte * buffer = nullptr, bool readBuffer = false)
{
    struct task_dyld_info dyld_info;
    mach_vm_address_t address = 0;
    mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;
    if (task_info(task, TASK_DYLD_INFO, (task_info_t)&dyld_info, &count) == KERN_SUCCESS)
    {
        address = dyld_info.all_image_info_addr;
    }
    
    struct dyld_all_image_infos *dyldaii;
    mach_msg_type_number_t size = sizeof(dyld_all_image_infos);
    vm_offset_t readMem;
    kern_return_t kr = vm_read(task, address, size, &readMem, &size);
    if (kr != KERN_SUCCESS)
    {
        return;
    }
    
    dyldaii = (dyld_all_image_infos *) readMem;
    int imageCount = dyldaii->infoArrayCount;
    mach_msg_type_number_t dataCnt = imageCount * 24;
    struct dyld_image_info *g_dii = NULL;
    g_dii = (struct dyld_image_info *) malloc (dataCnt);
    // 32bit bs 64bit
    kern_return_t kr2 = vm_read(task, (mach_vm_address_t)dyldaii->infoArray, dataCnt, &readMem, &dataCnt);
    if (kr2)
    {
        return;
    }
    struct dyld_image_info *dii = (struct dyld_image_info *) readMem;
    for (int i = 0; i < imageCount; i++)
    {
        dataCnt = 1024;
        vm_read(task, (mach_vm_address_t)dii[i].imageFilePath, dataCnt, &readMem, &dataCnt);
        char *imageName = (char *)readMem;
        if (imageName)
        {
            g_dii[i].imageFilePath = strdup(imageName);
        }
        else
        {
            g_dii[i].imageFilePath = NULL;
        }
        g_dii[i].imageLoadAddress = dii[i].imageLoadAddress;
        if (strstr(imageName, module) != NULL)
        {
            struct stat st;
            stat(imageName, &st);
            *start = (mach_vm_address_t)dii[i].imageLoadAddress;
            
            *length = st.st_size;
        }
    }
}


uintptr_t GetLibraryAddress(const char* moduleName)
{
    pid_t pids[1024];
    pid_t p = -1;
    int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < numberOfProcesses; ++i)
    {
        if (pids[i] == 0) { continue; }
        char name[1024];
        proc_name(pids[i], name, sizeof(name));
        if (!strncmp(name, (const char *)"csgo_osx64", sizeof("csgo_osx64")))
        {
            p = pids[i];
            break;
        }
    }
    task_t task = 0;
    task_for_pid(current_task(), p, &task);
    off_t moduleLength = 0;
    mach_vm_address_t moduleStartAddress;
    getModule(task, &moduleStartAddress, &moduleLength, moduleName);
    return moduleStartAddress;
}


/* Display menu */
auto pwnmymenu() -> void {
    
    if(pInputSystem->IsButtonDown(KEY_LALT) || pInputSystem->IsButtonDown(KEY_RALT)) {
        vars.menu = !vars.menu;
    }
        
}
       





