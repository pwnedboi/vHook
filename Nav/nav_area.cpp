// Jun 26, 2016
// Credits: Valve

#include "nav_area.hpp"

#include <fstream>

#define fsel(c,x,y) ( (c) >= 0 ? (x) : (y) )

// Default constructor
CNavArea::CNavArea(void)
{
	
}

// Constructor
CNavArea::CNavArea(std::ifstream &ifs)
{
	this->LoadFromFile(ifs);
}

// Calculates the height of the area at the given x, z coordinates
// @return Height at the given point
float CNavArea::GetY(const Vector &pos)
{
	if (this->m_invDxCorners == 0.0f || this->m_invDzCorners == 0.0f)
		return m_neY;

	float u = (pos.x - m_nwCorner.x) * m_invDxCorners;
	float v = (pos.z - m_nwCorner.z) * m_invDzCorners;

	// clamp Z values to (x,y) volume

	u = fsel( u, u, 0 );			// u >= 0 ? u : 0
	u = fsel( u - 1.0f, 1.0f, u );	// u >= 1 ? 1 : u

	v = fsel( v, v, 0 );			// v >= 0 ? v : 0
	v = fsel( v - 1.0f, 1.0f, v );	// v >= 1 ? 1 : v

	float northY = m_nwCorner.z + u * (m_neY - m_nwCorner.z);
	float southY = m_swY + u * (m_seCorner.z - m_swY);

	return northY + v * (southY - northY);
}

// Calculates the height of the area at the given x, z coordinates
// @return Height at the given point
float CNavArea::GetY(const Vector &pos) const
{
	return const_cast<CNavArea *>(this)->GetY(pos);
}

// Calculates the distance between the area and the given point
// @return Non-squared distance
float CNavArea::GetDistanceSquaredToPoint(const Vector &pos) const
{
	if (pos.x < m_nwCorner.x)
	{
		if (pos.z < m_nwCorner.z)
		{
			// position is north-west of area
			return (m_nwCorner - pos).LengthSqr();
		}
		else if (pos.z > m_seCorner.z)
		{
			// position is south-west of area
			Vector d;
			d.x = m_nwCorner.x - pos.x;
			d.z = m_seCorner.y - pos.z;
			d.y = m_swY - pos.y;
			return d.LengthSqr();
		}
		else
		{
			// position is west of area
			float d = m_nwCorner.x - pos.x;
			return d * d;
		}
	}
	else if (pos.x > m_seCorner.x)
	{
		if (pos.z < m_nwCorner.z)
		{
			// position is north-east of area
			Vector d;
			d.x = m_seCorner.x - pos.x;
			d.z = m_nwCorner.y - pos.z;
			d.y = m_neY - pos.y;
			return d.LengthSqr();
		}
		else if (pos.z > m_seCorner.z)
		{
			// position is south-east of area
			return (m_seCorner - pos).LengthSqr();
		}
		else
		{
			// position is east of area
			float d = pos.x - m_seCorner.x;
			return d * d;
		}
	}
	else if (pos.z < m_nwCorner.z)
	{
		// position is north of area
		float d = m_nwCorner.z - pos.z;
		return d * d;
	}
	else if (pos.z > m_seCorner.z)
	{
		// position is south of area
		float d = pos.z - m_seCorner.z;
		return d * d;
	}
	else
	{
		// position is inside of 2D extent of area - find delta Z
		float y = this->GetY(pos);
		float d = y - pos.y;
		return d * d;
	}
}

// Check if the given point is overlapping the area
// @return True if 'pos' is within 2D extents of area.
bool CNavArea::IsOverlapping(const Vector &vecPos, float flTolerance) const
{
	if (vecPos.x + flTolerance < this->m_nwCorner.x)
	{
		return false;
	}

	if (vecPos.x - flTolerance > this->m_seCorner.x)
	{
		return false;
	}

	if (vecPos.z + flTolerance < this->m_nwCorner.z)
	{
		return false;
	}

	if (vecPos.z - flTolerance > this->m_seCorner.z)
	{
		return false;
	}

	return true;
}

// Calculates whether or not the given point is inside the area
// @return True if the point is inside the area
bool CNavArea::Contains(const Vector &vecPoint) const
{
	if (!this->IsOverlapping(vecPoint))
	{
		return false;
	}


	if ((this->GetY(vecPoint) - 18.0f) > vecPoint.y)
	{
		return false;
	}

	return true;
}


