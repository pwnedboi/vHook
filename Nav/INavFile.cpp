// Jun 5, 2016

#include "./INavFile.hpp"

#include <memory>



// Loads a nav file
// @return True on success
bool INavFile::Load(std::ifstream &ifs)
{
	static std::string strFunctionName{ "INavFile::Load" };

	ifs.read((char *) &this->m_magic, sizeof(this->m_magic));

	ifs.read((char *) &this->m_version, sizeof(this->m_version));

    
    
	ifs.read((char *) &this->m_subVersion, sizeof(this->m_subVersion));

	ifs.read((char *) &this->m_saveBspSize, sizeof(this->m_saveBspSize));
	ifs.read((char *) &this->m_isAnalyzed, sizeof(this->m_isAnalyzed));

	ifs.read((char *) &this->m_usPlaceCount, sizeof(this->m_usPlaceCount));

	for (unsigned short us{ 0 }; us < this->m_usPlaceCount; ++us)
	{
		unsigned short usLength{ 0 };
		ifs.read((char *) &usLength, sizeof(usLength));

		std::unique_ptr<char[]> szName(new char[usLength]);
		ifs.read((char *) szName.get(), usLength);

		// Utils::Debug->Log("Loaded place name " + std::String(szName.get()), "", strFunctionName, Utils::DBG_LEVEL::kAlways);
		this->m_vStrPlaceNames.push_back(std::string(szName.get()));
	}

	ifs.read((char *) &this->m_hasUnnamedAreas, sizeof(this->m_hasUnnamedAreas));

	ifs.read((char *) &this->m_uiAreaCount, sizeof(this->m_uiAreaCount));

	for (unsigned int ui{ 0 }; ui < this->m_uiAreaCount; ++ui)
	{
		CNavArea area{ };
		area.LoadFromFile(ifs);
		this->m_areas.push_back(area);
	}

	return true;
}


// Initializes the class
bool INavFile::Initialize(void)
{
	this->RestoreDefaults();
	
	return true;
}

// Restores default values
void INavFile::RestoreDefaults(void)
{
	this->m_magic = 0;

	this->m_version = 0;
	this->m_subVersion = 0;

	this->m_saveBspSize = 0;

	this->m_isAnalyzed = (unsigned char) 0x00;

	this->m_usPlaceCount = 0;
	this->m_vStrPlaceNames.clear();
	this->m_hasUnnamedAreas = (unsigned char) 0x00;

	this->m_areas.clear();
	this->m_uiAreaCount = 0;
}

// Default constructor
INavFile::INavFile(void)
{
	this->RestoreDefaults();
}

// Destructor
INavFile::~INavFile(void)
{
	
}
