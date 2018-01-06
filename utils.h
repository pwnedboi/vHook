struct boxstruct { int x, y, w, h; };

extern void SinCos(float radians, float *sine, float *cosine);
extern void AngleVectors(const Vector & angles, Vector * forward);
extern void AngleVectors(const Vector & angles, Vector * forward, Vector * right, Vector * up);
extern void VectorAngles(const Vector& forward, Vector &angles);
extern void FixMovement(Vector& oang, CUserCmd* cmd);
typedef void (*SendClanTagFn) (const char*, const char*);
extern void SetClanTag(const char* tag, const char* name);
extern bool WorldToScreen(Vector& vFrom, Vector& vTo);
extern bool DrawPlayerBox(C_BaseEntity* pEntity, boxstruct& str); // Credit's to dude719 & keybode.
extern void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
extern Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox);
extern bool IsVisible(C_BaseEntity* local, C_BaseEntity* entity);
extern void FixMovement(Vector& oang, CUserCmd* pCmd);
extern void Normalize(Vector & vIn, Vector & vOut);

extern Vector CalcAngle(Vector src, Vector dst);
extern void NormalizeAngles(Vector& angle);
extern void ClampAngles(Vector& angle);
extern long GetEpochTime();
extern void StdReplaceStr(string& replaceIn, const string& replace, const string& replaceWith);
extern wstring stws(string str);
extern void NormalizeVector(Vector& vecIn);
bool IsVisible(C_BaseEntity* localPlayer, Vector position, bool exact = false);

extern string GetWeaponName(C_BaseCombatWeapon* pWeapon);
extern Vector GetHitboxPos(C_BaseEntity* pEntity, int Hitbox);
extern Bone GetBoneByName(C_BaseEntity* player, const char* boneName);
extern string GetItemDisplayName(ItemDefinitionIndex index);


enum class CSGOBones {
    Head = 0,
    Neck = 1,
    Neck_Lower = 2,
    Pelvis = 3,
    Stomach = 4,
    Lower_Chest = 5,
    Chest = 6,
    Upper_Chest = 7,
    Right_Thigh = 8,
    Left_Thigh = 9,
    Right_Shin = 10,
    Left_Shin = 11,
    Right_Foot = 12,
    Left_Foot = 13
};

template<typename T>
struct IntHash
{
    size_t operator()(const T& t) const noexcept
    {
        return std::hash<int>()((int) t);
    }
};