// Loads the area from a file stream
// @return True on success
bool CNavArea::LoadFromFile(std::ifstream &ifs)
{
	ifs.read((char *) &this->m_id, sizeof(this->m_id));
	ifs.read((char *) &this->m_attributeFlags, sizeof(this->m_attributeFlags));
	ifs.read((char *) &this->m_nwCorner, sizeof(this->m_nwCorner));
	ifs.read((char *) &this->m_seCorner, sizeof(this->m_seCorner));

	this->m_center[0] = (this->m_nwCorner[0] + this->m_seCorner[0]) / 2.0f;
	this->m_center[1] = (this->m_nwCorner[1] + this->m_seCorner[1]) / 2.0f;
	this->m_center[2] = (this->m_nwCorner[2] + this->m_seCorner[2]) / 2.0f;

	if ((m_seCorner.x - m_nwCorner.x) > 0.0f && (m_seCorner.y - m_nwCorner.y) > 0.0f)
	{
		m_invDxCorners = 1.0f / ( m_seCorner.x - m_nwCorner.x );
		m_invDzCorners = 1.0f / ( m_seCorner.z - m_nwCorner.z );
	}
	else
	{
		m_invDxCorners = m_invDzCorners = 0.0f;
	}

	ifs.read((char *) &this->m_neY, sizeof(this->m_neY));
	ifs.read((char *) &this->m_swY, sizeof(this->m_swY));

	for (size_t s{ 0 }; s < NavDirType::NUM_DIRECTIONS; ++s)
	{
		// Number of connections in the current direction
		unsigned int uiCount{ 0 };
		ifs.read((char *) &uiCount, sizeof(uiCount));

		for (unsigned int ui{ 0 }; ui < uiCount; ++ui)
		{
			NavConnect nc{ };

			ifs.read((char *) &nc.id, sizeof(nc.id));

			if (nc.id == this->m_id)
			{
				continue;
			}

			this->m_connect.push_back(nc);
		}
	}

	unsigned char hidingSpotCount{ (unsigned char) 0x00 };
	ifs.read((char *) &hidingSpotCount, sizeof(hidingSpotCount));

	for (unsigned char c{ (unsigned char) 0x00 }; c < hidingSpotCount; ++c)
	{
		HidingSpot hs;

		ifs.read((char *) &hs.m_id, sizeof(hs.m_id));
		ifs.read((char *) &hs.m_pos, sizeof(hs.m_pos));
		ifs.read((char *) &hs.m_flags, sizeof(hs.m_flags));

		this->m_hidingSpots.push_back(hs);
	}

	unsigned int uiEncounterSpotCount{ 0 };
	ifs.read((char *) &uiEncounterSpotCount, sizeof(uiEncounterSpotCount));

	for (unsigned int ui{ 0 }; ui < uiEncounterSpotCount; ++ui)
	{
		SpotEncounter se;

		ifs.read((char *) &se.from.id, sizeof(se.from.id));
		ifs.read((char *) &se.fromDir, sizeof(unsigned char));

		ifs.read((char *) &se.to.id, sizeof(se.to.id));
		ifs.read((char *) &se.toDir, sizeof(unsigned char));

		// Spots along this path
		unsigned char spotCount{ (unsigned char) 0x00 };
		ifs.read((char *) &spotCount, sizeof(spotCount));

		for (unsigned char c{ (unsigned char) 0x00 }; c < spotCount; ++c)
		{
			SpotOrder order{ };

			ifs.read((char *) &order.id, sizeof(order.id));
			ifs.read((char *) &order.t, sizeof(unsigned char));

			se.spots.push_back(order);
		}

		this->m_spotEncounters.push_back(se);
	}
	
	// PlaceDirectory::IndexType entry = fileBuffer.GetUnsignedShort();
	unsigned short entry{ 0 };
	ifs.read((char *) &entry, sizeof(entry));

	for (size_t s{ 0 }; s < CNavLadder::NUM_LADDER_DIRECTIONS; ++s)
	{
		unsigned int uiCount{ 0 };
		ifs.read((char *) &uiCount, sizeof(uiCount));

		for (unsigned int ui{ 0 }; ui < uiCount; ++ui)
		{
			bool bSkip{ false };
			NavLadderConnect connect{ };

			ifs.read((char *) &connect.id, sizeof(connect.id));

			for (const NavLadderConnect &ladder : this->m_ladder[s])
			{
				if (ladder.id == connect.id)
				{
					bSkip = true;
					break;
				}
			}

			if (bSkip)
			{
				continue;
			}

			this->m_ladder[s].push_back(connect);
		}
	}

	for (size_t s{ 0 }; s < MAX_NAV_TEAMS; ++s)
	{
		ifs.read((char *) &this->m_earliestOccupyTime[s], sizeof(this->m_earliestOccupyTime[s]));
	}

	for (size_t s{ 0 }; s < NUM_CORNERS; ++s)
	{
		ifs.read((char *) &this->m_lightIntensity[s], sizeof(this->m_lightIntensity[s]));
	}

	ifs.read((char *) &this->m_uiVisibleAreaCount, sizeof(this->m_uiVisibleAreaCount));

	for (unsigned int ui{ 0 }; ui < this->m_uiVisibleAreaCount; ++ui)
	{
		AreaBindInfo info;

		ifs.read((char *) &info.id, sizeof(info.id));
		ifs.read((char *) &info.attributes, sizeof(info.attributes));

		this->m_potentiallyVisibleAreas.push_back(info);
	}

	ifs.read((char *) &this->m_inheritVisibilityFrom.id, sizeof(this->m_inheritVisibilityFrom.id));

	unsigned char unknownCount{ (unsigned char) 0x00 };
	ifs.read((char *) &unknownCount, sizeof(unknownCount));

	for (unsigned char c{ (unsigned char) 0x00 }; c < unknownCount; ++c)
	{
		unsigned char unknown[0x0E];
		ifs.read((char *) unknown, 0x0E);
	}

	return true;
}
