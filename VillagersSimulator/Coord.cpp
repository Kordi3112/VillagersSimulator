#include "Coord.h"



Coord::Coord()
{
	this->m_main = sf::Vector2f(0,0);
	this->m_subx = 0;
	this->m_suby = 0;
}

Coord::Coord(sf::Vector2f main)
{
	this->m_main = main;
	this->m_subx = 0;
	this->m_suby = 0;
}

Coord::Coord(sf::Vector2f main, int subx, int suby)
{
	this->m_main = main;
	this->m_subx = subx;
	this->m_suby = suby;
}


Coord::~Coord()
{
}

sf::Vector2f Coord::getMain() const
{
	return this->m_main;
}

int Coord::getSubX() const
{
	return this->m_subx;
}

int Coord::getSubY() const
{
	return this->m_suby;
}

void Coord::set()
{
	this->m_main = sf::Vector2f(0,0);
	this->m_subx = 0;
	this->m_suby = 0;
}

void Coord::set(sf::Vector2f main)
{
	this->m_main = main;
	this->m_subx = 0;
	this->m_suby = 0;
}

void Coord::set(sf::Vector2f main, int subx, int suby)
{
	this->m_main = main;
	this->m_subx = subx;
	this->m_suby = suby;
}
