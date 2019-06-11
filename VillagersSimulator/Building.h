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
	virtual ~Building() = 0;
	//

private:
	//Coord m_position;
	Coord m_leftTop;
	Coord m_rightBot;
	BuildingType m_type;
};

/*
class House : public Building
{
public:
	House();
	~House();
};

class Warehouse : public Building
{
public:
	Warehouse();
	~Warehouse();
};

class Farm : public Building
{
public:
	Farm();
	~Farm();
};

class School : public Building
{
public:
	School();
	~School();
};

class Church : public Building
{
public:
	Church();
	~Church();
};


class Factory : public Building 
{
public:
	Factory();
	~Factory();
};
*/

