//
//  asuswalls.cpp
//  pwned
//
//  Created by Finn Le var on 8/05/17.
//  Copyright © 2017 vlone.cc. All rights reserved.
//

#include "asuswalls.h"

float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

std::unordered_map<MaterialHandle_t, Color> worldMaterials;
std::unordered_map<MaterialHandle_t, Color> worldMaterials2;

void asuswalls(ClientFrameStage_t stage) {
    
    if(!vars.misc.asuswalls)
        return;
    
    if (!pEngine->IsInGame() && worldMaterials.size() > 0) {
        
        for (const auto& it : worldMaterials) {
            
            IMaterial* mat = pMatSystem->GetMaterial(it.first);
            
            if (!mat)
                continue;
            
            mat->GetColorModulate(&r, &g, &b);
            a = mat->GetAlphaModulation();
            
            mat->ColorModulate(r, g, b);
            mat->AlphaModulate(a);
        }
        
        worldMaterials.clear();
        worldMaterials2.clear();
    }
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
        return;
    
    for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i)) {
        
        IMaterial* mat = pMatSystem->GetMaterial(i);
        
        if (!mat || strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_WORLD) != 0)
            continue;
        
        if (worldMaterials.find(i) == worldMaterials.end())
        {
            mat->GetColorModulate(&r, &g, &b);
            a = mat->GetAlphaModulation();
            worldMaterials.emplace(i, Color(r, g, b, a));
            worldMaterials2.emplace(i, Color(r, g, b, a));
        }
        
        Color color = (vars.misc.asuswalls && vars.visuals.enabled) ? vars.colors.asus : worldMaterials2.find(i)->second;
        
        if (worldMaterials.at(i) != color) {
            
            float sc = 1.0f/255.0f;
            float w = (float)vars.colors.asus.a() * sc;
            
            mat->ColorModulate(color);
            mat->AlphaModulate(w);
            
            worldMaterials.at(i) = color;
        }
    }
}
