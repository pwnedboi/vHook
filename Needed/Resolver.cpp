#include "main.h"

RecvVarProxyFn OldProxy_X, OldProxy_Y, OldProxy_Z, OldProxy_Velocity, VeloProx1, VeloProx2, VeloProx3;

float AAA_Pitch(C_BaseEntity* entity) {
    int index = entity->GetIndex();
    float angle = gCorrections[index].x;
    
    if(gCorrections[index].dropdown_x == 0) {
        if (angle == 0.f)
            angle = 89;
        if (angle > 90.0f &&  angle < 270.f)
        {
            if (angle > 180.f)
                angle = -89.f;
            else
                angle = 89.0f;
        }
    } else if(gCorrections[index].dropdown_x == 1) {
        angle = 89;
    } else if(gCorrections[index].dropdown_x == 2) {
        angle = -89;
    }
    
    return angle;
}

float AAA_Yaw(C_BaseEntity* entity) {
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    
    if(gCorrections[index].dropdown_y == 0) {
        angle = entity->GetLowerBodyYawTarget();
    } else if(gCorrections[index].dropdown_y == 1) {
        angle -= 90;
    } else if(gCorrections[index].dropdown_y == 2) {
        angle -= 270.f;
    } else if(gCorrections[index].dropdown_y == 3) {
        static bool bJitter;
        angle = (bJitter) ? 90 : -90;
        bJitter = !bJitter;
    } else if(gCorrections[index].dropdown_y == 4) {
        angle = pGlobals->curtime * 1000.f;
    }
    else if(gCorrections[index].dropdown_y == 6) {
        angle = entity->GetLowerBodyYawTarget();
    }else if(gCorrections[index].dropdown_y == 7) {
        angle += 45; // this is the real way of 45 step?
    }
    
    
    return angle;
}

void FixPitch(const CRecvProxyData *pData, void *pStruct, void *pOut) { // Auto Detection for FakeDown Down and Up.
    
    float angle = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].x = angle;
    
    OldProxy_X(pData, pStruct, pOut);
}

void FixYaw(const CRecvProxyData *pData, void *pStruct, void *pOut) {
    float flYaw = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].y = flYaw;
    
    
    OldProxy_Y(pData, pStruct, pOut);
}

void BaseVelocityProxy(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
    Vector baseVelocity = *(Vector*)(&pData->m_Value.m_Vector[0]);
    
    float fValue = -0.000977;
    
    baseVelocity = Vector(fValue, fValue, fValue);
    
    if (baseVelocity == Vector(fValue, fValue, fValue))
    {
        baseVelocity = Vector(0, 0, 0);
    }
    
    OldProxy_Velocity(pData, pStruct, pOut);
}

void ViewOffsetZProxy(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
    float viewOffsetZ = pData->m_Value.m_Float;
    
    if (viewOffsetZ == 64.062561) // 64.062561
    {
        viewOffsetZ = 64.f;
    }
    else if (viewOffsetZ == 46.044968) // 46.044968
    {
        viewOffsetZ = 46.f;
    }
    
    OldProxy_Z(pData, pStruct, pOut);
}

void VelocityProxy0(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
    *(float*)(pOut) = pData->m_Value.m_Float;
}

void VelocityProxy1(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
    *(float*)(pOut) = pData->m_Value.m_Float;
}

void VelocityProxy2(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
    *(float*)(pOut) = pData->m_Value.m_Float;
}

