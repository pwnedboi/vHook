// Jun 5, 2016
// Credits: Valve


#pragma once

#include "./INav.hpp"
#include "./nav_ladder.hpp"
#include "./nav_hidingspot.hpp"

#include "../main.h"

#include <vector>


enum { MAX_NAV_TEAMS = 2 };


class CNavArea;

struct NavConnect
{
	union
	{
		unsigned int id{ 0 };
		CNavArea *area;
	};

	mutable float length{ 0.0f };

	bool operator==( const NavConnect &other ) const
	{
		return (area == other.area);
	}
};

union NavLadderConnect
{
	unsigned int id{ 0 };
	CNavLadder *ladder;

	bool operator==( const NavLadderConnect &other ) const
	{
		return (ladder == other.ladder) ? true : false;
	}
};

struct SpotOrder
{
	float t{ 0.0f }; // parametric distance along ray where this spot first has LOS to our path

	union
	{
		HidingSpot *spot{ nullptr }; // the spot to look at
		unsigned int id; // spot ID for save/load
	};
};

struct SpotEncounter
{
	NavConnect from{ };
	NavDirType fromDir{ NavDirType::NUM_DIRECTIONS };
	NavConnect to{ };
	NavDirType toDir{ NavDirType::NUM_DIRECTIONS };
	Ray path{ }; // the path segment
	std::vector<SpotOrder> spots; // list of spots to look at, in order of occurrence
};

struct AreaBindInfo	// for pointer loading and binding
{
	union
	{
		CNavArea *area{ nullptr };
		unsigned int id;
	};

	unsigned char attributes;				// VisibilityType

	bool operator==( const AreaBindInfo &other ) const
	{
		return ( area == other.area );
	}
};

class CNavArea
{
// This should be private but this makes things a whole lot easier
public:

	unsigned int m_id{ 0 };

	Vector m_nwCorner{ 0.0f, 0.0f, 0.0f }; // North-west corner
	Vector m_seCorner{ 0.0f, 0.0f, 0.0f }; // South-east corner

	float m_invDxCorners{ 0.0f }; // TODO: What is this?
	float m_invDzCorners{ 0.0f }; // TODO: What is this?

	float m_neY{ 0.0f }; // Height of the north-east corner
	float m_swY{ 0.0f }; // Height of the south-west corner

	Vector m_center{ 0.0f, 0.0f, 0.0f }; // Center

	int m_attributeFlags{ 0 }; // Flags for this area, see NavAttributeType

	std::vector<NavConnect> m_connect; // Connected areas for each direction
	std::vector<NavLadderConnect> m_ladder[CNavLadder::NUM_LADDER_DIRECTIONS]; // Connected ladders

	unsigned int m_visibleAreaCount{ 0 }; // Areas visible from this area

	float m_lightIntensity[NUM_CORNERS]; // 0.0 -> 1.0

	unsigned int m_uiVisibleAreaCount{ 0 };

	AreaBindInfo m_inheritVisibilityFrom;

	std::vector<AreaBindInfo> m_potentiallyVisibleAreas;

	std::vector<HidingSpot> m_hidingSpots;

	std::vector<SpotEncounter> m_spotEncounters;

	float m_earliestOccupyTime[MAX_NAV_TEAMS]; // Minimum time to reach this area from the teams spawn


public:

	// Default constructor
	CNavArea(void);

	// Constructor
	CNavArea(std::ifstream &ifs);

	// Calculates the height of the area at the given x, z coordinates
	// @return Height at the given point
	float GetY(const Vector &pos);

	// Calculates the height of the area at the given x, z coordinates
	// @return Height at the given point
	float GetY(const Vector &pos) const;

	// Calculates the distance between the area and the given point
	// @return Non-squared distance
	float GetDistanceSquaredToPoint(const Vector &pos) const;

	// Check if the given point is overlapping the area
	// @return True if 'pos' is within 2D extents of area.
	bool IsOverlapping(const Vector &pos, float tolerance = 0.0f) const;

	// Calculates whether or not the given point is inside the area
	// @return True if the point is inside the area
	bool Contains(const Vector &vecPoint) const;


	// Loads the area from a file stream
	// @return True on success
	bool LoadFromFile(std::ifstream &ifs);

};
