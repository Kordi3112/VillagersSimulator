#pragma once
#include "Coord.h"

class Villager
{
public:

	Villager();
	virtual ~Villager() = 0;
	//

protected:
	Coord m_position; //position on map
	int m_hunger;
	int m_exhaustion;
	int m_thirst; //water

	int m_health;
};

