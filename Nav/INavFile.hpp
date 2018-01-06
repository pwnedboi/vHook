// Jun 5, 2016
// Credits: Valve


#pragma once

#include "./nav_area.hpp"

#include <string>

#include <fstream>
#include <vector>



class INavFile
{
private:

public:

	unsigned int m_magic{ 0 }; // Magic number used to identify the file

	unsigned int m_version{ 0 }; // Version of the file, CS:GO is using version 16 files
	unsigned int m_subVersion{ 0 };

	unsigned int m_saveBspSize{ 0 }; // Size of the corresponding BSP file used to verify an up-to-date a navigation mesh

	unsigned char m_isAnalyzed{ (unsigned char) 0x00 };

	unsigned short m_usPlaceCount{ 0 };
	std::vector<std::string> m_vStrPlaceNames;
	unsigned char m_hasUnnamedAreas{ (unsigned char) 0x00 };

	std::vector<CNavArea> m_areas;
	unsigned int m_uiAreaCount{ 0 };


	// Loads a nav file
	// @return True on success
	bool Load(std::ifstream &ifs);


	// Initializes the class
	bool Initialize(void);

	// Restores default values
	void RestoreDefaults(void);

	// Default constructor
	INavFile(void);

	// Destructor
	virtual ~INavFile(void);

};
