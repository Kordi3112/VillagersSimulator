#pragma once
#include <SFML/Graphics.hpp>
#include "Coord.h"

enum BuildingType
{
	SIMPLY_HOUSE,
	CHURCH,
	TOWER,



};

class Building
{
public:
	//
	Building();
	~Building();
	//

private:
	//Coord m_position;
	Coord m_leftTop;
	Coord m_rightBot;
	BuildingType m_type;
};

