// Jun 5, 2016
// Credits: Valve


#pragma once




class CNavLadder
{
private:

public:

	enum LadderDirectionType
	{
		LADDER_UP = 0,
		LADDER_DOWN,

		NUM_LADDER_DIRECTIONS
	};


	Vector m_top;
	Vector m_bottom;

	float m_length;
	float m_width;




};
