#pragma once
#include <SFML/Graphics.hpp>
#include "Coord.h"





class Building
{
public:
	///ENUMS
	enum BuildingType
	{
		LIVING_BUILDING, //uses for living
		USABLE_BUILDING, //make materials, do activities etc.
		BRIDGE,
		ROAD,
		ESSENTIALS, //campfires, fences, tables

	};

	enum LivingBuildingType
	{
		HUT,
		SHELTER,
		WOODEN_HOUSE,
		CLAY_HOUSE,
		BRICK_HOUSE,

	};
	///
	//
	Building();
	virtual ~Building();
	//

private:
	//Coord m_position;
	Coord m_leftTop;
	Coord m_rightBot;
	BuildingType m_type;
};

///=////////////////////////////////////////
// LIVING BUILDINGS
///=////////////////////////////////////////

class LivingBuilding : Building
{
public:
	LivingBuilding();
	~LivingBuilding();
	//
	
private:

};
