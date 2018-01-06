#include "INavFile.hpp"
/*
INavFile nav{ };

string curMap = pEngine->GetMapGroupName();
string path = "~/Library/Application Support/Steam/steamapps/common/Counter-Strike Global Offensive/csgo/maps/";

bool Load() {
    
    ifstream ifs;
    
    if(strstr(curMap.c_str(), "dust2"))
        ifstream ifs(path + "de_dust2", ios::binary);
    
    if(strstr(curMap.c_str(), "mirage"))
        ifstream ifs(path + "de_mirage", ios::binary);
    
    if(strstr(curMap.c_str(), "inferno"))
        ifstream ifs(path + "de_inferno", ios::binary);
    
    if(strstr(curMap.c_str(), "nuke"))
        ifstream ifs(path + "de_nuke", ios::binary);
    
    if(strstr(curMap.c_str(), "vertigo"))
        ifstream ifs(path + "de_vertigo", ios::binary);
    
    if(strstr(curMap.c_str(), "overpass"))
        ifstream ifs(path + "de_overpass", ios::binary);
    
    if(strstr(curMap.c_str(), ""))
        ifstream ifs(path + "", ios::binary);
    

	if (!ifs.is_open())
		return false;
	

	if (!nav.Load(ifs))
		return false;

	ifs.close();
	
	return true;
}

// Draws the navigation mesh
void DrawMesh(void)
{
	for (size_t s{ 0 }; s < nav.m_areas.size(); ++s)
	{
		const CNavArea *pArea{ &nav.m_areas[s] };

		Vector a{ pArea->m_nwCorner };
		Vector b{ pArea->m_seCorner.x, pArea->m_nwCorner.z, pArea->m_neY };
		Vector c{ pArea->m_seCorner };
		Vector d{ pArea->m_nwCorner.x, pArea->m_seCorner.z, pArea->m_swY };

		pOverlay->AddLineOverlay(a, b, 255, 0, 0, true, 0.1f);
		pOverlay->AddLineOverlay(b, c, 255, 0, 0, true, 0.1f);
		pOverlay->AddLineOverlay(c, d, 255, 0, 0, true, 0.1f);
		pOverlay->AddLineOverlay(d, a, 255, 0, 0, true, 0.1f);
	}
}
*/
